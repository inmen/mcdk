#ifndef MCDK_UTIL_BASE64_HPP
#define MCDK_UTIL_BASE64_HPP
#pragma once

#include "mcdk/util/base64.h"

class Base64 {
public:
    class Encoder;
    class Decoder;

private:
    Base64() {}

public:
    static Encoder getEncoder();
    static Encoder getUrlEncoder();
    static Encoder getMimeEncoder();
    static Decoder getDecoder();
    static Decoder getUrlDecoder();
    static Decoder getMimeDecoder();
};



#endif
