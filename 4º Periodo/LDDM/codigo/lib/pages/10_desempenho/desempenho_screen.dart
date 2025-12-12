import 'package:flutter/material.dart';
import '../../shared/theme/app_colors.dart';
import '../../services/database_service.dart';
import '../11_relatorio/relatorio_screen.dart';

class DesempenhoScreen extends StatefulWidget {
  final int userId;
  const DesempenhoScreen({super.key, required this.userId});

  @override
  State<DesempenhoScreen> createState() => _DesempenhoScreenState();
}

class _DesempenhoScreenState extends State<DesempenhoScreen> {
  final dbService = DatabaseService();
  late Future<List<StudyPerformance>> _statsFuture;

  @override
  void initState() {
    super.initState();
    _statsFuture = dbService.getPerformanceStats(widget.userId);
  }

  @override
  Widget build(BuildContext context) {
    final theme = Theme.of(context);

    return Scaffold(
      appBar: AppBar(title: const Text('Desempenho')),
      body: SafeArea(
        child: Column(
          children: [
            Expanded(
              child: FutureBuilder<List<StudyPerformance>>(
                future: _statsFuture,
                builder: (context, snapshot) {
                  // Caso 1: Carregando
                  if (snapshot.connectionState == ConnectionState.waiting) {
                    return const Center(
                      child: CircularProgressIndicator(
                        color: AppColors.purplePrimary,
                      ),
                    );
                  }

                  // Caso 2: Erro
                  if (snapshot.hasError) {
                    return Center(
                      child: Padding(
                        padding: const EdgeInsets.all(24.0),
                        child: Column(
                          mainAxisAlignment: MainAxisAlignment.center,
                          children: [
                            const Icon(
                              Icons.error_outline,
                              size: 64,
                              color: AppColors.red,
                            ),
                            const SizedBox(height: 16),
                            Text(
                              'Erro ao carregar dados: ${snapshot.error}',
                              style: theme.textTheme.bodyLarge,
                              textAlign: TextAlign.center,
                            ),
                            const SizedBox(height: 16),
                            ElevatedButton(
                              onPressed: () {
                                setState(() {
                                  _statsFuture = dbService.getPerformanceStats(
                                    widget.userId,
                                  );
                                });
                              },
                              style: ElevatedButton.styleFrom(
                                backgroundColor: AppColors.purplePrimary,
                              ),
                              child: const Text('Tentar Novamente'),
                            ),
                          ],
                        ),
                      ),
                    );
                  }

                  // Caso 3: Sem dados
                  if (!snapshot.hasData || snapshot.data!.isEmpty) {
                    return Center(
                      child: Padding(
                        padding: const EdgeInsets.all(24.0),
                        child: Column(
                          mainAxisAlignment: MainAxisAlignment.center,
                          children: [
                            Icon(
                              Icons.assessment_outlined,
                              size: 80,
                              color: theme.textTheme.bodyMedium?.color
                                  ?.withOpacity(0.5),
                            ),
                            const SizedBox(height: 16),
                            Text(
                              'Nenhuma sessão de estudo registrada ainda',
                              style: theme.textTheme.titleLarge?.copyWith(
                                fontWeight: FontWeight.bold,
                              ),
                              textAlign: TextAlign.center,
                            ),
                            const SizedBox(height: 8),
                            Text(
                              'Complete um Pomodoro para ver suas estatísticas!',
                              style: theme.textTheme.bodyLarge,
                              textAlign: TextAlign.center,
                            ),
                          ],
                        ),
                      ),
                    );
                  }

                  // Caso 4: Sucesso!
                  final stats = snapshot.data!;

                  // Calcula tempo total e máximo para as barras de progresso
                  final totalMinutes = stats.fold<int>(
                    0,
                    (sum, item) => sum + item.totalMinutes,
                  );
                  final maxMinutes = stats.isNotEmpty
                      ? stats
                            .map((e) => e.totalMinutes)
                            .reduce((a, b) => a > b ? a : b)
                      : 1;

                  return SingleChildScrollView(
                    child: Padding(
                      padding: const EdgeInsets.all(16.0),
                      child: Column(
                        crossAxisAlignment: CrossAxisAlignment.start,
                        children: [
                          const SizedBox(height: 8),

                          // Card de resumo com tempo total
                          _buildResumoCard(theme, totalMinutes, stats.length),

                          const SizedBox(height: 24),

                          // Título da seção
                          Text(
                            'Tempo por Matéria',
                            style: theme.textTheme.titleLarge?.copyWith(
                              fontWeight: FontWeight.bold,
                            ),
                          ),

                          const SizedBox(height: 16),

                          // Lista de matérias
                          ListView.separated(
                            shrinkWrap: true,
                            physics: const NeverScrollableScrollPhysics(),
                            itemCount: stats.length,
                            separatorBuilder: (context, index) =>
                                const SizedBox(height: 12),
                            itemBuilder: (context, index) {
                              final stat = stats[index];

                              // Alterna entre várias cores disponíveis
                              final colors = [
                                AppColors.purplePrimary,
                                AppColors.green,
                                AppColors.blueLight,
                                AppColors.orangeLight,
                                AppColors.pink,
                              ];
                              final cor = colors[index % colors.length];

                              return _buildMateriaCard(
                                theme: theme,
                                titulo: stat.subject,
                                tempo: stat.formattedTime,
                                totalMinutes: stat.totalMinutes,
                                maxMinutes: maxMinutes,
                                cor: cor,
                              );
                            },
                          ),

                          const SizedBox(height: 80),
                        ],
                      ),
                    ),
                  );
                },
              ),
            ),

            // Botão fixo na parte inferior
            Padding(
              padding: const EdgeInsets.all(16.0),
              child: SizedBox(
                width: double.infinity,
                height: 56,
                child: ElevatedButton(
                  onPressed: () {
                    Navigator.push(
                      context,
                      MaterialPageRoute(
                        builder: (context) =>
                            RelatorioScreen(userId: widget.userId),
                      ),
                    );
                  },
                  style: ElevatedButton.styleFrom(
                    backgroundColor: AppColors.purplePrimary,
                    shape: RoundedRectangleBorder(
                      borderRadius: BorderRadius.circular(28),
                    ),
                    elevation: 2,
                  ),
                  child: const Text(
                    'Ver Relatório Completo',
                    style: TextStyle(
                      fontSize: 16,
                      fontWeight: FontWeight.w500,
                      color: AppColors.white,
                    ),
                  ),
                ),
              ),
            ),
          ],
        ),
      ),
    );
  }

