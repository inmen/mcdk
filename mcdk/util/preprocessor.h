#ifndef MCDK_LANG_PREPROCESSOR_LOCATION_H
#define MCDK_LANG_PREPROCESSOR_LOCATION_H

#include "mcdk/util/string.h"
#include <boost/preprocessor.hpp>

#ifdef __GNUC__
#   define MC_LOC (mc::ToString(__FILE__) + ":" + mc::ToString(__LINE__) + " " + __PRETTY_FUNCTION__)
#else
#   define MC_LOC (mc::ToString(__FILE__) + ":" + mc::ToString(__LINE__) + " " + __FUNCTION__)
#endif

#define MC_CAT_II(a, b) BOOST_PP_CAT(a, b)
#define MC_CAT_III(a, b, c) MC_PP_CAT_II(MC_PP_CAT_II(a, b), c))
#define MC_CAT_IV(a, b, c, d) MC_PP_CAT_II(MC_PP_CAT_III(a, b, c), d)
#define MC_CAT_V(a, b, c, d, e) MC_PP_CAT_II(MC_PP_CAT_IV(a, b, c, d), e)
#define MC_CAT_VI(a, b, c, d, e, g) MC_PP_CAT_II(MC_PP_CAT_V(a, b, c, d, e), g)
#define MC_CAT_VII(a, b, c, d, e, g, h) MC_PP_CAT_II(MC_PP_CAT_VI(a, b, c, d, e, g), h)
#define MC_CAT_VIII(a, b, c, d, e, g, h, i) MC_PP_CAT_II(MC_PP_CAT_VII(a, b, c, d, e, g, h), i)
#define MC_CAT_IX(a, b, c, d, e, g, h, i, j) MC_PP_CAT_II(MC_PP_CAT_VIII(a, b, c, d, e, g, h, i), j)


#endif
