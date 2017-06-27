#ifndef MCDK_UTIL_THROW_H
#define MCDK_UTIL_THROW_H

#include "mcdk/util/string.h"
#include "mcdk/util/preprocessor.h"

namespace mc {

#define MC_THROW(ex, msg) throw ex(MC_PP_LOC + toString(msg))

}


#endif

