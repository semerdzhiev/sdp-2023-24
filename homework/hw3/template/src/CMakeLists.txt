# Sample static library
add_library(setlib STATIC)

target_sources(
    setlib
    PRIVATE
        "IntegerSet.cpp"
        "IntegerSet.h"
)


