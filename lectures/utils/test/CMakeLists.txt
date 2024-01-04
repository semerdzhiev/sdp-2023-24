# Executable target for the unit tests
add_executable(unit-tests-utilities)

target_link_libraries(
	unit-tests-utilities
	PRIVATE
        utils
		Catch2::Catch2WithMain
)

target_sources(
	unit-tests-utilities
	PRIVATE
		"Test-Allocator.cpp"
		"Test-MockingObjects.cpp"
)

catch_discover_tests(unit-tests-utilities)
