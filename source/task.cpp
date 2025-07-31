#include "../include/defines.hpp"
#include "../include/task.hpp"

Task createTask(size_t id, float gt, float xt, size_t p)
{
    Task newTask;
    newTask.id = id;
    newTask.generation_time = gt;
    newTask.execution_time = xt;
    newTask.priority = p;
    return newTask;
}

vector<Task> generateTasks(size_t n, float max_time)
{
    vector<Task> task_list;

    for (size_t i = 0; i < n; i++)
    {
        size_t id = i;
        float exec_time = static_cast<float>(rand() % 10 + 1);
        float generation_time = static_cast<float>(rand() % static_cast<size_t>(max_time - exec_time) + 1);
        size_t priority = rand() % 10 + 1;
        task_list.push_back(createTask(id, generation_time, exec_time, priority));
    }

    return task_list;
}