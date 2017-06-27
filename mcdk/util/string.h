#ifndef MCDK_UTIL_STRING_H
#define MCDK_UTIL_STRING_H

#include <string>
#include <sstream>

namespace mc {


template <class T>
inline std::string toString(T && t) {
    std::stringstream ss;
    ss << t;
    return ss.str();
}

inline std::string toString(const std::string & s) {
    return s;
}

inline std::string toString(const char * s) {
    return std::string(s);
}

template <class T1, class T2>
inline std::string toString(std::pair<T1, T2> && p, const std::string & delim = ",", const std::string & lborder = "[", const std::string & rborder = "]") {
    std::stringstream ss;
    ss << lborder << p.first << delim << p.second << rborder;
    return ss.str();
}

template <class ForwardIter>
inline std::string toString(ForwardIter iter_begin, ForwardIter iter_end, const std::string & delim = ",", const std::string & lborder = "[", const std::string & rborder = "]") {
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
    T operator()(std::string && s) {
        std::stringstream ss(s);
        T t;
        ss >> t;
        return t;
    }
};


}



#endif
