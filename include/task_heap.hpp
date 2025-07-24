#ifndef TASK_HEAP_HPP
#define TASK_HEAP_HPP

#include "defines.hpp"
#include "task.hpp"

struct TaskMinHeap 
{
    vector<Task> tasks;

    int parent(int i);
    int left_children(int i);
    int right_children(int i);
    
    void heapUp(int i);
    void heapDown(int i);
    void insertTask(const Task& Task);
    Task getNextTask();
    void showTasks() const;
};

#endif 
