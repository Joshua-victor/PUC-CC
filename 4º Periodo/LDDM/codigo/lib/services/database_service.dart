// lib/services/database_service.dart

import 'package:sqflite/sqflite.dart';
import 'package:path/path.dart';
import '../pages/3_home/home_screen.dart'; // Precisa disso para ChatSession
import '../pages/6_chat/chat_screen.dart'; // Precisa disso para ChatMessage, DocumentFile
import '../shared/utils/crypto_helper.dart';
import '../pages/4_calendar/calendar_screen.dart';

// --- Importar os schemas ---
import 'schemas/chat_schema.dart';
import 'schemas/user_schema.dart';
import 'schemas/todolist_schema.dart';
import 'schemas/pomodoro_schema.dart';
import 'schemas/calendario_schema.dart';
// ------------------------------------------

class DatabaseService {
  static final DatabaseService _instance = DatabaseService._internal();
  factory DatabaseService() => _instance;
  DatabaseService._internal();

  static Database? _database;

  Future<Database> get database async {
    if (_database != null) return _database!;
    _database = await _initDB();
    return _database!;
  }

  Future<Database> _initDB() async {
    final dbPath = await getDatabasesPath();
    final path = join(dbPath, 'smartstudy.db');
    return await openDatabase(
      path,
      version: 6,
      onCreate: _onCreate,
      onUpgrade: _onUpgrade,
    );
  }

  Future<void> _onCreate(Database db, int version) async {
    await UserSchema.createTables(db);
    await ChatSchema.createTables(db);
    await TodoListSchema.createTables(db);
    await PomodoroSchema.createTables(db);
    await CalendarioSchema.createTables(db);
  }

  Future<void> _onUpgrade(Database db, int oldVersion, int newVersion) async {
    await UserSchema.upgradeTables(db, oldVersion, newVersion);
    await ChatSchema.upgradeTables(db, oldVersion, newVersion);
    await TodoListSchema.upgradeTables(db, oldVersion, newVersion);
    await PomodoroSchema.upgradeTables(db, oldVersion, newVersion);
    await CalendarioSchema.upgradeTables(db, oldVersion, newVersion);
  }

  // --- MÉTODOS DE CHAT ---
  Future<void> createChat(ChatSession chat, int idUsuario) async {
    final db = await database;
    Map<String, dynamic> chatMap = chat.toMap();
    chatMap['id_usuario'] = idUsuario;
    await db.insert(
      'chats',
      chatMap,
      conflictAlgorithm: ConflictAlgorithm.replace,
    );
  }

  Future<List<ChatSession>> getChats(int idUsuario) async {
    final db = await database;
    final List<Map<String, dynamic>> maps = await db.query(
      'chats',
      where: 'id_usuario = ?',
      whereArgs: [idUsuario],
    );
    return List.generate(maps.length, (i) {
      if (maps[i]['id'] != null && maps[i]['title'] != null && maps[i]['subject'] != null) {
        // ChatSession.fromMap já trata a conversão de ID
        return ChatSession.fromMap(maps[i]);
      } else {
        print("Erro: Mapa de Chat inválido encontrado no DB: ${maps[i]}");
        return ChatSession(id: 'invalid_${i}', title: 'Chat Inválido', subject: 'Erro');
      }
    });
  }

  Future<void> updateChat(ChatSession chat, int idUsuario) async {
    final db = await database;
    Map<String, dynamic> chatMap = chat.toMap();
    chatMap['id_usuario'] = idUsuario;
    await db.update(
      'chats',
      chatMap,
      where: 'id = ? AND id_usuario = ?',
      whereArgs: [chat.id, idUsuario],
    );
  }

  Future<void> deleteChat(String id, int idUsuario) async {
    final db = await database;
    await db.delete(
      'chats',
      where: 'id = ? AND id_usuario = ?',
      whereArgs: [id, idUsuario],
    );
  }

