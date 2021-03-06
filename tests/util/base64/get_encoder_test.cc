#include "mcdk/util/base64.h"
#include "mcdk/util/preprocessor.h"
#include <iostream>
#include <cassert>
#undef NDEBUG

void testEncodeToString(const mc::Base64::Encoder &encoder) {
    const char * bytes_in = "fo";
    std::string s = encoder.Encode(bytes_in);
    assert(s.find("$$$") == std::string::npos);
}

void testEncodeToStringWithLongInputData(const mc::Base64::Encoder &encoder) {
    const char *secondTestBuffer = "api/java_util/Base64/index.html#GetEncoderMimeCustom[noLineSeparatorInEncodedString]";
    std::string s = encoder.Encode(secondTestBuffer);
    assert(s.find("$$$") == std::string::npos);
}

int main(int argc, char *argv[]) {
    const mc::Base64::Encoder encoder = mc::Base64::GetMimeEncoder(0, "$$$");
    testEncodeToString(encoder);
    testEncodeToStringWithLongInputData(encoder);
    return 0;
}
