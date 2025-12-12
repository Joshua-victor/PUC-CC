// lib/pages/11_relatorio/relatorio_screen.dart
import 'package:flutter/material.dart';
import 'package:intl/intl.dart';
import 'package:fl_chart/fl_chart.dart';
import '../../shared/theme/app_colors.dart';
import '../../services/database_service.dart';

class RelatorioScreen extends StatefulWidget {
  final int userId;

  const RelatorioScreen({super.key, required this.userId});

  @override
  State<RelatorioScreen> createState() => _RelatorioScreenState();
}

class _RelatorioScreenState extends State<RelatorioScreen> with SingleTickerProviderStateMixin {
  final dbService = DatabaseService();

  // TabController para alternar entre diferentes visualizações
  late TabController _tabController;

  // Futures para carregar dados
  late Future<Map<String, dynamic>> _statisticsFuture;
  late Future<List<Map<String, dynamic>>> _dailyDataFuture;
  late Future<List<Map<String, dynamic>>> _weekdayDataFuture;
  late Future<List<Map<String, dynamic>>> _subjectDistributionFuture;

  // Período selecionado para o gráfico de linha
  int _selectedDays = 7; // 7 ou 30 dias

  @override
  void initState() {
    super.initState();
    _tabController = TabController(length: 3, vsync: this);
    _loadData();
  }

  void _loadData() {
    _statisticsFuture = dbService.getStudyStatistics(widget.userId);
    _dailyDataFuture = dbService.getDailyStudyData(widget.userId, days: _selectedDays);
    _weekdayDataFuture = dbService.getWeekdayStudyData(widget.userId);
    _subjectDistributionFuture = dbService.getSubjectDistribution(widget.userId);
  }

  @override
  void dispose() {
    _tabController.dispose();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    final theme = Theme.of(context);

    return Scaffold(
      appBar: AppBar(
        title: const Text('Relatório Completo'),
        bottom: TabBar(
          controller: _tabController,
          indicatorColor: AppColors.white,
          labelColor: AppColors.white,
          unselectedLabelColor: AppColors.white.withOpacity(0.7),
          tabs: const [
            Tab(icon: Icon(Icons.bar_chart), text: 'Visão Geral'),
            Tab(icon: Icon(Icons.show_chart), text: 'Evolução'),
            Tab(icon: Icon(Icons.pie_chart), text: 'Distribuição'),
          ],
        ),
      ),
      body: TabBarView(
        controller: _tabController,
        children: [
          _buildOverviewTab(),
          _buildEvolutionTab(),
          _buildDistributionTab(),
        ],
      ),
    );
  }

  // ========== ABA 1: VISÃO GERAL ==========
  Widget _buildOverviewTab() {
    return FutureBuilder<Map<String, dynamic>>(
      future: _statisticsFuture,
      builder: (context, snapshot) {
        if (snapshot.connectionState == ConnectionState.waiting) {
          return const Center(
            child: CircularProgressIndicator(color: AppColors.purplePrimary),
          );
        }

        if (snapshot.hasError) {
          return _buildErrorWidget(() {
            setState(() => _loadData());
          });
        }

        if (!snapshot.hasData) {
          return _buildEmptyWidget();
        }

        final stats = snapshot.data!;

        return SingleChildScrollView(
          padding: const EdgeInsets.all(16.0),
          child: Column(
            crossAxisAlignment: CrossAxisAlignment.start,
            children: [
              // Cards de estatísticas principais
              _buildStatsCards(stats),

              const SizedBox(height: 24),

              // Gráfico de produtividade por dia da semana
              Text(
                'Produtividade por Dia da Semana',
                style: Theme.of(context).textTheme.titleLarge?.copyWith(
                  fontWeight: FontWeight.bold,
                ),
              ),
              const SizedBox(height: 16),
              _buildWeekdayChart(),
            ],
          ),
        );
      },
    );
  }

