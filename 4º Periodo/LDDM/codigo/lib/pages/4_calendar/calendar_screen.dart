// lib/pages/4_calendar/calendar_screen.dart

import 'dart:async';
import 'package:flutter/material.dart';
import 'package:intl/intl.dart';
import '../../services/database_service.dart';

// --- IMPORT DO FIREBASE ---
import 'package:cloud_firestore/cloud_firestore.dart';
// --------------------------

// --- MODELO CalendarEvent ATUALIZADO ---
class CalendarEvent {
  final int? id; // ID numérico (mantido para compatibilidade local)
  final String title;
  final String? description;
  final DateTime when;
  final String? firestoreId; // ID do documento no Firestore

  CalendarEvent({
    this.id,
    required this.title,
    this.description,
    required this.when,
    this.firestoreId,
  });

  // Factory para criar a partir do mapa do DB Local
  factory CalendarEvent.fromMap(Map<String, dynamic> map) {
    return CalendarEvent(
      id: map['id'],
      title: map['title'] ?? 'Sem título',
      description: map['description'],
      when: DateTime.fromMillisecondsSinceEpoch(map['whenTimestamp'] ?? 0),
      firestoreId: map['firestoreId'],
    );
  }

  // Factory para criar a partir do Firestore
  factory CalendarEvent.fromFirestore(DocumentSnapshot doc) {
    final data = doc.data() as Map<String, dynamic>;
    return CalendarEvent(
      id: data['local_id'], // Pode ser null
      title: data['title'] ?? 'Sem título',
      description: data['description'],
      when: DateTime.fromMillisecondsSinceEpoch(data['whenTimestamp'] ?? 0),
      firestoreId: doc.id,
    );
  }

  // --- MÉTODO REINSERIDO PARA CORRIGIR O ERRO ---
  Map<String, dynamic> toMapForDb() {
    return {
      'title': title,
      'description': description,
      'whenTimestamp': when.millisecondsSinceEpoch,
    };
  }
  // ---------------------------------------------

  CalendarEvent copyWith({
    int? id,
    String? title,
    String? description,
    DateTime? when,
    String? firestoreId,
  }) {
    return CalendarEvent(
      id: id ?? this.id,
      title: title ?? this.title,
      description: description ?? this.description,
      when: when ?? this.when,
      firestoreId: firestoreId ?? this.firestoreId,
    );
  }
}
// --- FIM DO MODELO ---

class CalendarScreen extends StatefulWidget {
  final int userId;
  const CalendarScreen({super.key, required this.userId});

  @override
  State<CalendarScreen> createState() => _CalendarScreenState();
}

class _CalendarScreenState extends State<CalendarScreen> {
  final dbService = DatabaseService();
  List<CalendarEvent> _events = [];
  bool _isLoading = true;
  DateTime? _selectedFilterDate;

  @override
  void initState() {
    super.initState();
    _loadEvents();
  }

  // --- CARREGAR EVENTOS (Firebase + Fallback) ---
  Future<void> _loadEvents() async {
    if (!mounted) return;
    setState(() => _isLoading = true);

    try {
      // 1. Tenta carregar do Firebase (Prioridade)
      final snapshot = await FirebaseFirestore.instance
          .collection('calendar_events')
          .where('id_usuario', isEqualTo: widget.userId)
          .get();

      final firebaseEvents = snapshot.docs
          .map((doc) => CalendarEvent.fromFirestore(doc))
          .toList();

      if (mounted) {
        setState(() {
          _events = firebaseEvents;
          _isLoading = false;
        });
      }
    } catch (e) {
      print("Erro ao carregar do Firebase: $e");

      // 2. Fallback para SQLite se Firebase falhar
      try {
        final localEvents = await dbService.getCalendarEventsByUser(widget.userId);
        if (mounted) {
          setState(() {
            _events = localEvents;
            _isLoading = false;
          });
        }
      } catch (localError) {
        print("Erro crítico (ambos falharam): $localError");
        if (mounted) setState(() => _isLoading = false);
      }
    }
  }

