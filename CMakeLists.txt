cmake_minimum_required(VERSION 3.7)

project(Rgraph)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_SOURCE_DIR}/deps/glfw)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/deps/include)

add_library(RG source/DirMan.cpp source/File.cpp source/RGraph.cpp
  			source/Texture.cpp source/Sprite.cpp
)
target_compile_options(RG PUBLIC -Wall -std=c++1z -lstdc++fs -o3 -s -lm)
target_link_libraries(RG glfw stdc++fs)


add_executable(Rgraph main.cpp source/DirMan.cpp source/File.cpp
			source/RGraph.cpp  source/Texture.cpp source/Sprite.cpp
)
target_compile_options(Rgraph PUBLIC -Wall -std=c++1z -lstdc++fs -g)
target_link_libraries(Rgraph glfw stdc++fs)
