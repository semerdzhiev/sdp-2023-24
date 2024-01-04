# Executable target for the unit tests
add_executable(unit-tests-triangle)

target_link_libraries(
	unit-tests-triangle
	PRIVATE
        triangle
		Catch2::Catch2WithMain
)

target_sources(
	unit-tests-triangle
	PRIVATE
		"Test-Triangle.cpp"
)

catch_discover_tests(unit-tests-triangle)
