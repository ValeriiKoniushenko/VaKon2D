set(SPDLOG_PATH "${DEPENDENCIES_PATH}/spdlog")
if (NOT IS_DIRECTORY ${SPDLOG_PATH})
	message(FATAL_ERROR "Can't find the library by the next path: " ${SPDLOG_PATH})
endif ()

file(
	GLOB Sources
	"include/*.h"
	"source/*.cpp"
)

add_library(
	Logger STATIC
	${Sources}
)

target_include_directories(
	Logger PUBLIC
	include
	${SPDLOG_PATH}
)

target_link_libraries(
	Logger PUBLIC
	Utils
)