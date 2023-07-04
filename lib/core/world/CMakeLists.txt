add_library(
	World STATIC
	include/Timer.h
	include/World.h

	source/Timer.cpp
	source/World.cpp
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