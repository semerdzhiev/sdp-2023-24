# Sample static library
add_library(solution STATIC)

target_sources(
    solution
    PRIVATE
        "solution.cpp"
        "solution.h"
)
