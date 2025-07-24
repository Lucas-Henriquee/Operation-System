#include <cstdlib> 
#include <ctime>   
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
    srand(time(nullptr));  

    for(int i=0; i<n; i++)
    {
        int priority = rand() % 10 + 1;      
        float exec_time = static_cast<float>(rand() % static_cast<int>(max_time) + 1);                
        task_list.push_back(createTask(i,i,exec_time, priority));  
    }
    
    return task_list;
}