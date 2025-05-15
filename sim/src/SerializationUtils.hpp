#pragma once
#include <cstdint>
void writeBigEndian16(uint16_t value, uint8_t* buffer);
uint16_t readBigEndian16(const uint8_t* buffer);
