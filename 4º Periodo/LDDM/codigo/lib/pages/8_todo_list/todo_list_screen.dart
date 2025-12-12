// lib/pages/8_todo_list/todo_list_screen.dart

import 'dart:math'; // Import necessário para gerar IDs seguros
import 'package:flutter/material.dart';
import 'package:showcaseview/showcaseview.dart';
import 'package:shared_preferences/shared_preferences.dart';
import 'package:intl/intl.dart';

import '../../shared/theme/app_colors.dart';
import '../../services/database_service.dart';
import '../../services/notification_service.dart';

// --- IMPORT DO FIREBASE ---
import 'package:cloud_firestore/cloud_firestore.dart';
// --------------------------

// ==========================
// ENUMs
// ==========================
enum TaskFilter { all, pending, completed }

enum TaskSort {
  insertedNewest,
  insertedOldest,
  dueDateOldest,
  dueDateNewest,
  byStatus,
  alphabetical,
}

// ==========================
// MODEL Task
// ==========================
class Task {
  final int id;
  final int id_usuario;
  String title;
  String? dueDate;
  bool isDone;
  String? firestoreId;

  Task({
    required this.id,
    required this.id_usuario,
    required this.title,
    this.dueDate,
    this.isDone = false,
    this.firestoreId,
  });

  factory Task.fromMap(Map<String, dynamic> map) {
    return Task(
      id: map['id'] ?? 0,
      id_usuario: map['id_usuario'] ?? 0,
      title: map['title'] ?? 'Sem título',
      isDone: (map['isDone'] == 1 || map['isDone'] == true),
      dueDate: map['dueDate'],
      firestoreId: map['firestoreId'],
    );
  }

  DateTime? get dueDateAsDateTime {
    if (dueDate == null || dueDate!.isEmpty) return null;
    try {
      return DateFormat('dd/MM/yyyy HH:mm').parseStrict(dueDate!);
    } catch (e) {
      try {
        return DateFormat('dd/MM/yyyy').parseStrict(dueDate!);
      } catch (e2) {
        return null;
      }
    }
  }
}

// ==========================
// TELA PRINCIPAL
// ==========================
class TodoListScreen extends StatelessWidget {
  final int userId;
  const TodoListScreen({super.key, required this.userId});

  @override
  Widget build(BuildContext context) {
    return Builder(
      key: UniqueKey(),
      builder: (context) {
        return ShowCaseWidget(
          onFinish: () async {
            final prefs = await SharedPreferences.getInstance();
            await prefs.setBool('todoTourDone', true);
          },
          builder: (context) => _TodoListContent(userId: userId),
        );
      },
    );
  }
}

// ==========================
// CONTEÚDO
// ==========================
class _TodoListContent extends StatefulWidget {
  final int userId;
  const _TodoListContent({super.key, required this.userId});

  @override
  State<_TodoListContent> createState() => _TodoListContentState();
}

class _TodoListContentState extends State<_TodoListContent> {
  final GlobalKey _kFab = GlobalKey();
  GlobalKey? _kFirstCard;
  GlobalKey? _kFirstToggle;
  final GlobalKey _kFilterButton = GlobalKey();

  final dbService = DatabaseService();
  final notificationService = NotificationService();

  List<Task> _tasks = [];
  bool _isLoading = true;

  TaskFilter _currentFilter = TaskFilter.all;
  TaskSort _currentSort = TaskSort.dueDateOldest;

  final TextEditingController _searchCtrl = TextEditingController();
  String _q = '';
  bool _tourStarted = false;

  @override
  void initState() {
    super.initState();
    _initServices();
  }

  Future<void> _initServices() async {
    try {
      await notificationService.init();
    } catch (e) {
      print("Erro ao inicializar notificações: $e");
    }
    _loadTasks();
  }

  @override
  void dispose() {
    _searchCtrl.dispose();
    super.dispose();
  }

