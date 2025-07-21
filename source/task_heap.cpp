#include "../include/task_heap.hpp"


// Struct que implementa uma Heap Mínima
struct TaskMinHeap 
{
    vector<Task> tasks;
    
    // Funções auxiliares para navegar na heap
    int parent(int i) { return (i - 1) / 2; }
    int left_children(int i) { return 2 * i + 1; }
    int right_children(int i) { return 2 * i + 2; }
    
    // Restaurar a propriedade de heap subindo
    void heapUp(int i) 
    {
        while (i > 0 && tasks[parent(i)].priority > tasks[i].priority) 
        {
            swap(tasks[parent(i)], tasks[i]);
            i = parent(i);
        }
    }
    
    // Restaurar a propriedade de heap descendo
    void heapDown(int i) 
    {
        int min_value = i;
        int left = left_children(i);
        int right = right_children(i);
        
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

    // insertTask novo elemento
    void insertTask(const Task& Task) 
    {
        tasks.push_back(Task);
        heapUp(tasks.size() - 1);
    }
    
    // Remover e retornar o elemento com min_value priority (topo)
    Task getNextTask() 
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
    void showTasks() const 
    {
        for (const auto& t : tasks) 
        {
            cout << "ID: " << t.id 
                 << ", priority: " << t.priority;
        }
    }
};