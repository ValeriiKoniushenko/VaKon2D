file(
	GLOB Sources
	"include/*.h"
	"source/*.cpp"
)

add_library(
	Window STATIC
	${Sources}
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
	World
)