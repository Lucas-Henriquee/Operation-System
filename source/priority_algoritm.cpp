#include "../include/priority_algoritm.hpp"
#include "../include/task_heap.hpp"

float current_time = 0;

void run_priority_algorithm(float time_window)
{
    //gerar tarefas
    //while heap nao vazia
        //executar e remover tarefa da heap
    vector<Task>task_list = generateTasks(10, time_window);

    TaskMinHeap task_heap;
    for(int i=0; i<task_list.size(); i++) 
    {
        task_heap.insertTask(task_list[i]);
        //task_list.erase(task_list.begin()+i)
    }

    while (!task_heap.empty() && current_time < time_window)
    {
        Task task_minimo=task_heap.getNextTask();

        cout << "Tarefa executada ID: " << task_minimo.id
             << " | prioridade : " << task_minimo.priority
             << " | tempo_exec: " << task_minimo.execution_time
             << " | tempo atual: " << current_time << endl;
        current_time++;
    }
    
    
}