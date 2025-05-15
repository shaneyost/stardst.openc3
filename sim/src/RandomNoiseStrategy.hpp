#pragma once
#include "SimulationStrategy.hpp"

class RandomNoiseStrategy : public SimulationStrategy
{
public:
    RandomNoiseStrategy() : rng_(std::random_device{}()), dist_(0, 100) {}

    template <typename T>
    void applyGeneric(T& value) { value = static_cast<T>(dist_(rng_)); }

    void apply(uint8_t& value) override { applyGeneric(value); }
    void apply(int8_t& value) override { applyGeneric(value); }
    void apply(uint16_t& value) override { applyGeneric(value); }
    void apply(uint32_t& value) override { applyGeneric(value); }
    void apply(int16_t& value) override { applyGeneric(value); }
    void apply(int32_t& value) override { applyGeneric(value); }
    void apply(float& value) override { applyGeneric(value); }
    void apply(double& value) override { applyGeneric(value); }

private:
    std::mt19937 rng_;
    std::uniform_int_distribution<> dist_;
};
