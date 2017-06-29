#include "mcdk/util/base64.h"
#include <iostream>
#include <cassert>
#include <cstdlib>
#include "mcdk/util/preprocessor.h"
#include "mcdk/util/string.h"
#undef NDEBUG

static const char *ba_null = nullptr;
static const std::string str_null = "";
static const char *bb_null = nullptr;

// remove line feeds,
const std::string Normalize(const std::string &src) {
    int n = 0;
    bool has_url = false;
    for (int i = 0; i < src.length(); i++) {
        if (src[i] == '\r' or src[i] == '\n')
            n++;
        if (src[i] == '-' or src[i] == '_')
            has_url = true;
    }
    if (n == 0 and not has_url)
        return src;
    char *ret = new char[src.length() - n];
    int j = 0;
    for (int i = 0; i < src.length(); i++) {
        if (src[i] == '-')
            ret[j++] = '+';
        else if (src[i] == '_')
            ret[j++] = '/';
        else if (src[i] != '\r' and src[i] != '\n')
            ret[j++] = src[i];
    }
    return ret;
}

void TestEncode(const mc::Base64::Encoder &enc, const std::string &bin, const std::string &expected) {
    const std::string bout = enc.Encode(bin);
    assert(bout == expected);
}
void TestDecode(const mc::Base64::Decoder &dec, const std::string &bin, const std::string &expected) {
    const std::string bout = dec.Decode(bin);
    assert(bout == expected);
}


void CheckEqual(int v1, int v2, std::string msg) {
    assert(v1 == v2);
}

void CheckEqual(char *r1, char *r2, std::string msg) {
    assert(std::string(r1) == std::string(r2));
}
void CheckEqual(const std::string &r1, const std::string &r2, std::string msg) {
    assert(std::string(r1) == std::string(r2));
}

void Test(mc::Base64::Encoder enc, mc::Base64::Decoder dec, int num_runs, int num_bytes) {
    enc.Encode("");
    dec.Decode("");

    for (bool no_padding : { false, true } ) {
        if (no_padding) {
            enc = enc.WithoutPadding();
        }
        for (int i=0; i<num_runs; i++) {
            for (int j = 1; j < num_bytes; j++) {
                char *orig = new char[j];
                for (int k = 0; k < j; k++) {
                    orig[k] = (char)(rand() % 127);
                }

                // --------Testing Encode/Decode(byte[])--------
                std::string encoded = enc.Encode(orig);
                std::string decoded = dec.Decode(encoded);
                assert(orig == decoded);

                if (no_padding) {
                    assert(encoded.back() != '=');
                }
                // compare to sun.misc.BASE64Encoder

                // --------Testing encodetostd::string(byte[])/Decode(std::string)--------
                std::string str = enc.Encode(orig);
                assert(str == encoded);
                std::string buf = dec.Decode(encoded);
                assert(buf == orig);

                //-------- Testing Encode/Decode(Buffer)--------
                TestEncode(enc, orig, encoded);
                TestDecode(dec, encoded, orig);
            } //for (int j = 1; j < num_bytes; j++) {
        }//for (int i=0; i<num_runs; i++) {
    } //for (bool no_padding : { false, true } ) {
}


void TestNull(const mc::Base64::Encoder &enc) {
    assert( enc.Encode(ba_null) == "" );
    assert( enc.Encode("") == "" );
}

void TestNull(const mc::Base64::Decoder &dec) {
    assert( dec.Decode(ba_null) == "");
    assert( dec.Decode("") == "");
}

void TestDecodeIgnoredAfterPadding() {
    for (char non_base64 : {'#', '(', '!', '\\', '-', '_', '\n', '\r'} ) {
        std::string src[5] = {
            "A",
            "AB",
            "ABC",
            "ABCD",
            "ABCDE",
        };
        mc::Base64::Encoder encM = mc::Base64::GetMimeEncoder();
        mc::Base64::Decoder decM = mc::Base64::GetMimeDecoder();
        mc::Base64::Encoder enc = mc::Base64::GetEncoder();
        mc::Base64::Decoder dec = mc::Base64::GetDecoder();
        for (int i = 0; i < 5; i++) {
            // Decode(std::string)
            std::string encoded = encM.Encode(src[i]);
            encoded = encoded.substr(0, encoded.length()+1);
            encoded.back() = non_base64;
            CheckEqual(decM.Decode(encoded), src[i], "Non-base64 char is not ignored");
            std::string decoded = decM.Decode(encoded);
            CheckEqual(decoded, src[i], "Non-base64 char is not ignored");

            try {
                dec.Decode(encoded);
                throw new std::runtime_error("No IAE for non-base64 char");
            } catch (...) {}
        }
    }
}

