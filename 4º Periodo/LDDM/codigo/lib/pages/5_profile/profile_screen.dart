import 'dart:io';
import 'package:flutter/material.dart';
import 'package:image_picker/image_picker.dart';
import '../../shared/theme/app_colors.dart';
import '../../services/database_service.dart'; // Importa o DB Service

// Modelo para os dados do usuário.
class UserModel {
  final int id_usuario;
  final String name;
  final String email;
  final String phone;

  UserModel({
    required this.id_usuario,
    required this.name,
    this.email = '', 
    this.phone = '', 
  });

  // Mapeia os dados do mapa do DB para o modelo (agora incluindo email e telefone)
  factory UserModel.fromMap(Map<String, dynamic> map) {
    // Note: O DB usa 'telefone', mas o modelo usa 'phone'
    return UserModel(
      id_usuario: map['id_usuario'],
      name: map['nome'],
      email: map['email'] ?? '',
      phone: map['telefone'] ?? '', // Mapeia 'telefone' do DB para 'phone' do modelo
    );
  }
}

// Widget principal da tela de Perfil
class PerfilPage extends StatefulWidget {
  final int userId;
  const PerfilPage({super.key, required this.userId});

  @override
  State<PerfilPage> createState() => _PerfilPageState();
}

class _PerfilPageState extends State<PerfilPage> {
  File? _imageFile;
  final dbService = DatabaseService();
  UserModel? _user;
  bool _isLoading = true;

  late final TextEditingController _emailController;
  late final TextEditingController _telefoneController;

  @override
  void initState() {
    super.initState();
    _emailController = TextEditingController();
    _telefoneController = TextEditingController();
    _loadUserData();
  }

  // --- FUNÇÃO DE READ (Leitura) ---
  Future<void> _loadUserData() async {
    setState(() => _isLoading = true);
    final userMap = await dbService.getUserById(widget.userId);
    if (userMap != null && mounted) {
      setState(() {
        _user = UserModel.fromMap(userMap);
        _emailController.text = _user!.email;
        _telefoneController.text = _user!.phone;
        _isLoading = false;
      });
    } else if (mounted) {
      setState(() => _isLoading = false);
      ScaffoldMessenger.of(context).showSnackBar(
          const SnackBar(content: Text('Erro: Usuário não encontrado.'))
      );
    }
  }

  // --- FUNÇÃO DE UPDATE (Atualização) ---
  Future<void> _saveChanges() async {
    if (_user == null || !mounted) return;
    
    final email = _emailController.text.trim();
    final telefone = _telefoneController.text.trim();

    // Impedir salvar se não houver mudança nos campos editáveis
    if (email == _user!.email && telefone == _user!.phone) {
      ScaffoldMessenger.of(context).showSnackBar(
          const SnackBar(content: Text('Nenhuma alteração detectada.'))
      );
      return;
    }
    
    setState(() => _isLoading = true); 

    try {
      final rowsAffected = await dbService.updateUser(
        idUsuario: widget.userId,
        newEmail: email,
        newPhone: telefone,
      );
      
      if (mounted) {
        if (rowsAffected > 0) {
          // Recarrega os dados para atualizar o _user localmente
          await _loadUserData(); 
          
          ScaffoldMessenger.of(context).showSnackBar(
              const SnackBar(content: Text('Perfil atualizado com sucesso! 🎉'))
          );
        } else {
          setState(() => _isLoading = false);
          ScaffoldMessenger.of(context).showSnackBar(
              const SnackBar(content: Text('Erro ao atualizar. Usuário não encontrado.'))
          );
        }
      }
    } catch (e) {
      if (mounted) {
        setState(() => _isLoading = false);
        ScaffoldMessenger.of(context).showSnackBar(
            SnackBar(content: Text('Erro ao salvar: ${e.toString()}'))
        );
      }
    }
  }

  @override
  void dispose() {
    _emailController.dispose();
    _telefoneController.dispose();
    super.dispose();
  }

