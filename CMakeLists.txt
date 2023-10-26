cmake_minimum_required(VERSION 3.26)
project(Overflow)

set(CMAKE_CXX_STANDARD 23)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/Engine/lib)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_definitions(-DPLATFORM_WINDOWS)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_definitions(-DPLATFORM_LINUX)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    add_definitions(-DPLATFORM_MAC)
else()
    message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_definitions(-DRELEASE)
endif()

option(EDITOR "Editor build mode" ON)

if(EDITOR)
    add_definitions(-DEDITOR)

file(GLOB_RECURSE IMGUI CONFIGURE_DEPENDS Editor/include/imgui/imgui.cpp
                                          Editor/include/imgui/imgui_demo.cpp
                                          Editor/include/imgui/imgui_draw.cpp
                                          Editor/include/imgui/imgui_tables.cpp
                                          Editor/include/imgui/imgui_widgets.cpp
                                          Editor/include/imgui/backends/imgui_impl_glfw.cpp
                                          Editor/include/imgui/backends/imgui_impl_opengl3.cpp)
file(GLOB_RECURSE SRC CONFIGURE_DEPENDS Editor/src/*.cpp)
file(GLOB_RECURSE YAML CONFIGURE_DEPENDS Editor/include/yaml-cpp/src/*.cpp)
endif ()

add_subdirectory(Engine)
add_executable(Overflow ${IMGUI} ${YAML} ${SRC})

target_link_libraries(Overflow PRIVATE Engine)

if(EDITOR)
target_include_directories(Overflow PUBLIC Editor/src/)
target_include_directories(Overflow PUBLIC Editor/)
target_include_directories(Overflow PUBLIC Editor/include/)
target_include_directories(Overflow PUBLIC Editor/include/imgui)
target_include_directories(Overflow PUBLIC Editor/include/yaml-cpp/include)
endif ()

target_include_directories(Overflow PUBLIC Engine/)
target_include_directories(Overflow PUBLIC Engine/src/)
target_include_directories(Overflow PUBLIC Engine/include/)
target_include_directories(Overflow PUBLIC Engine/include/glm/)
target_include_directories(Overflow PUBLIC Engine/include/spdlog/include)

set_target_properties(Overflow PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)

target_precompile_headers(Overflow PUBLIC pch.h)
set(CMAKE_PCH_INSTANTIATE_TEMPLATES ON)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/Editor/res/") #DEBUG
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    file(COPY ${CMAKE_SOURCE_DIR}/Editor/res DESTINATION ${CMAKE_BINARY_DIR})
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RES_PATH="${CMAKE_BINARY_DIR}./res/") #BUILD
endif()