  // --- MÉTODOS DE FILE E MESSAGE ---
  Future<void> addFileToChat(String chatId, DocumentFile file) async {
    final db = await database;
    await db.insert('chat_files', {
      'chatId': chatId,
      'name': file.name,
      'type': file.type,
    });
  }

  Future<List<DocumentFile>> getFilesForChat(String chatId) async {
    final db = await database;
    final List<Map<String, dynamic>> maps = await db.query(
      'chat_files',
      where: 'chatId = ?',
      whereArgs: [chatId],
    );
    return List.generate(maps.length, (i) {
      if (maps[i]['id'] != null && maps[i]['name'] != null && maps[i]['type'] != null) {
        return DocumentFile(
          // CORREÇÃO 1: Converte o ID (int) do SQLite para String
          id: maps[i]['id'].toString(),
          name: maps[i]['name'],
          type: maps[i]['type'],
        );
      } else {
        print("Erro: Mapa de DocumentFile inválido: ${maps[i]}");
        // CORREÇÃO 2: Passa string '-1' em vez de int -1
        return DocumentFile(id: '-1', name: "Arquivo Inválido", type: "err");
      }
    });
  }

  // CORREÇÃO 3: Recebe String, mas tenta converter para int para deletar do SQLite
  Future<void> deleteFile(String id) async {
    final db = await database;
    // O SQLite usa IDs inteiros. Se o ID for uma string numérica (ex: "1"), converte.
    // Se for um ID do Firestore (ex: "abcde"), não existe no SQLite, então ignora.
    final int? localId = int.tryParse(id);
    if (localId != null) {
      await db.delete('chat_files', where: 'id = ?', whereArgs: [localId]);
    }
  }

  Future<void> addMessage(String chatId, ChatMessage message) async {
    final db = await database;
    await db.insert('chat_messages', {
      'chatId': chatId,
      'text': message.text,
      'isSentByMe': message.isSentByMe ? 1 : 0,
      'timestamp': DateTime.now().millisecondsSinceEpoch,
    });
  }

  Future<List<ChatMessage>> getMessages(String chatId) async {
    final db = await database;
    final List<Map<String, dynamic>> maps = await db.query(
      'chat_messages',
      where: 'chatId = ?',
      whereArgs: [chatId],
      orderBy: 'timestamp ASC', // Localmente mantemos ASC, a tela inverte se necessário
    );

    return List.generate(maps.length, (i) {
      if (maps[i]['text'] != null && maps[i]['isSentByMe'] != null) {
        return ChatMessage(
          text: maps[i]['text'],
          isSentByMe: maps[i]['isSentByMe'] == 1,
          isLoading: false,
        );
      } else {
        print("Erro: Mapa de ChatMessage inválido: ${maps[i]}");
        return ChatMessage(text: "Mensagem Inválida", isSentByMe: false);
      }
    });
  }

  // --- MÉTODOS DE USUÁRIO ---
  Future<int> createUser(
      String nome,
      String senha,
      String email,
      String telefone,
      ) async {
    final db = await database;

    final usuarios = await db.query(
      'usuario',
      where: 'email = ?',
      whereArgs: [email],
    );

    if (usuarios.isNotEmpty) {
      throw Exception('Este e-mail já está cadastrado.');
    }

    return await db.insert('usuario', {
      'nome': nome,
      'senha': senha,
      'email': email,
      'telefone': telefone,
    });
  }

  Future<Map<String, dynamic>?> getUserByCredentials(
      String nome,
      String senha,
      ) async {
    final db = await database;
    final hash = CryptoHelper.hashPassword(senha);

    final List<Map<String, dynamic>> result = await db.query(
      'usuario',
      where: 'nome = ? AND senha = ?',
      whereArgs: [nome, hash],
    );

    return result.isNotEmpty ? result.first : null;
  }

  Future<Map<String, dynamic>?> getUserById(int idUsuario) async {
    final db = await database;
    final List<Map<String, dynamic>> result = await db.query(
      'usuario',
      where: 'id_usuario = ?',
      whereArgs: [idUsuario],
    );
    return result.isNotEmpty ? result.first : null;
  }

