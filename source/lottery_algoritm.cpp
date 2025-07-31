#include "../include/lottery_algoritm.hpp"
#include "../include/task.hpp"
#include "../include/data_base.hpp"
#include "../include/defines.hpp"

void run_lottery_algorithm(float time_window, vector<Task> &tasks)
{
    float current_time = 0;

    cout << "\n=== ALGORITMO DE LOTERIA ===\n";

    while (!tasks.empty() && current_time < time_window)
    {
        // Selecionar apenas tarefas que já chegaram
        vector<size_t> ready_indices;
        for (size_t i = 0; i < tasks.size(); ++i)
        {
            if (tasks[i].generation_time <= current_time)
                ready_indices.push_back(i);
        }

        if (ready_indices.empty())
        {
            // Avança o tempo caso nenhuma tarefa esteja disponível
            current_time += 1.0;
            continue;
        }

        cout << "\nTarefas prontas no tempo " << current_time << ":\n";
        for (size_t idx : ready_indices)
        {
            const Task &t = tasks[idx];
            cout << "  ID: " << t.id
                 << " | prioridade: " << t.priority
                 << " | geração: " << t.generation_time
                 << " | execução: " << t.execution_time << "\n";
        }

        // Construir a loteria com base nas tarefas prontas
        vector<size_t> ticket_pool;
        for (size_t idx : ready_indices)
        {
            for (size_t j = 0; j < tasks[idx].priority; ++j)
                ticket_pool.push_back(idx);
        }

        // Sorteia uma tarefa com base na loteria
        size_t winner_index = ticket_pool[rand() % ticket_pool.size()];
        Task selected_task = tasks[winner_index];

        // Calcula os tempos de execução
        float start_time = current_time;
        float end_time = current_time + selected_task.execution_time;
        float wait_time = start_time - selected_task.generation_time;
        float turnaround = end_time - selected_task.generation_time;

        cout << "Tarefa sorteada ID: " << selected_task.id
             << " | prioridade (tickets): " << selected_task.priority
             << " | tempo de geração: " << selected_task.generation_time
             << " | tempo_exec: " << selected_task.execution_time
             << " | tempo atual: " << current_time << "\n";

        cout << "→ Tempo de espera: " << wait_time
             << " | Turnaround: " << turnaround << "\n";

        // Registrar no "banco de dados"
        log_task_execution(selected_task, start_time, end_time, "Loteria");

        // Atualiza o tempo atual
        current_time += selected_task.execution_time;

        // Remove a tarefa executada
        tasks.erase(tasks.begin() + winner_index);
    }
}