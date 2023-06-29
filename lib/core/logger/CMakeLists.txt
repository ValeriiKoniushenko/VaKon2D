set(SPDLOG_PATH "${DEPENDENCIES_PATH}/spdlog")
if (NOT IS_DIRECTORY ${SPDLOG_PATH})
	message(FATAL_ERROR "Can't find the library by the next path: " ${SPDLOG_PATH})
endif ()

add_library(
	Logger STATIC
	include/Logger.h
	source/Logger.cpp
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