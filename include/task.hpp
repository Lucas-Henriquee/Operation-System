#ifndef TASK_HPP
#define TASK_HPP

#include "defines.hpp"

struct Task
{
    size_t id;
    float generation_time;
    float execution_time;
    size_t priority;
};

Task createTask(size_t id, float gt, float xt ,size_t p);
vector<Task> generateTasks(size_t n, float max_time);


#endif // TASK_HPP

