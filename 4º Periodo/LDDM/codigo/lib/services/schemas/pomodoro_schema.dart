import 'package:sqflite/sqflite.dart';

class PomodoroSchema {
  // Função para criar a tabela de pomodoro_sessions (para novas instalações)
  static Future<void> createTables(Database db) async {
    // CORREÇÃO: Adicionado IF NOT EXISTS
    await db.execute('''
      CREATE TABLE IF NOT EXISTS pomodoro_sessions(
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        id_usuario INTEGER NOT NULL,
        chatId TEXT,
        chatTitle TEXT,
        durationMinutes INTEGER NOT NULL,
        timestamp INTEGER NOT NULL,
        FOREIGN KEY (id_usuario) REFERENCES usuario(id_usuario) ON DELETE CASCADE
      )
    ''');
  }

  // Função para atualizar a tabela de pomodoro_sessions (para usuários existentes)
  static Future<void> upgradeTables(
      Database db,
      int oldVersion,
      int newVersion,
      ) async {
    if (oldVersion < 5) {
      // Verifica se a tabela já existe
      var tables = await db.rawQuery(
        "SELECT name FROM sqlite_master WHERE type='table' AND name='pomodoro_sessions'",
      );

      if (tables.isEmpty) {
        // Tabela não existe, criar do zero
        await createTables(db);
      } else {
        // Tabela existe, precisa adicionar id_usuario
        // Recriar a tabela com a nova estrutura

        // CORREÇÃO: Garante que a tabela temporária não existe antes de começar
        await db.execute('DROP TABLE IF EXISTS pomodoro_sessions_new');

        await db.execute('''
          CREATE TABLE pomodoro_sessions_new(
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            id_usuario INTEGER NOT NULL,
            chatId TEXT,
            chatTitle TEXT,
            durationMinutes INTEGER NOT NULL,
            timestamp INTEGER NOT NULL,
            FOREIGN KEY (id_usuario) REFERENCES usuario(id_usuario) ON DELETE CASCADE
          )
        ''');

        // Copiar dados antigos (atribuindo id_usuario = 1)
        try {
          await db.execute('''
            INSERT INTO pomodoro_sessions_new (id, id_usuario, chatId, chatTitle, durationMinutes, timestamp)
            SELECT id, 1, chatId, chatTitle, durationMinutes, timestamp FROM pomodoro_sessions
          ''');
        } catch (e) {
          print("Erro ao migrar dados de pomodoro: $e");
        }

        // CORREÇÃO: Drop seguro
        await db.execute('DROP TABLE IF EXISTS pomodoro_sessions');
        await db.execute(
          'ALTER TABLE pomodoro_sessions_new RENAME TO pomodoro_sessions',
        );
      }
    }
  }
}