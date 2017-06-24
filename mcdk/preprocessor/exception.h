#ifndef MCDK_PREPROCESSOR_EXCEPTION_H
#define MCDK_PREPROCESSOR_EXCEPTION_H

#include "mcdk/util/to_string.h"

namespace mc {

#define MC_THROW(ex, msg) throw ex(toString("[" __FILE__ " ") + toString(__FUNCTION__) + ":" + toString(__LINE__) + "] " + toString(msg))

}


#endif
