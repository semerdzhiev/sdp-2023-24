add_executable(hash-benchmark)

target_link_libraries(
	hash-benchmark
	PRIVATE
		containers	
		utils
)

target_sources(
	hash-benchmark
	PRIVATE
		"src/HashBenchmark.cpp"
)
