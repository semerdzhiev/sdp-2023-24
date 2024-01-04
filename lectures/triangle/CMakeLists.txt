add_library(triangle INTERFACE)

target_include_directories(
    triangle
    INTERFACE include
)

if(BUILD_TESTING)
	add_subdirectory(test)
endif()