  // ==========================
  // CARREGAMENTO DE DADOS
  // ==========================
  Future<void> _loadTasks() async {
    if (mounted) setState(() => _isLoading = true);
    try {
      // Busca do Firebase
      final snapshot = await FirebaseFirestore.instance
          .collection('tasks')
          .where('id_usuario', isEqualTo: widget.userId)
          .get();

      List<Task> loadedTasks = snapshot.docs.map((doc) {
        final data = doc.data();
        // Garante que local_id seja int, se não existir gera um aleatório seguro
        int safeId = data['local_id'] is int ? data['local_id'] : Random().nextInt(2147483647);

        return Task(
          id: safeId,
          id_usuario: widget.userId,
          title: data['title'] ?? '',
          dueDate: data['dueDate'],
          isDone: data['isDone'] ?? false,
          firestoreId: doc.id,
        );
      }).toList();

      if (mounted) {
        setState(() {
          _tasks = loadedTasks;
          _isLoading = false;

          if (_tasks.isNotEmpty) {
            _kFirstCard = GlobalKey();
            _kFirstToggle = GlobalKey();
          } else {
            _kFirstCard = null;
            _kFirstToggle = null;
          }
        });
        _checkAndShowTour();
      }

    } catch (e) {
      print("Erro ao carregar do Firebase: $e");
      if (mounted) setState(() => _isLoading = false);
    }
  }

  Future<void> _checkAndShowTour() async {
    if (_isLoading || !mounted) return;
    final prefs = await SharedPreferences.getInstance();
    final bool tourDone = prefs.getBool('todoTourDone') ?? false;

    if (!tourDone && !_tourStarted) {
      WidgetsBinding.instance.addPostFrameCallback((_) {
        if (mounted && ShowCaseWidget.of(context) != null) {
          final keys = <GlobalKey>[_kFab];
          if (_kFirstCard != null) keys.add(_kFirstCard!);
          if (_kFirstToggle != null) keys.add(_kFirstToggle!);
          keys.add(_kFilterButton);

          ShowCaseWidget.of(context).startShowCase(keys);
          _tourStarted = true;
        }
      });
    }
  }

  // ==========================
  // FILTROS
  // ==========================
  List<Task> get _filteredAndSortedTasks {
    final query = _q.toLowerCase();
    List<Task> list = _tasks.where((t) {
      if (query.isEmpty) return true;
      final inTitle = t.title.toLowerCase().contains(query);
      final inDate = (t.dueDate ?? '').toLowerCase().contains(query);
      return inTitle || inDate;
    }).toList();

    switch (_currentFilter) {
      case TaskFilter.pending: list = list.where((t) => !t.isDone).toList(); break;
      case TaskFilter.completed: list = list.where((t) => t.isDone).toList(); break;
      default: break;
    }

    int statusCmp(Task a, Task b) => a.isDone == b.isDone ? 0 : (a.isDone ? 1 : -1);
    int idAsc(Task a, Task b) => a.id.compareTo(b.id);
    int idDesc(Task a, Task b) => b.id.compareTo(a.id);
    int dateAsc(Task a, Task b) {
      final da = a.dueDateAsDateTime;
      final db = b.dueDateAsDateTime;
      if (da == null && db == null) return 0;
      if (da == null) return 1;
      if (db == null) return -1;
      return da.compareTo(db);
    }
    int dateDesc(Task a, Task b) => dateAsc(b, a);
    int alpha(Task a, Task b) => a.title.toLowerCase().compareTo(b.title.toLowerCase());

    switch (_currentSort) {
      case TaskSort.insertedNewest: list.sort(idDesc); break;
      case TaskSort.insertedOldest: list.sort(idAsc); break;
      case TaskSort.dueDateNewest: list.sort(dateDesc); break;
      case TaskSort.dueDateOldest: list.sort(dateAsc); break;
      case TaskSort.byStatus: list.sort(statusCmp); break;
      case TaskSort.alphabetical: list.sort(alpha); break;
    }
    return list;
  }

  void _onSearchChanged(String v) => setState(() => _q = v);

  // ==========================
  // CRUD
  // ==========================

