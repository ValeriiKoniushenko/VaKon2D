file(
	GLOB Sources
	"include/*.h"
	"source/*.cpp"
)

add_library(
	FreeType-Wrapper STATIC
	${Sources}
)

target_include_directories(
	FreeType-Wrapper PUBLIC
	include
)

target_link_libraries(
	FreeType-Wrapper PUBLIC
	Utils
	glfw
	Glad
	Logger
	Delegate
	Misc
	Window
	Boost
	freetype
)