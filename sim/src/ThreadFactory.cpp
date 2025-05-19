#include "ThreadFactory.hpp"

ThreadFactory::~ThreadFactory()
{
    for (auto& thread : threads)
    {
        if (thread.joinable())
        {
            thread.join();
        }
    }
}

template <typename SubsystemType>
void ThreadFactory::launch(std::atomic<bool>& runningFlag)
{
    std::unique_ptr<Subsystem> subsystem = std::make_unique<SubsystemType>(runningFlag);
    threads.emplace_back([subsystem = std::move(subsystem)]()
    {
        subsystem->run();
    });
}

// Explicit instantiation for known subsystem types
#include "NavigationSubsystem.hpp"
template void ThreadFactory::launch<NavigationSubsystem>(std::atomic<bool>&);