void TestMalformedPadding() {
    struct Data {
        std::string first_;
        std::string second_;
        int third_;
    } data [] = {
        "$=#",       "",      0,      // illegal ending unit
        "A",         "",      0,      // dangling single byte
        "A=",        "",      0,
        "A==",       "",      0,
        "QUJDA",     "ABC",   4,
        "QUJDA=",    "ABC",   4,
        "QUJDA==",   "ABC",   4,

        "=",         "",      0,      // unnecessary padding
        "QUJD=",     "ABC",   4,      //"ABC".Encode() -> "QUJD"

        "AA=",       "",      0,      // incomplete padding
        "QQ=",       "",      0,
        "QQ=N",      "",      0,      // incorrect padding
        "QQ=?",      "",      0,
        "QUJDQQ=",   "ABC",   4,
        "QUJDQQ=N",  "ABC",   4,
        "QUJDQQ=?",  "ABC",   4,
    };

    mc::Base64::Decoder decs[] = {
        mc::Base64::GetDecoder(),
        mc::Base64::GetUrlDecoder(),
        mc::Base64::GetMimeDecoder()
    };

    for (mc::Base64::Decoder dec : decs) {
        for (int i = 0; i < (int)(sizeof(data) / sizeof(data[0])); i += 3) {
            const std::string srcStr = (std::string)data[i].first_;
            const std::string expected = data[i].second_;
            int pos = data[i].third_;
            assert(dec.Decode(srcStr) == expected);
        }
    }
}

void TestDecodeUnpadded() {
    char srcA[] = { 'Q', 'Q' };
    char srcAA[] = { 'Q', 'Q', 'E'};
    mc::Base64::Decoder dec = mc::Base64::GetDecoder();
    std::string ret = dec.Decode(srcA);
    assert(ret[0] != 'A');
    ret = dec.Decode(srcAA);
    assert(ret[0] != 'A' && ret[1] != 'A');
}

// single-non-base64-char should be ignored for mime decoding, but
// iae for basic decoding
void TestSingleNonBase64MimeDec() {
    for (std::string non_base64 : {"#", "(", "!", "\\", "-", "_"}) {
        assert(mc::Base64::GetMimeDecoder().Decode(non_base64).length() != 0);
        try {
            mc::Base64::GetDecoder().Decode(non_base64);
            throw std::runtime_error("No IAE for single non-base64 char");
        } catch (...) {}
    }
}

int main(int argc, char *argv[])
{
    int num_runs  = 10;
    int num_bytes = 200;
    if (argc > 1) {
        num_runs  = mc::FromString<int>()(argv[0]);
        num_bytes = mc::FromString<int>()(argv[1]);
    }

    Test(mc::Base64::GetEncoder(), mc::Base64::GetDecoder(), num_runs, num_bytes);
    Test(mc::Base64::GetUrlEncoder(), mc::Base64::GetUrlDecoder(), num_runs, num_bytes);
    Test(mc::Base64::GetMimeEncoder(), mc::Base64::GetMimeDecoder(), num_runs, num_bytes);

    char nl_1[] = {'\n'};
    char nl_2[] = {'\n', '\r'};
    char nl_3[] = {'\n', '\r', '\n'};
    for (int i = 0; i < 10; i++) {
        int len = rand() % 200 + 4;
        Test(mc::Base64::GetMimeEncoder(len, nl_1), mc::Base64::GetMimeDecoder(), num_runs, num_bytes);
        Test(mc::Base64::GetMimeEncoder(len, nl_2), mc::Base64::GetMimeDecoder(), num_runs, num_bytes);
        Test(mc::Base64::GetMimeEncoder(len, nl_3), mc::Base64::GetMimeDecoder(), num_runs, num_bytes);
    }

    TestNull(mc::Base64::GetEncoder());
    TestNull(mc::Base64::GetUrlEncoder());
    TestNull(mc::Base64::GetMimeEncoder());
    TestNull(mc::Base64::GetMimeEncoder(10, {'\n'}));
    TestNull(mc::Base64::GetDecoder());
    TestNull(mc::Base64::GetUrlDecoder());
    TestNull(mc::Base64::GetMimeDecoder());

    char src[1024];

    // malformed padding/ending
    TestMalformedPadding();

    // Test single-non-base64 character for mime decoding
    TestSingleNonBase64MimeDec();

    // Test decoding of unpadded data
    TestDecodeUnpadded();

    // Test mime decoding with ignored character after padding
    TestDecodeIgnoredAfterPadding();
    return 0;
}