  Future<int> updateUser({
    required int idUsuario,
    String? newEmail,
    String? newPhone,
  }) async {
    final db = await database;
    final Map<String, dynamic> values = {};

    if (newEmail != null) {
      values['email'] = newEmail.trim();
    }
    if (newPhone != null) {
      values['telefone'] = newPhone.trim();
    }

    return await db.update(
      'usuario',
      values,
      where: 'id_usuario = ?',
      whereArgs: [idUsuario],
    );
  }

  // --- MÉTODOS DE TAREFAS ---
  Future<int> createTarefa(int idUsuario, String title, String? dueDate) async {
    final db = await database;
    return await db.insert('tarefas', {
      'id_usuario': idUsuario,
      'title': title,
      'isDone': 0,
      'dueDate': dueDate,
    });
  }

  Future<List<Map<String, dynamic>>> getTarefasByUser(int idUsuario) async {
    final db = await database;
    return await db.query(
      'tarefas',
      where: 'id_usuario = ?',
      whereArgs: [idUsuario],
      orderBy: 'dueDate ASC',
    );
  }

  Future<void> updateTarefa(int id, bool isDone) async {
    final db = await database;
    await db.update(
      'tarefas',
      {'isDone': isDone ? 1 : 0},
      where: 'id = ?',
      whereArgs: [id],
    );
  }

  Future<void> updateTarefaCompleta(int id, String title, String? dueDate, bool isDone) async {
    final db = await database;
    await db.update(
      'tarefas',
      {'title': title, 'dueDate': dueDate, 'isDone': isDone ? 1 : 0},
      where: 'id = ?',
      whereArgs: [id],
    );
  }

  Future<void> deleteTarefa(int id) async {
    final db = await database;
    await db.delete('tarefas', where: 'id = ?', whereArgs: [id]);
  }

  // --- MÉTODOS DE POMODORO ---
  Future<int> createPomodoroSession({
    required int idUsuario,
    String? chatId,
    String? chatTitle,
    required int durationMinutes,
  }) async {
    final db = await database;
    return await db.insert('pomodoro_sessions', {
      'id_usuario': idUsuario,
      'chatId': chatId,
      'chatTitle': chatTitle,
      'durationMinutes': durationMinutes,
      'timestamp': DateTime.now().millisecondsSinceEpoch,
    });
  }

  Future<List<Map<String, dynamic>>> getPomodoroSessionsByUser(
      int idUsuario,
      ) async {
    final db = await database;
    return await db.query(
      'pomodoro_sessions',
      where: 'id_usuario = ?',
      whereArgs: [idUsuario],
      orderBy: 'timestamp DESC',
    );
  }

  Future<List<StudyPerformance>> getPerformanceStats(int idUsuario) async {
    final db = await database;
    final List<Map<String, dynamic>> maps = await db.rawQuery('''
      SELECT chatTitle, SUM(durationMinutes) as totalMinutes
      FROM pomodoro_sessions
      WHERE id_usuario = ? AND chatTitle IS NOT NULL AND chatTitle != ''
      GROUP BY chatTitle
      ORDER BY totalMinutes DESC
    ''',
      [idUsuario],
    );

    return List.generate(maps.length, (i) {
      final totalMinutes = maps[i]['totalMinutes'] as int? ?? 0;
      final subject = maps[i]['chatTitle'] as String? ?? 'Geral';
      return StudyPerformance(subject: subject, totalMinutes: totalMinutes);
    });
  }

  // --- MÉTODOS DE CALENDÁRIO ---
  Future<int> createCalendarEvent({
    required int idUsuario,
    required String title,
    String? description,
    required DateTime when,
  }) async {
    final db = await database;
    return await db.insert('calendar_events', {
      'id_usuario': idUsuario,
      'title': title,
      'description': description,
      'whenTimestamp': when.millisecondsSinceEpoch,
    });
  }

