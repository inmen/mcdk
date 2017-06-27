#ifndef MCDK_UTIL_PREPROCESSOR_LOCATION_H
#define MCDK_UTIL_PREPROCESSOR_LOCATION_H

#include "mcdk/util/string.h"

#define MC_PP_LOC (mc::toString("[" __FILE__) + " " + __FUNCTION__ + ":" + mc::toString(__LINE__) + "]")



#endif
