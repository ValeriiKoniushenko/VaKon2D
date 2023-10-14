file(
	GLOB Sources
	"include/*.h"
	"source/*.cpp"
)

add_library(
	Camera STATIC
	${Sources}
)

target_include_directories(
	Camera PUBLIC
	include
)

target_link_libraries(
	Camera PUBLIC
	glfw
	Glad
	Utils
	Glm
	Core-Wrappers
)