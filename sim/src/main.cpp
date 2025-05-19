#include "ThreadFactory.hpp"
#include "NavigationSubsystem.hpp"
#include "Logger.hpp"

#include <atomic>
#include <iostream>

int main()
{
    std::atomic<bool> running(true);

    ThreadFactory factory;
    factory.launch<NavigationSubsystem>(running);

    LOG_INFO("Press ENTER to stop simulation...");
    std::cin.get();

    running.store(false);

    LOG_INFO("All subsystems stopped. Exiting cleanly...");
    return 0;
}

/*
*   Main.cpp
*       -> Calls factory.launch<NavigationSubsystem>()
*           -> Creates unique_ptr<Subsystem> to NavigationSubsystem
*               -> Starts new std::thread w/ subsystem->run()
*                   -> NavigationSubsystem::run() executes in the new thread
*/
