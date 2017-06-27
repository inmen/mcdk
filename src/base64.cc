#include "mcdk/util/base64.h"
#include <cstdint>
#include <string>
#include <tuple>
#include <stdexcept>
#include <boost/noncopyable.hpp>
#include <algorithm>
#include "mcdk/util/throw.h"

namespace mc {

Base64::Encoder::Encoder(bool is_url, char *new_line, int32_t new_line_len, int32_t line_max, bool padding)
        : is_url_(is_url),
          new_line_(new_line),
          new_line_len_(new_line_len),
          line_max_(line_max),
          padding_(padding) {
}

const Base64::Encoder & Base64::Encoder::RFC4648() {
    static Base64::Encoder rfc4648( false, nullptr, 0, -1, true );
    return rfc4648;
}
const Base64::Encoder & Base64::Encoder::RFC4648_URL_SAFE() {
    static Base64::Encoder rfc4648_url_safe( true, nullptr, 0, -1, true );
    return rfc4648_url_safe;
}
const Base64::Encoder & Base64::Encoder::RFC2045() {
    static Base64::Encoder rfc2045(false, (char*)CRLF_, (int32_t)(sizeof(CRLF_) / sizeof(CRLF_[0])), MIME_LINE_MAX_, true );
    return rfc2045;
}

std::string Base64::Encoder::encode(const std::string &src) const throw(std::invalid_argument) {
    int32_t len = outLength((int32_t)src.length());
    std::string dst;
    dst.resize(len);
    int32_t ret = encode0(src.data(), 0, src.length(), (char*)dst.data());
    if (ret != dst.length())
        return dst.substr(0, ret);
    return dst;
}

int32_t Base64::Encoder::outLength(int32_t src_len) const {
    int32_t len = 0;
    if (padding_) {
        len = 4 * ((src_len + 2) / 3);
    } else {
        int32_t n = src_len % 3;
        len = 4 * (src_len / 3) + (n == 0 ? 0 : n + 1);
    }
    if (line_max_ > 0)                                  // line separators
        len += (len - 1) / line_max_ * (new_line_len_);
    return len;
}
int32_t Base64::Encoder::encode0(const char *src, int32_t off, int32_t end, char *dst) const throw(std::invalid_argument) {
    char *base64 = is_url_ ? (char*)to_base64_url_ : (char*)to_base64_;
    int32_t sp = off;
    int32_t slen = (end - off) / 3 * 3;
    int32_t sl = off + slen;
    if (line_max_ > 0 and slen > line_max_ / 4 * 3)
        slen = line_max_ / 4 * 3;
    int32_t dp = 0;
    while (sp < sl) {
        int32_t sl0 = std::min(sp + slen, sl);
        for (int32_t sp0 = sp, dp0 = dp; sp0 < sl0;) {
            int32_t bits = (src[sp0++] & 0xff) << 16 |
                           (src[sp0++] & 0xff) << 8 |
                           (src[sp0++] & 0xff);
            dst[dp0++] = (char) base64[(bits >> 18) & 0x3f];
            dst[dp0++] = (char) base64[(bits >> 12) & 0x3f];
            dst[dp0++] = (char) base64[(bits >> 6) & 0x3f];
            dst[dp0++] = (char) base64[bits & 0x3f];
        }
        int32_t dlen = (sl0 - sp) / 3 * 4;
        dp += dlen;
        sp = sl0;
        if (dlen == line_max_ and sp < end) {
            for (int32_t i = 0; i < new_line_len_; i++) {
                dst[dp++] = new_line_[i];
            }
        }
    }
    if (sp < end) {               // 1 or 2 leftover char
        int32_t b0 = src[sp++] & 0xff;
        dst[dp++] = (char) base64[b0 >> 2];
        if (sp == end) {
            dst[dp++] = (char) base64[(b0 << 4) & 0x3f];
            if (padding_) {
                dst[dp++] = '=';
                dst[dp++] = '=';
            }
        } else {
            int b1 = src[sp++] & 0xff;
            dst[dp++] = (char) base64[(b0 << 4) & 0x3f | (b1 >> 4)];
            dst[dp++] = (char) base64[(b1 << 2) & 0x3f];
            if (padding_) {
                dst[dp++] = '=';
            }
        }
    }
    return dp;
}

Base64::Decoder::Decoder(bool is_url, bool is_mime)
        : is_url_(is_url),
          is_mime_(is_mime) {
}

const Base64::Decoder & Base64::Decoder::RFC4648() {
    static Base64::Decoder rfc4648(false, false);
    return rfc4648;
}
const Base64::Decoder & Base64::Decoder::RFC4648_URL_SAFE() {
    static Base64::Decoder rfc4648_url_safe(true, false);
    return rfc4648_url_safe;
}
const Base64::Decoder & Base64::Decoder::RFC2045() {
    static Decoder rfc2045(false, true);
    return rfc2045;
}

std::string Base64::Decoder::decode(const std::string &src) const throw(std::invalid_argument) {
    int32_t len = outLength(src.data(), 0, src.length());
    std::string dst;
    dst.resize(len);
    int32_t ret = decode0(src.data(), 0, src.length(), (char*)dst.data());
    if (ret != dst.length())
        return dst.substr(0, ret);
    return dst;
}

int32_t Base64::Decoder::outLength(const char *src, int32_t sp, int32_t sl) const throw(std::invalid_argument) {
    int *base64 = is_url_ ? from_base64_url_ : from_base64_;
    int32_t paddings = 0;
    int32_t len = sl - sp;
    if (len == 0)
        return 0;
    if (len < 2) {
        if (is_mime_ and base64[0] == -1)
            return 0;
        MC_THROW(std::invalid_argument, "Input src should at least have 2 bytes for base64 bytes");
    }
    if (is_mime_) {
        // scan all bytes to fill out all non-alphabet. a performance
        // trade-off of pre-scan or Arrays.copyOf
        int n = 0;
        while (sp < sl) {
            int b = src[sp++] & 0xff;
            if (b == '=') {
                len -= (sl - sp + 1);
                break;
            }
            if ((b = base64[b]) == -1)
                n++;
        }
        len -= n;
    } else {
        if (src[sl - 1] == '=') {
            paddings++;
            if (src[sl - 2] == '=')
                paddings++;
        }
    }
    if (paddings == 0 and (len & 0x3) != 0)
        paddings = 4 - (len & 0x3);
    return 3 * ((len + 3) / 4) - paddings;
}

int32_t Base64::Decoder::decode0(const char *src, int32_t sp, int32_t sl, char *dst) const throw(std::invalid_argument) {
    int *base64 = is_url_ ? from_base64_url_ : from_base64_;
    int32_t dp = 0;
    int32_t bits = 0;
    int32_t shiftto = 18;       // pos of first char of 4-char atom
    while (sp < sl) {
        int32_t b = src[sp++] & 0xff;
        if ((b = base64[b]) < 0) {
            if (b == -2) {         // padding char '='
                // =     shiftto==18 unnecessary padding
                // x=    shiftto==12 a dangling single x
                // x     to be handled together with non-padding case
                // xx=   shiftto==6&&sp==sl missing last =
                // xx=y  shiftto==6 last is not =
                if (shiftto == 6 and (sp == sl or src[sp++] != '=') or shiftto == 18) {
                    MC_THROW( std::invalid_argument, "Input char array has wrong 4-char ending unit" );
                }
                break;
            }
            if (is_mime_)    // skip if for rfc2045
                continue;
            else
                MC_THROW( std::invalid_argument, "Illegal base64 character " + toString(src[sp - 1]));
        }
        bits |= (b << shiftto);
        shiftto -= 6;
        if (shiftto < 0) {
            dst[dp++] = (char)(bits >> 16);
            dst[dp++] = (char)(bits >>  8);
            dst[dp++] = (char)(bits);
            shiftto = 18;
            bits = 0;
        }
    }
    // reached end of char array or hit padding '=' characters.
    if (shiftto == 6) {
        dst[dp++] = (char)(bits >> 16);
    } else if (shiftto == 0) {
        dst[dp++] = (char)(bits >> 16);
        dst[dp++] = (char)(bits >>  8);
    } else if (shiftto == 12) {
        // dangling single "x", incorrectly encoded.
        MC_THROW( std::invalid_argument, "Last unit does not have enough valid bits");
    }
    // anything left is invalid, if is not MIME.
    // if MIME, ignore all non-base64 character
    while (sp < sl) {
        if (is_mime_ and base64[src[sp++]] < 0)
            continue;
        MC_THROW(std::invalid_argument, "Input char array has incorrect ending char at " + toString(sp));
    }
    return dp;
}

const Base64::Encoder& Base64::getEncoder() {
    return Encoder::RFC4648();
}
const Base64::Encoder& Base64::getUrlEncoder() {
    return Encoder::RFC4648_URL_SAFE();
}
const Base64::Encoder& Base64::getMimeEncoder() {
    return Encoder::RFC2045();
}
const Base64::Decoder& Base64::getDecoder() {
    return Decoder::RFC4648();
}
const Base64::Decoder& Base64::getUrlDecoder() {
    return Decoder::RFC4648_URL_SAFE();
}
const Base64::Decoder& Base64::getMimeDecoder() {
    return Decoder::RFC2045();
}

}
