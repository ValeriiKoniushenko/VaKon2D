add_library(
	Utils
	include/NotCopyableAndNotMovable.h
	include/Rect.h
	include/Size.h
	include/Singleton.h

	source/Rect.cpp
	source/Size.cpp
)

set_target_properties(Utils PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(
	Utils PUBLIC
	include
)

target_link_libraries(
	Utils PUBLIC
	Glm
)