  // Cards com estatísticas principais
  Widget _buildStatsCards(Map<String, dynamic> stats) {
    final totalMinutes = stats['totalMinutes'] as int;
    final totalSessions = stats['totalSessions'] as int;
    final avgMinutes = stats['avgDailyMinutes'] as double;
    final streak = stats['currentStreak'] as int;

    return Column(
      children: [
        Row(
          children: [
            Expanded(
              child: _buildStatCard(
                icon: Icons.access_time,
                title: 'Tempo Total',
                value: _formatDuration(totalMinutes),
                color: AppColors.purplePrimary,
              ),
            ),
            const SizedBox(width: 12),
            Expanded(
              child: _buildStatCard(
                icon: Icons.play_circle_outline,
                title: 'Sessões',
                value: '$totalSessions',
                color: AppColors.green,
              ),
            ),
          ],
        ),
        const SizedBox(height: 12),
        Row(
          children: [
            Expanded(
              child: _buildStatCard(
                icon: Icons.trending_up,
                title: 'Média Diária',
                value: '${avgMinutes.toStringAsFixed(0)}min',
                color: AppColors.blueLight,
              ),
            ),
            const SizedBox(width: 12),
            Expanded(
              child: _buildStatCard(
                icon: Icons.local_fire_department,
                title: 'Sequência',
                value: '$streak ${streak == 1 ? "dia" : "dias"}',
                color: AppColors.orangeLight,
              ),
            ),
          ],
        ),
      ],
    );
  }

  Widget _buildStatCard({
    required IconData icon,
    required String title,
    required String value,
    required Color color,
  }) {
    return Container(
      padding: const EdgeInsets.all(16.0),
      decoration: BoxDecoration(
        color: color.withOpacity(0.1),
        borderRadius: BorderRadius.circular(12),
        border: Border.all(color: color.withOpacity(0.3)),
      ),
      child: Column(
        crossAxisAlignment: CrossAxisAlignment.start,
        children: [
          Icon(icon, color: color, size: 32),
          const SizedBox(height: 8),
          Text(
            title,
            style: TextStyle(
              fontSize: 12,
              color: color,
              fontWeight: FontWeight.w500,
            ),
          ),
          const SizedBox(height: 4),
          Text(
            value,
            style: TextStyle(
              fontSize: 20,
              fontWeight: FontWeight.bold,
              color: color,
            ),
          ),
        ],
      ),
    );
  }

