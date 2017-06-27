
set(SOURCE
        base64.cc
        )

add_library(mcdk SHARED ${SOURCE})
add_library(mcdk_static STATIC ${SOURCE})