  // --- CRIAR EVENTO ---
  Future<void> _handleEventCreated(CalendarEvent e) async {
    try {
      // 1. Salvar no Firestore
      await FirebaseFirestore.instance.collection('calendar_events').add({
        'id_usuario': widget.userId,
        'title': e.title,
        'description': e.description,
        'whenTimestamp': e.when.millisecondsSinceEpoch,
        'created_at': FieldValue.serverTimestamp(),
      });

      // 2. Tentar salvar no SQLite (Backup silencioso)
      // O método createCalendarEvent do seu DBService provavelmente chama o toMapForDb() internamente
      try {
        await dbService.createCalendarEvent(
          idUsuario: widget.userId,
          title: e.title,
          description: e.description,
          when: e.when,
        );
      } catch (_) {}

      _loadEvents(); // Recarrega
      if (mounted) {
        ScaffoldMessenger.of(context).showSnackBar(
          const SnackBar(content: Text('Evento salvo na nuvem!')),
        );
      }
    } catch (e) {
      print("Erro ao salvar: $e");
      if (mounted) {
        ScaffoldMessenger.of(context).showSnackBar(
          SnackBar(content: Text('Erro ao salvar: $e'), backgroundColor: Colors.red),
        );
      }
    }
  }

  // --- EDITAR EVENTO ---
  Future<void> _handleEditEvent(CalendarEvent eventToEdit) async {
    final CalendarEvent? updatedData = await showDialog<CalendarEvent>(
      context: context,
      builder: (context) => _AddEventDialog(eventToEdit: eventToEdit),
    );

    if (updatedData != null) {
      try {
        // Atualiza Firestore
        if (eventToEdit.firestoreId != null) {
          await FirebaseFirestore.instance
              .collection('calendar_events')
              .doc(eventToEdit.firestoreId)
              .update({
            'title': updatedData.title,
            'description': updatedData.description,
            'whenTimestamp': updatedData.when.millisecondsSinceEpoch,
          });
        }

        // Tenta atualizar Local (se tiver ID numérico)
        if (eventToEdit.id != null) {
          try {
            // Recria o objeto com os dados novos e ID antigo para o SQLite
            final localUpdate = eventToEdit.copyWith(
              title: updatedData.title,
              description: updatedData.description,
              when: updatedData.when,
            );
            await dbService.updateCalendarEvent(eventToEdit.id!, widget.userId, localUpdate);
          } catch (_) {}
        }

        _loadEvents();
        if (mounted) ScaffoldMessenger.of(context).showSnackBar(const SnackBar(content: Text('Evento atualizado!')));

      } catch (e) {
        print("Erro ao editar: $e");
        if (mounted) ScaffoldMessenger.of(context).showSnackBar(const SnackBar(content: Text('Erro ao editar evento')));
      }
    }
  }

  // --- DELETAR EVENTO ---
  Future<void> _handleDeleteEvent(CalendarEvent event) async {
    final bool? confirmed = await showDialog<bool>(
      context: context,
      builder: (context) => AlertDialog(
        title: const Text('Confirmar exclusão'),
        content: Text('Tem certeza que deseja remover "${event.title}"?'),
        actions: [
          TextButton(onPressed: () => Navigator.pop(context, false), child: const Text('Cancelar')),
          TextButton(
            onPressed: () => Navigator.pop(context, true),
            style: TextButton.styleFrom(foregroundColor: Colors.red),
            child: const Text('Remover'),
          ),
        ],
      ),
    );

    if (confirmed == true) {
      try {
        // Remove do Firestore
        if (event.firestoreId != null) {
          await FirebaseFirestore.instance.collection('calendar_events').doc(event.firestoreId).delete();
        }

        // Remove do SQLite
        if (event.id != null) {
          try { await dbService.deleteCalendarEvent(event.id!, widget.userId); } catch (_) {}
        }

        _loadEvents();
        if (mounted) ScaffoldMessenger.of(context).showSnackBar(const SnackBar(content: Text('Evento removido.')));
      } catch (e) {
        print("Erro ao deletar: $e");
      }
    }
  }

