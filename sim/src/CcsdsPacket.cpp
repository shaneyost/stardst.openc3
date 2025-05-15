#include "CcsdsPacket.hpp"

CcsdsPacket::CcsdsPacket(const CcsdsPrimaryHeader& primary,
                         const CcsdsSecondaryHeader& secondary,
                         std::vector<uint8_t>&& data)
    : primary_(primary), secondary_(secondary), data_(std::move(data)) {}

std::vector<uint8_t> CcsdsPacket::serialize() const
{
    uint16_t dataLength = static_cast<uint16_t>(secondary_.serialize().size() + data_.size() - 1);

    auto headerBytes = primary_.serialize(dataLength);
    auto secondaryBytes = secondary_.serialize();

    std::vector<uint8_t> packet;
    packet.insert(packet.end(), headerBytes.begin(), headerBytes.end());
    packet.insert(packet.end(), secondaryBytes.begin(), secondaryBytes.end());
    packet.insert(packet.end(), data_.begin(), data_.end());

    return packet;
}
