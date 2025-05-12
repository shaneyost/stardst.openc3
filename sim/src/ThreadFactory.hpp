#pragma once
#include "Subsystem.hpp"
#include <vector>
#include <memory>
#include <thread>

class ThreadFactory
{
public:
    template <typename SubsystemType>
    void launch(std::atomic<bool>& runningFlag);
    ~ThreadFactory();
private:
    std::vector<std::thread> threads;
};

/*
*   INFO:   Since I'm picking back up w/ Cpp I'm going to document stuff along 
*           the way as I relearn things.
*
*   What is a template? This is something I haven't done and I'm implementing
*   it here as an exercise to become familiar with it more.
*
*       A template lets me write one function or class that works with any type
*       not just one. Here, it lets ThreadFactory launch any kind of subsystem
*       not just a NavigationSubsystem for example.
*
*       The "template <typename SubsystemType> means this function works for
*       any type you pass in. That type must follow the interface defined in
*       Subsystem.hpp (aka have a run() function).
*
*       Subsystem.hpp defines what qualifies as a "subsystem", so the template
*       assumes any type passed in behaves like a Subsystem.
*
*       So "template" here says one function that works with any subsystem 
*       class (as long as it follows Subsystem's rules).
*
*   What would this look like without a template?
*
*       I would have to hardcode the function to only launch one specific type.
*
*       void launchNavigation()
*       {
*           std::unique_ptr<Subsystem> subsystem = std::make_unique<NavigationSubsystem>();
*           threads.emplace_back([subsystem = std::move(subsystem)]()
*           {
*               subsystem->run();
*           });
*       }
*
*       The problem is that I would need a new function for every subsystem
*       which sucks for scaling. So one "launch<AnySubsystem>()" works for all
*       subsystems.
*
*   What is the vector for and why does it have "std::thread in it?
*
*       The vector is a list that holds all the threads I start. This keeps 
*       track of running subsystems. So it says "start all the systems, and
*       keep their threads in a list so we can manage them later".
*
*       "sdt::vector<std::thread>" is defining a resizable array in C++. The
*       "std::thread" being a thread of execution. The vector stores all 
*       launched threads, so they don't go out of scope and get cleaned up too
*       early.
*
*       So vector here is a list of threads that keeps my subsystems alive and
*       manageable.
*
*   Why are we making the vector private?
*
*       Only ThreadFactory can add or manage threads so it's protected from
*       outside usage. Private here is hiding implementation details for me
*       thus exercising Encapsulation (hide and expose only what is needed).
*
*   Where is "memory" header used here? Where is "Subsystem.hpp" used here?
*
*       "memory" is used for std::unique_ptr" which will occur in the cpp.
*
*       "Subsystem" is included to recognize what a Subsystem is so the vector
*       and factory know what to work with.
*
*       The more technical explanation is that "memory" provides smart pointers
*       like std::unique_ptr. "Subsystem.hpp" declares the base interface so
*       the compiler knows the type. I must include what I reference even 
*       indirectly through templates.
*/
