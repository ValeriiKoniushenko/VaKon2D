add_library(
	Core-Wrappers STATIC
	include/Gl.h
	include/GlfwWrapper.h
	include/GladWrapper.h
	include/Vao.h
	include/Vbo.h

	source/Gl.cpp
	source/GlfwWrapper.cpp
	source/GladWrapper.cpp
	source/Vao.cpp
	source/Vbo.cpp
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