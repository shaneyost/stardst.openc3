#include "NavigationSubsystem.hpp"
#include <iostream>
#include <thread>
#include <chrono>

NavigationSubsystem::NavigationSubsystem(std::atomic<bool>& runningFlag)
    : running(runningFlag) {}

void NavigationSubsystem::run()
{
    while (running.load())
    {
        std::cout << "[NavigationSubsystem::run] " 
        << "simulating telemetry"
        << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "[NavigationSubsystem::run] "
    << "stopping cleanly."
    << std::endl;
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
