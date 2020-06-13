cmake_minimum_required(VERSION 3.7)

project(SDL2Test)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(SDL2Test main.cpp source/vec2.cpp source/DirMan.cpp source/File.cpp)
target_include_directories(SDL2Test PUBLIC include)
target_compile_options(SDL2Test PUBLIC -Wall -std=c++1z -lstdc++fs -g)
target_link_libraries(SDL2Test ${SDL2_LIBRARIES} stdc++fs)
