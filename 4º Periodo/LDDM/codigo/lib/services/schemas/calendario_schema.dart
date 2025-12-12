import 'package:sqflite/sqflite.dart';

class CalendarioSchema {
  static Future<void> createTables(Database db) async {
    // CORREÇÃO: Adicionado IF NOT EXISTS para evitar crash se a tabela já existir
    await db.execute('''
      CREATE TABLE IF NOT EXISTS calendar_events(
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        id_usuario INTEGER NOT NULL,
        title TEXT NOT NULL,
        description TEXT,
        whenTimestamp INTEGER NOT NULL, -- Armazena DateTime como milissegundos desde a epoch
        FOREIGN KEY (id_usuario) REFERENCES usuario(id_usuario) ON DELETE CASCADE
      )
    ''');
  }

  static Future<void> upgradeTables(Database db, int oldVersion, int newVersion) async {
    if (oldVersion < 6) {
      // Aqui já estava correto com IF NOT EXISTS, mantivemos a segurança.
      await db.execute('''
        CREATE TABLE IF NOT EXISTS calendar_events(
          id INTEGER PRIMARY KEY AUTOINCREMENT,
          id_usuario INTEGER NOT NULL,
          title TEXT NOT NULL,
          description TEXT,
          whenTimestamp INTEGER NOT NULL,
          FOREIGN KEY (id_usuario) REFERENCES usuario(id_usuario) ON DELETE CASCADE
        )
      ''');
    }
  }
}