// Requisitos no pubspec.yaml:
//   sqflite: ^2.0.0
//   path_provider: ^2.0.0
//   path: ^1.8.0
//   firebase_core: ^2.0.0
//   cloud_firestore: ^4.0.0
//
// Certifique-se de inicializar o Firebase no main() antes de executar a migração:
// WidgetsFlutterBinding.ensureInitialized();
// await Firebase.initializeApp();

import 'dart:io';
import 'package:path/path.dart' as p;
import 'package:path_provider/path_provider.dart';
import 'package:sqflite/sqflite.dart';
import 'package:cloud_firestore/cloud_firestore.dart';

class SqliteToFirestoreMigration {
  final FirebaseFirestore firestore = FirebaseFirestore.instance;

  Future<Database> _openSqliteDb({String filename = 'meubanco.db'}) async {
    // Ajuste se seu DB estiver em outro local
    try {
      final documentsDir = await getApplicationDocumentsDirectory();
      final dbPath = p.join(documentsDir.path, filename);
      if (!File(dbPath).existsSync()) {
        // alternativa: getDatabasesPath() se preferir
        final databasesPath = await getDatabasesPath();
        final altPath = p.join(databasesPath, filename);
        if (File(altPath).existsSync()) {
          return openDatabase(altPath, readOnly: true);
        } else {
          // Se nenhum existe, tentamos abrir o path padrão (irá criar se permitir)
          return openDatabase(altPath, readOnly: true);
        }
      }
      return openDatabase(dbPath, readOnly: true);
    } catch (e) {
      // Se houver qualquer problema, tente a abordagem fallback com getDatabasesPath()
      final databasesPath = await getDatabasesPath();
      final fallback = p.join(databasesPath, filename);
      return openDatabase(fallback, readOnly: true);
    }
  }

  Future<void> migrateSQLiteToFirestore() async {
    final db = await _openSqliteDb();
    try {
      // 1) Migrar usuarios -> coleção 'usuarios'
      await _migrateUsuarios(db);

      // 2) Migrar calendar_events -> coleção 'calendar_events'
      await _migrateCalendarEvents(db);

      // 3) Migrar chats -> coleção 'chats' (+ subcoleções files e messages)
      await _migrateChatsAndSubcollections(db);

      // 4) Migrar pomodoro_sessions -> coleção 'pomodoro_sessions'
      await _migratePomodoroSessions(db);

      // 5) Migrar tarefas -> coleção 'tarefas'
      await _migrateTarefas(db);

      print('Migração concluída com sucesso.');
    } catch (e, st) {
      print('Erro durante migração: $e\n$st');
      rethrow;
    } finally {
      await db.close();
    }
  }

  // Helper: write em batches com limite de 500 ops
  Future<void> _writeDocsInBatches(String collectionPath, List<Map<String, dynamic>> docs, {bool preserveId = true}) async {
    const int batchSize = 500;
    for (var i = 0; i < docs.length; i += batchSize) {
      final batch = firestore.batch();
      final end = (i + batchSize < docs.length) ? i + batchSize : docs.length;
      for (var j = i; j < end; j++) {
        final doc = Map<String, dynamic>.from(docs[j]);
        final id = preserveId && doc.containsKey('id') ? doc['id']?.toString() : null;
        if (id != null && id.isNotEmpty) {
          final ref = firestore.collection(collectionPath).doc(id);
          doc.remove('id');
          batch.set(ref, doc);
        } else {
          final ref = firestore.collection(collectionPath).doc();
          batch.set(ref, doc);
        }
      }
      await batch.commit();
      print('Committed batch ${i ~/ batchSize + 1} to $collectionPath');
    }
  }

