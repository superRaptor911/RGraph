cmake_minimum_required(VERSION 3.7)

project(Rgraph)

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_SOURCE_DIR}/deps/glfw)

include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/deps/include)

#Library
add_library(RG source/DirMan.cpp source/File.cpp deps/include/glad/glad.c 
			source/RGraph.cpp source/Texture.cpp source/Sprite.cpp source/Color.cpp
			source/Shader.cpp source/Keyboard.cpp source/SpriteBatcher.cpp
)
target_compile_options(RG PUBLIC -Wall -std=c++1z -lstdc++fs -o3 -lm)
target_link_libraries(RG glfw OpenGL::GL stdc++fs)

#For testing
add_executable(Rgraph main.cpp source/DirMan.cpp deps/include/glad/glad.c 
			source/File.cpp source/RGraph.cpp  source/Texture.cpp source/Sprite.cpp
			source/Color.cpp source/Shader.cpp source/Keyboard.cpp source/SpriteBatcher.cpp
)
target_compile_options(Rgraph PUBLIC -Wall -std=c++1z -lstdc++fs -o -ggdb3)
target_link_libraries(Rgraph glfw OpenGL::GL stdc++fs)
