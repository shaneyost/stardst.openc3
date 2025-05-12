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

/*
*   INFO:   Since I'm picking back up w/ Cpp I'm going to document stuff along 
*           the way as I relearn things.
*
*   What is "auto& thread" mean? 
*
*       Give me a reference to each thread in the list. It lets C++
*       automatically figure out the type, in this case, "std::thread&". The &
*       means "reference", so it doesn't copy the thread, it refers to the real
*       one.
*
*   Why use "unique_ptr" here? What is it for/doing?
*
*       "unique_ptr" is a smart pointer that owns one object and in this case
*       points to Subsystem. I can say "This is my object, no one else can have
*       it". 
*
*       I use "make_unique" to create a "unique_ptr" safely without needed new.
*
*   What is threads.emplace_back and what is this []() {} syntax for?
*
*       I am starting a new thread that runs code and then I add it to my 
*       thread list is the stupid version of how to think of it ... i guess.
*
*       The emplace_back adds a new thread to my list. The [](){} block is a 
*       lambda which is like a mini function in place.
*
*       Takeaway is "starts a new thread with inline code (lambda) and stores
*       it in my list for managing later.
*
*   Again why do I explicitly instantiate subsystem types here?
*
*       In plain english it is because templates aren't real code until I 
*       commit to a type. So I'm saying "i'm finalizing my promise to support
*       NavigationSubsystem here".
*
*       This is required because the template is defined in cpp not hpp. This 
*       is me saying "Hey Compiler, make this function real for ThisSubsystem
*/
