// lib/pages/5_pomodoro/pomodoro_screen.dart

import 'dart:async';
import 'package:flutter/material.dart';
import 'package:codigo/shared/theme/app_colors.dart';
import '../../services/database_service.dart';
import '../3_home/home_screen.dart';

// --- IMPORT FIREBASE ---
import 'package:cloud_firestore/cloud_firestore.dart';
// -----------------------

enum TimerMode { pomodoro, shortBreak }

class PomodoroManager extends ChangeNotifier {
  static final PomodoroManager _instance = PomodoroManager._internal();
  factory PomodoroManager() => _instance;
  PomodoroManager._internal();

  Timer? _ticker;
  DateTime? _endTime;
  int? _pausedRemainingSeconds;
  bool _isRunning = false;
  TimerMode _mode = TimerMode.pomodoro;

  int pomodoroDuration = 25;
  int shortBreakDuration = 5;
  ChatSession? selectedChat;

  // Variável para armazenar o ID do usuário (necessário para salvar no background)
  int? _currentUserId;

  bool get isRunning => _isRunning;
  TimerMode get mode => _mode;

  // Método para inicializar o usuário
  void initUser(int userId) {
    _currentUserId = userId;
  }

  int get remainingSeconds {
    if (_isRunning && _endTime != null) {
      final diff = _endTime!.difference(DateTime.now()).inSeconds;
      return diff > 0 ? diff : 0;
    }
    if (_pausedRemainingSeconds != null) return _pausedRemainingSeconds!;
    return _durationForModeInSeconds(_mode);
  }

  void selectChat(ChatSession? chat) {
    if (!_isRunning) {
      selectedChat = chat;
      notifyListeners();
    }
  }

  void updateDurations({required int newPomodoro, required int newShortBreak}) {
    pomodoroDuration = newPomodoro;
    shortBreakDuration = newShortBreak;
    reset(_mode);
    notifyListeners();
  }

  void start([TimerMode? newMode]) {
    if (newMode != null) {
      _mode = newMode;
      _pausedRemainingSeconds = _durationForModeInSeconds(_mode);
    }
    if (_isRunning) return;
    final secondsToRun =
        _pausedRemainingSeconds ?? _durationForModeInSeconds(_mode);
    _endTime = DateTime.now().add(Duration(seconds: secondsToRun));
    _isRunning = true;
    _pausedRemainingSeconds = null;
    _startTicker();
    notifyListeners();
  }

  void pause() {
    if (!_isRunning) return;
    if (_endTime != null) {
      final diff = _endTime!.difference(DateTime.now()).inSeconds;
      _pausedRemainingSeconds = diff > 0 ? diff : 0;
    } else {
      _pausedRemainingSeconds = _durationForModeInSeconds(_mode);
    }
    _isRunning = false;
    _endTime = null;
    _ticker?.cancel();
    _ticker = null;
    notifyListeners();
  }

  void reset(TimerMode mode) {
    pause();
    _mode = mode;
    _pausedRemainingSeconds = _durationForModeInSeconds(mode);
    notifyListeners();
  }

  // Lógica interna de completar
  void _handleComplete() {
    _ticker?.cancel();
    _ticker = null;
    _isRunning = false;
    _endTime = null;
    _pausedRemainingSeconds = null;

    bool pomodoroFinished = _mode == TimerMode.pomodoro;

    // SE TERMINOU UM POMODORO, SALVA AUTOMATICAMENTE
    if (pomodoroFinished) {
      _saveSessionInternal();
    }

    _mode = (pomodoroFinished) ? TimerMode.shortBreak : TimerMode.pomodoro;
    notifyListeners();
  }