  Future<void> _addTask() async {
    final Map<String, String>? created = await showModalBottomSheet<Map<String, String>>(
      context: context,
      isScrollControlled: true,
      backgroundColor: Colors.transparent,
      builder: (ctx) => const _TaskSheet(),
    );

    if (created != null) {
      try {
        // CORREÇÃO DO ID: Usa Bitwise AND para garantir que caiba em 32 bits positivos
        // Isso evita o erro "must fit within the size of a 32-bit integer"
        final int localId = DateTime.now().millisecondsSinceEpoch & 0x7FFFFFFF;

        print("Tentando salvar no Firebase... ID gerado: $localId");

        // 1. Salvar no Firestore
        final docRef = await FirebaseFirestore.instance.collection('tasks').add({
          'id_usuario': widget.userId,
          'title': created['title'],
          'dueDate': created['dueDate'],
          'isDone': false,
          'local_id': localId, // ID seguro para notificações
          'created_at': FieldValue.serverTimestamp(),
        });

        print("✅ Salvo no Firebase com ID do documento: ${docRef.id}");

        // 2. Tentar salvar no SQLite (Backup, ignora erro se falhar)
        try {
          await dbService.createTarefa(widget.userId, created['title']!, created['dueDate']!);
        } catch (e) {
          print("Aviso: SQLite falhou (normal se estiver offline/emulador bugado): $e");
        }

        final newTask = Task(
          id: localId,
          id_usuario: widget.userId,
          title: created['title']!,
          dueDate: created['dueDate']!.isEmpty ? null : created['dueDate'],
          isDone: false,
          firestoreId: docRef.id,
        );

        // 3. Agendar notificação
        try {
          await _scheduleTaskNotification(newTask);
        } catch (e) {
          print("Erro ao agendar notificação: $e");
        }

        _loadTasks(); // Recarrega a lista direto da nuvem
        if(mounted) ScaffoldMessenger.of(context).showSnackBar(const SnackBar(content: Text('Tarefa salva!')));

      } catch (e) {
        print("❌ ERRO CRÍTICO AO SALVAR: $e");
        if(mounted) ScaffoldMessenger.of(context).showSnackBar(SnackBar(content: Text('Erro ao salvar: $e'), backgroundColor: Colors.red));
      }
    }
  }

  Future<void> _toggleTask(Task task) async {
    final newState = !task.isDone;
    setState(() => task.isDone = newState);

    try {
      if (task.firestoreId != null) {
        await FirebaseFirestore.instance.collection('tasks').doc(task.firestoreId).update({
          'isDone': newState
        });
      }
      try { await dbService.updateTarefa(task.id, newState); } catch (_) {}

      if (newState) {
        await notificationService.cancelNotification(task.id);
      } else {
        try { await _scheduleTaskNotification(task); } catch (_) {}
      }
    } catch (e) {
      print("Erro ao atualizar: $e");
      setState(() => task.isDone = !newState);
      if(mounted) ScaffoldMessenger.of(context).showSnackBar(const SnackBar(content: Text('Erro ao atualizar status')));
    }
  }

  Future<void> _editTask(Task task) async {
    final Map<String, String>? updated = await showModalBottomSheet<Map<String, String>>(
      context: context,
      isScrollControlled: true,
      backgroundColor: Colors.transparent,
      builder: (ctx) => _TaskSheet(
        initialTitle: task.title,
        initialDescription: task.dueDate ?? '',
      ),
    );

    if (updated != null) {
      try {
        final newTitle = updated['title']!;
        final newDate = updated['dueDate']!.isEmpty ? null : updated['dueDate'];

        if (task.firestoreId != null) {
          await FirebaseFirestore.instance.collection('tasks').doc(task.firestoreId).update({
            'title': newTitle,
            'dueDate': newDate ?? '',
          });
        }

        try { await dbService.updateTarefaCompleta(task.id, newTitle, newDate, task.isDone); } catch (_) {}

        task.title = newTitle;
        task.dueDate = newDate;

        await notificationService.cancelNotification(task.id);
        if (!task.isDone) {
          try { await _scheduleTaskNotification(task); } catch (_) {}
        }

        _loadTasks();
      } catch (e) {
        print("Erro ao editar: $e");
        if(mounted) ScaffoldMessenger.of(context).showSnackBar(const SnackBar(content: Text('Erro ao editar tarefa')));
      }
    }
  }

  Future<void> _removeTask(Task task) async {
    try {
      if (task.firestoreId != null) {
        await FirebaseFirestore.instance.collection('tasks').doc(task.firestoreId).delete();
      }
      try { await dbService.deleteTarefa(task.id); } catch (_) {}
      await notificationService.cancelNotification(task.id);

      _loadTasks();
      if(mounted) ScaffoldMessenger.of(context).showSnackBar(const SnackBar(content: Text('Tarefa removida')));
    } catch (e) {
      print("Erro ao remover: $e");
    }
  }