  // ========== ABA 2: EVOLUÇÃO TEMPORAL ==========
  Widget _buildEvolutionTab() {
    return Column(
      children: [
        // Seletor de período
        Padding(
          padding: const EdgeInsets.all(16.0),
          child: Row(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              _buildPeriodButton('7 dias', 7),
              const SizedBox(width: 12),
              _buildPeriodButton('30 dias', 30),
            ],
          ),
        ),

        // Gráfico de linha
        Expanded(
          child: FutureBuilder<List<Map<String, dynamic>>>(
            future: _dailyDataFuture,
            builder: (context, snapshot) {
              if (snapshot.connectionState == ConnectionState.waiting) {
                return const Center(
                  child: CircularProgressIndicator(color: AppColors.purplePrimary),
                );
              }

              if (snapshot.hasError) {
                return _buildErrorWidget(() {
                  setState(() => _loadData());
                });
              }

              if (!snapshot.hasData || snapshot.data!.isEmpty) {
                return _buildEmptyWidget();
              }

              return Padding(
                padding: const EdgeInsets.all(16.0),
                child: _buildLineChart(snapshot.data!),
              );
            },
          ),
        ),
      ],
    );
  }

  Widget _buildPeriodButton(String label, int days) {
    final isSelected = _selectedDays == days;

    return ElevatedButton(
      onPressed: () {
        setState(() {
          _selectedDays = days;
          _dailyDataFuture = dbService.getDailyStudyData(widget.userId, days: days);
        });
      },
      style: ElevatedButton.styleFrom(
        backgroundColor: isSelected ? AppColors.purplePrimary : AppColors.lightGrey,
        foregroundColor: isSelected ? AppColors.white : AppColors.textBase,
        elevation: isSelected ? 2 : 0,
      ),
      child: Text(label),
    );
  }

  // Gráfico de linha temporal
  Widget _buildLineChart(List<Map<String, dynamic>> data) {
    if (data.isEmpty) return _buildEmptyWidget();

    // Prepara os dados para o gráfico
    final spots = <FlSpot>[];
    final dates = <DateTime>[];

    for (int i = 0; i < data.length; i++) {
      final minutes = (data[i]['totalMinutes'] as int).toDouble();
      spots.add(FlSpot(i.toDouble(), minutes));
      dates.add(data[i]['date'] as DateTime);
    }

    final maxY = spots.isEmpty ? 60.0 : spots.map((s) => s.y).reduce((a, b) => a > b ? a : b) * 1.2;

    return Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: [
        Text(
          'Evolução do Tempo de Estudo',
          style: Theme.of(context).textTheme.titleLarge?.copyWith(
            fontWeight: FontWeight.bold,
          ),
        ),
        const SizedBox(height: 24),
        Expanded(
          child: LineChart(
            LineChartData(
              gridData: FlGridData(
                show: true,
                drawVerticalLine: false,
                horizontalInterval: maxY / 5,
                getDrawingHorizontalLine: (value) {
                  return FlLine(
                    color: AppColors.lightGrey,
                    strokeWidth: 1,
                  );
                },
              ),
              titlesData: FlTitlesData(
                show: true,
                bottomTitles: AxisTitles(
                  sideTitles: SideTitles(
                    showTitles: true,
                    reservedSize: 32,
                    interval: 1,
                    getTitlesWidget: (value, meta) {
                      final index = value.toInt();
                      if (index < 0 || index >= dates.length) return const SizedBox();

                      // Mostra apenas algumas labels para não poluir
                      if (_selectedDays == 7 || index % 5 == 0 || index == dates.length - 1) {
                        return Padding(
                          padding: const EdgeInsets.only(top: 8.0),
                          child: Text(
                            DateFormat('dd/MM').format(dates[index]),
                            style: const TextStyle(fontSize: 10),
                          ),
                        );
                      }
                      return const SizedBox();
                    },
                  ),
                ),
                leftTitles: AxisTitles(
                  sideTitles: SideTitles(
                    showTitles: true,
                    reservedSize: 40,
                    getTitlesWidget: (value, meta) {
                      return Text(
                        '${value.toInt()}min',
                        style: const TextStyle(fontSize: 10),
                      );
                    },
                  ),
                ),
                topTitles: const AxisTitles(sideTitles: SideTitles(showTitles: false)),
                rightTitles: const AxisTitles(sideTitles: SideTitles(showTitles: false)),
              ),
              borderData: FlBorderData(
                show: true,
                border: Border.all(color: AppColors.lightGrey),
              ),
              minX: 0,
              maxX: (spots.length - 1).toDouble(),
              minY: 0,
              maxY: maxY,
              lineBarsData: [
                LineChartBarData(
                  spots: spots,
                  isCurved: true,
                  color: AppColors.purplePrimary,
                  barWidth: 3,
                  isStrokeCapRound: true,
                  dotData: FlDotData(
                    show: true,
                    getDotPainter: (spot, percent, barData, index) {
                      return FlDotCirclePainter(
                        radius: 4,
                        color: AppColors.purplePrimary,
                        strokeWidth: 2,
                        strokeColor: AppColors.white,
                      );
                    },
                  ),
                  belowBarData: BarAreaData(
                    show: true,
                    color: AppColors.purplePrimary.withOpacity(0.2),
                  ),
                ),
              ],
              lineTouchData: LineTouchData(
                touchTooltipData: LineTouchTooltipData(
                  getTooltipItems: (touchedSpots) {
                    return touchedSpots.map((spot) {
                      final date = dates[spot.x.toInt()];
                      return LineTooltipItem(
                        '${DateFormat('dd/MM').format(date)}\n${spot.y.toInt()}min',
                        const TextStyle(
                          color: AppColors.white,
                          fontWeight: FontWeight.bold,
                        ),
                      );
                    }).toList();
                  },
                ),
              ),
            ),
          ),
        ),
      ],
    );
  }

  // ========== ABA 3: DISTRIBUIÇÃO POR MATÉRIA ==========
  Widget _buildDistributionTab() {
    return FutureBuilder<List<Map<String, dynamic>>>(
      future: _subjectDistributionFuture,
      builder: (context, snapshot) {
        if (snapshot.connectionState == ConnectionState.waiting) {
          return const Center(
            child: CircularProgressIndicator(color: AppColors.purplePrimary),
          );
        }

        if (snapshot.hasError) {
          return _buildErrorWidget(() {
            setState(() => _loadData());
          });
        }

        if (!snapshot.hasData || snapshot.data!.isEmpty) {
          return _buildEmptyWidget();
        }

        final data = snapshot.data!;

        return SingleChildScrollView(
          padding: const EdgeInsets.all(16.0),
          child: Column(
            crossAxisAlignment: CrossAxisAlignment.start,
            children: [
              Text(
                'Distribuição de Tempo por Matéria',
                style: Theme.of(context).textTheme.titleLarge?.copyWith(
                  fontWeight: FontWeight.bold,
                ),
              ),
              const SizedBox(height: 24),

              // Gráfico de pizza
              SizedBox(
                height: 300,
                child: _buildPieChart(data),
              ),

              const SizedBox(height: 24),

              // Legenda com detalhes
              _buildLegend(data),
            ],
          ),
        );
      },
    );
  }

  // Gráfico de pizza
  Widget _buildPieChart(List<Map<String, dynamic>> data) {
    // Define cores para cada matéria
    final colors = [
      AppColors.purplePrimary,
      AppColors.green,
      AppColors.blueLight,
      AppColors.orangeLight,
      AppColors.pink,
      AppColors.yellow,
    ];

    final sections = data.asMap().entries.map((entry) {
      final index = entry.key;
      final item = entry.value;
      final percentage = item['percentage'] as double;
      final color = colors[index % colors.length];

      return PieChartSectionData(
        color: color,
        value: percentage,
        title: '${percentage.toStringAsFixed(1)}%',
        radius: 100,
        titleStyle: const TextStyle(
          fontSize: 14,
          fontWeight: FontWeight.bold,
          color: AppColors.white,
        ),
      );
    }).toList();

    return PieChart(
      PieChartData(
        sections: sections,
        sectionsSpace: 2,
        centerSpaceRadius: 40,
        startDegreeOffset: -90,
      ),
    );
  }

  // Legenda do gráfico de pizza
  Widget _buildLegend(List<Map<String, dynamic>> data) {
    final colors = [
      AppColors.purplePrimary,
      AppColors.green,
      AppColors.blueLight,
      AppColors.orangeLight,
      AppColors.pink,
      AppColors.yellow,
    ];

    return Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: data.asMap().entries.map((entry) {
        final index = entry.key;
        final item = entry.value;
        final subject = item['subject'] as String;
        final minutes = item['minutes'] as int;
        final percentage = item['percentage'] as double;
        final color = colors[index % colors.length];

        return Padding(
          padding: const EdgeInsets.only(bottom: 12.0),
          child: Row(
            children: [
              Container(
                width: 16,
                height: 16,
                decoration: BoxDecoration(
                  color: color,
                  shape: BoxShape.circle,
                ),
              ),
              const SizedBox(width: 12),
              Expanded(
                child: Column(
                  crossAxisAlignment: CrossAxisAlignment.start,
                  children: [
                    Text(
                      subject,
                      style: const TextStyle(
                        fontWeight: FontWeight.w600,
                        fontSize: 14,
                      ),
                    ),
                    Text(
                      '${_formatDuration(minutes)} • ${percentage.toStringAsFixed(1)}%',
                      style: TextStyle(
                        fontSize: 12,
                        color: Theme.of(context).textTheme.bodyMedium?.color,
                      ),
                    ),
                  ],
                ),
              ),
            ],
          ),
        );
      }).toList(),
    );
  }

  // ========== GRÁFICO DE BARRAS (DIA DA SEMANA) ==========
  Widget _buildWeekdayChart() {
    return FutureBuilder<List<Map<String, dynamic>>>(
      future: _weekdayDataFuture,
      builder: (context, snapshot) {
        if (snapshot.connectionState == ConnectionState.waiting) {
          return const SizedBox(
            height: 200,
            child: Center(
              child: CircularProgressIndicator(color: AppColors.purplePrimary),
            ),
          );
        }

        if (snapshot.hasError || !snapshot.hasData || snapshot.data!.isEmpty) {
          return const SizedBox(
            height: 200,
            child: Center(child: Text('Sem dados suficientes')),
          );
        }

        final data = snapshot.data!;

        // Nomes dos dias da semana
        final weekdayNames = ['Dom', 'Seg', 'Ter', 'Qua', 'Qui', 'Sex', 'Sáb'];

        // Cria um mapa para garantir que todos os dias estejam presentes
        final weekdayMap = <int, int>{};
        for (int i = 0; i < 7; i++) {
          weekdayMap[i] = 0;
        }

        // Preenche com os dados reais
        for (var item in data) {
          final weekday = item['weekday'] as int;
          final minutes = item['totalMinutes'] as int;
          weekdayMap[weekday] = minutes;
        }

        // Cria as barras
        final barGroups = <BarChartGroupData>[];
        for (int i = 0; i < 7; i++) {
          barGroups.add(
            BarChartGroupData(
              x: i,
              barRods: [
                BarChartRodData(
                  toY: weekdayMap[i]!.toDouble(),
                  color: AppColors.purplePrimary,
                  width: 20,
                  borderRadius: const BorderRadius.only(
                    topLeft: Radius.circular(4),
                    topRight: Radius.circular(4),
                  ),
                ),
              ],
            ),
          );
        }

        final maxY = weekdayMap.values.isEmpty ? 60.0 : weekdayMap.values.reduce((a, b) => a > b ? a : b).toDouble() * 1.2;

        return SizedBox(
          height: 250,
          child: BarChart(
            BarChartData(
              alignment: BarChartAlignment.spaceAround,
              maxY: maxY,
              barGroups: barGroups,
              gridData: FlGridData(
                show: true,
                drawVerticalLine: false,
                horizontalInterval: maxY / 5,
                getDrawingHorizontalLine: (value) {
                  return FlLine(
                    color: AppColors.lightGrey,
                    strokeWidth: 1,
                  );
                },
              ),
              titlesData: FlTitlesData(
                show: true,
                bottomTitles: AxisTitles(
                  sideTitles: SideTitles(
                    showTitles: true,
                    getTitlesWidget: (value, meta) {
                      final index = value.toInt();
                      if (index >= 0 && index < 7) {
                        return Padding(
                          padding: const EdgeInsets.only(top: 8.0),
                          child: Text(
                            weekdayNames[index],
                            style: const TextStyle(fontSize: 12),
                          ),
                        );
                      }
                      return const SizedBox();
                    },
                  ),
                ),
                leftTitles: AxisTitles(
                  sideTitles: SideTitles(
                    showTitles: true,
                    reservedSize: 40,
                    getTitlesWidget: (value, meta) {
                      return Text(
                        '${value.toInt()}min',
                        style: const TextStyle(fontSize: 10),
                      );
                    },
                  ),
                ),
                topTitles: const AxisTitles(sideTitles: SideTitles(showTitles: false)),
                rightTitles: const AxisTitles(sideTitles: SideTitles(showTitles: false)),
              ),
              borderData: FlBorderData(
                show: true,
                border: Border.all(color: AppColors.lightGrey),
              ),
              barTouchData: BarTouchData(
                touchTooltipData: BarTouchTooltipData(
                  getTooltipItem: (group, groupIndex, rod, rodIndex) {
                    return BarTooltipItem(
                      '${weekdayNames[group.x.toInt()]}\n${rod.toY.toInt()}min',
                      const TextStyle(
                        color: AppColors.white,
                        fontWeight: FontWeight.bold,
                      ),
                    );
                  },
                ),
              ),
            ),
          ),
        );
      },
    );
  }

  // ========== WIDGETS AUXILIARES ==========

  Widget _buildErrorWidget(VoidCallback onRetry) {
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
            const Text(
              'Erro ao carregar dados',
              textAlign: TextAlign.center,
            ),
            const SizedBox(height: 16),
            ElevatedButton(
              onPressed: onRetry,
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

  Widget _buildEmptyWidget() {
    return const Center(
      child: Padding(
        padding: EdgeInsets.all(24.0),
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: [
            Icon(
              Icons.assessment_outlined,
              size: 80,
              color: AppColors.lightGrey,
            ),
            SizedBox(height: 16),
            Text(
              'Nenhum dado disponível ainda',
              style: TextStyle(
                fontSize: 18,
                fontWeight: FontWeight.bold,
              ),
              textAlign: TextAlign.center,
            ),
            SizedBox(height: 8),
            Text(
              'Complete algumas sessões de estudo para ver suas estatísticas!',
              textAlign: TextAlign.center,
            ),
          ],
        ),
      ),
    );
  }

  String _formatDuration(int totalMinutes) {
    final hours = totalMinutes ~/ 60;
    final minutes = totalMinutes % 60;
    if (hours > 0) {
      return minutes > 0 ? '${hours}h ${minutes}min' : '${hours}h';
    }
    return '${minutes}min';
  }
}