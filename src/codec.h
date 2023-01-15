// Derived from Fibre
//
// Original License follows
//
// MIT License

// Copyright (c) 2017-2020 The Fibre Contributors

// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#pragma once

//#include <limits>
//#include <climits>
#include <Arduino.h>

template<typename T>
inline size_t write_le(T value, uint8_t* buffer);

template<typename T>
inline size_t read_le(T* value, const uint8_t* buffer);

template<>
inline size_t write_le<bool>(bool value, uint8_t* buffer) {
    buffer[0] = value ? 1 : 0;
    return 1;
}

template<>
inline size_t write_le<uint8_t>(uint8_t value, uint8_t* buffer) {
    buffer[0] = value;
    return 1;
}

template<>
inline size_t write_le<int8_t>(int8_t value, uint8_t* buffer) {
    buffer[0] = value;
    return 1;
}

template<>
inline size_t write_le<uint16_t>(uint16_t value, uint8_t* buffer) {
    buffer[0] = (value >> 0) & 0xff;
    buffer[1] = (value >> 8) & 0xff;
    return 2;
}

template<>
inline size_t write_le<int16_t>(int16_t value, uint8_t* buffer) {
    buffer[0] = (value >> 0) & 0xff;
    buffer[1] = (value >> 8) & 0xff;
    return 2;
}

template<>
inline size_t write_le<uint32_t>(uint32_t value, uint8_t* buffer) {
    buffer[0] = (value >> 0) & 0xff;
    buffer[1] = (value >> 8) & 0xff;
    buffer[2] = (value >> 16) & 0xff;
    buffer[3] = (value >> 24) & 0xff;
    return 4;
}

template<>
inline size_t write_le<int32_t>(int32_t value, uint8_t* buffer) {
    buffer[0] = (value >> 0) & 0xff;
    buffer[1] = (value >> 8) & 0xff;
    buffer[2] = (value >> 16) & 0xff;
    buffer[3] = (value >> 24) & 0xff;
    return 4;
}

template<>
inline size_t write_le<uint64_t>(uint64_t value, uint8_t* buffer) {
    buffer[0] = (value >> 0) & 0xff;
    buffer[1] = (value >> 8) & 0xff;
    buffer[2] = (value >> 16) & 0xff;
    buffer[3] = (value >> 24) & 0xff;
    buffer[4] = (value >> 32) & 0xff;
    buffer[5] = (value >> 40) & 0xff;
    buffer[6] = (value >> 48) & 0xff;
    buffer[7] = (value >> 56) & 0xff;
    return 8;
}

template<>
inline size_t write_le<float>(float value, uint8_t* buffer) {
    //static_assert(CHAR_BIT * sizeof(float) == 32, "32 bit floating point expected");
    //static_assert(std::numeric_limits<float>::is_iec559, "IEEE 754 floating point expected");
    const uint32_t * value_as_uint32 = reinterpret_cast<const uint32_t*>(&value);
    return write_le<uint32_t>(*value_as_uint32, buffer);
}

template<>
inline size_t read_le<bool>(bool* value, const uint8_t* buffer) {
    *value = buffer[0];
    return 1;
}

template<>
inline size_t read_le<uint8_t>(uint8_t* value, const uint8_t* buffer) {
    *value = buffer[0];
    return 1;
}

template<>
inline size_t read_le<uint8_t>(int8_t* value, const uint8_t* buffer) {
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
inline size_t read_le<uint64_t>(uint64_t* value, const uint8_t* buffer) {
    *value = (static_cast<uint64_t>(buffer[0]) << 0) |
             (static_cast<uint64_t>(buffer[1]) << 8) |
             (static_cast<uint64_t>(buffer[2]) << 16) |
             (static_cast<uint64_t>(buffer[3]) << 24) |
             (static_cast<uint64_t>(buffer[4]) << 32) |
             (static_cast<uint64_t>(buffer[5]) << 40) |
             (static_cast<uint64_t>(buffer[6]) << 48) |
             (static_cast<uint64_t>(buffer[7]) << 56);
    return 8;
}

template<>
inline size_t read_le<float>(float* value, const uint8_t* buffer) {
    //static_assert(CHAR_BIT * sizeof(float) == 32, "32 bit floating point expected");
    //static_assert(std::numeric_limits<float>::is_iec559, "IEEE 754 floating point expected");
    return read_le(reinterpret_cast<uint32_t*>(value), buffer);
}

// @brief Reads a value of type T from the buffer.
// @param buffer    Pointer to the buffer to be read. The pointer is updated by the number of bytes that were read.
// @param length    The number of available bytes in buffer. This value is updated to subtract the bytes that were read.
template<typename T>
static inline T read_le(const uint8_t** buffer, size_t* length) {
    T result;
    size_t cnt = read_le(&result, *buffer);
    *buffer += cnt;
    *length -= cnt;
    return result;
}