  void _handleFilterDateSelected(DateTime? date) {
    setState(() {
      _selectedFilterDate = date == null ? null : DateUtils.dateOnly(date);
    });
  }

  @override
  Widget build(BuildContext context) {
    final List<CalendarEvent> filteredEvents;
    final filterDate = _selectedFilterDate;

    if (filterDate == null) {
      filteredEvents = _events;
    } else {
      filteredEvents = _events.where((e) => DateUtils.isSameDay(e.when, filterDate)).toList();
    }
    // Ordena por data
    filteredEvents.sort((a, b) => a.when.compareTo(b.when));

    return Scaffold(
      body: SafeArea(
        child: Padding(
          padding: const EdgeInsets.all(16),
          child: Column(
            crossAxisAlignment: CrossAxisAlignment.stretch,
            children: [
              AdaptiveHeader(
                onEventCreated: _handleEventCreated,
                onFilterDateSelected: _handleFilterDateSelected,
              ),
              if (filterDate != null)
                Padding(
                  padding: const EdgeInsets.only(top: 12.0),
                  child: _FilterChip(
                    date: filterDate,
                    onCleared: () => _handleFilterDateSelected(null),
                  ),
                ),
              const SizedBox(height: 12),
              Expanded(
                child: _isLoading
                    ? const Center(child: CircularProgressIndicator())
                    : EventList(
                  events: filteredEvents,
                  hasFilter: filterDate != null,
                  onEditEvent: _handleEditEvent,
                  onDeleteEvent: _handleDeleteEvent,
                ),
              ),
            ],
          ),
        ),
      ),
    );
  }
}

// ===================== COMPONENTES DE UI (Mantidos) =====================

class AdaptiveHeader extends StatefulWidget {
  const AdaptiveHeader({super.key, required this.onEventCreated, required this.onFilterDateSelected});
  final ValueChanged<CalendarEvent> onEventCreated;
  final ValueChanged<DateTime?> onFilterDateSelected;

  @override
  State<AdaptiveHeader> createState() => _AdaptiveHeaderState();
}

class _AdaptiveHeaderState extends State<AdaptiveHeader> {
  bool _fitsInline = true;
  void _onMiddleDecision(bool fitsNow) {
    if (mounted && _fitsInline != fitsNow) setState(() => _fitsInline = fitsNow);
  }

  @override
  Widget build(BuildContext context) {
    return LayoutBuilder(builder: (_, constraints) {
      return Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          Padding(
            padding: const EdgeInsets.symmetric(horizontal: 10),
            child: Row(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                const TodayDate(),
                const SizedBox(width: 16),
                Expanded(child: _MiddleSlot(onDecision: _onMiddleDecision)),
                const SizedBox(width: 16),
                _ButtonsRow(onEventCreated: widget.onEventCreated, onFilterDateSelected: widget.onFilterDateSelected),
              ],
            ),
          ),
          if (!_fitsInline) ...const [SizedBox(height: 12), CalendarBody(compact: false, shrinkToFitWidth: true)],
        ],
      );
    });
  }
}

class _MiddleSlot extends StatelessWidget {
  const _MiddleSlot({required this.onDecision});
  final ValueChanged<bool> onDecision;
  @override
  Widget build(BuildContext context) {
    return LayoutBuilder(builder: (_, constraints) {
      final fits = constraints.maxWidth >= 350; // Largura mínima estimada
      WidgetsBinding.instance.addPostFrameCallback((_) => onDecision(fits));
      return fits ? const Align(alignment: Alignment.topCenter, child: CalendarBody(compact: true)) : const SizedBox.shrink();
    });
  }
}

class _ButtonsRow extends StatelessWidget {
  const _ButtonsRow({required this.onEventCreated, required this.onFilterDateSelected});
  final ValueChanged<CalendarEvent> onEventCreated;
  final ValueChanged<DateTime?> onFilterDateSelected;

