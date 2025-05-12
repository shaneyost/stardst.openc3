#pragma once
class Subsystem
{
public:
    virtual void run() = 0;
    virtual ~Subsystem() = default;
};

/*
*   INFO:   Since I'm picking back up w/ Cpp I'm going to document stuff along
*           the way as I relearn things.
*
*   Why doesn't "Subsystem.hpp" have a cpp?
*
*       We only need to define the interface, not any actual work. Technically
*       there's nothing to implement yet so this will do.
*
*       Pure virtual classes (like this one) define an interface, not behavior.
*       They force derived classes to implement the methods. There's not work
*       to put here thus no logic.
*
*       The only function defined here is the destructor, and it's defaulted 
*       meaning the compiler will generate it for me.
*
*   What is virtual and why am I inilializing this to zero?
*
*       Virtual keyword lets child classes customize how this function works.
*       The init to zero forces child classes to provide their own version of
*       the function.
*
*       Virtual enables runtime polymorphism. This means you can treat 
*       different subsystems the same way (through a base pointer) but they run
*       their own logic.
*
*       I guess saying we init to zero is wrong. I should say assign zero that
*       makes the function pure virtual, turning this class into an abstract
*       base class. Moreo specifically ...
*           
*           - I cannot create an instance of Subsystem directly
*           - I must create a dervied class (like NavigationSubsystem) that 
*             overrides "run()".
*
*       So the story is, "virtual" and "=0" is a way of defining an interface
*       that requires implementation by others.
*
*   What is "#pragma once"? Why use is than the C style alternative?
*
*       It does the same thing as "#ifndef" guards but looks cleaner. It 
*       prevents the file from being included more than once.
*
*       It is supported by all major compilers, but not part of the official 
*       C++ standard. Considered safe and modern. Simplicity and readability
*/
