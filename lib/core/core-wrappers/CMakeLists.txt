add_library(
	Core-Wrappers STATIC
	include/Gl.h
	include/GladWrapper.h
	include/GlfwWrapper.h
	include/Image.h
	include/Shader.h
	include/ShaderProgram.h
	include/Texture.h
	include/Vao.h
	include/Vbo.h

	source/Gl.cpp
	source/GladWrapper.cpp
	source/GlfwWrapper.cpp
	source/Image.cpp
	source/Shader.cpp
	source/ShaderProgram.cpp
	source/Texture.cpp
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
	Delegate
	Misc
)