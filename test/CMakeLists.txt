cmake_minimum_required(VERSION 3.7)

project(Test)

#find_package(SDL2 REQUIRED)
include_directories(RG/include)

add_executable(FsTest FsTest/main.cpp)
target_include_directories(FsTest PUBLIC include)
target_compile_options(FsTest PUBLIC -Wall -std=c++1z -g)
target_link_libraries(FsTest ${CMAKE_SOURCE_DIR}/RG/lib/libRG.a)

