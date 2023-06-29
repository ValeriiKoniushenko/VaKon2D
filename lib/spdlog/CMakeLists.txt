set(P7_PATH "${DEPENDENCIES_PATH}/p7/Headers")
if (NOT IS_DIRECTORY ${P7_PATH})
	message(FATAL_ERROR "Can't find the library by the next path: " ${P7_PATH})
endif ()

add_library(P7 INTERFACE)

target_include_directories(P7 INTERFACE ${P7_PATH})