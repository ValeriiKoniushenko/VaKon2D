file(
	GLOB Sources
	"include/*.h"
	"source/*.cpp"
)

add_library(
	BaseGame STATIC
	${Sources}
)

target_include_directories(BaseGame PUBLIC include/)

target_link_libraries(BaseGame PUBLIC
	Utils
)