  Future<void> _scheduleTaskNotification(Task task) async {
    final scheduledDate = task.dueDateAsDateTime;
    if (task.isDone || scheduledDate == null) return;

    final now = DateTime.now();
    DateTime notificationTime;
    Duration reminderLeadTime = const Duration(hours: 1);

    if (scheduledDate.hour == 0 && scheduledDate.minute == 0) {
      notificationTime = DateTime(scheduledDate.year, scheduledDate.month, scheduledDate.day, 9, 0);
    } else {
      notificationTime = scheduledDate.subtract(reminderLeadTime);
    }

    if (notificationTime.isAfter(now)) {
      try {
        await notificationService.scheduleNotification(
          id: task.id,
          title: 'Lembrete: ${task.title}',
          body: 'Sua tarefa vence em breve.',
          scheduledDate: notificationTime,
          payload: 'task_${task.id}',
        );
      } catch (e) {
        print("Erro ao agendar (ID=${task.id}): $e");
      }
    }
  }

  Future<bool> _confirmDelete(BuildContext context, Task task) async {
    return await showDialog<bool>(
      context: context,
      builder: (_) => AlertDialog(
        title: const Text('Excluir tarefa'),
        content: Text('Tem certeza que deseja excluir "${task.title}"?'),
        actions: [
          TextButton(onPressed: () => Navigator.pop(context, false), child: const Text('Cancelar')),
          FilledButton(
            onPressed: () => Navigator.pop(context, true),
            style: FilledButton.styleFrom(backgroundColor: Theme.of(context).colorScheme.error),
            child: const Text('Excluir'),
          ),
        ],
      ),
    ) ?? false;
  }

  void _showFilterSortSheet() {
    showModalBottomSheet(
        context: context,
        builder: (context) => Container(
          padding: const EdgeInsets.all(24),
          child: const Text("Opções de filtro (Implementação simplificada para teste)"),
        )
    );
  }

  @override
  Widget build(BuildContext context) {
    final displayedTasks = _filteredAndSortedTasks;
    final theme = Theme.of(context);

    return Scaffold(
      appBar: AppBar(
        title: const Text('Lista de Tarefas'),
        actions: [
          Showcase(
            key: _kFilterButton,
            description: 'Filtrar e Ordenar',
            child: IconButton(
              icon: const Icon(Icons.filter_list_outlined),
              onPressed: _showFilterSortSheet,
            ),
          ),
        ],
      ),
      body: Column(
        children: [
          Padding(
            padding: const EdgeInsets.fromLTRB(16, 8, 16, 12),
            child: TextField(
              controller: _searchCtrl,
              onChanged: _onSearchChanged,
              decoration: InputDecoration(
                isDense: true,
                hintText: 'Buscar...',
                filled: true,
                fillColor: theme.colorScheme.surfaceVariant.withOpacity(0.7),
                border: OutlineInputBorder(borderRadius: BorderRadius.circular(24), borderSide: BorderSide.none),
                prefixIcon: const Icon(Icons.search),
                suffixIcon: _q.isNotEmpty ? IconButton(icon: const Icon(Icons.close), onPressed: () { _searchCtrl.clear(); _onSearchChanged(''); }) : null,
              ),
            ),
          ),
          Expanded(
            child: _isLoading
                ? const Center(child: CircularProgressIndicator())
                : displayedTasks.isEmpty
                ? const Center(child: Text('Nenhuma tarefa encontrada.'))
                : ListView.separated(
              padding: const EdgeInsets.fromLTRB(16, 0, 16, 80),
              itemCount: displayedTasks.length,
              separatorBuilder: (_, __) => const SizedBox(height: 12),
              itemBuilder: (context, index) {
                final task = displayedTasks[index];

                GlobalKey? cardKey = (index == 0 && _kFirstCard != null) ? _kFirstCard : null;
                GlobalKey? toggleKey = (index == 0 && _kFirstToggle != null) ? _kFirstToggle : null;

                final cardChild = GestureDetector(
                  onTap: () => _editTask(task),
                  onLongPress: () async {
                    final ok = await _confirmDelete(context, task);
                    if (ok && mounted) _removeTask(task);
                  },
                  child: _TaskCard(
                    task: task,
                    onToggle: () => _toggleTask(task),
                    toggleKey: toggleKey,
                  ),
                );

                final cardWidget = cardKey != null
                    ? Showcase(
                  key: cardKey,
                  title: 'Suas tarefas',
                  description: 'Toque para editar.\nSegure para excluir.',
                  child: cardChild,
                )
                    : cardChild;

                return Dismissible(
                  key: ValueKey(task.id),
                  direction: DismissDirection.endToStart,
                  onDismissed: (_) => _removeTask(task),
                  background: Container(
                    alignment: Alignment.centerRight,
                    padding: const EdgeInsets.only(right: 20),
                    decoration: BoxDecoration(
                      color: theme.colorScheme.errorContainer,
                      borderRadius: BorderRadius.circular(14),
                    ),
                    child: Icon(Icons.delete_outline, color: theme.colorScheme.onErrorContainer),
                  ),
                  child: cardWidget,
                );
              },
            ),
          ),
        ],
      ),
      floatingActionButtonLocation: FloatingActionButtonLocation.centerFloat,
      floatingActionButton: Showcase(
        key: _kFab,
        title: 'Adicionar',
        description: 'Criar nova tarefa',
        child: FloatingActionButton(
          onPressed: _addTask,
          backgroundColor: AppColors.purplePrimary,
          child: const Icon(Icons.add, color: Colors.white),
        ),
      ),
    );
  }
}

