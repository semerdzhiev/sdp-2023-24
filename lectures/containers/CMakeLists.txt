add_library(containers INTERFACE)

target_link_libraries(
	containers
	INTERFACE utils
)

target_include_directories(
	containers
	INTERFACE include
)

if(BUILD_TESTING)
	add_subdirectory(test)
endif()
