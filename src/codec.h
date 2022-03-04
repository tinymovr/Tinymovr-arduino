#pragma once 

#include <Arduino.h>

template<typename T>
inline size_t read_le(T* value, const uint8_t* buffer);

template<>
inline size_t read_le<uint8_t>(uint8_t* value, const uint8_t* buffer) {
    *value = buffer[0];
    return 1;
}

template<>
inline size_t read_le<uint16_t>(uint16_t* value, const uint8_t* buffer) {
    *value = (static_cast<uint16_t>(buffer[0]) << 0) |
             (static_cast<uint16_t>(buffer[1]) << 8);
    return 2;
}

template<>
inline size_t read_le<int16_t>(int16_t* value, const uint8_t* buffer) {
    *value = (static_cast<int16_t>(buffer[0]) << 0) |
             (static_cast<int16_t>(buffer[1]) << 8);
    return 2;
}

template<>
inline size_t read_le<int32_t>(int32_t* value, const uint8_t* buffer) {
    *value = (static_cast<int32_t>(buffer[0]) << 0) |
             (static_cast<int32_t>(buffer[1]) << 8) |
             (static_cast<int32_t>(buffer[2]) << 16) |
             (static_cast<int32_t>(buffer[3]) << 24);
    return 4;
}

template<>
inline size_t read_le<uint32_t>(uint32_t* value, const uint8_t* buffer) {
    *value = (static_cast<uint32_t>(buffer[0]) << 0) |
             (static_cast<uint32_t>(buffer[1]) << 8) |
             (static_cast<uint32_t>(buffer[2]) << 16) |
             (static_cast<uint32_t>(buffer[3]) << 24);
    return 4;
}

template<>
inline size_t read_le<float>(float* value, const uint8_t* buffer) {
    // static_assert(CHAR_BIT * sizeof(float) == 32, "32 bit floating point expected");
    // static_assert(std::numeric_limits<float>::is_iec559, "IEEE 754 floating point expected");
    return read_le(reinterpret_cast<uint32_t*>(value), buffer);
}
