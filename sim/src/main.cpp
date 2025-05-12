#include "ThreadFactory.hpp"
#include "NavigationSubsystem.hpp"
#include <thread>
#include <chrono>
#include <iostream>

int main()
{
    ThreadFactory factory;
    factory.launch<NavigationSubsystem>();

    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "Main thread exiting (sim continues in detached threads)." << std::endl;

    return 0;
}

/*
*   Main.cpp
*       -> Calls factory.launch<NavigationSubsystem>()
*           -> Creates unique_ptr<Subsystem> to NavigationSubsystem
*               -> Starts new std::thread w/ subsystem->run()
*                   -> NavigationSubsystem::run() executes in the new thread
*/
