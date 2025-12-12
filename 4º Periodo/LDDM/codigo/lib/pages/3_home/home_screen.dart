// lib/pages/3_home/home_screen.dart

import 'dart:async';
import 'package:flutter/material.dart';
import 'package:flutter_svg/flutter_svg.dart';
import 'package:intl/intl.dart';
import 'package:shared_preferences/shared_preferences.dart';
import '../../shared/theme/app_colors.dart';
import '../1_login/login_screen.dart';
import '../6_chat/chat_screen.dart';
import '../8_todo_list/todo_list_screen.dart';
import '../10_desempenho/desempenho_screen.dart';
import '../4_calendar/calendar_screen.dart';
import '../../main.dart';
import '../../services/database_service.dart';
import '../../services/settings_service.dart';

// --- IMPORT DO FIREBASE ---
import 'package:cloud_firestore/cloud_firestore.dart';
// --------------------------

// --- MODELO ChatSession ---
class ChatSession {
  final String id; // ID local (mantido para referência)
  String title;
  String subject;
  String? firestoreId; // ID REAL do documento no Firebase

  ChatSession({
    required this.id,
    required this.title,
    required this.subject,
    this.firestoreId,
  });

  Map<String, dynamic> toMap() {
    return {
      'id': id,
      'title': title,
      'subject': subject,
      'firestoreId': firestoreId,
    };
  }

  factory ChatSession.fromMap(Map<String, dynamic> map) {
    return ChatSession(
      id: map['id'].toString(),
      title: map['title'],
      subject: map['subject'],
      firestoreId: map['firestoreId'],
    );
  }

  // Factory para criar a partir do Firestore
  factory ChatSession.fromFirestore(DocumentSnapshot doc) {
    final data = doc.data() as Map<String, dynamic>;
    return ChatSession(
      id: data['local_id']?.toString() ?? doc.id,
      title: data['title'] ?? 'Sem título',
      subject: data['subject'] ?? 'Geral',
      firestoreId: doc.id, // <--- IMPORTANTE: Pega o ID do documento
    );
  }
}
// -------------------------------------

class HomePage extends StatefulWidget {
  final int userId;
  const HomePage({super.key, required this.userId});

  @override
  State<HomePage> createState() => _HomePageState();
}

class _HomePageState extends State<HomePage> {
  final dbService = DatabaseService();
  final settingsService = SettingsService();

  List<ChatSession> _userChats = [];
  final List<String> _subjects = ['Biologia', 'História', 'Cálculo', 'Programação', 'Outras'];
  bool _isLoading = true;

  bool _notificationsEnabled = true;
  late bool _darkModeEnabled;

  @override
  void initState() {
    super.initState();
    _loadInitialData();
  }

  // --- CARREGAR DADOS (Firebase + Fallback) ---
  Future<void> _loadInitialData() async {
    final notifications = await settingsService.getNotifications();
    final themeMode = await settingsService.getThemeMode();

    List<ChatSession> chats = [];
    try {
      // 1. Busca do Firestore
      final snapshot = await FirebaseFirestore.instance
          .collection('chats')
          .where('id_usuario', isEqualTo: widget.userId)
          .get();

      chats = snapshot.docs
          .map((doc) => ChatSession.fromFirestore(doc))
          .toList();

    } catch (e) {
      print("Erro ao carregar chats do Firebase: $e");
      // 2. Fallback Local
      try {
        chats = await dbService.getChats(widget.userId);
      } catch (localError) {
        print("Erro crítico ao carregar chats: $localError");
      }
    }

    if (mounted) {
      setState(() {
        _notificationsEnabled = notifications;
        _darkModeEnabled = themeMode == ThemeMode.dark;
        _userChats = chats;
        _isLoading = false;
      });
    }
  }

  Future<void> _refreshChats() async {
    await _loadInitialData();
  }

