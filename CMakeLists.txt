cmake_minimum_required(VERSION 3.7)

project(SDL2Test)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(RG source/DirMan.cpp source/File.cpp source/RGraph.cpp
  			source/Texture.cpp
)
target_compile_options(RG PUBLIC -Wall -std=c++1z -lstdc++fs -o3 -s -lm)
target_link_libraries(RG ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARY} stdc++fs)


add_executable(SDL2Test main.cpp source/DirMan.cpp source/File.cpp
			source/RGraph.cpp  source/Texture.cpp
)

target_compile_options(SDL2Test PUBLIC -Wall -std=c++1z -lstdc++fs -g)
target_link_libraries(SDL2Test ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARY} stdc++fs)
