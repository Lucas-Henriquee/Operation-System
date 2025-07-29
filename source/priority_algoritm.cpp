#include "../include/priority_algoritm.hpp"
#include "../include/task_heap.hpp"

float current_time = 0;

void run_priority_algorithm(float time_window)
{
    //Enquanto tempo limite não atingido
    while (current_time<=time_window)
    {
        //Gera lista de tarefas
        vector<Task>task_list = generateTasks(10, time_window);

        //Cria heap de mínimo para selecionar maior prioridade em O(1)
        TaskMinHeap task_heap;

        //Insere na heap as tarefas com tempo de aparecimento
        //menor que tempo atual e exclui da lista
        for(int i=0; i<task_list.size(); i++)
        {
            if(task_list[i].generation_time<=current_time)
            task_heap.insertTask(task_list[i]);
            task_list.erase(task_list.begin()+i);
        }

        //Seleciona próxima tarefa na heap
        Task next_task=task_heap.getNextTask();

        //"Executa" a tarefa
        cout << "Tarefa executada ID: " << next_task.id
             << " | prioridade : " << next_task.priority
             << " | tempo inicial : "<< current_time
             << " | tempo_exec: " << next_task.execution_time
             << " | tempo atual: " << current_time+next_task.execution_time << endl;
            
        //Atualiza tempo
        current_time+=next_task.execution_time;
    }
}