  // Card de resumo com tempo total
  Widget _buildResumoCard(ThemeData theme, int totalMinutes, int numMaterias) {
    final hours = totalMinutes ~/ 60;
    final minutes = totalMinutes % 60;
    final formattedTotal = hours > 0
        ? '${hours}h ${minutes}min'
        : '${minutes}min';

    return Container(
      width: double.infinity,
      padding: const EdgeInsets.all(24.0),
      decoration: BoxDecoration(
        gradient: LinearGradient(
          colors: [
            AppColors.purplePrimary,
            AppColors.purplePrimary.withOpacity(0.7),
          ],
          begin: Alignment.topLeft,
          end: Alignment.bottomRight,
        ),
        borderRadius: BorderRadius.circular(16),
        boxShadow: [
          BoxShadow(
            color: AppColors.purplePrimary.withOpacity(0.3),
            spreadRadius: 1,
            blurRadius: 8,
            offset: const Offset(0, 4),
          ),
        ],
      ),
      child: Column(
        children: [
          const Icon(Icons.access_time, size: 48, color: AppColors.white),
          const SizedBox(height: 12),
          const Text(
            'Tempo Total de Estudo',
            style: TextStyle(
              fontSize: 14,
              color: AppColors.textOnPurple,
              fontWeight: FontWeight.w500,
            ),
          ),
          const SizedBox(height: 8),
          Text(
            formattedTotal,
            style: const TextStyle(
              fontSize: 36,
              fontWeight: FontWeight.bold,
              color: AppColors.white,
            ),
          ),
          const SizedBox(height: 8),
          Text(
            '$numMaterias ${numMaterias == 1 ? "matéria" : "matérias"}',
            style: const TextStyle(fontSize: 14, color: AppColors.textOnPurple),
          ),
        ],
      ),
    );
  }

  // Card de matéria com barra de progresso
  Widget _buildMateriaCard({
    required ThemeData theme,
    required String titulo,
    required String tempo,
    required int totalMinutes,
    required int maxMinutes,
    required Color cor,
  }) {
    // Calcula a porcentagem para a barra de progresso
    final percentage = maxMinutes > 0 ? totalMinutes / maxMinutes : 0.0;

    return Container(
      width: double.infinity,
      decoration: BoxDecoration(
        color: theme.cardTheme.color ?? AppColors.white,
        borderRadius: BorderRadius.circular(12),
        boxShadow: [
          BoxShadow(
            color: Colors.black.withOpacity(0.06),
            spreadRadius: 1,
            blurRadius: 4,
            offset: const Offset(0, 2),
          ),
        ],
      ),
      child: Padding(
        padding: const EdgeInsets.all(16.0),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            Row(
              children: [
                // Ícone da matéria
                Container(
                  width: 48,
                  height: 48,
                  decoration: BoxDecoration(
                    color: cor.withOpacity(0.15),
                    borderRadius: BorderRadius.circular(8),
                  ),
                  child: Icon(Icons.book_outlined, color: cor, size: 24),
                ),

                const SizedBox(width: 12),

                // Nome e tempo
                Expanded(
                  child: Column(
                    crossAxisAlignment: CrossAxisAlignment.start,
                    children: [
                      Text(
                        titulo,
                        style: theme.textTheme.bodyLarge?.copyWith(
                          fontWeight: FontWeight.bold,
                        ),
                        maxLines: 2,
                        overflow: TextOverflow.ellipsis,
                      ),
                      const SizedBox(height: 4),
                      Text(tempo, style: theme.textTheme.bodyMedium),
                    ],
                  ),
                ),

                // Badge com porcentagem
                Container(
                  padding: const EdgeInsets.symmetric(
                    horizontal: 12,
                    vertical: 6,
                  ),
                  decoration: BoxDecoration(
                    color: cor.withOpacity(0.1),
                    borderRadius: BorderRadius.circular(12),
                  ),
                  child: Text(
                    '${(percentage * 100).toStringAsFixed(0)}%',
                    style: TextStyle(
                      fontSize: 12,
                      fontWeight: FontWeight.bold,
                      color: cor,
                    ),
                  ),
                ),
              ],
            ),

            const SizedBox(height: 12),

            // Barra de progresso
            ClipRRect(
              borderRadius: BorderRadius.circular(4),
              child: LinearProgressIndicator(
                value: percentage,
                minHeight: 8,
                backgroundColor: AppColors.lightGrey,
                valueColor: AlwaysStoppedAnimation<Color>(cor),
              ),
            ),
          ],
        ),
      ),
    );
  }
}
