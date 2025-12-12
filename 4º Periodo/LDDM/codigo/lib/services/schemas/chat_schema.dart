import 'package:sqflite/sqflite.dart';

class ChatSchema {
  // Função para criar as tabelas de Chat (para novas instalações)
  static Future<void> createTables(Database db) async {
    // CORREÇÃO: Adicionado IF NOT EXISTS
    await db.execute('''
      CREATE TABLE IF NOT EXISTS chats(
        id TEXT PRIMARY KEY,
        id_usuario INTEGER NOT NULL,
        title TEXT NOT NULL,
        subject TEXT NOT NULL,
        FOREIGN KEY (id_usuario) REFERENCES usuario(id_usuario) ON DELETE CASCADE
      )
    ''');

    // CORREÇÃO: Adicionado IF NOT EXISTS (Isso resolve o seu erro atual)
    await db.execute('''
      CREATE TABLE IF NOT EXISTS chat_files(
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        chatId TEXT NOT NULL,
        name TEXT NOT NULL,
        type TEXT NOT NULL,
        FOREIGN KEY (chatId) REFERENCES chats (id) ON DELETE CASCADE
      )
    ''');

    // CORREÇÃO: Adicionado IF NOT EXISTS
    await db.execute('''
      CREATE TABLE IF NOT EXISTS chat_messages(
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        chatId TEXT NOT NULL,
        text TEXT NOT NULL,
        isSentByMe INTEGER NOT NULL,
        timestamp INTEGER NOT NULL,
        FOREIGN KEY (chatId) REFERENCES chats (id) ON DELETE CASCADE
      )
    ''');
  }

  // Função para atualizar as tabelas de Chat (para usuários existentes)
  static Future<void> upgradeTables(
      Database db,
      int oldVersion,
      int newVersion,
      ) async {
    if (oldVersion < 2) {
      // Adiciona chat_files se veio da v1
      // CORREÇÃO: Adicionado IF NOT EXISTS
      await db.execute('''
        CREATE TABLE IF NOT EXISTS chat_files(
          id INTEGER PRIMARY KEY AUTOINCREMENT,
          chatId TEXT NOT NULL,
          name TEXT NOT NULL,
          type TEXT NOT NULL,
          FOREIGN KEY (chatId) REFERENCES chats (id) ON DELETE CASCADE
        )
      ''');
    }

    if (oldVersion < 3) {
      // Adiciona chat_messages se veio da v2
      // CORREÇÃO: Adicionado IF NOT EXISTS
      await db.execute('''
        CREATE TABLE IF NOT EXISTS chat_messages(
          id INTEGER PRIMARY KEY AUTOINCREMENT,
          chatId TEXT NOT NULL,
          text TEXT NOT NULL,
          isSentByMe INTEGER NOT NULL,
          timestamp INTEGER NOT NULL,
          FOREIGN KEY (chatId) REFERENCES chats (id) ON DELETE CASCADE
        )
      ''');
    }

    if (oldVersion < 5) {
      // Adiciona coluna id_usuario na tabela chats
      // IMPORTANTE: SQLite não suporta ALTER TABLE ADD COLUMN com FOREIGN KEY
      // Então precisamos recriar a tabela

      // CORREÇÃO: Garante que a tabela temporária não existe antes de tentar criar
      // Isso evita crash se a migração falhou na metade anteriormente
      await db.execute('DROP TABLE IF EXISTS chats_new');

      // 1. Criar tabela temporária com nova estrutura
      await db.execute('''
        CREATE TABLE chats_new(
          id TEXT PRIMARY KEY,
          id_usuario INTEGER NOT NULL,
          title TEXT NOT NULL,
          subject TEXT NOT NULL,
          FOREIGN KEY (id_usuario) REFERENCES usuario(id_usuario) ON DELETE CASCADE
        )
      ''');

      // 2. Copiar dados antigos (atribuindo id_usuario = 1 para dados existentes)
      // Usamos try/catch aqui caso a tabela 'chats' original não tenha dados compatíveis ou não exista
      try {
        await db.execute('''
          INSERT INTO chats_new (id, id_usuario, title, subject)
          SELECT id, 1, title, subject FROM chats
        ''');
      } catch (e) {
        print("Erro ao migrar dados de chats: $e");
      }

      // 3. Remover tabela antiga
      await db.execute('DROP TABLE IF EXISTS chats');

      // 4. Renomear tabela nova
      await db.execute('ALTER TABLE chats_new RENAME TO chats');
    }
  }
}