file(GLOB_RECURSE ENGINE_SRC CONFIGURE_DEPENDS src/*.cpp)

#file(GLOB_RECURSE ASSYMP CONFIGURE_DEPENDS include/assimp/code/AssetLib/Obj/*.cpp
#                                           include/assimp/code/AssetLib/FBX/*.cpp)

add_library(Engine include/glad/glad.c
                   include/stb/stb_image.cpp
                   include/entt/entt.hpp
#                   ${ASSYMP}
                   ${ENGINE_SRC})

target_link_libraries(Engine PUBLIC glfw3)

target_include_directories(Engine PUBLIC src/)
target_include_directories(Engine PUBLIC include/)
target_include_directories(Engine PUBLIC include/glm/)
target_include_directories(Engine PUBLIC include/entt/)
target_include_directories(Engine PUBLIC include/spdlog/include)
#target_include_directories(Engine PUBLIC include/assimp/include)
target_include_directories(Engine PUBLIC ../)
