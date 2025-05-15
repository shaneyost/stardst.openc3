#pragma once
#include <array>
#include <cstdint>

class CcsdsPrimaryHeader
{
public:
    static CcsdsPrimaryHeader createTelemetryPacket(uint16_t apid);

    void setApid(uint16_t apid);
    void incrementSequenceCount();
    uint16_t getSequenceCount() const;
    std::array<uint8_t, 6> serialize(uint16_t dataLength) const;
    static CcsdsPrimaryHeader deserialize(const std::array<uint8_t, 6>& buffer);

private:
    uint8_t version_ = 0;
    uint8_t type_ = 0;
    uint8_t secondaryHeaderFlag_ = 1;
    uint16_t apid_;
    uint8_t sequenceFlags_ = 3; // Standalone packet
    uint16_t sequenceCount_ = 0;
};

