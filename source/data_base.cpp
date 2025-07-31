// implementar banco de dados ou similar para registrar as alreações do escalonador

#include "../include/data_base.hpp"
#include "../include/defines.hpp"

static string log_filename = "results/task_log.csv";

// Inicializa o arquivo CSV com cabeçalho
void init_log_file()
{
    ofstream file(log_filename, ios::out);
    if (file.is_open())
    {
        file << "ID,Priority,GenerationTime,StartTime,EndTime,Algorithm\n";
        file.close();
    }
    else
    {
        cerr << "Erro ao criar arquivo de log: " << log_filename << endl;
    }
}

// Registra a execução de uma tarefa no arquivo CSV
void log_task_execution(const Task &task, float start_time, float end_time, const string &algorithm_name)
{
    ofstream file(log_filename, ios::app);
    if (file.is_open())
    {
        file << task.id << ","
             << task.priority << ","
             << task.generation_time << ","
             << start_time << ","
             << end_time << ","
             << algorithm_name << "\n";
        file.close();
    }
    else
    {
        cerr << "Erro ao escrever no arquivo de log: " << log_filename << endl;
    }
}
