file(
	GLOB Sources
	"include/*.h"
	"source/*.cpp"
)

add_library(
	Animations STATIC
	${Sources}
)

target_include_directories(
	Input-Devices PUBLIC
	include
)