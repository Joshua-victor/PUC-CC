// lib/services/settings_service.dart

import 'package:shared_preferences/shared_preferences.dart';
import 'package:flutter/material.dart';

class SettingsService {
  // Chaves para salvar os dados
  static const _darkModeKey = 'darkMode';
  static const _notificationsKey = 'notificationsEnabled';

  // --- MODO ESCURO ---
  Future<void> saveThemeMode(ThemeMode themeMode) async {
    final prefs = await SharedPreferences.getInstance();
    await prefs.setBool(_darkModeKey, themeMode == ThemeMode.dark);
  }

  Future<ThemeMode> getThemeMode() async {
    final prefs = await SharedPreferences.getInstance();
    final isDarkMode = prefs.getBool(_darkModeKey) ?? false; // Padrão: modo claro
    return isDarkMode ? ThemeMode.dark : ThemeMode.light;
  }

  // --- NOTIFICAÇÕES ---
  Future<void> saveNotifications(bool isEnabled) async {
    final prefs = await SharedPreferences.getInstance();
    await prefs.setBool(_notificationsKey, isEnabled);
  }

  Future<bool> getNotifications() async {
    final prefs = await SharedPreferences.getInstance();
    return prefs.getBool(_notificationsKey) ?? true; // Padrão: notificações ativadas
  }
}