#include "mcdk/util/base64.h"
#include "mcdk/util/preprocessor.h"
#include "mcdk/util/string.h"
#include <iostream>
#include <cassert>
#include <cstdlib>
#undef NDEBUG

static sun.misc.BASE64Encoder sunmisc = new sun.misc.BASE64Encoder();

static const char *ba_null = nullptr;
static const std::string str_null = "";
static const char *bb_null = null;

// remove line feeds,
const std::string normalize(const std::string &src) {
    int n = 0;
    bool has_url = false;
    for (int i = 0; i < src.length; i++) {
        if (src[i] == '\r' or src[i] == '\n')
            n++;
        if (src[i] == '-' or src[i] == '_')
            has_url = true;
    }
    if (n == 0 and not has_url)
        return src;
    char *ret = new char[src.length() - n];
    int j = 0;
    for (int i = 0; i < src.length; i++) {
        if (src[i] == '-')
            ret[j++] = '+';
        else if (src[i] == '_')
            ret[j++] = '/';
        else if (src[i] != '\r' and src[i] != '\n')
            ret[j++] = src[i];
    }
    return ret;
}

void testEncode(const Base64::Encoder &enc, const std::string &bin, const std::string &expected) {
    const std::string bout = enc.encode(bin);
    assert(bout == expected);
}
void testDecode(const Base64::Decoder &dec, const std::string &bin, const std::string &expected) {
    const std::string bout = dec.decode(bin);
    assert(bout == expected);
}


