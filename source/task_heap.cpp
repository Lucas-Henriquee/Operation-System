#include "../include/task_heap.hpp"

// Funções auxiliares para navegar na heap
size_t TaskMinHeap ::parent(size_t i)
{
    return (i - 1) / 2;
}

size_t TaskMinHeap ::left_children(size_t i)
{
    return 2 * i + 1;
}

size_t TaskMinHeap ::right_children(size_t i)
{
    return 2 * i + 2;
}

// Restaurar a propriedade de heap subindo
void TaskMinHeap ::heapUp(size_t i)
{
    while (i > 0 && tasks[parent(i)].priority > tasks[i].priority)
    {
        swap(tasks[parent(i)], tasks[i]);
        i = parent(i);
    }
}

// Restaurar a propriedade de heap descendo
void TaskMinHeap ::heapDown(size_t i)
{
    size_t min_value = i;
    size_t left = left_children(i);
    size_t right = right_children(i);

    if (left < tasks.size() && tasks[left].priority < tasks[min_value].priority)
    {
        min_value = left;
    }

    if (right < tasks.size() && tasks[right].priority < tasks[min_value].priority)
    {
        min_value = right;
    }

    if (min_value != i)
    {
        swap(tasks[i], tasks[min_value]);
        heapDown(min_value);
    }
}

// Inserir task na heap
void TaskMinHeap ::insertTask(const Task &Task)
{
    tasks.push_back(Task);
    heapUp(tasks.size() - 1);
}

// Remover e retornar o elemento com maior prioridade (topo)
Task TaskMinHeap ::getNextTask()
{
    if (tasks.empty())
    {
        throw runtime_error("Heap tasks.empty");
    }

    Task minimo = tasks[0];
    tasks[0] = tasks.back();
    tasks.pop_back();

    if (!tasks.empty())
    {
        heapDown(0);
    }

    return minimo;
}

// Mostrar todos os tasks (para debug)
void TaskMinHeap ::showTasks() const
{
    for (const auto &t : tasks)
    {
        cout << "ID: " << t.id
             << ", priority: " << t.priority;
    }
}

bool TaskMinHeap ::empty()
{
    return tasks.empty();
}
