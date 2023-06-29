
add_executable(
	Benchmark
	TestUtils.cpp
)

target_link_libraries(Benchmark PUBLIC benchmark::benchmark)