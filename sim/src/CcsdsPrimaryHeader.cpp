#include "CcsdsPrimaryHeader.hpp"
#include "SerializationUtils.hpp"

CcsdsPrimaryHeader CcsdsPrimaryHeader::createTelemetryPacket(uint16_t apid)
{
    CcsdsPrimaryHeader hdr;
    hdr.apid_ = apid;
    return hdr;
}

void CcsdsPrimaryHeader::setApid(uint16_t apid)
{
    apid_ = apid;
}

void CcsdsPrimaryHeader::incrementSequenceCount()
{
    sequenceCount_ = (sequenceCount_ + 1) & 0x3FFF; // Wraps at 14 bits
}

uint16_t CcsdsPrimaryHeader::getSequenceCount() const
{
    return sequenceCount_;
}

std::array<uint8_t, 6> CcsdsPrimaryHeader::serialize(uint16_t dataLength) const
{
    std::array<uint8_t, 6> buffer{};

    uint16_t word1 =    ((version_ & 0x07) << 13)               |
                        ((type_ & 0x01) << 12)                  |
                        ((secondaryHeaderFlag_ & 0x01) << 11)   |
                        ((apid_ & 0x07FF));

    uint16_t word2 =    ((sequenceFlags_ & 0x03) << 14)         |
                        ((sequenceCount_ & 0x3FFF));

    uint16_t word3 =    dataLength;

    writeBigEndian16(word1, &buffer[0]);
    writeBigEndian16(word2, &buffer[2]);
    writeBigEndian16(word3, &buffer[4]);

    return buffer;
}
