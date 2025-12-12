// lib/pages/2_signup/signup_screen.dart

import 'package:codigo/pages/1_login/login_screen.dart';
import 'package:flutter/material.dart';
import 'package:flutter_svg/flutter_svg.dart';
import '../../shared/utils/crypto_helper.dart';
import '../../shared/theme/app_colors.dart';
import '../../services/database_service.dart';

// --- IMPORTS DO FIREBASE ---
import 'package:firebase_auth/firebase_auth.dart';
import 'package:cloud_firestore/cloud_firestore.dart';
// ---------------------------

class SignUpScreen extends StatefulWidget {
  const SignUpScreen({super.key});

  @override
  State<SignUpScreen> createState() => _SignUpScreenState();
}

class _SignUpScreenState extends State<SignUpScreen> {
  final _nameController = TextEditingController();
  final _emailController = TextEditingController();
  final _phoneController = TextEditingController();
  final _passwordController = TextEditingController();
  final _confirmPasswordController = TextEditingController();

  final dbService = DatabaseService();
  bool _isLoading = false;

  Future<void> _handleRegister() async {
    if (_isLoading) return;
    setState(() => _isLoading = true);

    final name = _nameController.text.trim();
    final email = _emailController.text.trim();
    final phone = _phoneController.text.trim();
    final password = _passwordController.text.trim();
    final confirmPassword = _confirmPasswordController.text.trim();

    // --- VALIDAÇÕES (Mantidas iguais) ---
    if (name.isEmpty || email.isEmpty || phone.isEmpty || password.isEmpty || confirmPassword.isEmpty) {
      _showError('Preencha todos os campos obrigatórios.');
      return;
    }

    final emailRegex = RegExp(r'^(\w+(?:[.-]\w+)*)@((?:\w+\-)*\w+)\.([a-z]{2,6}(?:\.[a-z]{2})?)', caseSensitive: false);
    if (!emailRegex.hasMatch(email)) {
      _showError('Digite um e-mail válido.');
      return;
    }

    if (password.length < 8) {
      _showError('A senha deve ter pelo menos 8 caracteres.');
      return;
    }

    if (password != confirmPassword) {
      _showError('As senhas não coincidem.');
      return;
    }
    // ------------------------------------

    try {
      // 1. TENTA CRIAR NO FIREBASE PRIMEIRO (Autenticação + Dados)
      UserCredential? userCredential;
      try {
        // Cria usuário no Firebase Auth
        userCredential = await FirebaseAuth.instance.createUserWithEmailAndPassword(
          email: email,
          password: password,
        );

        // Salva dados no Firestore (Nuvem)
        if (userCredential.user != null) {
          await FirebaseFirestore.instance.collection('users').doc(userCredential.user!.uid).set({
            'nome': name,
            'email': email,
            'telefone': phone,
            'uid_firebase': userCredential.user!.uid, // Link entre auth e dados
            'created_at': FieldValue.serverTimestamp(),
          });
        }
      } catch (firebaseError) {
        print("Aviso: Falha ao criar no Firebase (pode estar offline): $firebaseError");
        // Não paramos o código aqui para permitir o cadastro local (SQLite) funcionar offline
      }

      // 2. CRIA NO BANCO LOCAL (SQLite)
      // Mantemos isso para o app funcionar como você já programou (usando IDs inteiros)
      final hashedPassword = CryptoHelper.hashPassword(password);
      await dbService.createUser(name, hashedPassword, email, phone);

      // Sucesso!
      if (mounted) {
        ScaffoldMessenger.of(context).showSnackBar(
          const SnackBar(
            content: Text('Cadastro realizado com sucesso!'),
            backgroundColor: Colors.green,
          ),
        );

        Navigator.of(context).pushAndRemoveUntil(
          MaterialPageRoute(builder: (context) => const LoginScreen()),
              (Route<dynamic> route) => false,
        );
      }
    } catch (e) {
      print("Erro no cadastro: $e");
      _showError('Erro ao realizar cadastro: $e');
    } finally {
      if (mounted) setState(() => _isLoading = false);
    }
  }

  void _showError(String msg) {
    if (mounted) {
      ScaffoldMessenger.of(context).showSnackBar(
        SnackBar(content: Text(msg), backgroundColor: AppColors.red),
      );
    }
    setState(() => _isLoading = false);
  }

