#pragma once
#include <cstdint>
#include <memory>
#include <random>

class SimulationStrategy
{
public:
    virtual ~SimulationStrategy() = default;

    virtual void apply(uint8_t& value) = 0;
    virtual void apply(int8_t& value) = 0;
    virtual void apply(uint16_t& value) = 0;
    virtual void apply(int16_t& value) = 0;
    virtual void apply(uint32_t& value) = 0;
    virtual void apply(int32_t& value) = 0;
    virtual void apply(float& value) = 0;
    virtual void apply(double& value) = 0;
};
