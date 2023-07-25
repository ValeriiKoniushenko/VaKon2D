file(
	GLOB Sources
	"include/*.h"
	"source/*.cpp"
)

add_library(
	Utils
	${Sources}
)

set_target_properties(Utils PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(
	Utils PUBLIC
	include
)

target_link_libraries(
	Utils PUBLIC
	Glm
	Boost
)