  // --- ADICIONAR CHAT (ATUALIZADO) ---
  Future<void> _showAddChatDialog() async {
    final formKey = GlobalKey<FormState>();
    final titleController = TextEditingController();
    final customSubjectController = TextEditingController(); // Controlador para matéria customizada

    // Define o valor inicial do dropdown (pode ser null ou o primeiro da lista)
    String? selectedSubject;

    await showDialog(
      context: context,
      builder: (context) {
        // StatefulBuilder é necessário para atualizar o layout DENTRO do diálogo
        return StatefulBuilder(
          builder: (context, setStateModal) {
            return AlertDialog(
              title: const Text('Criar Novo Chat'),
              content: Form(
                key: formKey,
                child: Column(
                  mainAxisSize: MainAxisSize.min,
                  children: [
                    TextFormField(
                      controller: titleController,
                      decoration: const InputDecoration(labelText: 'Título'),
                      autofocus: true,
                      textCapitalization: TextCapitalization.sentences,
                      validator: (v) => (v == null || v.trim().isEmpty) ? 'Insira um título' : null,
                    ),
                    const SizedBox(height: 16),
                    DropdownButtonFormField<String>(
                      decoration: const InputDecoration(labelText: 'Matéria'),
                      value: selectedSubject,
                      items: _subjects.map((s) => DropdownMenuItem(value: s, child: Text(s))).toList(),
                      onChanged: (v) {
                        // Atualiza o estado do modal para mostrar/esconder o campo extra
                        setStateModal(() {
                          selectedSubject = v;
                        });
                      },
                      validator: (v) => v == null ? 'Selecione uma matéria' : null,
                    ),
                    // Se selecionou "Outras", mostra o campo para digitar
                    if (selectedSubject == 'Outras') ...[
                      const SizedBox(height: 16),
                      TextFormField(
                        controller: customSubjectController,
                        decoration: const InputDecoration(
                          labelText: 'Nome da Nova Matéria',
                          hintText: 'Ex: Filosofia',
                        ),
                        textCapitalization: TextCapitalization.sentences,
                        validator: (v) {
                          if (selectedSubject == 'Outras' && (v == null || v.trim().isEmpty)) {
                            return 'Digite o nome da matéria';
                          }
                          return null;
                        },
                      ),
                    ],
                  ],
                ),
              ),
              actions: [
                TextButton(onPressed: () => Navigator.pop(context), child: const Text('Cancelar')),
                ElevatedButton(
                  onPressed: () async {
                    if (formKey.currentState!.validate()) {
                      try {
                        // Define a matéria final: se for "Outras", pega do texto, senão pega do dropdown
                        final finalSubject = (selectedSubject == 'Outras')
                            ? customSubjectController.text.trim()
                            : selectedSubject;

                        final localId = DateTime.now().millisecondsSinceEpoch.toString();

                        // 1. Salva no Firestore
                        await FirebaseFirestore.instance.collection('chats').add({
                          'id_usuario': widget.userId,
                          'title': titleController.text.trim(),
                          'subject': finalSubject,
                          'local_id': localId,
                          'created_at': FieldValue.serverTimestamp(),
                        });

                        // 2. Salva Local (Backup)
                        final newChat = ChatSession(
                          id: localId,
                          title: titleController.text.trim(),
                          subject: finalSubject!,
                        );
                        try { await dbService.createChat(newChat, widget.userId); } catch (_) {}

                        _refreshChats();
                        if (mounted) {
                          Navigator.pop(context);
                          ScaffoldMessenger.of(context).showSnackBar(const SnackBar(content: Text('Chat criado!')));
                        }
                      } catch (e) {
                        print("Erro ao criar: $e");
                        if (mounted) ScaffoldMessenger.of(context).showSnackBar(const SnackBar(content: Text('Erro ao criar chat')));
                      }
                    }
                  },
                  child: const Text('Criar'),
                ),
              ],
            );
          },
        );
      },
    );
  }

