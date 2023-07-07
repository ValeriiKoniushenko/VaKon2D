cmake_minimum_required(VERSION 3.2...3.5)

project(VaKon2D-project VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(DEPENDENCIES_DIR_NAME dependencies)
set(DEPENDENCIES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/${DEPENDENCIES_DIR_NAME})

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	add_compile_definitions(OPENGL_DEBUG)
endif ()

add_subdirectory(game)
add_subdirectory(tests)
add_subdirectory(benchmark)

add_subdirectory(dependencies/freetype-2.10.0)
add_subdirectory(dependencies/glfw-3.3.7)
add_subdirectory(dependencies/googlebenchmark)
add_subdirectory(dependencies/googletest)

add_subdirectory(lib/boost)
add_subdirectory(lib/glad)
add_subdirectory(lib/glew)
add_subdirectory(lib/glm)
add_subdirectory(lib/misc)

add_subdirectory(lib/core/core-wrappers)
add_subdirectory(lib/core/delegate)
add_subdirectory(lib/core/input-devices)
add_subdirectory(lib/core/logger)
add_subdirectory(lib/core/shapes)
add_subdirectory(lib/core/utils)
add_subdirectory(lib/core/window)
add_subdirectory(lib/core/world)
