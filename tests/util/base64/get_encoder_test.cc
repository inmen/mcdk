#include "mcdk/util/base64.h"
#include "mcdk/util/preprocessor.h"
#include <iostream>
#include <cassert>
#undef NDEBUG

void testEncodeToString(const mc::Base64::Encoder &encoder) {
    const char * bytes_in = "fo";
    std::cout << MC_PP_LOC << std::endl;
    std::string s = encoder.encode(bytes_in);
    assert(s.find("$$$") == std::string::npos);
}


void testEncodeToStringWithLongInputData(const mc::Base64::Encoder &encoder) {
    const char *secondTestBuffer = "api/java_util/Base64/index.html#GetEncoderMimeCustom[noLineSeparatorInEncodedString]";
    std::string s = encoder.encode(secondTestBuffer);
    std::cout << MC_PP_LOC << std::endl;
    assert(s.find("$$$") == std::string::npos);
}


int main(int argc, char *argv[]) {
    testEncodeToString(mc::Base64::getEncoder());
    testEncodeToStringWithLongInputData(mc::Base64::getEncoder());
    return 0;
}