class _TaskCard extends StatelessWidget {
  final Task task;
  final VoidCallback onToggle;
  final GlobalKey? toggleKey;

  const _TaskCard({super.key, required this.task, required this.onToggle, this.toggleKey});

  @override
  Widget build(BuildContext context) {
    final theme = Theme.of(context);
    final isDone = task.isDone;

    String? dateStr;
    bool isOverdue = false;
    final dt = task.dueDateAsDateTime;
    if (dt != null) {
      final now = DateTime.now();
      if (dt.hour == 0 && dt.minute == 0) {
        dateStr = DateFormat('dd/MM/yyyy').format(dt);
        if (!isDone && DateUtils.dateOnly(dt).isBefore(DateUtils.dateOnly(now))) isOverdue = true;
      } else {
        dateStr = DateFormat('dd/MM/yyyy HH:mm').format(dt);
        if (!isDone && dt.isBefore(now)) isOverdue = true;
      }
    }

    final iconBtn = InkWell(
      onTap: onToggle,
      borderRadius: BorderRadius.circular(20),
      child: Padding(
        padding: const EdgeInsets.all(8.0),
        child: Icon(
          isDone ? Icons.check_circle : Icons.radio_button_unchecked,
          color: isDone ? Colors.green : theme.colorScheme.onSurfaceVariant,
        ),
      ),
    );

    return Container(
      decoration: BoxDecoration(
        color: theme.cardTheme.color ?? Colors.white,
        borderRadius: BorderRadius.circular(14),
        border: isOverdue ? Border.all(color: Colors.red.withOpacity(0.5)) : null,
        boxShadow: const [BoxShadow(color: Colors.black12, blurRadius: 4, offset: Offset(0, 2))],
      ),
      child: Row(
        children: [
          toggleKey != null
              ? Showcase(key: toggleKey!, title: 'Concluir', description: 'Marque como feita', child: iconBtn)
              : iconBtn,
          Expanded(
            child: Padding(
              padding: const EdgeInsets.symmetric(vertical: 12, horizontal: 8),
              child: Column(
                crossAxisAlignment: CrossAxisAlignment.start,
                children: [
                  Text(
                    task.title,
                    style: TextStyle(
                      fontSize: 16,
                      fontWeight: FontWeight.w500,
                      decoration: isDone ? TextDecoration.lineThrough : null,
                      color: isDone ? Colors.grey : theme.colorScheme.onSurface,
                    ),
                  ),
                  if (dateStr != null)
                    Padding(
                      padding: const EdgeInsets.only(top: 4),
                      child: Text(
                        dateStr,
                        style: TextStyle(
                          fontSize: 12,
                          color: isOverdue ? Colors.red : Colors.grey[600],
                          decoration: isDone ? TextDecoration.lineThrough : null,
                        ),
                      ),
                    ),
                ],
              ),
            ),
          ),
        ],
      ),
    );
  }
}

class _TaskSheet extends StatefulWidget {
  final String? initialTitle;
  final String? initialDescription;
  const _TaskSheet({this.initialTitle, this.initialDescription});
  @override
  State<_TaskSheet> createState() => _TaskSheetState();
}

