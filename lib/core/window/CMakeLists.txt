add_library(
	Window STATIC
	include/Window.h
	source/Window.cpp
)

target_include_directories(
	Window PUBLIC
	include
)

target_link_libraries(
	Window PUBLIC
	Utils
	glfw
	Glad
	Logger
	Core-Wrappers
)