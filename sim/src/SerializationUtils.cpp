#include "SerializationUtils.hpp"

void writeBigEndian16(uint16_t value, uint8_t* buffer)
{
    buffer[0] = (value >> 8) & 0xFF;
    buffer[1] = value & 0xFF;
}

uint16_t readBigEndian16(const uint8_t* buffer)
{
    return (static_cast<uint16_t>(buffer[0]) << 8) | buffer[1];
}

