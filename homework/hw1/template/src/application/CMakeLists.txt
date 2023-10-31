# Target for the calculator application
add_executable(calc)

target_link_libraries(
	calc
	PRIVATE
		expression-lib
)

target_sources(
	calc
	PRIVATE
		"calc.cpp"
)