  @override
  Widget build(BuildContext context) {
    return Row(
      mainAxisSize: MainAxisSize.min,
      children: [
        RoundAddButton(onEventCreated: onEventCreated),
        const SizedBox(width: 8),
        RoundCalendarButton(onFilterDateSelected: onFilterDateSelected),
      ],
    );
  }
}

class RoundAddButton extends StatelessWidget {
  const RoundAddButton({super.key, required this.onEventCreated});
  final ValueChanged<CalendarEvent> onEventCreated;
  @override
  Widget build(BuildContext context) {
    return IconButton(
      onPressed: () async {
        final CalendarEvent? created = await showDialog<CalendarEvent>(
          context: context,
          builder: (context) => const _AddEventDialog(),
        );
        if (created != null) onEventCreated(created);
      },
      icon: const Icon(Icons.add, color: Colors.white),
      style: IconButton.styleFrom(backgroundColor: Theme.of(context).colorScheme.primary),
    );
  }
}

class RoundCalendarButton extends StatelessWidget {
  const RoundCalendarButton({super.key, required this.onFilterDateSelected});
  final ValueChanged<DateTime?> onFilterDateSelected;
  @override
  Widget build(BuildContext context) {
    return IconButton(
      onPressed: () async {
        final DateTime? picked = await showDatePicker(
          context: context,
          initialDate: DateTime.now(),
          firstDate: DateTime(2020),
          lastDate: DateTime(2030),
          locale: const Locale('pt', 'BR'),
        );
        onFilterDateSelected(picked);
      },
      icon: const Icon(Icons.filter_list, color: Colors.white),
      style: IconButton.styleFrom(backgroundColor: Theme.of(context).colorScheme.primary),
    );
  }
}

class TodayDate extends StatelessWidget {
  const TodayDate({super.key});
  @override
  Widget build(BuildContext context) {
    final now = DateTime.now();
    return Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        Text(DateFormat('EEEE', 'pt_BR').format(now).toUpperCase(), style: Theme.of(context).textTheme.titleMedium),
        Text(DateFormat("d 'de' MMM", 'pt_BR').format(now), style: Theme.of(context).textTheme.bodyMedium),
      ],
    );
  }
}

class CalendarBody extends StatelessWidget {
  const CalendarBody({super.key, this.compact = false, this.shrinkToFitWidth = false});
  final bool compact;
  final bool shrinkToFitWidth;

  @override
  Widget build(BuildContext context) {
    final now = DateTime.now();
    final startOfWeek = now.subtract(Duration(days: now.weekday - 1));
    final weekDays = List.generate(7, (i) => startOfWeek.add(Duration(days: i)));
    final theme = Theme.of(context);

    return Row(
      mainAxisAlignment: MainAxisAlignment.spaceAround,
      children: weekDays.map((date) {
        final isToday = DateUtils.isSameDay(date, now);
        return Container(
          padding: const EdgeInsets.all(8),
          decoration: isToday ? BoxDecoration(color: theme.colorScheme.primaryContainer, borderRadius: BorderRadius.circular(8)) : null,
          child: Column(
            children: [
              Text(DateFormat('EEE', 'pt_BR').format(date), style: TextStyle(fontSize: compact ? 12 : 14, fontWeight: isToday ? FontWeight.bold : FontWeight.normal)),
              Text('${date.day}', style: TextStyle(fontSize: compact ? 14 : 16, fontWeight: isToday ? FontWeight.bold : FontWeight.normal)),
            ],
          ),
        );
      }).toList(),
    );
  }
}

class _AddEventDialog extends StatefulWidget {
  final CalendarEvent? eventToEdit;
  const _AddEventDialog({this.eventToEdit});
  @override
  State<_AddEventDialog> createState() => _AddEventDialogState();
}