  // --- EDITAR CHAT (ATUALIZADO) ---
  Future<void> _showEditChatDialog(int index) async {
    final chatToEdit = _userChats[index];
    final formKey = GlobalKey<FormState>();
    final titleController = TextEditingController(text: chatToEdit.title);

    // Verifica se a matéria atual está na lista padrão
    bool isStandardSubject = _subjects.contains(chatToEdit.subject);

    // Se não estiver na lista (é customizada), seleciona 'Outras' e preenche o controller
    String? selectedSubject = isStandardSubject ? chatToEdit.subject : 'Outras';
    final customSubjectController = TextEditingController(
        text: isStandardSubject ? '' : chatToEdit.subject
    );

    await showDialog(
      context: context,
      builder: (context) {
        return StatefulBuilder(
          builder: (context, setStateModal) {
            return AlertDialog(
              title: const Text('Editar Chat'),
              content: Form(
                key: formKey,
                child: Column(
                  mainAxisSize: MainAxisSize.min,
                  children: [
                    TextFormField(
                      controller: titleController,
                      decoration: const InputDecoration(labelText: 'Título'),
                      textCapitalization: TextCapitalization.sentences,
                      validator: (v) => (v == null || v.trim().isEmpty) ? 'Insira um título' : null,
                    ),
                    const SizedBox(height: 16),
                    DropdownButtonFormField<String>(
                      value: selectedSubject,
                      decoration: const InputDecoration(labelText: 'Matéria'),
                      items: _subjects.map((s) => DropdownMenuItem(value: s, child: Text(s))).toList(),
                      onChanged: (v) {
                        setStateModal(() {
                          selectedSubject = v;
                          // Limpa o texto customizado se o usuário voltar para uma matéria padrão
                          if (v != 'Outras') {
                            customSubjectController.clear();
                          }
                        });
                      },
                      validator: (v) => v == null ? 'Selecione uma matéria' : null,
                    ),

                    // Lógica para mostrar o campo se for "Outras"
                    if (selectedSubject == 'Outras') ...[
                      const SizedBox(height: 16),
                      TextFormField(
                        controller: customSubjectController,
                        decoration: const InputDecoration(
                          labelText: 'Nome da Matéria',
                          hintText: 'Ex: Fisiologia',
                        ),
                        textCapitalization: TextCapitalization.sentences,
                        validator: (v) {
                          if (selectedSubject == 'Outras' && (v == null || v.trim().isEmpty)) {
                            return 'Digite o nome da matéria';
                          }
                          return null;
                        },
                      ),
                    ],
                  ],
                ),
              ),
              actions: [
                TextButton(onPressed: () => Navigator.pop(context), child: const Text('Cancelar')),
                ElevatedButton(
                  onPressed: () async {
                    if (formKey.currentState!.validate()) {
                      try {
                        // Define matéria final
                        final finalSubject = (selectedSubject == 'Outras')
                            ? customSubjectController.text.trim()
                            : selectedSubject;

                        if (chatToEdit.firestoreId != null) {
                          await FirebaseFirestore.instance
                              .collection('chats')
                              .doc(chatToEdit.firestoreId)
                              .update({
                            'title': titleController.text.trim(),
                            'subject': finalSubject,
                          });
                        }

                        final updatedChat = ChatSession(
                          id: chatToEdit.id,
                          title: titleController.text.trim(),
                          subject: finalSubject!,
                        );
                        try { await dbService.updateChat(updatedChat, widget.userId); } catch (_) {}

                        _refreshChats();
                        if (mounted) {
                          Navigator.pop(context);
                          ScaffoldMessenger.of(context).showSnackBar(const SnackBar(content: Text('Chat atualizado!')));
                        }
                      } catch (e) {
                        print("Erro ao editar: $e");
                      }
                    }
                  },
                  child: const Text('Salvar'),
                ),
              ],
            );
          },
        );
      },
    );
  }

  // --- EXCLUIR CHAT ---
  Future<void> _deleteChat(int index) async {
    final chatToDelete = _userChats[index];
    final bool? confirm = await showDialog(
      context: context,
      builder: (context) => AlertDialog(
        title: const Text('Excluir Chat'),
        content: Text('Tem certeza que deseja excluir o chat "${chatToDelete.title}"?'),
        actions: [
          TextButton(onPressed: () => Navigator.pop(context, false), child: const Text('Cancelar')),
          ElevatedButton(
            onPressed: () => Navigator.pop(context, true),
            style: ElevatedButton.styleFrom(backgroundColor: AppColors.red),
            child: const Text('Excluir'),
          ),
        ],
      ),
    );

    if (confirm == true) {
      try {
        if (chatToDelete.firestoreId != null) {
          await FirebaseFirestore.instance.collection('chats').doc(chatToDelete.firestoreId).delete();
        }
        try { await dbService.deleteChat(chatToDelete.id, widget.userId); } catch (_) {}

        _refreshChats();
        if(mounted) {
          ScaffoldMessenger.of(context).showSnackBar(
            SnackBar(content: Text('Chat "${chatToDelete.title}" excluído.')),
          );
        }
      } catch (e) {
        print("Erro ao excluir: $e");
      }
    }
  }

