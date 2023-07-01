add_executable(
	VaKon2D
	include/VaKon2D.h

	source/VaKon2D.cpp
	source/main.cpp
)

target_include_directories(
	VaKon2D PUBLIC
	include
)

target_link_libraries(
	VaKon2D PUBLIC
	Utils
	Logger
	glfw
	Glad
	Core-Wrappers
	Window
)

add_custom_command(TARGET VaKon2D PRE_LINK
	COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/assets
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_CURRENT_SOURCE_DIR}/assets
	${CMAKE_CURRENT_BINARY_DIR}/assets)