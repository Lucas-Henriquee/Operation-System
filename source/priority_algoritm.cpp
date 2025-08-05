#include "../include/priority_algoritm.hpp"
#include "../include/task_heap.hpp"
#include "../include/task.hpp"
#include "../include/data_base.hpp"
#include "../include/defines.hpp"

void run_priority_algorithm(float time_window, vector<Task> &task_list)
{
    float current_time = 0;

    cout << "\n=== ALGORITMO DE PRIORIDADE ===\n";

    // Cria heap de mínimo para selecionar maior prioridade em O(1)
    TaskMinHeap task_heap;

    // Vetor para armazenar tarefas prontas
    vector<Task> ready_tasks;
    
    // Enquanto tempo limite não atingido
    do 
    {   
        ready_tasks.clear(); // Limpa tarefas prontas a cada iteração
        
        // Insere na heap as tarefas com tempo de aparecimento
        // menor que tempo atual e exclui da lista
        for (size_t i = 0; i < task_list.size();)
        {
            if (task_list[i].generation_time <= current_time)
            {
                ready_tasks.push_back(task_list[i]);
                task_heap.insertTask(task_list[i]);
                task_list.erase(task_list.begin() + i);
            }
            else
            {
                i++; // só avança se não remover
            }
        }

        // Nenhuma tarefa pronta: avança tempo
        if (task_heap.empty())
        {
            current_time += 1.0;
            continue;
        }

        cout << "\nTarefas prontas no tempo " << current_time << ":\n";
        for (const Task &idx : ready_tasks)
        {
            cout << "  ID: " << idx.id
                 << " | prioridade: " << idx.priority
                 << " | geração: " << idx.generation_time
                 << " | execução: " << idx.execution_time << "\n";
        }

        // Seleciona próxima tarefa na heap
        Task next_task = task_heap.getNextTask();

        // Calcula tempos de execução
        float start_time = current_time;
        float end_time = current_time + next_task.execution_time;
        float wait_time = start_time - next_task.generation_time;
        float turnaround = end_time - next_task.generation_time;

        cout << "Tarefa executada ID: " << next_task.id
             << " | prioridade: " << next_task.priority
             << " | tempo de geração: " << next_task.generation_time
             << " | tempo_exec: " << next_task.execution_time
             << " | tempo atual: " << current_time << "\n";

        cout << "→ Tempo de espera: " << wait_time
             << " | Turnaround: " << turnaround << "\n";

        // Loga execução no arquivo
        log_task_execution(next_task, start_time, end_time, "Prioridade");

        // Atualiza tempo atual
        current_time = end_time;
    } while ((!task_list.empty()  || !task_heap.empty() ) && current_time <= time_window );
}