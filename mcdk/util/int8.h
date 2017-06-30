#ifndef MCDK_UTIL_INT8_H
#define MCDK_UTIL_INT8_H

#include <cstdint>
#include "mcdk/util/preprocessor.h"

namespace mc {

class Int8 {
public:

#define MC_CAST(func_name, from_type, to_type, to_min, to_max) \
    static to_type func_name(from_type i) {     \
        if (i > to_max) return to_max;  \
        if (i < to_min) return to_min;  \
        return static_cast<to_type>(i);     \
    }

    MC_CAST(ToUInt8, int8_t, uint8_t, 0, UINT8_MAX)
    MC_CAST(FromUInt8, uint8_t, int8_t, INT8_MIN, INT8_MAX)
    MC_CAST(ToInt16, int8_t, int16_t, INT16_MIN, INT16_MAX)
    MC_CAST(FromInt16, int16_t, int8_t, INT8_MIN, INT8_MAX)
    MC_CAST(ToUInt16, int8_t, uint16_t, 0, UINT16_MAX)
    MC_CAST(FromUInt16, uint16_t, int8_t, INT8_MIN, INT8_MAX)
    MC_CAST(ToInt32, int8_t, int32_t, INT32_MIN, INT32_MAX)
    MC_CAST(FromInt32, int32_t, int8_t, INT8_MIN, INT8_MAX)
    MC_CAST(ToUInt32, int8_t, uint32_t, 0, UINT32_MAX)
    MC_CAST(FromUInt32, uint32_t, int8_t, INT8_MIN, INT8_MAX)
    MC_CAST(ToInt64, int8_t, int64_t, INT64_MIN, INT64_MAX)
    MC_CAST(FromInt64, int64_t, int8_t, INT8_MIN, INT8_MAX)
    MC_CAST(ToUInt64, int8_t, uint64_t, 0, UINT64_MAX)
    MC_CAST(FromUInt64, uint64_t, int8_t, INT8_MIN, INT8_MAX)
};

class UInt8 {
public:
    MC_CAST(ToInt8, uint8_t, int8_t, INT8_MIN, INT8_MAX)
    MC_CAST(FromInt8, int8_t, uint8_t, 0, UINT8_MAX)
    MC_CAST(ToInt16, int8_t, int16_t, INT16_MIN, INT16_MAX)
    MC_CAST(FromInt16, int16_t, int8_t, INT8_MIN, INT8_MAX)
    MC_CAST(ToUInt16, int8_t, uint16_t, 0, UINT16_MAX)
    MC_CAST(FromUInt16, uint16_t, int8_t, INT8_MIN, INT8_MAX)
    MC_CAST(ToInt32, int8_t, int32_t, INT32_MIN, INT32_MAX)
    MC_CAST(FromInt32, int32_t, int8_t, INT8_MIN, INT8_MAX)
    MC_CAST(ToUInt32, int8_t, uint32_t, 0, UINT32_MAX)
    MC_CAST(FromUInt32, uint32_t, int8_t, INT8_MIN, INT8_MAX)
    MC_CAST(ToInt64, int8_t, int64_t, INT64_MIN, INT64_MAX)
    MC_CAST(FromInt64, int64_t, int8_t, INT8_MIN, INT8_MAX)
    MC_CAST(ToUInt64, int8_t, uint64_t, 0, UINT64_MAX)
    MC_CAST(FromUInt64, uint64_t, int8_t, INT8_MIN, INT8_MAX)

#undef MC_CAST
};

}

#endif
