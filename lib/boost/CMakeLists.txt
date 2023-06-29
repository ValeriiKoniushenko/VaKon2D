set(BOOST_PATH "${DEPENDENCIES_PATH}/boost_1_80_0")
if (NOT IS_DIRECTORY ${BOOST_PATH})
	message(FATAL_ERROR "Can't find the library by the next path: " ${BOOST_PATH})
endif ()

add_library(Boost INTERFACE)

target_include_directories(Boost INTERFACE ${BOOST_PATH})