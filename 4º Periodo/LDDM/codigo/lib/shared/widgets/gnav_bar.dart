import 'package:flutter/material.dart';
import 'package:google_nav_bar/google_nav_bar.dart';
import '../theme/app_colors.dart';

class SharedGNavBar extends StatelessWidget {
  final int currentIndex;
  final Function(int) onTabChange;

  const SharedGNavBar({
    super.key,
    required this.currentIndex,
    required this.onTabChange,
  });

  @override
  Widget build(BuildContext context) {
    final theme = Theme.of(context);

    return Container(
      decoration: BoxDecoration(
        color: theme.colorScheme.surface,
        boxShadow: [
          BoxShadow(
            blurRadius: 20,
            color: theme.shadowColor.withOpacity(0.1),
          )
        ],
      ),
      child: SafeArea(
        child: Padding(
          padding: const EdgeInsets.symmetric(horizontal: 15.0, vertical: 8),
          child: GNav(
            rippleColor: AppColors.purplePrimary.withOpacity(0.3),
            hoverColor: theme.hoverColor,
            gap: 0,
            activeColor: AppColors.purplePrimary, // Ícone ativo continua roxo
            iconSize: 28,
            padding: const EdgeInsets.symmetric(horizontal: 20, vertical: 12),
            duration: const Duration(milliseconds: 400),
            tabBackgroundColor: AppColors.purplePrimary.withOpacity(0.1),

            // ***** ALTERAÇÃO AQUI *****
            // Usando a cor 'onSurface' para garantir um bom contraste
            // tanto no modo claro quanto no escuro.
            color: theme.colorScheme.onSurface.withOpacity(0.6),

            tabs: const [
              GButton(icon: Icons.home, text: ''),
              GButton(icon: Icons.calendar_today, text: ''),
              GButton(icon: Icons.timer, text: ''),
              GButton(icon: Icons.person, text: ''),
            ],
            selectedIndex: currentIndex,
            onTabChange: onTabChange,
          ),
        ),
      ),
    );
  }
}