  // ---------- USERS ----------
  Future<void> _migrateUsuarios(Database db) async {
    final rows = await db.query('usuario');
    if (rows.isEmpty) {
      print('Nenhum usuário encontrado para migrar.');
      return;
    }

    final docs = rows.map((r) {
      // ATENÇÃO: senha em texto plano não é seguro. Avalie migrar para Firebase Auth via Admin SDK.
      return {
        'id': r['id_usuario']?.toString(),
        'nome': r['nome'],
        'senha': r['senha'], // cuidado!
        'email': r['email'],
        'telefone': r['telefone'],
      };
    }).toList();

    await _writeDocsInBatches('usuarios', docs, preserveId: true);
    print('Usuarios migrados: ${docs.length}');
  }

  // ---------- CALENDAR EVENTS ----------
  Future<void> _migrateCalendarEvents(Database db) async {
    final rows = await db.query('calendar_events');
    if (rows.isEmpty) {
      print('Nenhum calendar event encontrado.');
      return;
    }

    final docs = rows.map((r) {
      final whenMillis = r['whenTimestamp'] is int
          ? r['whenTimestamp'] as int
          : (r['whenTimestamp'] != null ? int.tryParse(r['whenTimestamp'].toString()) : null);

      final whenValue = whenMillis != null
          ? Timestamp.fromMillisecondsSinceEpoch(whenMillis)
          : FieldValue.serverTimestamp();

      return {
        'id': r['id']?.toString(),
        'id_usuario': r['id_usuario']?.toString(),
        'title': r['title'],
        'description': r['description'],
        // Convertendo milissegundos para Timestamp do Firestore
        'when': whenValue,
      };
    }).toList();

    await _writeDocsInBatches('calendar_events', docs, preserveId: true);
    print('Calendar events migrados: ${docs.length}');
  }

  // ---------- CHATS (+ FILES, MESSAGES como subcoleções) ----------
  Future<void> _migrateChatsAndSubcollections(Database db) async {
    // Ler chats
    final chats = await db.query('chats');
    if (chats.isEmpty) {
      print('Nenhum chat encontrado.');
      return;
    }

    // Escrever chats (preservando id string)
    final chatDocs = chats.map((r) {
      return {
        'id': r['id']?.toString(),
        'id_usuario': r['id_usuario']?.toString(),
        'title': r['title'],
        'subject': r['subject'],
      };
    }).toList();
    await _writeDocsInBatches('chats', chatDocs, preserveId: true);
    print('Chats migrados: ${chatDocs.length}');

    // Migrar chat_files e chat_messages para subcoleções
    // chat_files -> chats/{chatId}/files
    final filesRows = await db.query('chat_files');
    if (filesRows.isNotEmpty) {
      // Agrupa por chatId para reduzir chamadas
      final Map<String, List<Map<String, dynamic>>> groupedFiles = {};
      for (final r in filesRows) {
        final chatId = r['chatId']?.toString() ?? 'unknown';
        groupedFiles.putIfAbsent(chatId, () => []).add({
          'id': r['id']?.toString(),
          'name': r['name'],
          'type': r['type'],
        });
      }

      // Para cada chat, gravar em batches (cada subcoleção é um caminho distinto)
      for (final entry in groupedFiles.entries) {
        final chatId = entry.key;
        final docs = entry.value;
        const batchSize = 500;
        for (var i = 0; i < docs.length; i += batchSize) {
          final batch = firestore.batch();
          final end = (i + batchSize < docs.length) ? i + batchSize : docs.length;
          for (var j = i; j < end; j++) {
            final doc = docs[j];
            final id = doc['id']?.toString();
            final collectionRef = firestore.collection('chats').doc(chatId).collection('files');
            final docRef = (id != null && id.isNotEmpty) ? collectionRef.doc(id) : collectionRef.doc();
            final copy = Map<String, dynamic>.from(doc);
            copy.remove('id');
            batch.set(docRef, copy);
          }
          await batch.commit();
        }
      }
      print('Chat files migrados por chat: ${filesRows.length}');
    }

    // chat_messages -> chats/{chatId}/messages
    final messagesRows = await db.query('chat_messages');
    if (messagesRows.isNotEmpty) {
      final Map<String, List<Map<String, dynamic>>> groupedMessages = {};
      for (final r in messagesRows) {
        final chatId = r['chatId']?.toString() ?? 'unknown';
        final timestampMillis = r['timestamp'] is int
            ? r['timestamp'] as int
            : (r['timestamp'] != null ? int.tryParse(r['timestamp'].toString()) : null);

        groupedMessages.putIfAbsent(chatId, () => []).add({
          'id': r['id']?.toString(),
          'text': r['text'],
          'isSentByMe': (r['isSentByMe'] == 1) ? true : false,
          'timestamp': timestampMillis != null ? Timestamp.fromMillisecondsSinceEpoch(timestampMillis) : FieldValue.serverTimestamp(),
        });
      }

      // escrever por chat
      for (final entry in groupedMessages.entries) {
        final chatId = entry.key;
        final docs = entry.value;
        const batchSize = 500;
        for (var i = 0; i < docs.length; i += batchSize) {
          final batch = firestore.batch();
          final end = (i + batchSize < docs.length) ? i + batchSize : docs.length;
          for (var j = i; j < end; j++) {
            final doc = docs[j];
            final id = doc['id']?.toString();
            final collectionRef = firestore.collection('chats').doc(chatId).collection('messages');
            final docRef = (id != null && id.isNotEmpty) ? collectionRef.doc(id) : collectionRef.doc();
            final copy = Map<String, dynamic>.from(doc);
            copy.remove('id');
            batch.set(docRef, copy);
          }
          await batch.commit();
        }
      }
      print('Chat messages migrados: ${messagesRows.length}');
    }
  }