  Future<List<CalendarEvent>> getCalendarEventsByUser(int idUsuario) async {
    final db = await database;
    final List<Map<String, dynamic>> maps = await db.query(
      'calendar_events',
      where: 'id_usuario = ?',
      whereArgs: [idUsuario],
      orderBy: 'whenTimestamp ASC',
    );

    return List.generate(maps.length, (i) => CalendarEvent.fromMap(maps[i]));
  }

  Future<void> updateCalendarEvent(int eventId, int idUsuario, CalendarEvent event) async {
    final db = await database;
    await db.update(
      'calendar_events',
      event.toMapForDb(),
      where: 'id = ? AND id_usuario = ?',
      whereArgs: [eventId, idUsuario],
    );
  }

  Future<void> deleteCalendarEvent(int eventId, int idUsuario) async {
    final db = await database;
    await db.delete(
      'calendar_events',
      where: 'id = ? AND id_usuario = ?',
      whereArgs: [eventId, idUsuario],
    );
  }

  // --- MÉTODOS PARA GRÁFICOS E ANÁLISES ---

  /// Retorna dados agregados por data (dia) para gráfico de linha temporal
  /// Cada item contém: date (DateTime), totalMinutes (int)
  Future<List<Map<String, dynamic>>> getDailyStudyData(int idUsuario, {int days = 30}) async {
    final db = await database;

    // Calcula o timestamp de 'days' dias atrás
    final cutoffDate = DateTime.now().subtract(Duration(days: days));
    final cutoffTimestamp = cutoffDate.millisecondsSinceEpoch;

    final List<Map<String, dynamic>> maps = await db.rawQuery('''
      SELECT 
        DATE(timestamp / 1000, 'unixepoch', 'localtime') as dateStr,
        SUM(durationMinutes) as totalMinutes
      FROM pomodoro_sessions
      WHERE id_usuario = ? AND timestamp >= ?
      GROUP BY dateStr
      ORDER BY dateStr ASC
    ''', [idUsuario, cutoffTimestamp]);

    // Converte dateStr para DateTime
    return maps.map((m) {
      return {
        'date': DateTime.parse(m['dateStr'] as String),
        'totalMinutes': m['totalMinutes'] as int,
      };
    }).toList();
  }

  /// Retorna dados agregados por dia da semana (0=domingo, 6=sábado)
  /// Útil para ver quais dias da semana você estuda mais
  Future<List<Map<String, dynamic>>> getWeekdayStudyData(int idUsuario) async {
    final db = await database;

    final List<Map<String, dynamic>> maps = await db.rawQuery('''
      SELECT 
        CAST(strftime('%w', timestamp / 1000, 'unixepoch', 'localtime') AS INTEGER) as weekday,
        SUM(durationMinutes) as totalMinutes,
        COUNT(*) as sessionCount
      FROM pomodoro_sessions
      WHERE id_usuario = ?
      GROUP BY weekday
      ORDER BY weekday ASC
    ''', [idUsuario]);

    return maps;
  }