  Future<void> _pickImageFromGallery() async {
    final ImagePicker picker = ImagePicker();
    final XFile? pickedFile = await picker.pickImage(source: ImageSource.gallery);
    if (pickedFile != null) {
      setState(() {
        _imageFile = File(pickedFile.path);
      });
    }
  }

  @override
  Widget build(BuildContext context) {
    if (_isLoading) {
      return const Center(child: CircularProgressIndicator());
    }

    if (_user == null) {
      return const Center(child: Text('Não foi possível carregar o perfil.'));
    }

    // Passa a função de salvamento (onSave) para o widget de corpo.
    return PerfilBody(
      user: _user!,
      emailController: _emailController,
      telefoneController: _telefoneController,
      imageFile: _imageFile,
      onAvatarTap: _pickImageFromGallery,
      onSave: _saveChanges, // <<-- FUNÇÃO AGORA SENDO PASSADA
    );
  }
}

// (O PerfilBody constrói a UI da tela.)
class PerfilBody extends StatelessWidget {
  final UserModel user;
  final TextEditingController emailController;
  final TextEditingController telefoneController;
  final File? imageFile;
  final VoidCallback onAvatarTap;
  final VoidCallback onSave; // <<-- 1. ADICIONADO AQUI

  const PerfilBody({
    super.key,
    required this.user,
    required this.emailController,
    required this.telefoneController,
    this.imageFile,
    required this.onAvatarTap,
    required this.onSave, // <<-- 2. ADICIONADO AO CONSTRUTOR
  });

  @override
  Widget build(BuildContext context) {
    // Estrutura principal com header fixo e conteúdo rolável.
    return Column(
      children: [
        // 1. O novo header roxo com o nome do usuário.
        _buildHeader(context, user.name),

        // 2. O resto do conteúdo é colocado dentro de um Expanded para ser rolável.
        Expanded(
          child: SingleChildScrollView(
            padding: const EdgeInsets.symmetric(horizontal: 24.0),
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.center,
              children: [
                const SizedBox(height: 32),
                _buildAvatar(context, onAvatarTap, imageFile),
                const SizedBox(height: 48),
                _buildEditableFields(context, emailController, telefoneController),
                const SizedBox(height: 80),
                // Passa o onSave, que será a função _saveChanges do State
                _buildSaveButton(context), 
                const SizedBox(height: 32),
              ],
            ),
          ),
        ),
      ],
    );
  }

  // Constrói a faixa roxa no topo da tela.
  Widget _buildHeader(BuildContext context, String userName) {
    final theme = Theme.of(context);
    return Container(
      width: double.infinity,
      padding: const EdgeInsets.symmetric(vertical: 24, horizontal: 24),
      color: theme.colorScheme.primary, // Cor roxa do tema
      child: SafeArea(
        bottom: false, // O SafeArea se aplica apenas ao topo.
        child: Text(
          'Olá, $userName',
          style: theme.textTheme.titleLarge?.copyWith(
            color: AppColors.white, // Texto branco
          ),
          textAlign: TextAlign.center,
        ),
      ),
    );
  }

  // Constrói o avatar clicável.
  Widget _buildAvatar(BuildContext context, VoidCallback onTap, File? imageFile) {
    return InkWell(
      onTap: onTap,
      borderRadius: BorderRadius.circular(15),
      child: Container(
        width: 120,
        height: 120,
        decoration: BoxDecoration(
          color: AppColors.lightGrey,
          borderRadius: BorderRadius.circular(15),
          boxShadow: [ BoxShadow(color: Colors.black.withOpacity(0.05), blurRadius: 10, offset: const Offset(0, 5)) ],
        ),
        child: ClipRRect(
          borderRadius: BorderRadius.circular(15),
          child: Stack(
            alignment: Alignment.center,
            children: [
              if (imageFile != null)
                Image.file(imageFile, width: 120, height: 120, fit: BoxFit.cover)
              else
                Icon(Icons.person, size: 60, color: Theme.of(context).colorScheme.primary.withOpacity(0.7)),
              Positioned(
                bottom: 8,
                right: 8,
                child: Container(
                  padding: const EdgeInsets.all(4),
                  decoration: BoxDecoration(
                    color: Theme.of(context).colorScheme.primary,
                    shape: BoxShape.circle,
                    border: Border.all(color: AppColors.white, width: 2),
                  ),
                  child: const Icon(Icons.edit, size: 16, color: AppColors.white),
                ),
              ),
            ],
          ),
        ),
      ),
    );
  }

  // Constrói os campos de texto editáveis.
  Widget _buildEditableFields(BuildContext context, TextEditingController email, TextEditingController telefone) {
    return Column(
      children: [
        _EditableProfileField(label: 'email', controller: email, keyboardType: TextInputType.emailAddress),
        const Divider(height: 1, color: AppColors.lightGrey),
        _EditableProfileField(label: 'telefone', controller: telefone, keyboardType: TextInputType.phone),
        const Divider(height: 1, color: AppColors.lightGrey),
        _ActionProfileItem(label: 'senha', value: 'troque a senha', onTap: () => print('Navegar para Trocar Senha')),
        const Divider(height: 1, color: AppColors.lightGrey),
      ],
    );
  }

  // Constrói o botão de salvar.
  Widget _buildSaveButton(BuildContext context) {
    return SizedBox(
      width: double.infinity,
      child: ElevatedButton(
        onPressed: onSave, // <<-- 3. CHAMA A FUNÇÃO onSave RECEBIDA
        style: Theme.of(context).elevatedButtonTheme.style,
        child: const Text('SALVAR ALTERAÇÕES'),
      ),
    );
  }
}

