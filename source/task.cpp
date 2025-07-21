#include "../include/task.hpp"

Task createTask(int id, float gt, float xt ,int p)
{
    Task newTask;
    newTask.id=id;
    newTask.generation_time = gt;
    newTask.execution_time = xt;
    newTask.priority = p;
    return newTask;
}

vector<Task> generateTasks(int n, float max_time)
{
    vector<Task> task_list;
    for(int i=0; i<n; i++)
    {
        task_list.push_back(createTask(i,i,max_time,1));  //implementar geração aleatória de tasks em um intervalo de tempo
    }
    return task_list;
}

//