#ifndef MCDK_UTIL_THROW_H
#define MCDK_UTIL_THROW_H

#include "mcdk/util/string.h"

namespace mc {

#define MC_THROW(ex, msg) throw ex(toString("[" __FILE__ " ") + toString(__FUNCTION__) + ":" + toString(__LINE__) + "] " + toString(msg))

}


#endif

