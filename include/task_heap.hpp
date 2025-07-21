#ifndef TASK_HEAP_HPP
#define TASK_HEAP_HPP

#include "defines.hpp"
#include "task.hpp"

void heapUp(int i);
void heapDown(int i);
void insertTask(const Task& Task);
Task getNextTask();
void showTasks();

#endif // TASK_HEAP_HPP