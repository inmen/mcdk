#ifndef MCDK_PREPROCESSOR_EXCEPTION_H
#define MCDK_PREPROCESSOR_EXCEPTION_H

#include <string>

#define MC_THROW(ex, msg) throw ex(std::string("[" __FILE__ " " __FUNCTION__ ":") + std::to_string(__LINE__) + "] " + std::to_string(msg))


#endif
