cmake_minimum_required(VERSION 3.18)

project(sketchy_mvc VERSION 1.0)

# project config
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT "colorpal")

add_subdirectory(extern/raylib)
add_subdirectory(extern/imgui)

list(APPEND EXTRA_LIBS raylib
                       imgui
                       )
list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/src"
                           "${PROJECT_SOURCE_DIR}/extern/raylib/src"
                           "${PROJECT_SOURCE_DIR}/extern/imgui/imgui"
                           )

file(GLOB_RECURSE SOURCE_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/*.h)
list(APPEND SOURCE_FILES ${PROJECT_SOURCE_DIR}/main.cpp)

add_executable(sketchy_mvc ${SOURCE_FILES})

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_FILES})

target_precompile_headers(sketchy_mvc PUBLIC "${PROJECT_SOURCE_DIR}/src/pch.h")

target_link_libraries(sketchy_mvc PUBLIC ${EXTRA_LIBS})

target_include_directories(sketchy_mvc PUBLIC ${EXTRA_INCLUDES})
