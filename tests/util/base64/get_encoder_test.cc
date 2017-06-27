#include "mcdk/util/base64.h"
#include "mcdk/util/preprocessor.h"
#include <iostream>
#include <cassert>
#undef NDEBUG

void testEncodeToString(const mc::Base64::Encoder &encoder) {
    const char * bytes_in = "fo";
    std::cout << MC_PP_LOC << std::endl;
    std::string s = encoder.encode(bytes_in);
    assert(s.find("$$$") == s.length());
}



int main(int argc, char *argv[]) {

    return 0;
}