  // --- LÓGICA DE SALVAR MOVIDA PARA DENTRO DO MANAGER ---
  Future<void> _saveSessionInternal() async {
    if (_currentUserId == null) {
      print("Erro: ID do usuário não definido no PomodoroManager.");
      return;
    }

    String? chatId = selectedChat?.id;
    String chatTitle = selectedChat?.title ?? "Sessão Avulsa";
    String chatSubject = selectedChat?.subject ?? "Estudo Geral";

    if (chatId == null && selectedChat == null) {
      chatTitle = "Estudo Geral";
      chatSubject = "Estudo Geral";
    }

    print('💾 Manager salvando sessão em background: $chatSubject ($pomodoroDuration min)');

    try {
      // 1. Firebase
      await FirebaseFirestore.instance.collection('pomodoro_sessions').add({
        'id_usuario': _currentUserId,
        'chatId': chatId,
        'chatTitle': chatTitle,
        'subject': chatSubject,
        'durationMinutes': pomodoroDuration,
        'timestamp': DateTime.now().millisecondsSinceEpoch,
        'created_at': FieldValue.serverTimestamp(),
      });

      // 2. SQLite
      try {
        final dbService = DatabaseService();
        await dbService.createPomodoroSession(
          idUsuario: _currentUserId!,
          chatId: chatId,
          chatTitle: chatSubject,
          durationMinutes: pomodoroDuration,
        );
      } catch (localError) {
        print("Erro ao salvar localmente no background: $localError");
      }

      print("✅ Sessão salva com sucesso pelo Manager!");

    } catch (e) {
      print("❌ Erro crítico ao salvar sessão no Manager: $e");
    }
  }

  void _startTicker() {
    _ticker?.cancel();
    _ticker = Timer.periodic(const Duration(seconds: 1), (_) {
      if (!_isRunning || _endTime == null) {
        _ticker?.cancel();
        _ticker = null;
        return;
      }
      final remaining = _endTime!.difference(DateTime.now()).inSeconds;
      if (remaining <= 0) {
        _handleComplete();
      } else {
        notifyListeners();
      }
    });
  }

  int _durationForModeInSeconds(TimerMode mode) {
    switch (mode) {
      case TimerMode.pomodoro:
        return pomodoroDuration * 60;
      case TimerMode.shortBreak:
        return shortBreakDuration * 60;
    }
  }
}

class PomodoroPage extends StatefulWidget {
  final int userId;
  const PomodoroPage({super.key, required this.userId});

  @override
  State<PomodoroPage> createState() => _PomodoroPageState();
}

class _PomodoroPageState extends State<PomodoroPage> {
  final PomodoroManager manager = PomodoroManager();
  final dbService = DatabaseService();
  bool _isLoadingChats = false;

  @override
  void initState() {
    super.initState();
    // IMPORTANTE: Passa o ID do usuário para o Manager assim que a tela abre
    manager.initUser(widget.userId);
    manager.addListener(_onManagerUpdate);
  }

  void _onManagerUpdate() {
    // A lógica de salvar saiu daqui e foi para dentro do Manager.
    // Aqui só precisamos atualizar a UI.
    if (mounted) setState(() {});
  }

  @override
  void dispose() {
    manager.removeListener(_onManagerUpdate);
    super.dispose();
  }

  String _formatTime(int totalSeconds) {
    final minutes = (totalSeconds ~/ 60).toString().padLeft(2, '0');
    final seconds = (totalSeconds % 60).toString().padLeft(2, '0');
    return "$minutes:$seconds";
  }

  Future<void> _showSettingsDialog() async {
    final formKey = GlobalKey<FormState>();
    final pomodoroController = TextEditingController(text: manager.pomodoroDuration.toString());
    final shortBreakController = TextEditingController(text: manager.shortBreakDuration.toString());

    await showDialog(
      context: context,
      builder: (context) {
        return AlertDialog(
          title: const Text('Configurar Tempos'),
          content: Form(
            key: formKey,
            child: Column(
              mainAxisSize: MainAxisSize.min,
              children: [
                TextFormField(
                  controller: pomodoroController,
                  autofocus: true,
                  decoration: const InputDecoration(
                    labelText: 'Tempo de Foco (minutos)',
                    icon: Icon(Icons.psychology_alt_outlined),
                  ),
                  keyboardType: TextInputType.number,
                  validator: (value) {
                    if (value == null || value.isEmpty || int.tryParse(value) == null || int.parse(value) <= 0) {
                      return 'Valor inválido (> 0)';
                    }
                    return null;
                  },
                ),
                const SizedBox(height: 16),
                TextFormField(
                  controller: shortBreakController,
                  decoration: const InputDecoration(
                    labelText: 'Tempo de Pausa (minutos)',
                    icon: Icon(Icons.coffee_outlined),
                  ),
                  keyboardType: TextInputType.number,
                  validator: (value) {
                    if (value == null || value.isEmpty || int.tryParse(value) == null || int.parse(value) <= 0) {
                      return 'Valor inválido (> 0)';
                    }
                    return null;
                  },
                ),
              ],
            ),
          ),
          actions: [
            TextButton(onPressed: () => Navigator.pop(context), child: const Text('Cancelar')),
            ElevatedButton(
              onPressed: () {
                if (formKey.currentState!.validate()) {
                  final newPomo = int.parse(pomodoroController.text);
                  final newBreak = int.parse(shortBreakController.text);
                  if (newPomo != manager.pomodoroDuration || newBreak != manager.shortBreakDuration) {
                    manager.updateDurations(newPomodoro: newPomo, newShortBreak: newBreak);
                  }
                  Navigator.pop(context);
                }
              },
              child: const Text('Salvar'),
            ),
          ],
        );
      },
    );
  }

