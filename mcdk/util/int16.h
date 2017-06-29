#ifndef MCDK_UTIL_INT16_H
#define MCDK_UTIL_INT16_H

#include <cstdint>
#include "mcdk/util/preprocessor.h"

namespace mc {

class Int16 {
public:
    static int8_t ToInt8(int16_t i) {
        if (i < INT8_MIN) return INT8_MIN;
        if (i > INT8_MAX) return INT8_MAX;
        return static_cast<int8_t>(i);
    }
    static int16_t FromInt8(int8_t i) { return static_cast<int16_t>(i); }
    static uint8_t ToUInt8(int16_t i) {
        if (i < 0) return 0;
        if (i > )
        return static_cast<uint8_t>(i);
    }
    static int8_t FromUInt8(uint8_t i) {
        if (i > INT8_MAX) return INT8_MAX;
        return static_cast<int8_t>(i);
    }
    static int16_t ToInt16(int8_t i) { return static_cast<int16_t>(i); }
    static int8_t FromInt16(int16_t i) {
        if (i < INT8_MIN) return INT8_MIN;
        if (i > INT8_MAX) return INT8_MAX;
        return static_cast<int8_t>(i);
    }
    static uint16_t ToUInt16(int8_t i) {
        if (i < 0) return 0;
        return static_cast<uint16_t>(i);
    }
    static int8_t FromUInt16(uint16_t i) {
        if (i > INT8_MAX) return INT8_MAX;
        return static_cast<int8_t>(i);
    }
    static int32_t ToInt32(int8_t i) { return static_cast<int32_t>(i); }
    static int8_t FromInt32(int32_t i) {
        if (i < INT8_MIN) return INT8_MIN;
        if (i > INT8_MAX) return INT8_MAX;
        return static_cast<int8_t>(i);
    }
    static uint32_t ToUInt32(int8_t i) {
        if (i < 0) return 0;
        return static_cast<uint32_t>(i);
    }
    static int8_t FromUInt32(uint32_t i) {
        if (i > INT8_MAX) return INT8_MAX;
        return static_cast<int8_t>(i);
    }
    static int64_t ToInt64(int8_t i) { return static_cast<int64_t>(i); }
    static int8_t FromInt64(int64_t i) {
        if (i < INT8_MIN) return INT8_MIN;
        if (i > INT8_MAX) return INT8_MAX;
        return static_cast<int8_t>(i);
    }
    static uint64_t ToUInt64(int8_t i) {
        if (i < 0) return 0;
        return static_cast<uint64_t>(i);
    }
    static int8_t FromUInt64(uint64_t i) {
        if (i > INT8_MAX) return INT8_MAX;
        return static_cast<int8_t>(i);
    }
};

class UInt16 {
public:
    static int8_t ToInt8(uint8_t i) {
        if (i > INT8_MAX) return INT8_MAX;
        return static_cast<int8_t>(i);
    }
    static uint8_t FromInt8(int8_t i) {
        if (i < 0) return 0;
        return static_cast<uint8_t>(i);
    }
    static uint8_t ToUInt8(uint8_t i) { return i; }
    static uint8_t FromUInt8(uint8_t i) { return i; }
    static int16_t ToInt16(uint8_t i) { return static_cast<int16_t>(i); }
    static uint8_t FromInt16(int16_t i) {
        if (i < 0) return 0;
        return static_cast<uint8_t>(i);
    }
    static uint16_t ToUInt16(uint8_t i) { return static_cast<uint16_t>(i); }
    static uint8_t FromUInt16(uint16_t i) {
        if (i > UINT8_MAX) return UINT8_MAX;
        return static_cast<uint8_t>(i);
    }
    static int32_t ToInt32(int8_t i) { return static_cast<int32_t>(i); }
    static uint8_t FromInt32(int32_t i) {
        if (i < 0) return 0;
        if (i > UINT8_MAX) return UINT8_MAX;
        return static_cast<uint8_t>(i);
    }
    static uint32_t ToUInt32(uint8_t i) { return static_cast<uint32_t>(i); }
    static uint8_t FromUInt32(uint32_t i) {
        if (i > UINT8_MAX) return UINT8_MAX;
        return static_cast<uint8_t>(i);
    }
    static int64_t ToInt64(uint8_t i) { return static_cast<int64_t>(i); }
    static uint8_t FromInt64(int64_t i) {
        if (i < 0) return 0;
        if (i > UINT8_MAX) return UINT8_MAX;
        return static_cast<uint8_t>(i);
    }
    static uint64_t ToUInt64(uint8_t i) { return static_cast<uint64_t>(i); }
    static uint8_t FromUInt64(uint64_t i) {
        if (i > UINT8_MAX) return UINT8_MAX;
        return static_cast<uint8_t>(i);
    }
};

}

#endif

