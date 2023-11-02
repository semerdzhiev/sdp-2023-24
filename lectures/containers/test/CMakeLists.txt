# Executable target for the unit tests
add_executable(unit-tests-containers)

target_link_libraries(
	unit-tests-containers
	PRIVATE
		containers
		Catch2::Catch2WithMain
)

target_sources(
	unit-tests-containers
	PRIVATE
		"Test-DynamicArray.cpp"
		"Test-FixedSizeArray.cpp"
)

catch_discover_tests(unit-tests-containers)
