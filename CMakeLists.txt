cmake_minimum_required(VERSION 3.27.0)

project(VaKon2d VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(DEPENDENCIES_DIR_NAME dependencies)
set(DEPENDENCIES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/${DEPENDENCIES_DIR_NAME})

set(GLAD_PATH "${DEPENDENCIES_PATH}/GLAD")
set(GLEW_PATH "${DEPENDENCIES_PATH}/GLEW")
set(GLM_PATH "${DEPENDENCIES_PATH}/GLM")
set(MISC_PATH "${DEPENDENCIES_PATH}/misc")
set(FREETYPE_PATH "${DEPENDENCIES_PATH}/freetype-2.10.0")
set(BOOST_PATH "${DEPENDENCIES_PATH}/boost_1_80_0")

# TODO: move to .cmake include file
# TODO: make a function from following
if (NOT IS_DIRECTORY ${GLAD_PATH})
    message(FATAL_ERROR "Can't find the library by the next path: " ${GLAD_PATH})
elseif(NOT IS_DIRECTORY ${GLEW_PATH})
    message(FATAL_ERROR "Can't find the library by the next path: " ${GLEW_PATH})
elseif(NOT IS_DIRECTORY ${GLM_PATH})
    message(FATAL_ERROR "Can't find the library by the next path: " ${GLM_PATH})
elseif(NOT IS_DIRECTORY ${MISC_PATH})
    message(FATAL_ERROR "Can't find the library by the next path: " ${MISC_PATH})
elseif(NOT IS_DIRECTORY ${FREETYPE_PATH})
    message(FATAL_ERROR "Can't find the library by the next path: " ${FREETYPE_PATH})
elseif(NOT IS_DIRECTORY ${BOOST_PATH})
    message(FATAL_ERROR "Can't find the library by the next path: " ${BOOST_PATH})
endif()

include_directories(
    ${GLAD_PATH}
    ${GLEW_PATH}/include
    ${GLM_PATH}
    ${MISC_PATH}
    ${DEPENDS_PATH}
    ${FREETYPE_PATH}/include
    ${BOOST_PATH}
)

add_subdirectory(dependencies/freetype-2.10.0)
add_subdirectory(dependencies/glfw-3.3.7)