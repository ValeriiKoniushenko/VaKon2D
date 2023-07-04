add_library(
	Delegate INTERFACE
	include/Delegate.h
)

target_include_directories(
	Delegate INTERFACE
	include
)

target_link_libraries(Delegate INTERFACE Utils)