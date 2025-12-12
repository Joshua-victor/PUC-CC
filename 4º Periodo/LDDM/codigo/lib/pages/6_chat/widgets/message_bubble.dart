// lib/pages/6_chat/widgets/message_bubble.dart

import 'package:flutter/material.dart';
import '../chat_screen.dart';

class MessageBubble extends StatelessWidget {
  final ChatMessage message;

  const MessageBubble({super.key, required this.message});

  @override
  Widget build(BuildContext context) {
    final theme = Theme.of(context);
    final isSentByMe = message.isSentByMe;

    final alignment = isSentByMe ? CrossAxisAlignment.end : CrossAxisAlignment.start;
    final color = isSentByMe ? theme.colorScheme.primary : theme.colorScheme.surface;
    final textColor = isSentByMe ? theme.colorScheme.onPrimary : theme.colorScheme.onSurface;
    final borderRadius = isSentByMe
        ? const BorderRadius.only(
      topLeft: Radius.circular(12.0),
      bottomLeft: Radius.circular(12.0),
      bottomRight: Radius.circular(12.0),
    )
        : const BorderRadius.only(
      topRight: Radius.circular(12.0),
      bottomLeft: Radius.circular(12.0),
      bottomRight: Radius.circular(12.0),
    );

    return Container(
      margin: const EdgeInsets.symmetric(vertical: 5.0),
      child: Column(
        crossAxisAlignment: alignment,
        children: [
          Text(
            isSentByMe ? 'Você' : 'Assistente',
            style: theme.textTheme.bodyMedium,
          ),
          const SizedBox(height: 5),
          Container(
            padding: const EdgeInsets.symmetric(horizontal: 16.0, vertical: 10.0),
            constraints: BoxConstraints(maxWidth: MediaQuery.of(context).size.width * 0.75),
            decoration: BoxDecoration(
                color: color,
                borderRadius: borderRadius,
                border: isSentByMe ? null : Border.all(color: theme.dividerColor, width: 1)
            ),
            // Lógica para mostrar o indicador de "carregando"
            child: message.isLoading
                ? SizedBox(
              width: 20,
              height: 20,
              child: CircularProgressIndicator(
                strokeWidth: 2,
                color: textColor,
              ),
            )
                : Text(
              message.text,
              style: theme.textTheme.bodyLarge?.copyWith(color: textColor),
            ),
          ),
        ],
      ),
    );
  }
}