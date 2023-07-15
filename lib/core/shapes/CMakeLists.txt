file(
	GLOB Sources
	"include/*.h"
	"source/*.cpp"
)

add_library(Shapes STATIC ${Sources})

target_include_directories(
	Shapes PUBLIC
	include
)

target_link_libraries(
	Shapes PUBLIC
	Utils
	Core-Wrappers
	Glm
	Window
	Input-Devices
)