// lib/pages/6_chat/chat_screen.dart

import 'package:flutter/material.dart';
import 'package:file_picker/file_picker.dart';
import 'package:showcaseview/showcaseview.dart';
import 'package:shared_preferences/shared_preferences.dart';
import 'package:cloud_firestore/cloud_firestore.dart'; // IMPORT FIRESTORE
import '../../services/api_service.dart';
import '../../services/database_service.dart';
import 'widgets/message_bubble.dart';
import 'widgets/chat_input_field.dart';

// --- MODELOS ---
class DocumentFile {
  final String? id; // ID do Firestore
  final String name;
  final String type;

  DocumentFile({this.id, required this.name, required this.type});

  factory DocumentFile.fromFirestore(DocumentSnapshot doc) {
    final data = doc.data() as Map<String, dynamic>;
    return DocumentFile(
      id: doc.id,
      name: data['name'] ?? 'Sem nome',
      type: data['type'] ?? 'pdf',
    );
  }
}

class ChatMessage {
  final String text;
  final bool isSentByMe;
  final bool isLoading;
  final DateTime? timestamp;

  ChatMessage({
    required this.text,
    required this.isSentByMe,
    this.isLoading = false,
    this.timestamp
  });

  factory ChatMessage.fromFirestore(DocumentSnapshot doc) {
    final data = doc.data() as Map<String, dynamic>;
    return ChatMessage(
      text: data['text'] ?? '',
      isSentByMe: data['isSentByMe'] ?? false,
      timestamp: (data['created_at'] as Timestamp?)?.toDate(),
    );
  }
}
// ---------------

class ChatScreen extends StatelessWidget {
  final String chatId;
  final String chatTitle;
  const ChatScreen({super.key, required this.chatId, required this.chatTitle});

  @override
  Widget build(BuildContext context) {
    return Builder(
      key: UniqueKey(),
      builder: (context) => ShowCaseWidget(
        onFinish: () async {
          final prefs = await SharedPreferences.getInstance();
          await prefs.setBool('chatTourDone', true);
        },
        builder: (context) => _ChatScreenContent(chatId: chatId, chatTitle: chatTitle),
      ),
    );
  }
}

class _ChatScreenContent extends StatefulWidget {
  final String chatId;
  final String chatTitle;
  const _ChatScreenContent({required this.chatId, required this.chatTitle});

  @override
  State<_ChatScreenContent> createState() => _ChatScreenContentState();
}

class _ChatScreenContentState extends State<_ChatScreenContent> {
  final GlobalKey _documentsKey = GlobalKey();
  final GlobalKey _inputKey = GlobalKey();
  final GlobalKey _sendKey = GlobalKey();

  final ApiService _apiService = ApiService();
  final DatabaseService _dbService = DatabaseService(); // Mantido como backup

  List<ChatMessage> _messages = [];
  List<DocumentFile> _documents = [];
  bool _isLoadingFiles = true;
  bool _isLoadingHistory = true;

  final TextEditingController _textController = TextEditingController();
  final FocusNode _focusNode = FocusNode();

  @override
  void initState() {
    super.initState();
    _loadAllData();
    _checkAndShowTour();
  }

  Future<void> _loadAllData() async {
    await _loadFiles();
    await _loadMessages();
  }

  // --- CARREGAR ARQUIVOS (Firestore) ---
  Future<void> _loadFiles() async {
    if(mounted) setState(() => _isLoadingFiles = true);
    try {
      final snapshot = await FirebaseFirestore.instance
          .collection('chats')
          .doc(widget.chatId)
          .collection('files')
          .get();

      final files = snapshot.docs.map((doc) => DocumentFile.fromFirestore(doc)).toList();

      if(mounted) {
        setState(() {
          _documents = files;
          _isLoadingFiles = false;
        });
      }
    } catch (e) {
      print("Erro ao carregar arquivos: $e");
      if(mounted) setState(() => _isLoadingFiles = false);
    }
  }

