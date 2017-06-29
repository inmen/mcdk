#ifndef MCDK_LANG_PREPROCESSOR_LOCATION_H
#define MCDK_LANG_PREPROCESSOR_LOCATION_H

#include "mcdk/util/string.h"

#ifdef __GNUC__
#   define MC_PP_LOC (mc::ToString(__FILE__) + ":" + mc::ToString(__LINE__) + " " + __PRETTY_FUNCTION__)
#else
#   define MC_PP_LOC (mc::ToString(__FILE__) + ":" + mc::ToString(__LINE__) + " " + __FUNCTION__)
#endif


#endif
