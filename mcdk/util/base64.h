#ifndef MCDK_UTIL_BASE64_H
#define MCDK_UTIL_BASE64_H
#pragma once

#include <cstdint>

class Base64 {
public:
    class Encoder {
    private:
        Encoder(bool is_url, char *new_line, int32_t line_max, bool padding);

        

    public:
        static const Encoder RFC4648_ = Encoder(false, nullptr, -1, true);
        static const Encoder RFC4648_URL_SAFE_ = Encoder(true, nullptr, -1, true);
        static const Encoder RFC2045_ = Encoder(false, nullptr, -1, true);

    private:
        const char *new_line_;
        const int32_t line_max_;
        bool is_url_;
        bool padding_;
    }
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
