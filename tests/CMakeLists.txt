
add_executable(
	Tests
	main.cpp
	TestUtils.cpp
)

target_link_libraries(Tests PUBLIC GoogleTests)