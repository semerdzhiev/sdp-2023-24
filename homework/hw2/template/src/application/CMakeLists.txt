# Target for the simulator
add_executable(simulator)

target_link_libraries(
	simulator
	PRIVATE
		simulator-lib
)

target_sources(
	simulator
	PRIVATE
		"simulation.cpp"
)
