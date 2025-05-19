#pragma once
class Subsystem
{
public:
    virtual void run() = 0;
    virtual ~Subsystem() = default;
};
