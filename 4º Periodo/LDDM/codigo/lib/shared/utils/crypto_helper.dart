import 'package:crypto/crypto.dart';
import 'dart:convert';

class CryptoHelper {
  static const String _secretKey = 'SECRET_KEY'; // Mudar chave depois
  // static final String _secretKey = const String.fromEnvironment('SECRET_KEY');

  static String hashPassword(String password) {
    final key = utf8.encode(_secretKey);
    final bytes = utf8.encode(password);
    final hmacSha256 = Hmac(sha256, key);
    final digest = hmacSha256.convert(bytes);
    return digest.toString();
  }

  static bool verifyPassword(String password, String hashedPassword) {
    final hash = hashPassword(password);
    return hash == hashedPassword;
  }
}
