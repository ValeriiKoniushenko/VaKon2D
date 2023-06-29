set(GLM_PATH "${DEPENDENCIES_PATH}/GLM")
if (NOT IS_DIRECTORY ${GLM_PATH})
	message(FATAL_ERROR "Can't find the library by the next path: " ${GLM_PATH})
endif ()

add_library(Glm INTERFACE)

target_include_directories(Glm INTERFACE ${GLM_PATH})