  @override
  void dispose() {
    _nameController.dispose();
    _emailController.dispose();
    _phoneController.dispose();
    _passwordController.dispose();
    _confirmPasswordController.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    final theme = Theme.of(context);

    return Scaffold(
      appBar: AppBar(backgroundColor: Colors.transparent, elevation: 0),
      backgroundColor: theme.colorScheme.background,
      body: SingleChildScrollView(
        child: Padding(
          padding: const EdgeInsets.symmetric(horizontal: 32.0),
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            crossAxisAlignment: CrossAxisAlignment.stretch,
            children: [
              const SizedBox(height: 32),
              _buildLogo(),
              const SizedBox(height: 48),
              _buildTextField(controller: _nameController, label: "Nome completo"),
              const SizedBox(height: 16),
              _buildTextField(controller: _emailController, label: "E-mail", keyboardType: TextInputType.emailAddress),
              const SizedBox(height: 16),
              _buildTextField(controller: _phoneController, label: "Telefone", keyboardType: TextInputType.phone),
              const SizedBox(height: 16),
              _buildTextField(controller: _passwordController, label: "Senha", obscureText: true),
              const SizedBox(height: 16),
              _buildTextField(controller: _confirmPasswordController, label: "Confirmar senha", obscureText: true),
              const SizedBox(height: 32),
              _isLoading
                  ? const Center(child: CircularProgressIndicator())
                  : ElevatedButton(
                onPressed: _handleRegister,
                style: ElevatedButton.styleFrom(
                  backgroundColor: theme.colorScheme.primary,
                  foregroundColor: theme.colorScheme.onPrimary,
                  padding: const EdgeInsets.symmetric(vertical: 16),
                ),
                child: Text("Cadastrar", style: theme.textTheme.labelLarge),
              ),
              const SizedBox(height: 24),
              Wrap(
                alignment: WrapAlignment.center,
                crossAxisAlignment: WrapCrossAlignment.center,
                children: [
                  Text("Já tem conta? ", style: theme.textTheme.bodyMedium),
                  GestureDetector(
                    onTap: () {
                      if (Navigator.canPop(context)) {
                        Navigator.pop(context);
                      } else {
                        Navigator.pushReplacement(
                          context,
                          MaterialPageRoute(builder: (context) => const LoginScreen()),
                        );
                      }
                    },
                    child: Text(
                      "Entrar",
                      style: theme.textTheme.bodyLarge?.copyWith(
                        fontWeight: FontWeight.bold,
                        color: theme.colorScheme.primary,
                      ),
                    ),
                  ),
                ],
              ),
              const SizedBox(height: 24),
            ],
          ),
        ),
      ),
    );
  }

  Widget _buildTextField({
    required TextEditingController controller,
    required String label,
    bool obscureText = false,
    TextInputType? keyboardType,
  }) {
    return TextField(
      controller: controller,
      keyboardType: keyboardType,
      obscureText: obscureText,
      decoration: InputDecoration(labelText: label),
    );
  }

  Widget _buildLogo() {
    const String rawSvg =
    '''<svg xmlns="http://www.w3.org/2000/svg" width="132" height="140" viewBox="0 0 132 140" fill="none">
      <path d="M12.3818 78.4706C11.2618 81.3706 6.78181 79.5606 6.78181 76.2206C6.78181 74.4906 6.40181 73.9806 5.53181 74.5206C1.04181 77.3306 0.331806 74.0006 3.46181 64.7306C5.22181 59.4906 5.65181 56.8705 4.98181 55.4005C4.00181 53.2405 4.92181 49.5105 6.71181 48.4005C7.35181 48.0105 7.78181 43.9306 7.78181 38.3206C7.78181 29.1806 7.71182 28.8805 5.35182 28.2905C2.60182 27.6005 -0.768184 24.3206 0.471816 23.5506C0.921816 23.2706 6.47181 21.1606 12.7918 18.8606C24.5518 14.5806 56.4518 2.54056 60.5818 0.820561C65.1718 -1.09944 69.8918 0.000553131 90.8918 7.89055C102.662 12.3006 115.432 17.0906 119.282 18.5306C127.732 21.6906 128.532 22.2606 128.532 25.1406C128.532 27.1006 126.912 28.0006 115.902 32.1406C108.962 34.7506 102.722 36.8906 102.032 36.8806C101.342 36.8706 100.772 35.6306 100.762 34.1106C100.742 30.2006 99.9118 29.3606 94.2818 27.5606C84.4318 24.4206 77.1518 23.6306 62.6118 24.1106C51.4218 24.4806 46.5318 25.1106 40.2818 26.9706L32.2818 29.3606L31.9718 33.1106C31.5918 37.6906 30.5018 37.8206 21.9718 34.3606L21.6318 34.2206C17.1718 32.4106 14.9618 31.5106 13.8618 32.2506C12.7818 32.9906 12.7818 35.3206 12.7818 39.9406V40.3006C12.7818 45.4306 13.2218 49.0106 13.8918 49.4306C14.5918 49.8606 14.7918 51.6806 14.4218 54.2406C14.0018 57.1906 14.5718 60.7106 16.4318 66.6106C18.5818 73.4806 18.8018 75.1306 17.7218 76.4306C17.0018 77.2906 15.6318 77.7906 14.6618 77.5406C13.7018 77.2906 12.6718 77.7106 12.3818 78.4706ZM90.7818 137.021C85.6418 138.711 81.3418 139.211 70.2818 139.421C62.5818 139.571 55.1618 139.471 53.7818 139.191C38.8018 136.201 22.2918 129.411 20.9018 125.671C18.4518 119.101 24.4718 117.101 33.9318 121.351C49.3518 128.271 69.1518 130.621 83.8618 127.271C92.0618 125.411 96.2518 122.311 99.0118 116.081C102.312 108.621 99.2318 100.211 91.7918 96.3606C88.3718 94.5906 76.3018 91.5906 63.7818 89.3806C49.9118 86.9406 45.3318 85.2506 41.8318 81.2606C39.5018 78.6106 38.7818 76.8306 38.7818 73.7306C38.7818 63.6006 45.8018 59.8606 64.8018 59.8606C76.9118 59.8606 81.7318 60.6206 91.9618 64.1306C101.332 67.3406 103.842 71.1006 99.8718 76.0006L97.9618 78.3606L93.1218 76.5106C80.9418 71.8506 65.0218 69.7006 54.4418 71.2806C45.0818 72.6906 50.7318 75.8906 66.9018 78.3606C81.2318 80.5506 86.3218 81.8006 93.3118 84.8806C105.492 90.2406 110.782 97.6705 110.782 109.411C110.782 123.211 103.892 132.721 90.7818 137.021ZM87.5518 122.391C81.7818 124.761 64.8918 125.231 53.9718 123.321C44.4918 121.661 31.3818 116.551 28.0418 113.211C25.3018 110.481 25.1518 107.741 27.6118 105.511C30.1218 103.241 31.0618 103.371 40.2418 107.301C50.1718 111.561 65.5218 114.341 74.7218 113.561C82.3818 112.911 84.7818 112.141 84.7818 110.341C84.7818 108.911 81.9318 108.191 63.2818 104.891C41.0518 100.951 32.8018 96.8206 27.4118 86.9206C20.7718 74.7106 23.9518 59.2706 34.6518 51.7806C42.6118 46.2106 46.7518 45.3606 65.7818 45.4106C82.7618 45.4506 83.5718 45.5506 92.9018 48.6606C103.772 52.2906 107.782 54.9006 107.782 58.3606C107.782 61.1606 105.352 63.8606 102.832 63.8606C101.842 63.8606 98.3918 62.6906 95.1618 61.2706C79.1118 54.1706 50.4118 54.0106 40.6418 60.9606C36.7218 63.7506 34.7818 67.8506 34.7818 73.3606C34.7818 81.6806 39.7318 87.5506 49.0218 90.2306C51.9118 91.0706 60.8018 92.9305 68.7818 94.3805C76.7618 95.8205 85.6418 98.0705 88.5318 99.3805C94.3818 102.021 95.7818 104.321 95.7818 111.291C95.7818 116.661 93.2918 120.021 87.5518 122.391ZM42.0618 45.7305C38.6418 46.9005 35.6818 47.8606 35.4818 47.8606C33.2918 47.8606 33.0018 32.7506 35.1518 30.9706C35.9118 30.3406 38.9418 29.0506 41.9018 28.1006C50.1318 25.4506 82.8618 25.6906 91.2818 28.4606L97.2818 30.4406L97.5718 39.2706C97.8418 47.4206 97.7218 48.0506 96.0718 47.3906C95.0918 47.0006 90.6918 45.7706 86.3118 44.6406C75.4218 41.8606 51.6318 42.4405 42.0618 45.7305Z" fill="#8A69ED"/>
      <path d="M2.40182 68.1705C0.591821 74.7905 1.65181 76.9506 5.53181 74.5206C6.40181 73.9806 6.78181 74.4906 6.78181 76.2206C6.78181 77.7806 7.76183 79.0105 8.92183 79.5805C7.77183 79.2405 6.78183 78.4105 6.78183 77.2805C6.78183 76.5005 6.33183 75.8605 5.78183 75.8605C5.23183 75.8605 4.78183 76.3105 4.78183 76.8605C4.78183 78.3905 2.18183 78.0505 0.751827 76.3305C-0.178173 75.2005 -0.238174 74.2005 0.531826 72.5805C1.20183 71.1405 1.84182 69.6505 2.40182 68.1705ZM103.612 36.4805C106.012 35.7505 110.772 34.0806 115.902 32.1406C126.912 28.0006 128.532 27.1006 128.532 25.1406C128.532 22.2606 127.732 21.6906 119.282 18.5306C117.172 17.7406 112.392 15.9505 106.562 13.7605C118.582 18.2205 128.652 21.8805 130.602 22.4605C131.332 22.6805 131.782 23.6205 131.602 24.5605C131.382 25.7205 126.992 27.9305 117.782 31.5005C110.152 34.4605 105.932 36.0405 103.612 36.4805ZM5.11183 55.7405C5.41183 56.7105 5.32183 58.1405 4.78183 60.3105C5.22183 58.2605 5.35183 56.6205 5.11183 55.7405ZM101.192 36.1505C100.842 35.7305 100.772 35.0406 100.762 34.1106C100.772 34.9206 100.932 35.6405 101.192 36.1505Z" fill="#9881E4"/>
    </svg>''';
    return SvgPicture.string(rawSvg, height: 80);
  }
}