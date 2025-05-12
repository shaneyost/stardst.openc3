#include "ThreadFactory.hpp"
#include "NavigationSubsystem.hpp"
#include <atomic>
#include <iostream>

int main()
{
    std::atomic<bool> running(true);

    ThreadFactory factory;
    factory.launch<NavigationSubsystem>(running);

    std::cout << "Press ENTER to stop simulation..." << std::endl;
    std::cin.get();

    running.store(false);

    std::cout << "All subsystems stopped. Exiting cleanly." << std::endl;
    return 0;
}

/*
*   Main.cpp
*       -> Calls factory.launch<NavigationSubsystem>()
*           -> Creates unique_ptr<Subsystem> to NavigationSubsystem
*               -> Starts new std::thread w/ subsystem->run()
*                   -> NavigationSubsystem::run() executes in the new thread
*/