  Future<void> _resetTours() async {
    final prefs = await SharedPreferences.getInstance();
    await prefs.remove('chatTourDone');
    await prefs.remove('todoTourDone');
    if (mounted) Navigator.pop(context);
    ScaffoldMessenger.of(context).showSnackBar(
      const SnackBar(content: Text('Tours resetados.')),
    );
  }

  void _showSettingsBottomSheet() {
    showModalBottomSheet(
      context: context,
      shape: const RoundedRectangleBorder(
        borderRadius: BorderRadius.vertical(top: Radius.circular(20)),
      ),
      builder: (context) {
        return StatefulBuilder(
          builder: (BuildContext context, StateSetter setModalState) {
            return Container(
              padding: const EdgeInsets.all(24),
              child: Column(
                mainAxisSize: MainAxisSize.min,
                crossAxisAlignment: CrossAxisAlignment.start,
                children: [
                  Text('Configurações', style: Theme.of(context).textTheme.titleLarge),
                  const SizedBox(height: 24),
                  SwitchListTile(
                    title: const Text('Ativar Notificações'),
                    value: _notificationsEnabled,
                    onChanged: (bool value) async {
                      await settingsService.saveNotifications(value);
                      setModalState(() => _notificationsEnabled = value);
                      setState(() => _notificationsEnabled = value);
                    },
                    secondary: const Icon(Icons.notifications_outlined),
                  ),
                  SwitchListTile(
                    title: const Text('Modo Escuro'),
                    value: _darkModeEnabled,
                    onChanged: (bool value) async {
                      final newTheme = value ? ThemeMode.dark : ThemeMode.light;
                      await settingsService.saveThemeMode(newTheme);
                      themeNotifier.value = newTheme;
                      setModalState(() => _darkModeEnabled = value);
                      setState(() => _darkModeEnabled = value);
                    },
                    secondary: const Icon(Icons.dark_mode_outlined),
                  ),
                  const Divider(height: 32),
                  ListTile(
                    leading: const Icon(Icons.replay_circle_filled_outlined),
                    title: const Text('Resetar Tours (para teste)'),
                    onTap: _resetTours,
                  ),
                  ListTile(
                    leading: Icon(Icons.logout, color: Theme.of(context).colorScheme.error),
                    title: Text(
                      'Sair da Conta',
                      style: TextStyle(color: Theme.of(context).colorScheme.error),
                    ),
                    onTap: () async {
                      final navigator = Navigator.of(context);
                      navigator.pop();
                      final bool? confirmLogout = await showDialog<bool>(
                        context: context,
                        builder: (BuildContext dialogContext) {
                          return AlertDialog(
                            title: const Text('Sair da Conta'),
                            content: const Text('Tem certeza que deseja sair?'),
                            actions: <Widget>[
                              TextButton(
                                child: const Text('Cancelar'),
                                onPressed: () => navigator.pop(false),
                              ),
                              TextButton(
                                style: TextButton.styleFrom(
                                  foregroundColor: Theme.of(dialogContext).colorScheme.error,
                                ),
                                child: const Text('Sair'),
                                onPressed: () => navigator.pop(true),
                              ),
                            ],
                          );
                        },
                      );
                      if (confirmLogout == true && mounted) {
                        navigator.pushAndRemoveUntil(
                          MaterialPageRoute(builder: (context) => const LoginScreen()),
                              (Route<dynamic> route) => false,
                        );
                      }
                    },
                  ),
                  const SizedBox(height: 16),
                  Center(child: TextButton(onPressed: () => Navigator.pop(context), child: const Text('Fechar'))),
                ],
              ),
            );
          },
        );
      },
    );
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: _isLoading
          ? const Center(child: CircularProgressIndicator())
          : SingleChildScrollView(
        padding: const EdgeInsets.all(16),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            // --- CARROSSEL DE DASHBOARD ---
            DashboardCarousel(userId: widget.userId),
            // ------------------------------

            const SizedBox(height: 20),
            Row(
              mainAxisAlignment: MainAxisAlignment.spaceAround,
              children: [
                ShortcutIcon(label: "Configurações", icon: Icons.settings, iconColor: AppColors.purplePrimary, onTap: _showSettingsBottomSheet),
                ShortcutIcon(
                    label: "Estatísticas",
                    icon: Icons.bar_chart,
                    iconColor: AppColors.green,
                    onTap: () => Navigator.push(context, MaterialPageRoute(
                        builder: (context) => DesempenhoScreen(userId: widget.userId)
                    ))
                ),
                ShortcutIcon(
                    label: "Lista de Tarefas",
                    icon: Icons.check_box,
                    iconColor: AppColors.orangeLight,
                    onTap: () => Navigator.push(context, MaterialPageRoute(
                        builder: (context) => TodoListScreen(userId: widget.userId)
                    ))
                ),
              ],
            ),
            const SizedBox(height: 20),
            Text("Meus Chats", style: Theme.of(context).textTheme.titleLarge),
            const SizedBox(height: 10),
            _userChats.isEmpty
                ? const Padding(
              padding: EdgeInsets.symmetric(vertical: 32.0),
              child: Center(child: Text("Nenhum chat criado ainda.")),
            )
                : ListView.builder(
              shrinkWrap: true,
              physics: const NeverScrollableScrollPhysics(),
              itemCount: _userChats.length,
              itemBuilder: (context, index) {
                final chat = _userChats[index];
                return Card(
                  margin: const EdgeInsets.only(bottom: 10),
                  child: ListTile(
                    leading: const Icon(Icons.chat_bubble_outline, color: AppColors.purplePrimary),
                    title: Text(chat.title, style: const TextStyle(fontWeight: FontWeight.bold)),
                    subtitle: Text(chat.subject),
                    onTap: () {
                      // --- CORREÇÃO CRÍTICA AQUI ---
                      // Envia o ID do Firestore se existir, senão o ID local.
                      // Isso garante que o ChatScreen salve no documento correto.
                      final correctId = chat.firestoreId ?? chat.id;

                      Navigator.push(
                        context,
                        MaterialPageRoute(
                          builder: (context) => ChatScreen(
                            chatId: correctId,
                            chatTitle: chat.title,
                          ),
                        ),
                      );
                    },
                    trailing: Row(
                      mainAxisSize: MainAxisSize.min,
                      children: [
                        IconButton(
                          icon: const Icon(Icons.edit_outlined),
                          color: Theme.of(context).colorScheme.onSurface.withOpacity(0.6),
                          onPressed: () => _showEditChatDialog(index),
                          tooltip: 'Editar Chat',
                        ),
                        IconButton(
                          icon: const Icon(Icons.delete_outline),
                          color: AppColors.red,
                          onPressed: () => _deleteChat(index),
                          tooltip: 'Excluir Chat',
                        ),
                      ],
                    ),
                  ),
                );
              },
            ),
          ],
        ),
      ),
      floatingActionButtonLocation: FloatingActionButtonLocation.centerFloat,
      floatingActionButton: SizedBox(
        width: 64,
        height: 64,
        child: FloatingActionButton(
          onPressed: _showAddChatDialog,
          tooltip: 'Criar Novo Chat',
          backgroundColor: AppColors.purplePrimary,
          child: const Icon(Icons.add, color: Colors.white, size: 32),
        ),
      ),
    );
  }
}

