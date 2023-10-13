file(
        GLOB Sources
        "include/*.h"
        "source/*.cpp"
)

add_library(
        Animations STATIC
        ${Sources}
)

target_include_directories(
        Animations PUBLIC
        include
)

target_link_libraries(
        Animations PUBLIC
        Glm
        Utils
        Shapes
)