  /// Retorna estatísticas gerais de estudo
  Future<Map<String, dynamic>> getStudyStatistics(int idUsuario) async {
    final db = await database;

    // Total de minutos estudados
    final totalResult = await db.rawQuery('''
      SELECT 
        COALESCE(SUM(durationMinutes), 0) as totalMinutes,
        COUNT(*) as totalSessions
      FROM pomodoro_sessions
      WHERE id_usuario = ?
    ''', [idUsuario]);

    final totalMinutes = totalResult.first['totalMinutes'] as int;
    final totalSessions = totalResult.first['totalSessions'] as int;

    // Dia com mais estudo
    final bestDayResult = await db.rawQuery('''
      SELECT 
        DATE(timestamp / 1000, 'unixepoch', 'localtime') as dateStr,
        SUM(durationMinutes) as totalMinutes
      FROM pomodoro_sessions
      WHERE id_usuario = ?
      GROUP BY dateStr
      ORDER BY totalMinutes DESC
      LIMIT 1
    ''', [idUsuario]);

    String? bestDay;
    int? bestDayMinutes;
    if (bestDayResult.isNotEmpty) {
      bestDay = bestDayResult.first['dateStr'] as String?;
      bestDayMinutes = bestDayResult.first['totalMinutes'] as int?;
    }

    // Média diária (últimos 30 dias)
    final thirtyDaysAgo = DateTime.now().subtract(const Duration(days: 30)).millisecondsSinceEpoch;
    final avgResult = await db.rawQuery('''
      SELECT 
        AVG(daily_total) as avgMinutes
      FROM (
        SELECT 
          DATE(timestamp / 1000, 'unixepoch', 'localtime') as dateStr,
          SUM(durationMinutes) as daily_total
        FROM pomodoro_sessions
        WHERE id_usuario = ? AND timestamp >= ?
        GROUP BY dateStr
      )
    ''', [idUsuario, thirtyDaysAgo]);

    final avgMinutes = (avgResult.first['avgMinutes'] as num?)?.toDouble() ?? 0.0;

    // Streak (dias consecutivos de estudo)
    final streak = await _calculateStreak(idUsuario);

    return {
      'totalMinutes': totalMinutes,
      'totalSessions': totalSessions,
      'bestDay': bestDay,
      'bestDayMinutes': bestDayMinutes,
      'avgDailyMinutes': avgMinutes,
      'currentStreak': streak,
    };
  }

  /// Calcula quantos dias consecutivos o usuário estudou (até hoje ou até a última pausa)
  Future<int> _calculateStreak(int idUsuario) async {
    final db = await database;

    // Busca todas as datas com estudo, ordenadas de forma decrescente
    final List<Map<String, dynamic>> maps = await db.rawQuery('''
      SELECT DISTINCT DATE(timestamp / 1000, 'unixepoch', 'localtime') as dateStr
      FROM pomodoro_sessions
      WHERE id_usuario = ?
      ORDER BY dateStr DESC
    ''', [idUsuario]);

    if (maps.isEmpty) return 0;

    final today = DateTime.now();

    int streak = 0;
    DateTime? lastDate;

    for (var m in maps) {
      final dateStr = m['dateStr'] as String;
      final date = DateTime.parse(dateStr);

      if (lastDate == null) {
        // Primeira iteração: verifica se estudou hoje ou ontem
        final diffDays = today.difference(date).inDays;
        if (diffDays > 1) {
          // Última sessão foi há mais de 1 dia, streak = 0
          return 0;
        }
        streak = 1;
        lastDate = date;
      } else {
        // Verifica se a data é consecutiva (1 dia antes)
        final diffDays = lastDate.difference(date).inDays;
        if (diffDays == 1) {
          streak++;
          lastDate = date;
        } else {
          // Quebrou a sequência
          break;
        }
      }
    }

    return streak;
  }

  /// Retorna dados para o gráfico de pizza (distribuição por matéria)
  /// Já existe o método getPerformanceStats, mas vamos criar um específico
  /// que também retorna porcentagens calculadas
  Future<List<Map<String, dynamic>>> getSubjectDistribution(int idUsuario) async {
    final stats = await getPerformanceStats(idUsuario);

    if (stats.isEmpty) return [];

    final totalMinutes = stats.fold<int>(0, (sum, s) => sum + s.totalMinutes);

    return stats.map((s) {
      return {
        'subject': s.subject,
        'minutes': s.totalMinutes,
        'percentage': totalMinutes > 0 ? (s.totalMinutes / totalMinutes * 100) : 0.0,
      };
    }).toList();
  }
}

// --- CLASSE StudyPerformance (Sem mudanças) ---
class StudyPerformance {
  final String subject;
  final int totalMinutes;
  StudyPerformance({required this.subject, required this.totalMinutes});

  String get formattedTime {
    if (totalMinutes <= 0) return '0min';
    final int hours = totalMinutes ~/ 60;
    final int minutes = totalMinutes % 60;
    if (hours > 0) {
      if (minutes > 0) {
        return '${hours}h ${minutes}min';
      } else {
        return '${hours}h';
      }
    } else {
      return '${minutes}min';
    }
  }
}