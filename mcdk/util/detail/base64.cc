#ifndef MCDK_UTIL_BASE64_DETAIL_CC
#define MCDK_UTIL_BASE64_DETAIL_CC
#pragma once


#include "mcdk/util/detail/base64.h"
#include "mcdk/preprocessor/exception.h"

namespace mc {

std::string Base64::Encoder::encode(const std::string &src) throw(std::invalid_argument) {
    int32_t len = outLength((int32_t)src.length());
    return encode0(src.data(), 0, len);
}

int32_t Base64::Encoder::outLength(int32_t src_len) {
    int32_t len = 0;
    if (padding_) {
        len = 4 * ((src_len + 2) / 3);
    } else {
        int32_t n = src_len % 3;
        len = 4 * (src_len / 3) + (n == 0 ? 0 : n + 1);
    }
    if (line_max_ > 0)                                  // line separators
        len += (len - 1) / line_max_ * new_line_.length;
    return len;
}

std::string Base64::Encoder::encode0(char *src, int32_t off, int32_t len) throw(std::invalid_argument) {
    char *base64 = is_url_ ? to_base64_url_ : to_base64_;
    int32_t sp = off;
    int32_t slen = (end - off) / 3 * 3;
    int32_t sl = off + slen;
    if (line_max_ > 0 and slen  > line_max_ / 4 * 3)
        slen = line_max_ / 4 * 3;
    int32_t dp = 0;
    while (sp < sl) {
        int32_t sl0 = std::min(sp + slen, sl);
        for (int32_t sp0 = sp, dp0 = dp ; sp0 < sl0; ) {
            int32_t bits = (src[sp0++] & 0xff) << 16 |
                    (src[sp0++] & 0xff) <<  8 |
                    (src[sp0++] & 0xff);
            dst[dp0++] = (char)base64[(bits >> 18) & 0x3f];
            dst[dp0++] = (char)base64[(bits >> 12) & 0x3f];
            dst[dp0++] = (char)base64[(bits >> 6)  & 0x3f];
            dst[dp0++] = (char)base64[bits & 0x3f];
        }
        int32_t dlen = (sl0 - sp) / 3 * 4;
        dp += dlen;
        sp = sl0;
        if (dlen == line_max_ and sp < end) {
            for (char b : new_line_){
                dst[dp++] = b;
            }
        }
    }
    if (sp < end) {               // 1 or 2 leftover char
        int32_t b0 = src[sp++] & 0xff;
        dst[dp++] = (char)base64[b0 >> 2];
        if (sp == end) {
            dst[dp++] = (char)base64[(b0 << 4) & 0x3f];
            if (doPadding) {
                dst[dp++] = '=';
                dst[dp++] = '=';
            }
        } else {
            int b1 = src[sp++] & 0xff;
            dst[dp++] = (char)base64[(b0 << 4) & 0x3f | (b1 >> 4)];
            dst[dp++] = (char)base64[(b1 << 2) & 0x3f];
            if (doPadding) {
                dst[dp++] = '=';
            }
        }
    }
    return dp;

}

std::string Base64::Decoder::decode(const std::string &src) throw(std::invalid_argument) {
    int32_t len = outLength(src.data(), 0, src.length());
    return decode0(src.data(), 0, len);
}

int32_t Base64::Decoder::outLength(const char *src, int32_t sp, int32_t sl) {
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
    if (isMIME) {
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
    if (paddings == 0 && (len & 0x3) !=  0)
        paddings = 4 - (len & 0x3);
    return 3 * ((len + 3) / 4) - paddings;
}

std::string Base64::Decoder::decode0(const char *src, int32_t sp, int32_t sl) throw(std::invalid_argument) {

}


} //namespace mcdk


#endif