  // --- CARREGAR MENSAGENS (Firestore) ---
  Future<void> _loadMessages() async {
    if(mounted) setState(() => _isLoadingHistory = true);
    try {
      final snapshot = await FirebaseFirestore.instance
          .collection('chats')
          .doc(widget.chatId)
          .collection('messages')
          .orderBy('created_at', descending: true) // Mais recentes primeiro
          .get();

      final history = snapshot.docs.map((doc) => ChatMessage.fromFirestore(doc)).toList();

      if(mounted) {
        setState(() {
          _messages = history;
          if (_messages.isEmpty) {
            _messages.add(ChatMessage(text: 'Olá! Adicione um PDF para começarmos.', isSentByMe: false));
          }
          _isLoadingHistory = false;
        });
      }
    } catch (e) {
      print("Erro ao carregar mensagens: $e");
      if(mounted) setState(() => _isLoadingHistory = false);
    }
  }

  Future<void> _checkAndShowTour() async {
    final prefs = await SharedPreferences.getInstance();
    final bool tourDone = prefs.getBool('chatTourDone') ?? false;
    if (!tourDone && mounted) {
      WidgetsBinding.instance.addPostFrameCallback((_) {
        if(mounted) ShowCaseWidget.of(context).startShowCase([_documentsKey, _inputKey, _sendKey]);
      });
    }
  }

  @override
  void dispose() {
    _focusNode.dispose();
    _textController.dispose();
    super.dispose();
  }

  // --- ENVIAR MENSAGEM ---
  void _handleSubmitted(String text) async {
    if (text.trim().isEmpty) return;
    _textController.clear();
    _focusNode.requestFocus();

    // 1. UI Otimista (Adiciona user msg)
    final userMessage = ChatMessage(text: text, isSentByMe: true, timestamp: DateTime.now());
    setState(() => _messages.insert(0, userMessage)); // Insere no topo (lista reversa)

    // 2. Salva User Msg no Firestore
    await _saveMessageToFirestore(userMessage);

    // 3. UI Loading
    final loadingMsg = ChatMessage(text: "...", isSentByMe: false, isLoading: true);
    setState(() => _messages.insert(0, loadingMsg));

    try {
      // 4. Chama API Python
      final response = await _apiService.sendMessage(widget.chatId, text);

      // 5. Remove loading e adiciona resposta
      setState(() {
        _messages.removeWhere((msg) => msg.isLoading);
        final assistantMessage = ChatMessage(text: response, isSentByMe: false, timestamp: DateTime.now());
        _messages.insert(0, assistantMessage);

        // 6. Salva resposta no Firestore
        _saveMessageToFirestore(assistantMessage);
      });

    } catch (e) {
      setState(() {
        _messages.removeWhere((msg) => msg.isLoading);
        final errorMsg = ChatMessage(text: "Erro: $e", isSentByMe: false);
        _messages.insert(0, errorMsg);
      });
    }
  }

  Future<void> _saveMessageToFirestore(ChatMessage msg) async {
    try {
      await FirebaseFirestore.instance
          .collection('chats')
          .doc(widget.chatId)
          .collection('messages')
          .add({
        'text': msg.text,
        'isSentByMe': msg.isSentByMe,
        'created_at': FieldValue.serverTimestamp(),
      });
    } catch (e) {
      print("Erro ao salvar msg: $e");
    }
  }

  // --- REMOVER ARQUIVO ---
  Future<void> _removeDocument(DocumentFile document, StateSetter setModalState) async {
    if (document.id == null) return;
    try {
      // Deleta da API
      await _apiService.deleteFile(widget.chatId, document.name);

      // Deleta do Firestore
      await FirebaseFirestore.instance
          .collection('chats')
          .doc(widget.chatId)
          .collection('files')
          .doc(document.id)
          .delete();

      // Atualiza UI
      if(mounted) {
        setModalState(() => _documents.removeWhere((doc) => doc.id == document.id));
        setState(() => _documents.removeWhere((doc) => doc.id == document.id));
      }
    } catch (e) {
      if(mounted) ScaffoldMessenger.of(context).showSnackBar(SnackBar(content: Text('Erro ao deletar: $e')));
    }
  }

