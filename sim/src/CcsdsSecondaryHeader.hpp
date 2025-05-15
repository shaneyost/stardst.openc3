#pragma once
#include <array>
#include <cstdint>

class CcsdsSecondaryHeader
{
public:
    CcsdsSecondaryHeader() = default;

    void setEpoch(uint64_t epoch);
    uint64_t getEpoch() const;
    static CcsdsSecondaryHeader now();

    std::array<uint8_t, 8> serialize() const;

private:
    uint64_t epoch_ = 0;
};
