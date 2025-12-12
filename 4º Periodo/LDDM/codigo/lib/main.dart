// lib/main.dart

import 'package:firebase_core/firebase_core.dart';
import 'firebase_options.dart'; // gerado pelo flutterfire configure
import 'package:flutter/material.dart';
import 'package:codigo/shared/theme/app_theme.dart';
// import 'package:codigo/pages/0_splash/splash_screen.dart'; // Mantido comentado
import 'package:codigo/pages/1_login/login_screen.dart'; // Tela inicial agora é Login
import 'package:flutter_localizations/flutter_localizations.dart';
import 'services/settings_service.dart';
import 'services/notification_service.dart';

// Imports adicionais que adicionamos
import 'package:shared_preferences/shared_preferences.dart';
import 'services/sqlite_to_firestore_migration.dart';

// --- IMPORTANTE: Adicione este import para o teste ---
import 'package:cloud_firestore/cloud_firestore.dart';

// Para detectar web/desktop e Platform
import 'package:flutter/foundation.dart' show kIsWeb;
import 'dart:io'; // <--- NECESSÁRIO para usar Platform.isAndroid, etc.

// sqflite / ffi imports
import 'package:sqflite_common_ffi/sqflite_ffi.dart' show sqfliteFfiInit, databaseFactoryFfi;
import 'package:sqflite/sqflite.dart' show databaseFactory;

/// A variável global que controla o tema em tempo real.
final ValueNotifier<ThemeMode> themeNotifier = ValueNotifier(ThemeMode.light);

Future<void> main() async {
  // Garante que o Flutter está pronto.
  WidgetsFlutterBinding.ensureInitialized();

  // Inicializa Firebase
  try {
    await Firebase.initializeApp(
      options: DefaultFirebaseOptions.currentPlatform,
    );
    print("Firebase inicializado.");

  } catch (e) {
    print("Erro ao inicializar Firebase: $e");
    // se preferir, rethrow para impedir rodar sem Firebase
  }

  // --- Inicializa sqflite_ffi APENAS se for Desktop (Windows/Linux/Mac) ---
  // CORREÇÃO: Não executamos isso no Android/iOS, pois eles usam a implementação nativa (MethodChannel).
  if (!kIsWeb) {
    if (Platform.isWindows || Platform.isLinux || Platform.isMacOS) {
      try {
        sqfliteFfiInit();
        databaseFactory = databaseFactoryFfi;
        print('sqflite_ffi inicializado para Desktop.');
      } catch (e) {
        print('Falha ao inicializar sqflite_ffi: $e');
      }
    } else {
      print('Rodando em Mobile (Android/iOS) - Usando sqflite nativo.');
    }
  } else {
    print('Executando em Web - pulando inicialização sqflite_ffi.');
  }

  // ------------------ MIGRAÇÃO (OPÇÃO A, executa apenas 1x) ------------------
  try {
    final prefs = await SharedPreferences.getInstance();
    final alreadyMigrated = prefs.getBool('migration_done') ?? false;

    if (!alreadyMigrated) {
      print('Iniciando migração SQLite -> Firestore (apenas 1x)...');

      final migrator = SqliteToFirestoreMigration();
      try {
        await migrator.migrateSQLiteToFirestore();
        // marca como migrado para não rodar de novo
        await prefs.setBool('migration_done', true);
        print('Migração concluída e flag salva em SharedPreferences.');
      } catch (migError, st) {
        print('Erro durante migração: $migError\n$st');
        // NÃO marque como migrado — permite tentativas futuras
      }
    } else {
      print('Migração já realizada anteriormente — pulando.');
    }
  } catch (e) {
    print('Erro ao verificar/registrar flag de migração: $e');
  }
  // ---------------------------------------------------------------------------

  // Carrega as configurações de tema
  final settingsService = SettingsService();
  ThemeMode savedThemeMode = ThemeMode.light; // Padrão
  try {
    savedThemeMode = await settingsService.getThemeMode();
  } catch (e) {
    print("Erro ao carregar tema salvo: $e. Usando padrão.");
  }
  themeNotifier.value = savedThemeMode;

  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return ValueListenableBuilder<ThemeMode>(
      valueListenable: themeNotifier,
      builder: (_, ThemeMode currentMode, __) {
        return MaterialApp(
          debugShowCheckedModeBanner: false,
          title: 'SmartStudy',

          theme: AppTheme.lightTheme,
          darkTheme: AppTheme.darkTheme,
          themeMode: currentMode,

          // Configuração de Localização para pt_BR
          localizationsDelegates: const [
            GlobalMaterialLocalizations.delegate,
            GlobalWidgetsLocalizations.delegate,
            GlobalCupertinoLocalizations.delegate,
          ],
          supportedLocales: const [
            Locale('pt', 'BR'), // Português do Brasil
            // Locale('en', ''), // Adicione Inglês como fallback se necessário
          ],
          locale: const Locale('pt', 'BR'), // Define o locale padrão

          // --- Tela Inicial ---
          home: const LoginScreen(), // Define LoginScreen como a tela inicial
          // home: const WelcomeScreen(), // Se você tiver uma WelcomeScreen
          // --------------------
        );
      },
    );
  }
}