void test(Base64::Encoder & enc, Base64::Decoder &dec, int num_runs, int num_bytes) {
    enc.encode(new byte[0]);
    dec.decode(new byte[0]);

    for (bool no_padding : { false, true } ) {
        if (no_padding) {
            enc = enc.no_padding();
        }
        for (int i=0; i<num_runs; i++) {
            for (int j=1; j<num_bytes; j++) {
                char *orig = new char[j];
                rnd.nextBytes(orig);

                // --------testing encode/decode(byte[])--------
                std::string encoded = enc.encode(orig);
                std::string decoded = dec.decode(encoded);
                assert(orig == decoded);

                if (no_padding) {
                    assert(encoded.back() != '=');
                }
                // compare to sun.misc.BASE64Encoder

                std::string encoded2 = sunmisc.encode(orig).getBytes("ASCII");
                if (!no_padding) {    // don't test for no_padding()
                    assert(normalize(encoded), normalize(encoded2));
                }
                // remove padding '=' to test non-padding decoding case
                if (encoded[encoded.length() -2] == '=')
                    encoded2 = encoded.substr(0, encoded.length()-2);
                else if (encoded.back() == '=')
                    encoded2 = encoded.substr(0, encoded.length()-1);
                else
                    encoded2 = "";

                // --------testing encodetostd::string(byte[])/decode(std::string)--------
                std::string str = enc.encode(orig);
                assert(str == encoded);
                std::string buf = dec.decode(encoded);
                assert(buf == orig);

                if (encoded2 != "") {
                    buf = dec.decode(encoded2);
                    assert(buf == orig);
                }

                //-------- testing encode/decode(Buffer)--------
                testEncode(enc, orig, encoded);
                testDecode(dec, encoded, orig);

                if (encoded2 != "")
                    testDecode(dec, encoded2, orig);
        }
    }
}


void testNull(const Base64::Encoder &enc) {
    assert( enc.encode(ba_null) == "" );
    assert( enc.encode("") == "" );
}

void testNull(const Base64::Decoder &dec) {
    assert( dec.decode(ba_null) == "");
    assert( dec.decode("") == "");
}

void testDecodeIgnoredAfterPadding() {
    for (char non_base64 : {'#', '(', '!', '\\', '-', '_', '\n', '\r'} ) {
        std::string src[] = {
            "A",
            "AB",
            "ABC",
            "ABCD",
            "ABCDE",
        };
        Base64::Encoder encM = Base64::getMimeEncoder();
        Base64::Decoder decM = Base64::getMimeDecoder();
        Base64::Encoder enc = Base64::getEncoder();
        Base64::Decoder dec = Base64::getDecoder();
        for (int i = 0; i < src.length; i++) {
            // decode(byte[])
            std::string encoded = encM.encode(src[i]);
            encoded = encoded.substr(0, encoded.length()+1);
            encoded.back() = non_base64;
            checkEqual(decM.decode(encoded), src[i], "Non-base64 char is not ignored");
            byte[] decoded = new byte[src[i].length];
            decM.decode(encoded, decoded);
            checkEqual(decoded, src[i], "Non-base64 char is not ignored");

            try {
                dec.decode(encoded);
                throw new RuntimeException("No IAE for non-base64 char");
            } catch (IllegalArgumentException iae) {}
        }
    }
}

private static void testMalformedPadding() throws Throwable {
    Object[] data = new Object[] {
        "$=#",       "",      0,      // illegal ending unit
        "A",         "",      0,      // dangling single byte
        "A=",        "",      0,
        "A==",       "",      0,
        "QUJDA",     "ABC",   4,
        "QUJDA=",    "ABC",   4,
        "QUJDA==",   "ABC",   4,

        "=",         "",      0,      // unnecessary padding
        "QUJD=",     "ABC",   4,      //"ABC".encode() -> "QUJD"

        "AA=",       "",      0,      // incomplete padding
        "QQ=",       "",      0,
        "QQ=N",      "",      0,      // incorrect padding
        "QQ=?",      "",      0,
        "QUJDQQ=",   "ABC",   4,
        "QUJDQQ=N",  "ABC",   4,
        "QUJDQQ=?",  "ABC",   4,
    };

    Base64.Decoder[] decs = new Base64.Decoder[] {
        Base64.getDecoder(),
        Base64.getUrlDecoder(),
        Base64.getMimeDecoder()
    };

    for (Base64.Decoder dec : decs) {
        for (int i = 0; i < data.length; i += 3) {
            final std::string srcStr = (std::string)data[i];
            final byte[] srcBytes = srcStr.getBytes("ASCII");
            final ByteBuffer srcBB = ByteBuffer.wrap(srcBytes);
            byte[] expected = ((std::string)data[i + 1]).getBytes("ASCII");
            int pos = (Integer)data[i + 2];

            // decode(byte[])
            checkIAE(new Runnable() { public void run() { dec.decode(srcBytes); }});

            // decode(std::string)
            checkIAE(new Runnable() { public void run() { dec.decode(srcStr); }});

            // decode(ByteBuffer)
            checkIAE(new Runnable() { public void run() { dec.decode(srcBB); }});

            // wrap stream
            checkIOE(new Testable() {
                public void test() throws IOException {
                    try (InputStream is = dec.wrap(new ByteArrayInputStream(srcBytes))) {
                        while (is.read() != -1);
                    }
            }});
        }
    }
}

private static void  testDecodeUnpadded() throws Throwable {
    byte[] srcA = new byte[] { 'Q', 'Q' };
    byte[] srcAA = new byte[] { 'Q', 'Q', 'E'};
    Base64.Decoder dec = Base64.getDecoder();
    byte[] ret = dec.decode(srcA);
    if (ret[0] != 'A')
        throw new RuntimeException("Decoding unpadding input A failed");
    ret = dec.decode(srcAA);
    if (ret[0] != 'A' && ret[1] != 'A')
        throw new RuntimeException("Decoding unpadding input AA failed");
    ret = new byte[10];
    if (dec.wrap(new ByteArrayInputStream(srcA)).read(ret) != 1 &&
        ret[0] != 'A')
        throw new RuntimeException("Decoding unpadding input A from stream failed");
    if (dec.wrap(new ByteArrayInputStream(srcA)).read(ret) != 2 &&
        ret[0] != 'A' && ret[1] != 'A')
        throw new RuntimeException("Decoding unpadding input AA from stream failed");
}

// single-non-base64-char should be ignored for mime decoding, but
// iae for basic decoding
private static void testSingleNonBase64MimeDec() throws Throwable {
    for (std::string non_base64 : new std::string[] {"#", "(", "!", "\\", "-", "_"}) {
        if (Base64.getMimeDecoder().decode(non_base64).length != 0) {
            throw new RuntimeException("non-base64 char is not ignored");
        }
        try {
            Base64.getDecoder().decode(non_base64);
            throw new RuntimeException("No IAE for single non-base64 char");
        } catch (IllegalArgumentException iae) {}
    }
}

private static final void checkEqual(int v1, int v2, std::string msg)
    throws Throwable {
   if (v1 != v2) {
       System.out.printf("    v1=%d%n", v1);
       System.out.printf("    v2=%d%n", v2);
       throw new RuntimeException(msg);
   }
}

private static final void checkEqual(byte[] r1, byte[] r2, std::string msg)
    throws Throwable {
   if (!Arrays.equals(r1, r2)) {
       System.out.printf("    r1[%d]=[%s]%n", r1.length, new std::string(r1));
       System.out.printf("    r2[%d]=[%s]%n", r2.length, new std::string(r2));
       throw new RuntimeException(msg);
   }
}

int main(int argc, char *argv[])
{
    int num_runs  = 10;
    int num_bytes = 200;
    if (args.length > 1) {
        num_runs  = Integer.parseInt(args[0]);
        num_bytes = Integer.parseInt(args[1]);
    }

    test(Base64::getEncoder(), Base64::getDecoder(), num_runs, num_bytes);
    test(Base64::getUrlEncoder(), Base64::getUrlDecoder(), num_runs, num_bytes);
    test(Base64::getMimeEncoder(), Base64::getMimeDecoder(), num_runs, num_bytes);

    byte[] nl_1 = new byte[] {'\n'};
    byte[] nl_2 = new byte[] {'\n', '\r'};
    byte[] nl_3 = new byte[] {'\n', '\r', '\n'};
    for (int i = 0; i < 10; i++) {
        int len = rnd.nextInt(200) + 4;
        test(Base64.getMimeEncoder(len, nl_1),
             Base64.getMimeDecoder(),
             num_runs, num_bytes);
        test(Base64.getMimeEncoder(len, nl_2),
             Base64.getMimeDecoder(),
             num_runs, num_bytes);
        test(Base64.getMimeEncoder(len, nl_3),
             Base64.getMimeDecoder(),
             num_runs, num_bytes);
    }

    testNull(Base64.getEncoder());
    testNull(Base64.getUrlEncoder());
    testNull(Base64.getMimeEncoder());
    testNull(Base64.getMimeEncoder(10, new byte[]{'\n'}));
    testNull(Base64.getDecoder());
    testNull(Base64.getUrlDecoder());
    testNull(Base64.getMimeDecoder());
    checkNull(new Runnable() { public void run() { Base64.getMimeEncoder(10, null); }});

    testIOE(Base64.getEncoder());
    testIOE(Base64.getUrlEncoder());
    testIOE(Base64.getMimeEncoder());
    testIOE(Base64.getMimeEncoder(10, new byte[]{'\n'}));

    byte[] src = new byte[1024];
    new Random().nextBytes(src);
    final byte[] decoded = Base64.getEncoder().encode(src);
    testIOE(Base64.getDecoder(), decoded);
    testIOE(Base64.getMimeDecoder(), decoded);
    testIOE(Base64.getUrlDecoder(), Base64.getUrlEncoder().encode(src));

    // illegal line separator
    checkIAE(new Runnable() { public void run() { Base64.getMimeEncoder(10, new byte[]{'\r', 'N'}); }});

    // malformed padding/ending
    testMalformedPadding();

    // illegal base64 character
    decoded[2] = (byte)0xe0;
    checkIAE(new Runnable() {
        public void run() { Base64.getDecoder().decode(decoded); }});
    checkIAE(new Runnable() {
        public void run() { Base64.getDecoder().decode(decoded, new byte[1024]); }});
    checkIAE(new Runnable() { public void run() {
            Base64.getDecoder().decode(ByteBuffer.wrap(decoded)); }});

    // test single-non-base64 character for mime decoding
    testSingleNonBase64MimeDec();

    // test decoding of unpadded data
    testDecodeUnpadded();

    // test mime decoding with ignored character after padding
    testDecodeIgnoredAfterPadding();
    return 0;
}
