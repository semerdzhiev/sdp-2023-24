# Executable target for the unit tests
add_executable(unit-tests)

target_link_libraries(
    unit-tests
    PRIVATE
        solution
        Catch2::Catch2WithMain
)

target_sources(
    unit-tests
    PRIVATE
        "test-additional.cpp"
        "test-solution.cpp"
)

# Automatically register all tests
catch_discover_tests(unit-tests)