  // --- UPLOAD DE ARQUIVO ---
  Future<void> _pickAndUploadFile() async {
    // Fecha o modal antes de abrir o picker para evitar travamentos de UI
    if (Navigator.canPop(context)) Navigator.pop(context);

    try {
      final result = await FilePicker.platform.pickFiles(
        type: FileType.custom,
        allowedExtensions: ['pdf'],
        withData: true, // Necessário para enviar bytes
      );

      if (result == null) return;

      final file = result.files.single;
      // Validação extra
      if (file.bytes == null) {
        ScaffoldMessenger.of(context).showSnackBar(const SnackBar(content: Text('Erro: Arquivo vazio ou inacessível.')));
        return;
      }

      ScaffoldMessenger.of(context).showSnackBar(SnackBar(content: Text('Enviando ${file.name}...')));

      // 1. Envia para API Python
      await _apiService.uploadFile(widget.chatId, file);

      // 2. Salva metadados no Firestore
      await FirebaseFirestore.instance
          .collection('chats')
          .doc(widget.chatId)
          .collection('files')
          .add({
        'name': file.name,
        'type': file.extension ?? 'pdf',
        'created_at': FieldValue.serverTimestamp(),
      });

      ScaffoldMessenger.of(context).hideCurrentSnackBar();
      ScaffoldMessenger.of(context).showSnackBar(const SnackBar(content: Text('Arquivo processado com sucesso!')));

      // 3. Recarrega lista
      _loadFiles();

    } catch (e) {
      print("Erro no upload: $e");
      ScaffoldMessenger.of(context).hideCurrentSnackBar();
      ScaffoldMessenger.of(context).showSnackBar(SnackBar(content: Text('Falha no upload: Verifique se a API está rodando.\nErro: $e'), backgroundColor: Colors.red));
    }
  }

  void _showDocumentsBottomSheet(BuildContext context) {
    showModalBottomSheet(
      context: context,
      isScrollControlled: true,
      shape: const RoundedRectangleBorder(borderRadius: BorderRadius.vertical(top: Radius.circular(20))),
      builder: (ctx) {
        return StatefulBuilder(builder: (BuildContext context, StateSetter setModalState) {
          return DraggableScrollableSheet(
            expand: false,
            initialChildSize: 0.5,
            maxChildSize: 0.9,
            builder: (_, scrollController) {
              return Container(
                padding: const EdgeInsets.all(24.0),
                child: Column(
                  crossAxisAlignment: CrossAxisAlignment.start,
                  children: [
                    Text('Documentos Carregados', style: Theme.of(context).textTheme.titleLarge),
                    const SizedBox(height: 16),
                    _isLoadingFiles
                        ? const Expanded(child: Center(child: CircularProgressIndicator()))
                        : _documents.isEmpty
                        ? const Expanded(child: Center(child: Text("Nenhum documento carregado.")))
                        : Expanded(
                      child: ListView.builder(
                        controller: scrollController,
                        itemCount: _documents.length,
                        itemBuilder: (context, index) {
                          final doc = _documents[index];
                          return Card(
                            margin: const EdgeInsets.symmetric(vertical: 4.0),
                            child: ListTile(
                              leading: const Icon(Icons.description_outlined),
                              title: Text(doc.name, overflow: TextOverflow.ellipsis),
                              trailing: IconButton(
                                icon: const Icon(Icons.delete_outline, color: Colors.red),
                                onPressed: () => _removeDocument(doc, setModalState),
                              ),
                            ),
                          );
                        },
                      ),
                    ),
                    const SizedBox(height: 16),
                    SizedBox(
                      width: double.infinity,
                      child: ElevatedButton.icon(
                        onPressed: _pickAndUploadFile,
                        icon: const Icon(Icons.add),
                        label: const Text('Adicionar Documento'),
                      ),
                    )
                  ],
                ),
              );
            },
          );
        });
      },
    );
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text(widget.chatTitle),
        actions: [
          Showcase(
            key: _documentsKey,
            description: 'Gerenciar documentos',
            child: IconButton(
              icon: const Icon(Icons.folder_open_outlined),
              onPressed: () => _showDocumentsBottomSheet(context),
            ),
          ),
        ],
      ),
      body: Column(
        children: [
          Expanded(
            child: _isLoadingHistory
                ? const Center(child: CircularProgressIndicator())
                : ListView.builder(
              reverse: true, // Mensagens mais novas embaixo (na lógica visual)
              padding: const EdgeInsets.all(16.0),
              itemCount: _messages.length,
              itemBuilder: (context, index) {
                return MessageBubble(message: _messages[index]);
              },
            ),
          ),
          ChatInputField(
            controller: _textController,
            focusNode: _focusNode,
            onSubmitted: _handleSubmitted,
            textFieldKey: _inputKey,
            sendButtonKey: _sendKey,
          ),
        ],
      ),
    );
  }
}