// Atalhos e Dashboard (Widget)
class ShortcutIcon extends StatelessWidget {
  final String label;
  final IconData icon;
  final VoidCallback onTap;
  final Color iconColor;

  const ShortcutIcon({super.key, required this.label, required this.icon, required this.onTap, required this.iconColor});

  @override
  Widget build(BuildContext context) {
    const double radius = 30;
    return Column(
      children: [
        Material(
          color: iconColor.withOpacity(0.1),
          borderRadius: BorderRadius.circular(radius),
          child: InkWell(
            borderRadius: BorderRadius.circular(radius),
            onTap: onTap,
            child: SizedBox(
              width: radius * 2,
              height: radius * 2,
              child: Center(
                child: Icon(icon, color: iconColor, size: 28),
              ),
            ),
          ),
        ),
        const SizedBox(height: 8),
        Text(label, style: const TextStyle(fontSize: 12)),
      ],
    );
  }
}

// ============================================================================
// WIDGET DO CARROSSEL (DASHBOARD)
// ============================================================================
class DashboardCarousel extends StatefulWidget {
  final int userId;
  const DashboardCarousel({super.key, required this.userId});

  @override
  State<DashboardCarousel> createState() => _DashboardCarouselState();
}

class _DashboardCarouselState extends State<DashboardCarousel> {
  final PageController _pageController = PageController();
  int _currentPage = 0;
  Timer? _timer;

