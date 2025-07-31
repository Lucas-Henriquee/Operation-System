#ifndef DATA_BASE_HPP
#define DATA_BASE_HPP

#include "task.hpp"
#include "defines.hpp"

void log_task_execution(const Task& task, float start_time, float end_time, const string& algorithm_name);
void init_log_file();

#endif // DATA_BASE_HPP