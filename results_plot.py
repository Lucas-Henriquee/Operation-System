import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import seaborn as sns
from matplotlib.patches import Patch

sns.set_theme(style="whitegrid")

df = pd.read_csv('results/task_log.csv')

# Calcula métricas adicionais
df['WaitTime'] = df['StartTime'] - df['GenerationTime']
df['Turnaround'] = df['EndTime'] - df['GenerationTime']
df['Duration'] = df['EndTime'] - df['StartTime']

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
output_csv = 'results/task_metrics_seed1024.csv'
grouped.to_csv(output_csv)


# ==== Gráfico de Gantt original ====
fig, ax = plt.subplots(figsize=(12, 6))
for idx, row in df.iterrows():
    ax.broken_barh([(row['StartTime'], row['Duration'])], (row['ID'] - 0.4, 0.8),
                   facecolors='tab:blue' if row['Algorithm'] == 'Loteria' else 'tab:orange')
    ax.text(x=row['StartTime'] + row['Duration'] / 2,
            y=row['ID'] + 0.4,
            s=str(int(row['Priority'])),
            ha='center', va='bottom', fontsize=8, color='black')
ax.set_yticks(sorted(df['ID'].unique()))
ax.set_xlabel('Tempo')
ax.set_ylabel('Tarefa (ID)')
ax.set_title('Gráfico de Gantt das Execuções das Tarefas')
ax.grid(True)
legend_handles = [
    mpatches.Patch(color='tab:blue', label='Loteria'),
    mpatches.Patch(color='tab:orange', label='Prioridade')
]
ax.legend(handles=legend_handles)
plt.tight_layout()
plt.savefig('results/images/gantt_chart.png')
plt.close()
plt.show()


# ==== Gráfico de Gantt para o Algoritmo de Prioridade ====
df_priority = df[df['Algorithm'] == 'Prioridade'].copy().sort_values('Priority')
fig, ax = plt.subplots(figsize=(14, 8))
for idx, row in df_priority.iterrows():
    # Tempo de espera 
    ax.broken_barh([(row['GenerationTime'], row['WaitTime'])], (row['ID'] - 0.4, 0.8),
                   facecolors='lightgray', edgecolor='gray')
    # Tempo de execução 
    ax.broken_barh([(row['StartTime'], row['Duration'])], (row['ID'] - 0.4, 0.8),
                   facecolors='tab:orange', edgecolor='black', linewidth=0.5)
    ax.text(x=row['StartTime'] + row['Duration'] / 2, 
            y=row['ID'], 
            s=f"P{int(row['Priority'])}",
            ha='center', va='center', fontsize=9, color='white', fontweight='bold')
ax.set_yticks(df_priority['ID'].unique())
ax.set_xlabel('Tempo', fontsize=12)
ax.set_ylabel('Tarefa (ID)', fontsize=12)
ax.set_title('Gráfico de Gantt do Algoritmo de Prioridade (Ordenado por Prioridade)', fontsize=14)
ax.grid(axis='x', linestyle='--')
legend_elements = [
    Patch(facecolor='lightgray', label='Tempo de Espera'),
    Patch(facecolor='tab:orange', label='Tempo de Execução')
]
ax.legend(handles=legend_elements, loc='upper left')
plt.tight_layout()
plt.savefig('results/images/gantt_chart_priority.png')
plt.close()
plt.show()

# ==== Gráfico de Gantt para o Algoritmo de Loteria (Ordem de Execução) ====
df_lottery = df[df['Algorithm'] == 'Loteria'].copy()
fig, ax = plt.subplots(figsize=(14, 8))
for idx, row in df_lottery.iterrows():
    # Tempo de espera 
    ax.broken_barh([(row['GenerationTime'], row['WaitTime'])], (row['ID'] - 0.4, 0.8),
                   facecolors='lightgray', edgecolor='gray')
    # Tempo de execução
    ax.broken_barh([(row['StartTime'], row['Duration'])], (row['ID'] - 0.4, 0.8),
                   facecolors='tab:blue', edgecolor='black', linewidth=0.5)
    ax.text(x=row['StartTime'] + row['Duration'] / 2, 
            y=row['ID'], 
            s=f"P{int(row['Priority'])}",
            ha='center', va='center', fontsize=9, color='white', fontweight='bold')
ax.set_yticks(df_lottery['ID'].unique())
ax.set_xlabel('Tempo', fontsize=12)
ax.set_ylabel('Tarefa (ID)', fontsize=12)
ax.set_title('Gráfico de Gantt do Algoritmo de Loteria (Ordem de Execução)', fontsize=14)
ax.grid(axis='x', linestyle='--')
legend_elements = [
    Patch(facecolor='lightgray', label='Tempo de Espera'),
    Patch(facecolor='tab:blue', label='Tempo de Execução')
]
ax.legend(handles=legend_elements, loc='upper left')
plt.tight_layout()
plt.savefig('results/images/gantt_chart_lottery.png')
plt.close()
plt.show()


# ==== Gráfico de barras: Tempo médio de espera ====
plt.figure(figsize=(10, 5))
sns.barplot(data=df, x='Algorithm', y='WaitTime', estimator='mean')
plt.title('Tempo Médio de Espera por Algoritmo')
plt.ylabel('Tempo de Espera (médio)')
plt.xlabel('Algoritmo')
plt.tight_layout()
plt.savefig('results/images/average_wait_time.png')
plt.close()
plt.show()

# ==== Histograma do tempo de espera ====
plt.figure(figsize=(10, 5))
sns.histplot(data=df, x='WaitTime', hue='Algorithm', multiple='stack', bins=20)
plt.title('Distribuição do Tempo de Espera por Algoritmo')
plt.xlabel('Tempo de Espera')
plt.ylabel('Número de Tarefas')
plt.tight_layout()
plt.savefig('results/images/wait_time_distribution.png')
plt.close()
plt.show()

# ==== Scatter plot: geração x início da execução com linha de melhor caso ====
plt.figure(figsize=(10, 5))
sns.scatterplot(data=df, x='GenerationTime', y='StartTime', hue='Algorithm', style='Algorithm', s=100)
plt.title('Tempo de Geração vs Início da Execução')
plt.xlabel('Tempo de Geração')
plt.ylabel('Início da Execução')
max_val = max(df['GenerationTime'].max(), df['StartTime'].max())
plt.plot([0, max_val], [0, max_val], 'k-', lw=2, label='Melhor Caso')
plt.legend()
plt.tight_layout()
plt.savefig('results/images/generation_vs_start_time.png')
plt.show()