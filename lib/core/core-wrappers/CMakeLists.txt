add_library(
	Core-Wrappers STATIC
	include/GlfwWrapper.h
	include/GladWrapper.h

	source/GlfwWrapper.cpp
	source/GladWrapper.cpp
)

target_include_directories(
	Core-Wrappers PUBLIC
	include
)

target_link_libraries(
	Core-Wrappers PUBLIC
	Utils
	glfw
	Glad
	Logger
)