// lib/services/notification_service.dart
import 'package:flutter_local_notifications/flutter_local_notifications.dart';
import 'package:timezone/data/latest_all.dart' as tz;
import 'package:timezone/timezone.dart' as tz;
import 'package:flutter/material.dart'; // Necessário para debugPrint
import 'package:flutter/foundation.dart'; // Para kIsWeb

class NotificationService {
  static final NotificationService _instance = NotificationService._internal();
  factory NotificationService() => _instance;
  NotificationService._internal();

  final FlutterLocalNotificationsPlugin flutterLocalNotificationsPlugin =
  FlutterLocalNotificationsPlugin();

  Future<void> init() async {
    if (kIsWeb) return;

    // Android Initialization
    const AndroidInitializationSettings initializationSettingsAndroid =
    AndroidInitializationSettings('@mipmap/ic_launcher'); // Use seu ícone padrão

    // --- MUDANÇA 1: DarwinInitializationSettings ATUALIZADO ---
    // Remove onDidReceiveLocalNotification. Permissões padrão são solicitadas aqui.
    const DarwinInitializationSettings initializationSettingsIOS =
    DarwinInitializationSettings(
      requestAlertPermission: true, // Solicita permissão de alerta
      requestBadgePermission: true, // Solicita permissão de badge
      requestSoundPermission: true, // Solicita permissão de som
      // onDidReceiveLocalNotification is deprecated and removed here.
      // Foreground notifications on iOS 10+ are handled by NotificationDetails.
    );
    // --- FIM DA MUDANÇA 1 ---

    final InitializationSettings initializationSettings =
    InitializationSettings(
        android: initializationSettingsAndroid,
        iOS: initializationSettingsIOS);

    try {
      // Configura o timezone ANTES de inicializar
      tz.initializeTimeZones();
      try {
        // Tenta usar um timezone comum no Brasil
        tz.setLocalLocation(tz.getLocation('America/Sao_Paulo'));
      } catch (e) {
        print("Erro ao definir timezone 'America/Sao_Paulo': $e. Usando padrão do dispositivo/UTC.");
        // Deixa o sistema operacional decidir ou use tz.UTC
      }

      await flutterLocalNotificationsPlugin.initialize(initializationSettings,
        onDidReceiveNotificationResponse: onDidReceiveNotificationResponse,
        // onDidReceiveBackgroundNotificationResponse: onDidReceiveBackgroundNotificationResponse, // Para ações em background
      );


      print("NotificationService inicializado.");

    } catch (e) {
      print("Erro ao inicializar NotificationService: $e");
    }
  }

  // iOS < 10 foreground (Este método é chamado pelo DarwinInitializationSettings antigo,
  // mas como o parâmetro foi removido, esta função pode não ser mais chamada diretamente
  // por ele. Mantemos para referência ou caso precise ser chamado manualmente.)
  // IMPORTANTE: Para iOS 10+, notificações foreground são controladas pelo 'presentAlert', etc.
  // nos DarwinNotificationDetails ao agendar.
  void onDidReceiveLocalNotification(
      int id, String? title, String? body, String? payload) async {
    print('Callback onDidReceiveLocalNotification chamado (iOS < 10 ou manual): $title');
    // Você pode exibir um Dialog ou SnackBar aqui se o app estiver aberto.
  }

  // Toque na notificação (App estava fechado ou em background)
  void onDidReceiveNotificationResponse(NotificationResponse notificationResponse) async {
    final String? payload = notificationResponse.payload;
    if (payload != null) {
      debugPrint('Payload da notificação (onDidReceiveNotificationResponse): $payload');
      // TODO: Implementar navegação baseada no payload
      // Ex: if (payload.startsWith('task_')) { navegaParaTarefa(payload); }
    }
    // Pode adicionar navegação padrão se não houver payload
  }

  // Callback para ações de notificação em background (requer setup extra)
  /*
  @pragma('vm:entry-point') // Necessário para background isolates
  void onDidReceiveBackgroundNotificationResponse(NotificationResponse notificationResponse) async {
     final String? payload = notificationResponse.payload;
     if (payload != null) {
       debugPrint('Payload da notificação (BACKGROUND): $payload');
       // Aqui você pode fazer lógica leve, como salvar algo em SharedPreferences
       // NÃO PODE fazer navegação direta ou atualizar UI complexa
     }
  }
  */

