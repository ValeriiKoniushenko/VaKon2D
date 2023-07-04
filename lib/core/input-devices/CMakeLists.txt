add_library(
	Input-Devices STATIC
	include/Keyboard.h
	include/Mouse.h

	source/Keyboard.cpp
	source/Mouse.cpp
)

target_include_directories(
	Input-Devices PUBLIC
	include
)

target_link_libraries(
	Input-Devices PUBLIC
	Glm
	Window
)