  Future<void> _showChatSelectionDialog() async {
    if (manager.isRunning) {
      ScaffoldMessenger.of(context).showSnackBar(
        const SnackBar(content: Text('Pause o timer para mudar a matéria.')),
      );
      return;
    }

    setState(() => _isLoadingChats = true);
    List<ChatSession> chats = [];

    try {
      final snapshot = await FirebaseFirestore.instance
          .collection('chats')
          .where('id_usuario', isEqualTo: widget.userId)
          .get();

      chats = snapshot.docs
          .map((doc) => ChatSession.fromFirestore(doc))
          .toList();

    } catch (e) {
      print("Erro ao buscar chats do Firebase: $e");
      try {
        chats = await dbService.getChats(widget.userId);
      } catch (localError) {
        print("Erro crítico ao buscar chats localmente: $localError");
      }
    } finally {
      if (mounted) setState(() => _isLoadingChats = false);
    }

    if (!mounted) return;

    final dynamic selected = await showDialog<dynamic>(
      context: context,
      builder: (context) {
        return AlertDialog(
          title: const Text('Selecionar Matéria'),
          content: SizedBox(
            width: double.maxFinite,
            height: 300,
            child: _isLoadingChats
                ? const Center(child: CircularProgressIndicator())
                : (chats.isEmpty)
                ? const Center(child: Text('Nenhuma matéria encontrada.'))
                : ListView.builder(
              shrinkWrap: true,
              itemCount: chats.length + 1,
              itemBuilder: (context, index) {
                if (index == 0) {
                  return ListTile(
                    leading: const Icon(Icons.menu_book),
                    title: const Text('Estudo Geral'),
                    selected: manager.selectedChat == null,
                    onTap: () => Navigator.pop(context, null),
                  );
                }
                final chat = chats[index - 1];
                return ListTile(
                  leading: const Icon(Icons.chat_bubble_outline),
                  title: Text(chat.title),
                  subtitle: Text(chat.subject),
                  selected: manager.selectedChat?.id == chat.id,
                  onTap: () => Navigator.pop(context, chat),
                );
              },
            ),
          ),
          actions: [
            TextButton(onPressed: () => Navigator.pop(context, 'cancel'), child: const Text('Cancelar')),
          ],
        );
      },
    );

    if (selected != 'cancel') {
      manager.selectChat(selected as ChatSession?);
    }
  }