// Widget auxiliar para os campos de texto.
class _EditableProfileField extends StatelessWidget {
  final String label;
  final TextEditingController controller;
  final TextInputType keyboardType;
  final ValueChanged<String>? onChanged;

  const _EditableProfileField({
    required this.label,
    required this.controller,
    this.keyboardType = TextInputType.text,
    this.onChanged,
  });

  @override
  Widget build(BuildContext context) {
    final bodyMediumStyle = Theme.of(context).textTheme.bodyMedium;
    return Padding(
      padding: const EdgeInsets.symmetric(vertical: 8.0),
      child: Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          Text(label.toUpperCase(), style: bodyMediumStyle?.copyWith(fontWeight: FontWeight.bold)),
          const SizedBox(height: 4),
          TextFormField(
            controller: controller,
            keyboardType: keyboardType,
            onChanged: onChanged,
            style: Theme.of(context).textTheme.bodyLarge,
            decoration: const InputDecoration(border: InputBorder.none, isDense: true, contentPadding: EdgeInsets.zero),
          ),
        ],
      ),
    );
  }
}

// Widget auxiliar para itens de ação.
class _ActionProfileItem extends StatelessWidget {
  final String label;
  final String value;
  final VoidCallback onTap;

  const _ActionProfileItem({
    required this.label,
    required this.value,
    required this.onTap,
  });

  @override
  Widget build(BuildContext context) {
    final bodyMediumStyle = Theme.of(context).textTheme.bodyMedium;
    final bodyLargeStyle = Theme.of(context).textTheme.bodyLarge;
    return InkWell(
      onTap: onTap,
      borderRadius: BorderRadius.circular(8),
      child: Padding(
        padding: const EdgeInsets.symmetric(vertical: 16.0),
        child: Row(
          mainAxisAlignment: MainAxisAlignment.spaceBetween,
          children: [
            Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                Text(label.toUpperCase(), style: bodyMediumStyle?.copyWith(fontWeight: FontWeight.bold)),
                const SizedBox(height: 4),
                Text(value, style: bodyLargeStyle),
              ],
            ),
            Icon(Icons.arrow_forward_ios, size: 16, color: Theme.of(context).colorScheme.primary),
          ],
        ),
      ),
    );
  }
}
