#ifndef MCDK_UTIL_BOOL_H
#define MCDK_UTIL_BOOL_H

#include "mcdk/util/preprocessor.h"

namespace mc {

class Bool {
public:

    static std::string ToString(bool b) { return b ? "true" : "false"; }
    static bool FromString(const std::string &b) { return b == "true"; }

};

}


#endif
