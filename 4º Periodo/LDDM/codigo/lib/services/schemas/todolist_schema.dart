import 'package:sqflite/sqflite.dart';

class TodoListSchema {
  // Função para criar a tabela de tarefas (para novas instalações)
  static Future<void> createTables(Database db) async {
    // CORREÇÃO: Adicionado IF NOT EXISTS
    await db.execute('''
      CREATE TABLE IF NOT EXISTS tarefas(
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        id_usuario INTEGER NOT NULL,
        title TEXT NOT NULL,
        isDone INTEGER NOT NULL DEFAULT 0,
        dueDate TEXT,
        FOREIGN KEY (id_usuario) REFERENCES usuario(id_usuario) ON DELETE CASCADE
      )
    ''');
  }

  // Função para atualizar a tabela de tarefas (para usuários existentes)
  static Future<void> upgradeTables(
      Database db,
      int oldVersion,
      int newVersion,
      ) async {
    if (oldVersion < 5) {
      // Verifica se a tabela já existe
      var tables = await db.rawQuery(
        "SELECT name FROM sqlite_master WHERE type='table' AND name='tarefas'",
      );

      if (tables.isEmpty) {
        // Tabela não existe, criar do zero
        await createTables(db);
      } else {
        // Tabela existe, precisa adicionar id_usuario
        // Recriar a tabela com a nova estrutura

        // CORREÇÃO: Garante que a tabela temporária não existe antes de começar
        await db.execute('DROP TABLE IF EXISTS tarefas_new');

        await db.execute('''
          CREATE TABLE tarefas_new(
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            id_usuario INTEGER NOT NULL,
            title TEXT NOT NULL,
            isDone INTEGER NOT NULL DEFAULT 0,
            dueDate TEXT,
            FOREIGN KEY (id_usuario) REFERENCES usuario(id_usuario) ON DELETE CASCADE
          )
        ''');

        // Copiar dados antigos (atribuindo id_usuario = 1)
        try {
          await db.execute('''
            INSERT INTO tarefas_new (id, id_usuario, title, isDone, dueDate)
            SELECT id, 1, title, isDone, dueDate FROM tarefas
          ''');
        } catch (e) {
          print("Erro ao migrar dados de tarefas: $e");
        }

        // CORREÇÃO: Drop seguro da tabela antiga
        await db.execute('DROP TABLE IF EXISTS tarefas');
        await db.execute('ALTER TABLE tarefas_new RENAME TO tarefas');
      }
    }
  }
}