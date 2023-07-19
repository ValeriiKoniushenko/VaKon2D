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
	Delegate
	World
	Input-Devices
	Misc
	Shapes
	freetype
)

add_custom_command(TARGET VaKon2D PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_CURRENT_BINARY_DIR}/assets
	COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/assets
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_CURRENT_SOURCE_DIR}/assets
	${CMAKE_CURRENT_BINARY_DIR}/assets)

add_custom_target(
	Copy-Assets
	COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_CURRENT_BINARY_DIR}/assets
	COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/assets
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_CURRENT_SOURCE_DIR}/assets
	${CMAKE_CURRENT_BINARY_DIR}/assets
)