#ifndef MCDK_UTIL_STRING_H
#define MCDK_UTIL_STRING_H

#include <string>
#include <sstream>

namespace mc {


template <class T>
inline std::string ToString(T && t) {
    std::stringstream ss;
    ss << t;
    return ss.str();
}

inline std::string ToString(const std::string & s) {
    return s;
}

    /*
inline std::string ToString(const char * s) {
    return std::string(s);
}
     */

template <class T1, class T2>
inline std::string ToString(std::pair<T1, T2> && p, const std::string & delim = ",", const std::string & lborder = "[", const std::string & rborder = "]") {
    std::stringstream ss;
    ss << lborder << p.first << delim << p.second << rborder;
    return ss.str();
}

template <class ForwardIter>
inline std::string ToString(ForwardIter iter_begin, ForwardIter iter_end, const std::string & delim = ",", const std::string & lborder = "[", const std::string & rborder = "]") {
    std::stringstream ss;
    ss << lborder;
    for (; iter_begin != iter_end; ++iter_begin) {
        ss << *iter_begin << delim;
    }
    ss << rborder;
    return ss.str();
}


template <class T>
struct FromString {
    T operator()(const std::string && s) {
        std::stringstream ss(s);
        T t;
        ss >> t;
        return t;
    }
    T operator()(const char *s) {
        std::stringstream ss(s);
        T t;
        ss >> t;
        return t;
    }
};
template <>
struct FromString<std::string> {
    std::string operator()(const std::string & s) {
        return s;
    }
};


}



#endif
