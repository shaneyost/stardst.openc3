#pragma once
#include "SimulationStrategy.hpp"

class IncrementalStrategy : public SimulationStrategy
{
public:
    template <typename T>
    void applyGeneric(T& value) { value += 1; }

    void apply(uint8_t& value) override { applyGeneric(value); }
    void apply(int8_t& value) override { applyGeneric(value); }
    void apply(uint16_t& value) override { applyGeneric(value); }
    void apply(uint32_t& value) override { applyGeneric(value); }
    void apply(int16_t& value) override { applyGeneric(value); }
    void apply(int32_t& value) override { applyGeneric(value); }
    void apply(float& value) override { applyGeneric(value); }
    void apply(double& value) override { applyGeneric(value); }
};
