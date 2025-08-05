import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

sns.set_theme(style="whitegrid")

seed_files = {
    'Seed 42': 'results/task_metrics_seed42.csv',
    'Seed 666': 'results/task_metrics_seed666.csv',
    'Seed 1024': 'results/task_metrics_seed1024.csv'
}

all_metrics_df = pd.DataFrame()

for seed_name, file_path in seed_files.items():
    try:
        temp_df = pd.read_csv(file_path, index_col=0)
        
        temp_df = temp_df.reset_index()
        
        temp_df['Seed'] = seed_name
        
        all_metrics_df = pd.concat([all_metrics_df, temp_df], ignore_index=True)
    except FileNotFoundError:
        print(f"Aviso: O arquivo {file_path} não foi encontrado. Ignorando...")

if all_metrics_df.empty:
    print("Erro: Nenhum arquivo de métricas foi carregado. Verifique os caminhos dos arquivos.")
else:
    plt.figure(figsize=(12, 7))
    sns.barplot(data=all_metrics_df, x='Algorithm', y='WaitTime_Mean', hue='Seed', palette='viridis')
    
    plt.title('Comparativo do Tempo Médio de Espera por Algoritmo e Seed', fontsize=16)
    plt.xlabel('Algoritmo', fontsize=12)
    plt.ylabel('Tempo Médio de Espera', fontsize=12)
    plt.legend(title='Configuração de Seed')
    
    plt.tight_layout()
    plt.savefig('results/images/seed_waittime.png')
    plt.close()
    # plt.show()