class _AddEventDialogState extends State<_AddEventDialog> {
  final _titleCtrl = TextEditingController();
  final _descCtrl = TextEditingController();
  DateTime? _selectedDateTime;

  @override
  void initState() {
    super.initState();
    _titleCtrl.text = widget.eventToEdit?.title ?? '';
    _descCtrl.text = widget.eventToEdit?.description ?? '';
    _selectedDateTime = widget.eventToEdit?.when;
  }

  @override
  Widget build(BuildContext context) {
    return AlertDialog(
      title: Text(widget.eventToEdit == null ? 'Novo Evento' : 'Editar Evento'),
      content: Column(
        mainAxisSize: MainAxisSize.min,
        children: [
          TextField(controller: _titleCtrl, decoration: const InputDecoration(labelText: 'Título')),
          TextField(controller: _descCtrl, decoration: const InputDecoration(labelText: 'Descrição')),
          const SizedBox(height: 10),
          ListTile(
            title: Text(_selectedDateTime == null ? 'Selecionar Data/Hora' : DateFormat('dd/MM/yyyy HH:mm').format(_selectedDateTime!)),
            trailing: const Icon(Icons.calendar_today),
            onTap: () async {
              final date = await showDatePicker(context: context, initialDate: DateTime.now(), firstDate: DateTime(2020), lastDate: DateTime(2030));
              if (date != null) {
                final time = await showTimePicker(context: context, initialTime: TimeOfDay.now());
                if (time != null) {
                  setState(() => _selectedDateTime = DateTime(date.year, date.month, date.day, time.hour, time.minute));
                }
              }
            },
          ),
        ],
      ),
      actions: [
        TextButton(onPressed: () => Navigator.pop(context), child: const Text('Cancelar')),
        ElevatedButton(
          onPressed: () {
            if (_titleCtrl.text.isNotEmpty && _selectedDateTime != null) {
              Navigator.pop(context, CalendarEvent(
                title: _titleCtrl.text,
                description: _descCtrl.text.isEmpty ? null : _descCtrl.text,
                when: _selectedDateTime!,
              ));
            }
          },
          child: const Text('Salvar'),
        ),
      ],
    );
  }
}

class EventList extends StatelessWidget {
  final List<CalendarEvent> events;
  final bool hasFilter;
  final Function(CalendarEvent) onEditEvent;
  final Function(CalendarEvent) onDeleteEvent;

  const EventList({super.key, required this.events, required this.hasFilter, required this.onEditEvent, required this.onDeleteEvent});

  @override
  Widget build(BuildContext context) {
    if (events.isEmpty) return Center(child: Text(hasFilter ? 'Sem eventos nesta data.' : 'Nenhum evento.'));

    return ListView.builder(
      itemCount: events.length,
      itemBuilder: (context, index) {
        final e = events[index];
        return Card(
          margin: const EdgeInsets.symmetric(vertical: 4),
          child: ListTile(
            leading: const Icon(Icons.event),
            title: Text(e.title, style: const TextStyle(fontWeight: FontWeight.bold)),
            subtitle: Text("${DateFormat('dd/MM HH:mm').format(e.when)}${e.description != null ? '\n${e.description}' : ''}"),
            trailing: PopupMenuButton(
              onSelected: (v) => v == 'edit' ? onEditEvent(e) : onDeleteEvent(e),
              itemBuilder: (context) => [
                const PopupMenuItem(value: 'edit', child: Text('Editar')),
                const PopupMenuItem(value: 'delete', child: Text('Remover', style: TextStyle(color: Colors.red))),
              ],
            ),
          ),
        );
      },
    );
  }
}

class _FilterChip extends StatelessWidget {
  final DateTime date;
  final VoidCallback onCleared;
  const _FilterChip({required this.date, required this.onCleared});

  @override
  Widget build(BuildContext context) {
    return Chip(
      label: Text('Filtro: ${DateFormat('dd/MM/yyyy').format(date)}'),
      deleteIcon: const Icon(Icons.close),
      onDeleted: onCleared,
    );
  }
}