  // Streams para ouvir o banco em tempo real
  late Stream<QuerySnapshot> _calendarStream;
  late Stream<QuerySnapshot> _tasksStream;
  late Stream<QuerySnapshot> _pomodoroStream;

  @override
  void initState() {
    super.initState();
    _initStreams();

    // Timer do carrossel automático
    _timer = Timer.periodic(const Duration(seconds: 5), (Timer timer) {
      if (_currentPage < 2) {
        _currentPage++;
      } else {
        _currentPage = 0;
      }
      if (_pageController.hasClients) {
        _pageController.animateToPage(
          _currentPage,
          duration: const Duration(milliseconds: 350),
          curve: Curves.easeIn,
        );
      }
    });
  }

  void _initStreams() {
    // 1. Stream de Eventos (apenas futuros ou de hoje)
    // Nota: O filtro de data idealmente é feito no backend, mas aqui faremos na memória
    // para simplificar, já que o Firestore tem limitações de query complexa sem índices.
    _calendarStream = FirebaseFirestore.instance
        .collection('calendar_events')
        .where('id_usuario', isEqualTo: widget.userId)
        .snapshots();

    // 2. Stream de Tarefas Pendentes
    _tasksStream = FirebaseFirestore.instance
        .collection('tasks')
        .where('id_usuario', isEqualTo: widget.userId)
        .where('isDone', isEqualTo: false)
        .snapshots();

    // 3. Stream de Pomodoro (para somar tempo)
    _pomodoroStream = FirebaseFirestore.instance
        .collection('pomodoro_sessions')
        .where('id_usuario', isEqualTo: widget.userId)
        .snapshots();
  }

  @override
  void dispose() {
    _timer?.cancel();
    _pageController.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return Container(
      height: 170,
      decoration: BoxDecoration(
        color: AppColors.purplePrimary,
        borderRadius: BorderRadius.circular(16),
        boxShadow: [
          BoxShadow(
            color: AppColors.purplePrimary.withOpacity(0.3),
            blurRadius: 10,
            offset: const Offset(0, 4),
          ),
        ],
      ),
      child: Stack(
        children: [
          // Usamos StreamBuilder para reconstruir a UI quando os dados mudam
          StreamBuilder<QuerySnapshot>(
            stream: _pomodoroStream,
            builder: (context, snapshotPomo) {
              return StreamBuilder<QuerySnapshot>(
                stream: _calendarStream,
                builder: (context, snapshotCal) {
                  return StreamBuilder<QuerySnapshot>(
                    stream: _tasksStream,
                    builder: (context, snapshotTasks) {

                      // Se algum ainda estiver carregando a primeira vez
                      if (!snapshotPomo.hasData || !snapshotCal.hasData || !snapshotTasks.hasData) {
                        return const Center(child: CircularProgressIndicator(color: Colors.white));
                      }

                      // --- PROCESSAMENTO DOS DADOS ---

                      // 1. Calculando Tempo Total
                      int totalMins = 0;
                      for (var doc in snapshotPomo.data!.docs) {
                        final data = doc.data() as Map<String, dynamic>;
                        totalMins += (data['durationMinutes'] as int? ?? 0);
                      }

                      // 2. Processando Próximo Evento
                      final events = snapshotCal.data!.docs
                          .map((doc) => CalendarEvent.fromFirestore(doc))
                          .toList();
                      final now = DateTime.now();

                      // Filtra apenas eventos futuros ou de hoje
                      final futureEvents = events.where((e) {
                        final eventDate = DateUtils.dateOnly(e.when);
                        final today = DateUtils.dateOnly(now);
                        return eventDate.isAtSameMomentAs(today) || eventDate.isAfter(today);
                      }).toList();

                      futureEvents.sort((a, b) => a.when.compareTo(b.when));
                      final nextEvent = futureEvents.isNotEmpty ? futureEvents.first : null;

                      // 3. Contando Tarefas
                      final pendingCount = snapshotTasks.data!.docs.length;

                      // --- RENDERIZAÇÃO ---
                      return PageView(
                        controller: _pageController,
                        onPageChanged: (int page) {
                          setState(() {
                            _currentPage = page;
                          });
                        },
                        children: [
                          _buildPerformanceSlide(totalMins),
                          _buildCalendarSlide(nextEvent),
                          _buildTodoSlide(pendingCount),
                        ],
                      );
                    },
                  );
                },
              );
            },
          ),

          // Indicador de Páginas (Bolinhas)
          Positioned(
            bottom: 12,
            left: 0,
            right: 0,
            child: Row(
              mainAxisAlignment: MainAxisAlignment.center,
              children: List.generate(3, (index) {
                return AnimatedContainer(
                  duration: const Duration(milliseconds: 300),
                  margin: const EdgeInsets.symmetric(horizontal: 4),
                  width: _currentPage == index ? 24 : 8,
                  height: 8,
                  decoration: BoxDecoration(
                    color: _currentPage == index
                        ? Colors.white
                        : Colors.white.withOpacity(0.4),
                    borderRadius: BorderRadius.circular(4),
                  ),
                );
              }),
            ),
          ),
        ],
      ),
    );
  }

