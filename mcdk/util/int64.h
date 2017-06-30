#ifndef MCDK_UTIL_INT64_H
#define MCDK_UTIL_INT64_H
#pragma once

#include <cstdint>
#include "mcdk/util/preprocessor.h"

namespace mc {

class Int64 {
public:

#define MC_CAST(func_name, from_type, to_type, to_min, to_max) \
    static to_type func_name(from_type i) {     \
        if (i > to_max) return to_max;  \
        if (i < to_min) return to_min;  \
        return static_cast<to_type>(i);     \
    }

    MC_CAST(ToInt8, int64_t, int8_t, INT8_MIN, INT8_MAX)
    MC_CAST(FromInt8, int8_t, int64_t, INT64_MIN, INT64_MAX)
    MC_CAST(ToUInt8, int64_t, uint8_t, 0, UINT8_MAX)
    MC_CAST(FromUInt8, uint8_t, int64_t, INT64_MIN, INT64_MAX)
    MC_CAST(ToInt16, int64_t, int16_t, INT16_MIN, INT16_MAX)
    MC_CAST(FromInt16, int16_t, int64_t, INT64_MIN, INT64_MAX)
    MC_CAST(ToUInt16, int64_t, uint16_t, 0, UINT16_MAX)
    MC_CAST(FromUInt16, uint16_t, int64_t, INT64_MIN, INT64_MAX)
    MC_CAST(ToInt32, int64_t, int32_t, INT32_MIN, INT32_MAX)
    MC_CAST(FromInt32, int32_t, int64_t, INT64_MIN, INT64_MAX)
    MC_CAST(ToUInt32, int64_t, uint32_t, 0, UINT32_MAX)
    MC_CAST(FromUInt32, uint32_t, int64_t, INT64_MIN, INT64_MAX)
    MC_CAST(ToUInt64, int64_t, uint64_t, 0, UINT64_MAX)
    MC_CAST(FromUInt64, uint64_t, int64_t, INT64_MIN, INT64_MAX)

    static int64_t Parse(const std::string &s, int radix) throw(std::invalid_argument) {
        if (radix < 2) throw std::invalid_argument(MC_LOC + " radix " + ToString(radix) + " less than 2");
        if (radix > 36) throw std::invalid_argument(MC_LOC + " radix " + ToString(radix) + " greater than 36");

    }
};

class UInt64 {
public:
    MC_CAST(ToInt8, uint64_t, int8_t, INT8_MIN, INT8_MAX)
    MC_CAST(FromInt8, int8_t, uint64_t, 0, UINT64_MAX)
    MC_CAST(ToUInt8, uint64_t, uint8_t, 0, UINT8_MAX)
    MC_CAST(FromUInt8, uint8_t, uint64_t, 0, UINT64_MAX)
    MC_CAST(ToInt16, uint64_t, int16_t, INT16_MIN, INT16_MAX)
    MC_CAST(FromInt16, int16_t, uint64_t, 0, UINT64_MAX)
    MC_CAST(ToUInt16, uint64_t, uint16_t, 0, UINT16_MAX)
    MC_CAST(FromUInt16, uint16_t, uint64_t, 0, UINT64_MAX)
    MC_CAST(ToInt32, uint64_t, int32_t, INT32_MIN, INT32_MAX)
    MC_CAST(FromInt32, int32_t, uint64_t, 0, UINT64_MAX)
    MC_CAST(ToUInt32, uint64_t, uint32_t, 0, UINT32_MAX)
    MC_CAST(FromUInt32, uint32_t, uint64_t, 0, UINT64_MAX)
    MC_CAST(ToInt64, uint64_t, int64_t, INT64_MIN, INT64_MAX)
    MC_CAST(FromInt64, int64_t, uint64_t, 0, UINT64_MAX)

#undef MC_CAST
};

}

#endif
