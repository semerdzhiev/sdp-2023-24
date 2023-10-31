# Target for the expression processing library
add_library(expression-lib STATIC)

target_sources(
	expression-lib
	PRIVATE
		"expression.cpp"
		"expression.h"
)