  @override
  Widget build(BuildContext context) {
    final theme = Theme.of(context);
    final remaining = manager.remainingSeconds;
    final totalDuration = manager._durationForModeInSeconds(manager.mode);
    final double progress = totalDuration > 0 ? (totalDuration - remaining) / totalDuration : 0.0;

    return Scaffold(
      appBar: AppBar(
        title: const Text("Temporizador Pomodoro"),
        actions: [
          IconButton(
            icon: const Icon(Icons.settings_outlined),
            onPressed: _showSettingsDialog,
            tooltip: 'Configurações',
          ),
        ],
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            GestureDetector(
              onTap: manager.isRunning ? null : _showChatSelectionDialog,
              child: Container(
                padding: const EdgeInsets.symmetric(horizontal: 16, vertical: 8),
                decoration: BoxDecoration(
                    color: theme.colorScheme.primary.withOpacity(0.1),
                    borderRadius: BorderRadius.circular(20),
                    border: Border.all(color: theme.colorScheme.primary.withOpacity(0.3))
                ),
                child: Row(
                  mainAxisSize: MainAxisSize.min,
                  children: [
                    Icon(Icons.topic_outlined, size: 18, color: theme.colorScheme.primary),
                    const SizedBox(width: 8),
                    Text(
                      manager.selectedChat?.title ?? 'Estudo Geral',
                      style: theme.textTheme.bodyLarge?.copyWith(
                          color: theme.colorScheme.primary,
                          fontWeight: FontWeight.w500
                      ),
                    ),
                    const SizedBox(width: 4),
                    if (!manager.isRunning)
                      Icon(Icons.arrow_drop_down, size: 20, color: theme.colorScheme.primary),
                  ],
                ),
              ),
            ),
            const SizedBox(height: 24),
            SizedBox(
              width: 250,
              height: 250,
              child: Stack(
                fit: StackFit.expand,
                children: [
                  CircularProgressIndicator(
                    value: progress,
                    strokeWidth: 12,
                    backgroundColor: theme.colorScheme.surfaceVariant.withOpacity(0.5),
                    valueColor: AlwaysStoppedAnimation<Color>(theme.colorScheme.primary),
                    strokeCap: StrokeCap.round,
                  ),
                  Center(
                    child: Text(
                      _formatTime(remaining),
                      style: theme.textTheme.displayLarge?.copyWith(
                          fontSize: 60,
                          fontWeight: FontWeight.bold,
                          color: theme.colorScheme.onSurface
                      ),
                    ),
                  ),
                ],
              ),
            ),
            const SizedBox(height: 40),
            Row(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                OutlinedButton(
                  onPressed: manager.isRunning ? null : () => manager.reset(TimerMode.pomodoro),
                  style: OutlinedButton.styleFrom(
                      backgroundColor: manager.mode == TimerMode.pomodoro ? theme.colorScheme.primary : Colors.transparent,
                      foregroundColor: manager.mode == TimerMode.pomodoro ? theme.colorScheme.onPrimary : theme.colorScheme.primary,
                      side: BorderSide(color: manager.isRunning ? Colors.grey : theme.colorScheme.primary, width: 1.5),
                      shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(20)),
                      padding: const EdgeInsets.symmetric(horizontal: 24, vertical: 12)
                  ),
                  child: const Text("Foco"),
                ),
                const SizedBox(width: 20),
                OutlinedButton(
                  onPressed: manager.isRunning ? null : () => manager.reset(TimerMode.shortBreak),
                  style: OutlinedButton.styleFrom(
                      backgroundColor: manager.mode == TimerMode.shortBreak ? theme.colorScheme.primary : Colors.transparent,
                      foregroundColor: manager.mode == TimerMode.shortBreak ? theme.colorScheme.onPrimary : theme.colorScheme.primary,
                      side: BorderSide(color: manager.isRunning ? Colors.grey : theme.colorScheme.primary, width: 1.5),
                      shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(20)),
                      padding: const EdgeInsets.symmetric(horizontal: 24, vertical: 12)
                  ),
                  child: const Text("Pausa"),
                ),
              ],
            ),
            const SizedBox(height: 40),
            ElevatedButton(
              style: ElevatedButton.styleFrom(
                padding: const EdgeInsets.symmetric(horizontal: 40, vertical: 15),
                shape: const StadiumBorder(),
                backgroundColor: AppColors.green,
                foregroundColor: AppColors.white,
              ),
              onPressed: () {
                if (manager.isRunning) {
                  manager.pause();
                } else {
                  manager.start();
                }
              },
              child: Row(
                mainAxisSize: MainAxisSize.min,
                children: [
                  Icon(manager.isRunning ? Icons.pause : Icons.play_arrow, size: 32),
                  const SizedBox(width: 8),
                  Text(
                    manager.isRunning ? "PAUSAR" : "INICIAR",
                    style: theme.textTheme.labelLarge?.copyWith(letterSpacing: 1.2, color: AppColors.white),
                  ),
                ],
              ),
            ),
          ],
        ),
      ),
    );
  }
}