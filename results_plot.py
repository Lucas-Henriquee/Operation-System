import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import seaborn as sns

sns.set(style="whitegrid")

df = pd.read_csv('results/task_log.csv')

# Calcula métricas adicionais
df['WaitTime'] = df['StartTime'] - df['GenerationTime']
df['Turnaround'] = df['EndTime'] - df['GenerationTime']
df['Duration'] = df['EndTime'] - df['StartTime']

df = df.sort_values(by='StartTime')

# Função para calcular coeficiente de variação
def coef_var(x):
    return x.std() / x.mean() if x.mean() != 0 else float('nan')

# Agregações para ambas métricas
agg_funcs = {
    'WaitTime': ['count', 'mean', 'std', coef_var, 'min', 'median', 'max'],
    'Turnaround': ['count', 'mean', 'std', coef_var, 'min', 'median', 'max']
}

grouped = df.groupby('Algorithm').agg(agg_funcs)

grouped.columns = ['_'.join(col).strip() for col in grouped.columns.values]
grouped = grouped.rename(columns={
    'WaitTime_count': 'WaitTime_Count',
    'WaitTime_mean': 'WaitTime_Mean',
    'WaitTime_std': 'WaitTime_Std',
    'WaitTime_coef_var': 'WaitTime_CV',
    'WaitTime_min': 'WaitTime_Min',
    'WaitTime_median': 'WaitTime_Median',
    'WaitTime_max': 'WaitTime_Max',
    'Turnaround_count': 'Turnaround_Count',
    'Turnaround_mean': 'Turnaround_Mean',
    'Turnaround_std': 'Turnaround_Std',
    'Turnaround_coef_var': 'Turnaround_CV',
    'Turnaround_min': 'Turnaround_Min',
    'Turnaround_median': 'Turnaround_Median',
    'Turnaround_max': 'Turnaround_Max',
})

print("\n=== Estatísticas detalhadas por algoritmo ===")
print(grouped)
output_csv = 'results/task_metrics_summary.csv'
grouped.to_csv(output_csv)


# ==== Gráfico de Gantt das Execuções das Tarefas ====
fig, ax = plt.subplots(figsize=(12, 6))
for idx, row in df.iterrows():
    ax.broken_barh([(row['StartTime'], row['Duration'])], (row['ID'] - 0.4, 0.8),
                   facecolors='tab:blue' if row['Algorithm'] == 'Loteria' else 'tab:orange')
ax.set_yticks(sorted(df['ID'].unique()))
ax.set_xlabel('Tempo')
ax.set_ylabel('Tarefa (ID)')
ax.set_yticks(df['ID'].unique())
ax.set_title('Gráfico de Gantt das Execuções das Tarefas')
ax.grid(True)

legend_handles = [
    mpatches.Patch(color='tab:blue', label='Loteria'),
    mpatches.Patch(color='tab:orange', label='Prioridade')
]
ax.legend(handles=legend_handles)
plt.tight_layout()
plt.savefig('results/images/gantt_chart.png')
plt.show()


# ==== Gráfico de barras: Tempo médio de espera ====
plt.figure(figsize=(10, 5))
sns.barplot(data=df, x='Algorithm', y='WaitTime', estimator='mean')
plt.title('Tempo Médio de Espera por Algoritmo')
plt.ylabel('Tempo de Espera (médio)')
plt.xlabel('Algoritmo')
plt.tight_layout()
plt.savefig('results/images/average_wait_time.png')
plt.show()

# ==== Boxplot: distribuição do turnaround ====
plt.figure(figsize=(10, 5))
sns.boxplot(data=df, x='Algorithm', y='Turnaround')
plt.title('Distribuição de Turnaround por Algoritmo')
plt.ylabel('Tempo de Turnaround')
plt.xlabel('Algoritmo')
plt.tight_layout()
plt.savefig('results/images/turnaround_distribution.png')
plt.show()

# ==== 3. Histograma do tempo de espera ====
plt.figure(figsize=(10, 5))
sns.histplot(data=df, x='WaitTime', hue='Algorithm', multiple='stack', bins=20)
plt.title('Distribuição do Tempo de Espera por Algoritmo')
plt.xlabel('Tempo de Espera')
plt.ylabel('Número de Tarefas')
plt.tight_layout()
plt.savefig('results/images/wait_time_distribution.png')
plt.show()

# ==== Scatter plot: geração x início da execução ====
plt.figure(figsize=(10, 5))
sns.scatterplot(data=df, x='GenerationTime', y='StartTime', hue='Algorithm', style='Algorithm', s=100)
plt.title('Tempo de Geração vs Início da Execução')
plt.xlabel('Tempo de Geração')
plt.ylabel('Início da Execução')
plt.tight_layout()
plt.savefig('results/images/generation_vs_start_time.png')
plt.show()

# ==== Violinplot: distribuição detalhada do turnaround ====
plt.figure(figsize=(10, 5))
sns.violinplot(data=df, x='Algorithm', y='Turnaround', hue='Algorithm', inner='quartile', palette="Set2")
plt.title('Distribuição (Violin) do Turnaround por Algoritmo')
plt.ylabel('Turnaround')
plt.xlabel('Algoritmo')
plt.tight_layout()
plt.savefig('results/images/turnaround_distribution.png')
plt.show()