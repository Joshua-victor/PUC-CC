import 'package:flutter/material.dart';
import 'app_colors.dart';

class AppTheme {
  // TEMA CLARO (JÁ EXISTENTE)
  static final ThemeData lightTheme = ThemeData(
    brightness: Brightness.light,
    colorScheme: const ColorScheme.light(
      primary: AppColors.purplePrimary,
      secondary: AppColors.green,
      background: AppColors.background,
      surface: AppColors.white,
      error: AppColors.red,
      onPrimary: AppColors.white,
      onSecondary: AppColors.white,
      onBackground: AppColors.textBase,
      onSurface: AppColors.textBase,
      onError: AppColors.white,
    ),
    scaffoldBackgroundColor: AppColors.background,
    textTheme: const TextTheme(
      displayLarge: TextStyle(fontFamily: 'Poppins', color: AppColors.textTitle, fontWeight: FontWeight.bold, fontSize: 32),
      titleLarge: TextStyle(fontFamily: 'Poppins', color: AppColors.textTitle, fontWeight: FontWeight.w600, fontSize: 22),
      bodyLarge: TextStyle(fontFamily: 'Poppins', color: AppColors.textBase, fontSize: 16, height: 1.5),
      bodyMedium: TextStyle(fontFamily: 'Poppins', color: AppColors.textComplement, fontSize: 14, height: 1.5),
      labelLarge: TextStyle(fontFamily: 'Poppins', color: AppColors.white, fontWeight: FontWeight.bold, fontSize: 16),
    ),
    appBarTheme: const AppBarTheme(
      backgroundColor: AppColors.purplePrimary,
      foregroundColor: AppColors.white,
      elevation: 0,
      centerTitle: true,
      titleTextStyle: TextStyle(
        fontFamily: 'Poppins',
        color: AppColors.textOnPurple,
        fontSize: 20,
        fontWeight: FontWeight.bold,
      ),
    ),
    elevatedButtonTheme: ElevatedButtonThemeData(
      style: ElevatedButton.styleFrom(
        backgroundColor: AppColors.green,
        foregroundColor: AppColors.white,
        textStyle: const TextStyle(fontFamily: 'Poppins', fontWeight: FontWeight.bold, fontSize: 16),
        shape: RoundedRectangleBorder(
          borderRadius: BorderRadius.circular(12.0),
        ),
        padding: const EdgeInsets.symmetric(vertical: 16.0, horizontal: 24.0),
        elevation: 0,
      ),
    ),
    cardTheme: CardThemeData(
        color: AppColors.white,
        elevation: 1,
        shape: RoundedRectangleBorder(
            borderRadius: BorderRadius.circular(8.0),
            side: const BorderSide(
              color: AppColors.lightGrey,
              width: 1,
            )
        )
    ),
  );

  // ***** NOVO TEMA ESCURO ADICIONADO ABAIXO *****
  static final ThemeData darkTheme = ThemeData(
    brightness: Brightness.dark,

    // Esquema de Cores principal para o modo escuro
    colorScheme: const ColorScheme.dark(
      primary: AppColors.purplePrimary,
      secondary: AppColors.green,
      background: AppColors.darkBackground,
      surface: AppColors.darkSurface,
      error: AppColors.red,

      // Cores "On" - para textos e ícones
      onPrimary: AppColors.white,
      onSecondary: AppColors.white,
      onBackground: AppColors.darkText,
      onSurface: AppColors.darkText,
      onError: AppColors.white,
    ),

    // Cor de fundo principal das telas
    scaffoldBackgroundColor: AppColors.darkBackground,

    // Tema de Texto para o modo escuro
    textTheme: const TextTheme(
      displayLarge: TextStyle(fontFamily: 'Poppins', color: AppColors.darkText, fontWeight: FontWeight.bold, fontSize: 32),
      titleLarge: TextStyle(fontFamily: 'Poppins', color: AppColors.darkText, fontWeight: FontWeight.w600, fontSize: 22),
      bodyLarge: TextStyle(fontFamily: 'Poppins', color: AppColors.darkText, fontSize: 16, height: 1.5),
      bodyMedium: TextStyle(fontFamily: 'Poppins', color: AppColors.darkTextComplement, fontSize: 14, height: 1.5),
      labelLarge: TextStyle(fontFamily: 'Poppins', color: AppColors.white, fontWeight: FontWeight.bold, fontSize: 16),
    ),

    // AppBar mantém o mesmo estilo, pois já usa cores que funcionam bem
    appBarTheme: const AppBarTheme(
      backgroundColor: AppColors.purplePrimary,
      foregroundColor: AppColors.white,
      elevation: 0,
      centerTitle: true,
      titleTextStyle: TextStyle(
        fontFamily: 'Poppins',
        color: AppColors.textOnPurple,
        fontSize: 20,
        fontWeight: FontWeight.bold,
      ),
    ),

    // Botões mantêm o mesmo estilo
    elevatedButtonTheme: ElevatedButtonThemeData(
      style: ElevatedButton.styleFrom(
        backgroundColor: AppColors.green,
        foregroundColor: AppColors.white,
        textStyle: const TextStyle(fontFamily: 'Poppins', fontWeight: FontWeight.bold, fontSize: 16),
        shape: RoundedRectangleBorder(
          borderRadius: BorderRadius.circular(12.0),
        ),
        padding: const EdgeInsets.symmetric(vertical: 16.0, horizontal: 24.0),
        elevation: 0,
      ),
    ),

    // Tema para Cards no modo escuro
    cardTheme: CardThemeData(
        color: AppColors.darkSurface, // Cor de fundo do card
        elevation: 1,
        shape: RoundedRectangleBorder(
            borderRadius: BorderRadius.circular(8.0),
            side: const BorderSide(
              color: AppColors.darkBorder, // Cor da borda do card
              width: 1,
            )
        )
    ),

  );
}