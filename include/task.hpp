#ifndef TASK_HPP
#define TASK_HPP

#include "defines.hpp"

struct Task
{
    int id;
    float generation_time;
    float execution_time;
    int priority;
};

Task createTask(int id, float gt, float xt ,int p);
vector<Task> generateTasks(int n, float max_time);


#endif // TASK_HPP

