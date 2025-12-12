import 'package:flutter/material.dart';
import 'package:showcaseview/showcaseview.dart';

class ChatInputField extends StatelessWidget {
  final TextEditingController controller;
  final FocusNode focusNode;
  final Function(String) onSubmitted;
  final GlobalKey textFieldKey;
  final GlobalKey sendButtonKey;

  const ChatInputField({
    super.key,
    required this.controller,
    required this.focusNode,
    required this.onSubmitted,
    required this.textFieldKey,
    required this.sendButtonKey,
  });

  @override
  Widget build(BuildContext context) {
    final theme = Theme.of(context);
    return Container(
      padding: const EdgeInsets.symmetric(
        horizontal: 8.0,
      ).copyWith(bottom: MediaQuery.of(context).padding.bottom),
      decoration: BoxDecoration(
        color: theme.colorScheme.surface,
        boxShadow: [
          BoxShadow(
            offset: const Offset(0, -2),
            blurRadius: 4,
            color: Colors.black.withOpacity(0.05),
          ),
        ],
      ),
      child: SafeArea(
        top: false,
        child: Padding(
          padding: const EdgeInsets.symmetric(vertical: 8.0),
          child: Row(
            children: [
              Expanded(
                child: Showcase(
                  key: textFieldKey,
                  description: 'Digite sua pergunta sobre os documentos aqui',
                  child: TextField(
                    controller: controller,
                    focusNode: focusNode,
                    onSubmitted: onSubmitted,
                    decoration: InputDecoration(
                      hintText: 'Digite sua pergunta...',
                      filled: true,
                      fillColor: theme.colorScheme.surfaceVariant,
                      border: OutlineInputBorder(
                        borderRadius: BorderRadius.circular(24.0),
                        borderSide: BorderSide.none,
                      ),
                      contentPadding: const EdgeInsets.symmetric(
                        horizontal: 20.0,
                        vertical: 12.0,
                      ),
                    ),
                  ),
                ),
              ),
              const SizedBox(width: 8),
              Showcase(
                key: sendButtonKey,
                description: 'Pressione aqui para enviar sua pergunta',
                child: IconButton(
                  icon: const Icon(Icons.send),
                  color: theme.colorScheme.primary,
                  onPressed: () {
                    onSubmitted(controller.text);
                  },
                ),
              ),
            ],
          ),
        ),
      ),
    );
  }
}
