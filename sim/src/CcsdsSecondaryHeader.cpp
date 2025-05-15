#include "CcsdsSecondaryHeader.hpp"

void CcsdsSecondaryHeader::setEpoch(uint64_t epoch)
{
    epoch_ = epoch;
}

uint64_t CcsdsSecondaryHeader::getEpoch() const
{
    return epoch_;
}

CcsdsSecondaryHeader CcsdsSecondaryHeader::now()
{
    constexpr uint64_t BATTLE_OF_YAVIN_UNIX_EPOCH = 233366400;
    auto unixEpoch = std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();

    CcsdsSecondaryHeader header;
    header.setEpoch(unixEpoch - BATTLE_OF_YAVIN_UNIX_EPOCH);
    return header;
}

std::array<uint8_t, 8> CcsdsSecondaryHeader::serialize() const
{
    std::array<uint8_t, 8> buffer{};
    for (int i = 0; i < 8; ++i)
    {
        buffer[7 - i] = (epoch_ >> (i * 8)) & 0xFF; // Big-endian
    }
    return buffer;
}
