# Código do Projeto: SmartStudy

Este diretório contém todo o código-fonte do aplicativo móvel SmartStudy, desenvolvido utilizando o framework Flutter e a linguagem Dart.

A organização do código foi pensada para ser escalável, modular e fácil de entender, especialmente para equipes. Seguimos uma abordagem de "Feature-First" (ou "Funcionalidade Primeiro"), onde os arquivos são agrupados por funcionalidade/tela, e não por tipo.

Estrutura de Diretórios
Abaixo está a descrição das principais pastas e sua finalidade:

assets/: Contém todos os recursos estáticos do aplicativo.

assets/images/: Para todas as imagens, ícones e ilustrações.

lib/: O coração do projeto. Todo o nosso código Dart reside aqui.

main.dart: A porta de entrada da aplicação. Este arquivo é responsável por inicializar o app e definir o tema principal. Ele deve ser mantido o mais limpo possível.

shared/: Pasta dedicada a todo e qualquer código que pode ser reutilizado em múltiplas partes do aplicativo.

shared/theme/: Contém a identidade visual do app.

app_colors.dart: Define a paleta de cores padrão.

app_theme.dart: Define o ThemeData global (estilos de texto, botões, etc.).

shared/widgets/: Contém widgets customizados e reutilizáveis, como a nossa CustomNavBar, botões padrão, cards, etc.

shared/models/: (Para uso futuro) Conterá as classes que modelam os dados do nosso app (ex: UserModel, TaskModel).

pages/: A pasta mais importante para o desenvolvimento do dia a dia. Cada subpasta aqui dentro representa uma tela ou uma funcionalidade principal do aplicativo.
