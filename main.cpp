#include <iostream>
#include "../include/priority_algoritm.hpp"
#include "../include/lottery_algoritm.hpp"

int main()
{
    float time_window = 100.0;

    run_priority_algorithm(time_window);
    cout << "-------------------------------\n";
    run_lottery_algorithm(time_window);

    return 0;
}