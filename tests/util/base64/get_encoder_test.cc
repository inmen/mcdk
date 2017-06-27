#include "mcdk/util/base64.h"
#include "mcdk/util/compile_location.h"
#include <iostream>
#include <cassert>

void testEncodeToString(const mc::Base64::Encoder &encoder) {
    const char * bytes_in = "fo";
    std::cout << MC_COMPILE_LOC << std::endl;
    std::string s = encoder.encode(bytes_in);
    assert(s.find("$$$") == s.length());
}



int main(int argc, char *argv[]) {

    return 0;
}
