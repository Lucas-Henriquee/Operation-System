#ifndef TASK_HEAP_HPP
#define TASK_HEAP_HPP

#include "defines.hpp"
#include "task.hpp"

struct TaskMinHeap 
{
    vector<Task> tasks;

    size_t parent(size_t i);
    size_t left_children(size_t i);
    size_t right_children(size_t i);
    
    void heapUp(size_t i);
    void heapDown(size_t i);
    void insertTask(const Task& Task);
    Task getNextTask();
    void showTasks() const;
    bool empty();
};

#endif 
