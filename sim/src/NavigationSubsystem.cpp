#include "NavigationSubsystem.hpp"
#include <iostream>
#include <thread>
#include <chrono>

void NavigationSubsystem::run()
{
    while (true)
    {
        std::cout << "[NavigationSubsystem::run]\n" 
        << "simulating telemetry"
        << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

/*
*   INFO:   Since I'm picking back up w/ Cpp I'm going to document stuff along 
*           the way as I relearn things.
*
*   What is the "::" notation for?
*
*       It tells C++ where to find the function or type. Kind of all like
*       saying what "folder" or "owner" it belongs to. "::" more specially is
*       the scope resolution operator.
*
*   Where did "this_thread" come from?
*
*       It came from the "std" library as we can tell through the scope 
*       resolution operator. It represents the current thread you are running
*       in. 
*
*       So "std::this_thread" is a namespace in <thread>. It provides utilities
*       for the current thread, like sleeping.
*/
