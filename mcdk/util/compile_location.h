#ifndef MCDK_UTIL_COMPILE_LOCATION_H
#define MCDK_UTIL_COMPILE_LOCATION_H

#include "mcdk/util/string.h"

namespace mc {

#define MC_COMPILE_LOC (toString("[" __FILE__) + " " __FUNCTION__ + ":" + toString(__LINE__))


}


#endif
