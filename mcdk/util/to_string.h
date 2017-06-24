#ifndef MCDK_UTIL_TO_STRING_H
#define MCDK_UTIL_TO_STRING_H

#include <string>

namespace mc {


template <class T>
inline std::string toString(T && t) {
    return std::to_string(t);
}
inline std::string toString(std::string && msg) {
    return msg;
}
inline std::string toString(char *msg) {
    return std::string(msg);
}
inline std::string toString(const char *msg) {
    return std::string(msg);
}
inline std::string toString(char && c) {
    std::string r;
    r.push_back(c);
    return r;
}
inline std::string toString(const char && c) {
    std::string r;
    r.push_back(c);
    return r;
}
inline std::string toString(char c) {
    std::string r;
    r.push_back(c);
    return r;
}


}



#endif
