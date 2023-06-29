set(MISC_PATH "${DEPENDENCIES_PATH}/misc")
if (NOT IS_DIRECTORY ${MISC_PATH})
	message(FATAL_ERROR "Can't find the library by the next path: " ${MISC_PATH})
endif ()

add_library(Misc INTERFACE)

target_include_directories(Misc INTERFACE ${MISC_PATH})