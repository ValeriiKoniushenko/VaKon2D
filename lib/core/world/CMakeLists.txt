file(
	GLOB Sources
	"include/*.h"
	"source/*.cpp"
)

add_library(
	World STATIC
	${Sources}
)

target_include_directories(
	World PUBLIC
	include
)

target_link_libraries(
	World PUBLIC
	Utils
	Logger
)