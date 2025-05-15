#pragma once
#include "CcsdsPrimaryHeader.hpp"
#include "CcsdsSecondaryHeader.hpp"
#include <vector>
#include <cstdint>

class CcsdsPacket
{
public:
    CcsdsPacket(const CcsdsPrimaryHeader& primary,
                const CcsdsSecondaryHeader& secondary,
                std::vector<uint8_t>&& data);

    std::vector<uint8_t> serialize() const;

private:
    CcsdsPrimaryHeader primary_;
    CcsdsSecondaryHeader secondary_;
    std::vector<uint8_t> data_;
};
