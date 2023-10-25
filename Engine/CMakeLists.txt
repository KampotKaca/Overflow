file(GLOB_RECURSE ENGINE_SRC CONFIGURE_DEPENDS src/*.cpp)

add_library(Engine include/glad/glad.c
                   include/stb/stb_image.cpp
                   ${ENGINE_SRC})

target_link_libraries(Engine PUBLIC glfw3)

target_include_directories(Engine PUBLIC src/)
target_include_directories(Engine PUBLIC include/)
target_include_directories(Engine PUBLIC include/glm/)
target_include_directories(Engine PUBLIC include/spdlog/include)
target_include_directories(Engine PUBLIC ../)
