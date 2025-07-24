#include "../include/lottery_algoritm.hpp"
#include "../include/task.hpp"

#include <algorithm>

void run_lottery_algorithm(float time_window)
{
    vector<Task> tasks = generateTasks(10, time_window);
    float current_time = 0;

    cout << "\n=== ALGORITMO DE LOTERIA ===\n";

    while (!tasks.empty() && current_time < time_window)
    {
        // Criar a "loteria"
        vector<int> ticket_pool;
        for (int i = 0; i < tasks.size(); ++i)
        {
            for (int j = 0; j < tasks[i].priority; ++j)
                ticket_pool.push_back(i);
        }

        if (ticket_pool.empty())
            break;

        // Sorteio
        int winner_idx = ticket_pool[rand() % ticket_pool.size()];
        Task t = tasks[winner_idx];

        cout << "Sorteada tarefa ID: " << t.id
             << " | prioridade (tickets): " << t.priority
             << " | tempo_exec: " << t.execution_time
             << " | tempo atual: " << current_time << endl;

        current_time += t.execution_time;

        // Remove a tarefa sorteada
        tasks.erase(tasks.begin() + winner_idx);
    }
}