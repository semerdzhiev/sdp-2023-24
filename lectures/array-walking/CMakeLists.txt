add_executable(array-walking)

target_link_libraries(
	array-walking
	PRIVATE
	utils
)

target_sources(
	array-walking
	PRIVATE
		"src/ArrayWalking.cpp"
)
