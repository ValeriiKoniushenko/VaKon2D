add_library(
	Utils
	include/Rect.h
	include/Size.h

	source/Rect.cpp
	source/Size.cpp
)

set_target_properties(Utils PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(Utils
	PUBLIC
	include
	${GLM_PATH}
	)