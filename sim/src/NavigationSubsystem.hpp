#pragma once
#include "Subsystem.hpp"

class NavigationSubsystem : public Subsystem
{
public:
    void run() override;
};

/*
*   INFO:   Since I'm picking back up w/ Cpp I'm going to document stuff along 
*           the way as I relearn things.
*
*   Initially I forgot the syntax convention for implying inheritance. So lets
*   take a small note on what ":" means.
*
*       This ":" means "inherits from". "NavigationSubsystem" is a kind of 
*       "Subsystem". The ":" introduces a base class in inheritance. Is-a
*
*       Prepending "public" says inherit all public and protected members of 
*       Subsystem. Make them accessible in the same way to users of
*       NavigationSubsystem.
*
*   So why make "run()" public?
*
*       I've declared "run()" as public in Subsystem class so derived classes
*       must match or be less restrictive. 
*
*       ThreadFactory, which owns a Subsystem, needs to call "run()" on it. 
*       Public lets outside code (like my ThreadFactory) run the subsystem.
*
*       It might be helpful to understand here that ThreadFactory is a runner.
*       Subsystem and NavigationSubsystem are the runnables.
*
*           - "Subsystem.hpp (Here's what a runnable looks like"
*           - "NavigationSubsystem.hpp/cpp (Here's a runnable that does this)
*           - "ThreadFactory.hpp/cpp (Here's how to run one in a thread)
*
*       Best typically to define what to run first, then you define how to run
*       it.
*/
