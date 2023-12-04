# Target for the expression processing library
add_library(simulator-lib STATIC)

target_sources(
	simulator-lib
	PRIVATE
		"bar-simulator.cpp"
		"bar-simulator.h"
)
