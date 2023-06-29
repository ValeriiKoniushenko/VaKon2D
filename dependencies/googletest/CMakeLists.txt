add_library(
	GoogleTests STATIC
	src/gtest.cc
	src/gtest_main.cc
	src/gtest-all.cc
	src/gtest-death-test.cc
	src/gtest-filepath.cc
	src/gtest-matchers.cc
	src/gtest-port.cc
	src/gtest-printers.cc
	src/gtest-test-part.cc
	src/gtest-typed-test.cc
)

target_include_directories(
	GoogleTests PUBLIC
	./
	include/
)

set(RELEASE "Release")
set(DEBUG "Debug")

if (EXISTS "${CMAKE_CURRENT_BINARY_DIR}/${DEBUG}")
	add_custom_command(
		TARGET GoogleTests POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${CMAKE_CURRENT_BINARY_DIR}/${DEBUG}"
		"${CMAKE_CURRENT_SOURCE_DIR}/lib/${DEBUG}/"
	)
endif ()

if (EXISTS "${CMAKE_CURRENT_BINARY_DIR}/${RELEASE}")
	add_custom_command(
		TARGET GoogleTests POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${CMAKE_CURRENT_BINARY_DIR}/${RELEASE}"
		"${CMAKE_CURRENT_SOURCE_DIR}/lib/${RELEASE}/"
	)
endif ()