  // Pedir permissões (Continua importante)
  Future<void> requestPermissions() async {
    if (kIsWeb) return;

    try {
      // iOS (já solicitado no init, mas pode chamar de novo se necessário)
      // await flutterLocalNotificationsPlugin
      //     .resolvePlatformSpecificImplementation<IOSFlutterLocalNotificationsPlugin>()
      //     ?.requestPermissions(alert: true, badge: true, sound: true);

      // Android 13+
      final AndroidFlutterLocalNotificationsPlugin? androidImplementation =
      flutterLocalNotificationsPlugin.resolvePlatformSpecificImplementation<
          AndroidFlutterLocalNotificationsPlugin>();
      if (androidImplementation != null) {
        // Importante: Checar se a permissão já foi concedida antes de pedir de novo
        final bool? granted = await androidImplementation.areNotificationsEnabled();
        if (granted != null && !granted) {
          await androidImplementation.requestNotificationsPermission();
          print("Permissão de notificação Android solicitada.");
        } else {
          print("Permissão de notificação Android já concedida ou não aplicável.");
        }
      }

    } catch (e) {
      print("Erro ao solicitar/verificar permissões de notificação: $e");
    }
  }


  // Agendar notificação
  Future<void> scheduleNotification({
    required int id,
    required String title,
    required String body,
    required DateTime scheduledDate,
    String? payload,
  }) async {
    if (kIsWeb) return;

    // Detalhes Android
    const AndroidNotificationDetails androidDetails =
    AndroidNotificationDetails(
      'task_reminders_channel_v1', // ID do canal
      'Lembretes de Tarefas', // Nome do canal
      channelDescription: 'Canal para notificações de lembretes de tarefas',
      importance: Importance.max, // Máxima importância
      priority: Priority.high, // Alta prioridade
      ticker: 'Lembrete de Tarefa', // Texto breve na barra de status
      // Outras opções:
      // sound: RawResourceAndroidNotificationSound('nome_do_som'),
      // enableVibration: true,
      // styleInformation: BigTextStyleInformation(''), // Para texto longo
    );

    // --- MUDANÇA 2: DarwinNotificationDetails ATUALIZADO ---
    // Controla como a notificação aparece se o app estiver ABERTO (foreground) no iOS 10+
    const DarwinNotificationDetails iosDetails =
    DarwinNotificationDetails(
        presentAlert: true,  // Mostra alerta no foreground
        presentBadge: true,  // Atualiza badge no foreground
        presentSound: true); // Toca som no foreground
    // --- FIM DA MUDANÇA 2 ---

    const NotificationDetails platformDetails =
    NotificationDetails(android: androidDetails, iOS: iosDetails);

    try {
      // Converte para TZDateTime
      final tz.TZDateTime tzScheduledDate = tz.TZDateTime.from(scheduledDate, tz.local);

      // Validação: Não agendar no passado
      final tz.TZDateTime tzNow = tz.TZDateTime.now(tz.local);
      if (tzScheduledDate.isBefore(tzNow)) {
        print("Tentativa de agendar notificação ${id} no passado: $tzScheduledDate (Agora: $tzNow)");
        // Opcional: Agendar para alguns segundos no futuro se for muito próximo
        // if (tzScheduledDate.difference(tzNow).inSeconds < 5) {
        //    tzScheduledDate = tzNow.add(const Duration(seconds: 5));
        //    print("Ajustando data para 5 segundos no futuro: $tzScheduledDate");
        // } else {
        return; // Não agenda
        // }
      }

      // --- MUDANÇA 3: zonedSchedule ATUALIZADO ---
      // Remove uiLocalNotificationDateInterpretation
      await flutterLocalNotificationsPlugin.zonedSchedule(
        id,
        title,
        body,
        tzScheduledDate,
        platformDetails,
        androidScheduleMode: AndroidScheduleMode.exactAllowWhileIdle, // Mantido
        payload: payload,
        matchDateTimeComponents: DateTimeComponents.dateAndTime, // Mantido
      );
      // --- FIM DA MUDANÇA 3 ---

      print("Notificação agendada: ID=$id, Título=$title, Data=$tzScheduledDate");

    } catch(e) {
      print("Erro ao agendar notificação $id: $e");
    }
  }

  // Cancelar notificação (sem mudanças)
  Future<void> cancelNotification(int id) async {
    if (kIsWeb) return;
    try {
      await flutterLocalNotificationsPlugin.cancel(id);
      print("Notificação cancelada: ID=$id");
    } catch(e) {
      print("Erro ao cancelar notificação $id: $e");
    }
  }

  // Cancelar todas (sem mudanças)
  Future<void> cancelAllNotifications() async {
    if (kIsWeb) return;
    try {
      await flutterLocalNotificationsPlugin.cancelAll();
      print("Todas as notificações canceladas.");
    } catch (e) {
      print("Erro ao cancelar todas as notificações: $e");
    }
  }
}