  // ---------- POMODORO SESSIONS ----------
  Future<void> _migratePomodoroSessions(Database db) async {
    // Tabela pomodoro_sessions
    final rows = await db.query('pomodoro_sessions');
    if (rows.isEmpty) {
      print('Nenhuma pomodoro_sessions encontrada.');
      return;
    }

    final docs = rows.map((r) {
      final tsMillis = r['timestamp'] is int
          ? r['timestamp'] as int
          : (r['timestamp'] != null ? int.tryParse(r['timestamp'].toString()) : null);

      final tsValue = tsMillis != null ? Timestamp.fromMillisecondsSinceEpoch(tsMillis) : FieldValue.serverTimestamp();

      return {
        'id': r['id']?.toString(),
        'id_usuario': r['id_usuario']?.toString(),
        'chatId': r['chatId']?.toString(),
        'chatTitle': r['chatTitle'],
        'durationMinutes': r['durationMinutes'],
        'timestamp': tsValue,
      };
    }).toList();

    await _writeDocsInBatches('pomodoro_sessions', docs, preserveId: true);
    print('Pomodoro sessions migradas: ${docs.length}');
  }

  // ---------- TAREFAS ----------
  Future<void> _migrateTarefas(Database db) async {
    final rows = await db.query('tarefas');
    if (rows.isEmpty) {
      print('Nenhuma tarefa encontrada.');
      return;
    }

    final docs = rows.map((r) {
      // dueDate era TEXT — pode ser null ou ISO string; tentar parse para Timestamp
      Timestamp? dueTimestamp;
      if (r['dueDate'] != null) {
        try {
          final parsed = DateTime.tryParse(r['dueDate'].toString());
          if (parsed != null) dueTimestamp = Timestamp.fromDate(parsed);
        } catch (_) {
          dueTimestamp = null;
        }
      }

      return {
        'id': r['id']?.toString(),
        'id_usuario': r['id_usuario']?.toString(),
        'title': r['title'],
        'isDone': (r['isDone'] == 1) ? true : false,
        'dueDate': dueTimestamp ?? null,
      };
    }).toList();

    await _writeDocsInBatches('tarefas', docs, preserveId: true);
    print('Tarefas migradas: ${docs.length}');
  }
}