  // Métodos de construção atualizados para receber dados via parâmetro
  Widget _buildPerformanceSlide(int totalMinutes) {
    final hours = totalMinutes ~/ 60;
    final minutes = totalMinutes % 60;
    final timeStr = hours > 0 ? "${hours}h ${minutes}min" : "${minutes}min";

    return Padding(
      padding: const EdgeInsets.symmetric(horizontal: 16.0, vertical: 12.0),
      child: Column(
        mainAxisAlignment: MainAxisAlignment.center,
        children: [
          const Icon(Icons.timer_outlined, color: Colors.white, size: 28),
          const SizedBox(height: 6),
          const Text("Tempo Total de Estudo", style: TextStyle(color: Colors.white70, fontSize: 13)),
          const SizedBox(height: 2),
          Text(timeStr, style: const TextStyle(color: Colors.white, fontSize: 26, fontWeight: FontWeight.bold)),
        ],
      ),
    );
  }

  Widget _buildCalendarSlide(CalendarEvent? nextEvent) {
    String titleText = "Nenhum evento próximo";
    String dateText = "Toque em + para adicionar";

    if (nextEvent != null) {
      titleText = nextEvent.title;
      final fmt = DateFormat("dd/MM - HH:mm", 'pt_BR');
      dateText = fmt.format(nextEvent.when);
    }

    return Padding(
      padding: const EdgeInsets.symmetric(horizontal: 16.0, vertical: 12.0),
      child: Column(
        mainAxisAlignment: MainAxisAlignment.center,
        children: [
          const Icon(Icons.calendar_month_outlined, color: Colors.white, size: 28),
          const SizedBox(height: 6),
          const Text("Próximo Evento", style: TextStyle(color: Colors.white70, fontSize: 13)),
          const SizedBox(height: 2),
          Text(titleText, style: const TextStyle(color: Colors.white, fontSize: 18, fontWeight: FontWeight.bold), textAlign: TextAlign.center, maxLines: 1, overflow: TextOverflow.ellipsis),
          Text(dateText, style: const TextStyle(color: Colors.white, fontSize: 14)),
        ],
      ),
    );
  }

  Widget _buildTodoSlide(int pendingCount) {
    return Padding(
      padding: const EdgeInsets.symmetric(horizontal: 16.0, vertical: 12.0),
      child: Column(
        mainAxisAlignment: MainAxisAlignment.center,
        children: [
          const Icon(Icons.check_circle_outline, color: Colors.white, size: 28),
          const SizedBox(height: 6),
          const Text("Lista de Tarefas", style: TextStyle(color: Colors.white70, fontSize: 13)),
          const SizedBox(height: 2),
          Text("$pendingCount Pendentes", style: const TextStyle(color: Colors.white, fontSize: 26, fontWeight: FontWeight.bold)),
          const Text("Mantenha o foco!", style: TextStyle(color: Colors.white70, fontSize: 12)),
        ],
      ),
    );
  }
}