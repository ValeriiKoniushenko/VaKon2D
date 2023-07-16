file(
	GLOB Sources
	"include/*.h"
	"source/*.cpp"
)

add_library(
	Core-Wrappers STATIC
	${Sources}
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
	Window
	Boost
)