class _TaskSheetState extends State<_TaskSheet> {
  final _titleCtrl = TextEditingController();
  DateTime? _selectedDateTime;

  @override
  void initState() {
    super.initState();
    if (widget.initialTitle != null) _titleCtrl.text = widget.initialTitle!;
    if (widget.initialDescription != null && widget.initialDescription!.isNotEmpty) {
      try {
        _selectedDateTime = DateFormat('dd/MM/yyyy HH:mm').parseStrict(widget.initialDescription!);
      } catch (_) {
        try { _selectedDateTime = DateFormat('dd/MM/yyyy').parseStrict(widget.initialDescription!); } catch (_) {}
      }
    }
  }

  @override
  Widget build(BuildContext context) {
    final viewInsets = MediaQuery.of(context).viewInsets;
    final fmtDate = DateFormat('dd/MM/yyyy');
    final fmtTime = DateFormat('HH:mm');

    return Padding(
      padding: EdgeInsets.only(bottom: viewInsets.bottom),
      child: Container(
        padding: const EdgeInsets.all(20),
        decoration: BoxDecoration(
            color: Theme.of(context).scaffoldBackgroundColor,
            borderRadius: const BorderRadius.vertical(top: Radius.circular(20))
        ),
        child: Column(
          mainAxisSize: MainAxisSize.min,
          children: [
            TextField(
              controller: _titleCtrl,
              decoration: const InputDecoration(labelText: 'Título da Tarefa'),
              autofocus: true,
            ),
            const SizedBox(height: 20),
            Row(
              children: [
                Expanded(
                  child: OutlinedButton.icon(
                    icon: const Icon(Icons.calendar_today, size: 16),
                    label: Text(_selectedDateTime == null ? 'Data' : fmtDate.format(_selectedDateTime!)),
                    onPressed: () async {
                      final date = await showDatePicker(
                          context: context,
                          initialDate: _selectedDateTime ?? DateTime.now(),
                          firstDate: DateTime.now().subtract(const Duration(days: 30)),
                          lastDate: DateTime(2030)
                      );
                      if (date != null) {
                        setState(() {
                          final time = _selectedDateTime ?? DateTime(0,0,0,0,0);
                          _selectedDateTime = DateTime(date.year, date.month, date.day, time.hour, time.minute);
                        });
                      }
                    },
                  ),
                ),
                const SizedBox(width: 10),
                Expanded(
                  child: OutlinedButton.icon(
                    icon: const Icon(Icons.access_time, size: 16),
                    label: Text(_selectedDateTime == null ? 'Hora' : fmtTime.format(_selectedDateTime!)),
                    onPressed: () async {
                      final time = await showTimePicker(
                          context: context,
                          initialTime: _selectedDateTime != null ? TimeOfDay.fromDateTime(_selectedDateTime!) : TimeOfDay.now()
                      );
                      if (time != null) {
                        setState(() {
                          final date = _selectedDateTime ?? DateTime.now();
                          _selectedDateTime = DateTime(date.year, date.month, date.day, time.hour, time.minute);
                        });
                      }
                    },
                  ),
                ),
              ],
            ),
            if (_selectedDateTime != null)
              TextButton(
                onPressed: () => setState(() => _selectedDateTime = null),
                child: const Text("Remover Data", style: TextStyle(color: Colors.red)),
              ),
            const SizedBox(height: 20),
            SizedBox(
              width: double.infinity,
              child: ElevatedButton(
                onPressed: () {
                  if (_titleCtrl.text.trim().isNotEmpty) {
                    String dateStr = '';
                    if (_selectedDateTime != null) {
                      if (_selectedDateTime!.hour == 0 && _selectedDateTime!.minute == 0) {
                        dateStr = fmtDate.format(_selectedDateTime!);
                      } else {
                        dateStr = DateFormat('dd/MM/yyyy HH:mm').format(_selectedDateTime!);
                      }
                    }
                    Navigator.pop(context, {
                      'title': _titleCtrl.text.trim(),
                      'dueDate': dateStr
                    });
                  }
                },
                style: ElevatedButton.styleFrom(
                    backgroundColor: AppColors.purplePrimary,
                    padding: const EdgeInsets.symmetric(vertical: 12)
                ),
                child: const Text('Salvar', style: TextStyle(color: Colors.white, fontSize: 16)),
              ),
            )
          ],
        ),
      ),
    );
  }
}