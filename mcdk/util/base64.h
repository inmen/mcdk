#ifndef MCDK_UTIL_BASE64_H
#define MCDK_UTIL_BASE64_H
#pragma once

#include <cstdint>
#include <string>
#include <tuple>
#include <stdexcept>
#include <boost/noncopyable.hpp>
#include <algorithm>
#include "mcdk/util/throw.h"

namespace mc {

class Base64 : boost::noncopyable {
public:
    class Decoder;
    class Encoder : boost::noncopyable {
    private:
        friend class Decoder;
        friend class Base64;
        Encoder(bool is_url, char *new_line, int32_t new_line_len, int32_t line_max, bool padding);
        static const Encoder & RFC4648();
        static const Encoder & RFC4648_URL_SAFE();
        static const Encoder & RFC2045();

    public:
        std::string encode(const std::string &src) const throw(std::invalid_argument);

    private:
        bool is_url_;
        const char *new_line_;
        int32_t new_line_len_;
        const int32_t line_max_;
        bool padding_;

    private:
        /**
         * This array is a lookup table that translates 6-bit positive integer
         * index values into their "Base64 Alphabet" equivalents as specified
         * in "Table 1: The Base64 Alphabet" of RFC 2045 (and RFC 4648).
         */
        static const char to_base64_[64];
        /**
         * It's the lookup table for "URL and Filename safe Base64" as specified
         * in Table 2 of the RFC 4648, with the '+' and '/' changed to '-' and
         * '_'. This table is used when BASE64_URL is specified.
         */
        static const char to_base64_url_[64];

        static const int32_t MIME_LINE_MAX_;
        static const char CRLF_[2];

        int32_t outLength(int32_t src_len) const;
        int32_t encode0(const char *src, int32_t off, int32_t end, char *dst) const throw(std::invalid_argument);
    }; // class Encoder

    class Decoder : boost::noncopyable {
    private:
        friend class Encoder;
        friend class Base64;
        Decoder(bool is_url, bool is_mime);

        static const Decoder & RFC4648();
        static const Decoder & RFC4648_URL_SAFE();
        static const Decoder & RFC2045();

    public:
        std::string decode(const std::string &src) const throw(std::invalid_argument);

    private:
        bool is_url_;
        bool is_mime_;

    private:
        static int from_base64_[256];
        static int from_base64_url_[256];

        struct Constructor {
            Constructor() {
                for (auto &i : from_base64_) {
                    i = -1;
                }
                for (int i = 0; i < sizeof(Encoder::to_base64_) / sizeof(Encoder::to_base64_[0]); i++) {
                    from_base64_[ Encoder::to_base64_[i] ] = i;
                }
                from_base64_['='] = -2;
                for (auto &i : from_base64_url_) {
                    i = -1;
                }
                for (int i = 0; i < sizeof(Encoder::to_base64_url_) / sizeof(Encoder::to_base64_url_[0]); i++) {
                    from_base64_url_[ Encoder::to_base64_url_[i] ] = i;
                }
                from_base64_url_['='] = -2;
            }
        };
        // static call Constructor::Constructor()
        static Constructor constructor_;

        int32_t outLength(const char *src, int32_t sp, int32_t sl) const throw(std::invalid_argument);
        int32_t decode0(const char *src, int32_t sp, int32_t sl, char *dst) const throw(std::invalid_argument);
    }; // class Decoder

public:
    static const Encoder& getEncoder();
    static const Encoder& getUrlEncoder();
    static const Encoder& getMimeEncoder();
    static const Decoder& getDecoder();
    static const Decoder& getUrlDecoder();
    static const Decoder& getMimeDecoder();
};

}

#endif
