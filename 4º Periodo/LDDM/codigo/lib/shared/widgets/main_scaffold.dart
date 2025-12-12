// lib/shared/widgets/main_scaffold.dart
import 'package:flutter/material.dart';
import '../../pages/3_home/home_screen.dart';
import '../../pages/5_profile/profile_screen.dart';
import '../../pages/7_pomodoro/pomodoro_screen.dart';
import '../../pages/4_calendar/calendar_screen.dart';
import 'gnav_bar.dart';
// Removida a importação de UserModel daqui

class MainScaffold extends StatefulWidget {
  // --- MUDANÇA 1: Receber o ID do usuário (da tela de Login) ---
  final int userId;
  const MainScaffold({super.key, required this.userId});
  // -----------------------------------------------------------

  @override
  State<MainScaffold> createState() => _MainScaffoldState();
}

// Removido o 'currentUser' hardcoded

class _MainScaffoldState extends State<MainScaffold> {
  int _currentIndex = 0;

  // --- MUDANÇA 2: Inicializar a lista de páginas no initState ---
  late final List<Widget> _pages;

  @override
  void initState() {
    super.initState();
    // Agora inicializamos a lista aqui para poder usar o widget.userId
    _pages = [
      // Passa o userId para TODAS as telas filhas
      HomePage(userId: widget.userId),          // Tela para o Índice 0
      CalendarScreen(userId: widget.userId),    // Tela para o Índice 1
      PomodoroPage(userId: widget.userId),      // Tela para o Índice 2
      PerfilPage(userId: widget.userId),        // Tela para o Índice 3
    ];
  }
  // -----------------------------------------------------------

  void _onTabChange(int index) {
    setState(() {
      _currentIndex = index;
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      // O body agora muda dinamicamente
      body: _pages[_currentIndex],
      bottomNavigationBar: SharedGNavBar(
        currentIndex: _currentIndex,
        onTabChange: _onTabChange,
      ),
    );
  }
}