// lib/services/api_service.dart

import 'dart:convert';
import 'package:http/http.dart' as http;
import 'package:file_picker/file_picker.dart';
import 'dart:async';
// Remova o import do chat_screen se não estiver usando classes dele aqui, 
// ou mantenha se DocumentFile estiver lá. Normalmente models ficam em arquivos separados.

class ApiService {
  // --- AJUSTE AQUI ---
  // Para Emulador Android use: 'http://10.0.2.2:8000'
  // Para iOS Simulator use: 'http://127.0.0.1:8000'
  // Para Dispositivo Físico: Use o IP da sua máquina na rede (ex: 192.168.x.x)
  final String _baseUrl = 'http://10.0.2.2:8000';
  // -------------------

  Future<void> uploadFile(String chatId, PlatformFile file) async {
    final uri = Uri.parse('$_baseUrl/upload/$chatId');
    final request = http.MultipartRequest('POST', uri);

    // Adiciona o arquivo
    request.files.add(
      http.MultipartFile.fromBytes(
          'file',
          file.bytes!,
          filename: file.name
      ),
    );

    try {
      final response = await request.send();
      if (response.statusCode != 200) {
        // Lê a resposta para saber o erro detalhado do servidor
        final respStr = await response.stream.bytesToString();
        throw Exception('Falha no upload (${response.statusCode}): $respStr');
      }
    } catch (e) {
      print("Erro API Upload: $e");
      throw Exception('Não foi possível conectar ao servidor para upload.');
    }
  }

  Future<String> sendMessage(String chatId, String message) async {
    final uri = Uri.parse('$_baseUrl/chat/$chatId');
    try {
      final response = await http.post(
        uri,
        headers: {'Content-Type': 'application/json'},
        body: jsonEncode({'question': message}),
      );

      if (response.statusCode == 200) {
        // Decodifica UTF-8 corretamente para acentos
        final data = jsonDecode(utf8.decode(response.bodyBytes));

        String answer = data['answer'] ?? 'Erro ao decodificar resposta.';
        List<dynamic> sourcesRaw = data['sources'] ?? [];
        List<String> sources = sourcesRaw.cast<String>();

        // Formata as fontes, se houver
        if (sources.isNotEmpty) {
          // Remove duplicatas e formata
          final uniqueSources = sources.toSet().join(', ');
          answer += '\n\n📚 Fontes: $uniqueSources';
        }

        return answer;
      } else {
        throw Exception('Erro na API (${response.statusCode}): ${response.body}');
      }
    } catch (e) {
      print("Erro API Chat: $e");
      throw Exception('Falha na conexão com o assistente.');
    }
  }

  // Método para buscar a lista de arquivos do backend
  Future<List<String>> getFiles(String chatId) async {
    final uri = Uri.parse('$_baseUrl/files/$chatId');
    try {
      final response = await http.get(uri);
      if (response.statusCode == 200) {
        final List<dynamic> data = jsonDecode(utf8.decode(response.bodyBytes));
        return data.cast<String>();
      } else {
        // Se der 404 (chat novo), retorna lista vazia em vez de erro
        if (response.statusCode == 404) return [];
        throw Exception('Falha ao buscar arquivos: ${response.statusCode}');
      }
    } catch (e) {
      print("Erro API GetFiles: $e");
      // Retorna vazio em caso de erro de conexão para não travar a tela
      return [];
    }
  }

  // Método para deletar um arquivo no backend
  Future<void> deleteFile(String chatId, String fileName) async {
    // Codifica o nome do arquivo para URL (espaços, acentos, etc)
    final uri = Uri.parse(
      '$_baseUrl/files/$chatId?filename=${Uri.encodeComponent(fileName)}',
    );
    try {
      final response = await http.delete(uri);
      if (response.statusCode != 200) {
        throw Exception('Falha ao deletar arquivo: ${response.statusCode}');
      }
    } catch (e) {
      throw Exception('Erro ao conectar para deletar arquivo.');
    }
  }
}