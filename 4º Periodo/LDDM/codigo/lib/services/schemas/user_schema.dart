import 'package:sqflite/sqflite.dart';

class UserSchema {
  // Função para criar a tabela de usuários (para novas instalações)
  static Future<void> createTables(Database db) async {
    // CORREÇÃO: Adicionado IF NOT EXISTS para evitar erro se a tabela já existir
    await db.execute('''
      CREATE TABLE IF NOT EXISTS usuario(
        id_usuario INTEGER PRIMARY KEY AUTOINCREMENT,
        nome TEXT NOT NULL,
        senha TEXT NOT NULL,
        email TEXT NOT NULL,
        telefone TEXT NOT NULL
      )
    ''');
  }

  // Função para atualizar a tabela de usuários (para usuários existentes)
  static Future<void> upgradeTables(
      Database db,
      int oldVersion,
      int newVersion,
      ) async {
    if (oldVersion < 5) {
      var tables = await db.rawQuery(
        "SELECT name FROM sqlite_master WHERE type='table' AND name='usuario'",
      );

      if (tables.isEmpty) {
        // Se a tabela users antiga não existir, criamos
        await createTables(db);
      } else {
        // Se existir e precisarmos migrar a estrutura (ex: mudar id para id_usuario)

        // 1. Garante que a tabela temporária não existe
        await db.execute('DROP TABLE IF EXISTS usuario_new');

        // 2. Cria a nova tabela
        await db.execute('''
          CREATE TABLE usuario_new(
            id_usuario INTEGER PRIMARY KEY AUTOINCREMENT,
            nome TEXT NOT NULL,
            senha TEXT NOT NULL,
            email TEXT NOT NULL,
            telefone TEXT NOT NULL
          )
        ''');

        // 3. Copia dados antigos
        // ATENÇÃO: Corrigi o INSERT. A tabela nova tem 'id_usuario', não 'id'.
        // Assumindo que a tabela antiga tinha 'id' ou que você quer gerar novos IDs.
        // Se a tabela antiga tinha 'id', mude "NULL" para "id".
        try {
          await db.execute('''
            INSERT INTO usuario_new (id_usuario, nome, senha, email, telefone)
            SELECT id_usuario, nome, senha, email, telefone FROM usuario
          ''');
        } catch (e) {
          // Fallback se a coluna antiga se chamava 'id'
          await db.execute('''
            INSERT INTO usuario_new (id_usuario, nome, senha, email, telefone)
            SELECT id, nome, senha, email, telefone FROM usuario
          ''');
        }

        // 4. Substitui a tabela antiga pela nova
        await db.execute('DROP TABLE usuario');
        await db.execute('ALTER TABLE usuario_new RENAME TO usuario');
      }
    }
  }
}