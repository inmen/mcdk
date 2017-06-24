#ifndef MCDK_UTIL_BASE64_DETAIL_H
#define MCDK_UTIL_BASE64_DETAIL_H
#pragma once

#include <cstdint>
#include <string>
#include <tuple>

namespace mcdk {

class Base64 {
public:
    class Encoder {
    private:
        Encoder(bool is_url, char *new_line, int32_t line_max, bool padding)
                : new_line_(new_line),
                  line_max_(line_max),
                  is_url_(is_url),
                  padding_(padding) {
        }

    public:
        static const Encoder RFC4648_ { false, nullptr, -1, true };
        static const Encoder RFC4648_URL_SAFE_ { true, nullptr, -1, true };
        static const Encoder RFC2045_ { false, nullptr, -1, true };

        std::tuple<int, std::string> encode(const std::string &src);

    private:
        const char *new_line_;
        const int32_t line_max_;
        bool is_url_;
        bool padding_;

    private:
        // implementation

        /**
         * This array is a lookup table that translates 6-bit positive integer
         * index values into their "Base64 Alphabet" equivalents as specified
         * in "Table 1: The Base64 Alphabet" of RFC 2045 (and RFC 4648).
         */
        static const char to_base64_[] {
                'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'
        };

        /**
         * It's the lookup table for "URL and Filename safe Base64" as specified
         * in Table 2 of the RFC 4648, with the '+' and '/' changed to '-' and
         * '_'. This table is used when BASE64_URL is specified.
         */
        static const char to_base64_url_[] {
                'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-', '_'
        };

        static const int32_t MIME_LINE_MAX_ { 76 };
        static const char CRLF_[] {'\r', '\n'};

        int32_t outLength(int32_t src_len);
        std::tuple<int, std::string> encode0(char *src, int32_t off, int32_t len);
    };

    class Decoder {
    private:
        Decoder(bool is_url, bool is_mime)
                : is_url_(is_url), is_mime_(is_mime) {
        }

    public:
        static const Decoder RFC4648_ { false, nullptr, -1, true };
        static const Decoder RFC4648_URL_SAFE_ { true, nullptr, -1, true };
        static const Decoder RFC2045_ { false, nullptr, -1, true };

        std::tuple<int, std::string> decode(const std::string &src);

    private:
        bool is_url_;
        bool is_mime_;

    private:
        /**
         * from_base64_[ Encoder::to_base64_[i] ] = i;
         * from_base64_[ '=' ] = -2;
         */
        static const int from_base64_[] {
                'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/',
        };

        int32_t outLength(const char *src, int32_t sp, int32_t sl);
        std::tuple<int, std::string> decode0(const char *src, int32_t sp, int32_t sl);
    };

private:
    Base64() {}

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
