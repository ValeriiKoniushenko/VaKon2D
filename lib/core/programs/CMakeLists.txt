add_executable(
	VaKon2D
	include/VaKon2D.h

	source/VaKon2D.cpp
	source/main.cpp
)

target_include_directories(
	VaKon2D PUBLIC
	include
)

target_link_libraries(
	VaKon2D PUBLIC
	Utils
)