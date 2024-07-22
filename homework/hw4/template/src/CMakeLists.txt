# Sample static library
add_library(dictionarylib STATIC)

target_sources(
    dictionarylib
    PRIVATE
        "Dictionary.h"
        "Dictionary.cpp"
)

add_executable(application)

target_sources(
    application
    PRIVATE
        "application.cpp"
)

target_link_libraries(
    application
    PRIVATE
        dictionarylib
)
