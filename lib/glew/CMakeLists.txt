set(GLEW_PATH "${DEPENDENCIES_PATH}/GLEW/include")
if (NOT IS_DIRECTORY ${GLEW_PATH})
	message(FATAL_ERROR "Can't find the library by the next path: " ${GLEW_PATH})
endif ()

add_library(Glew INTERFACE)

target_include_directories(Glew INTERFACE ${GLEW_PATH}/include)