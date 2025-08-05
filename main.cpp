#include "../include/priority_algoritm.hpp"
#include "../include/lottery_algoritm.hpp"
#include "../include/data_base.hpp"
#include "../include/task.hpp"
#include "../include/task_heap.hpp"
#include "../include/defines.hpp"

int main()
{
    int seed = 1024;
    srand(seed); 
    
    init_log_file(); 
    
    float time_window = 100.0;
    vector<Task> tasks = generateTasks(25, time_window);

    vector<Task> tasks_lottery = tasks;
    vector<Task> tasks_priority = tasks;


    run_priority_algorithm(time_window, tasks_priority);
    cout << "-------------------------------\n";
    run_lottery_algorithm(time_window, tasks_lottery);

    return 0;
}