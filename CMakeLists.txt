cmake_minimum_required(VERSION 3.7)

project(Rgraph)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(CMAKE_CXX_FLAGS "-Wall -std=c++1z -lstdc++fs")
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# External deps
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/deps/glfw)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/deps/freetype)
# Testing dir
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)


#Library
add_library(RG source/File.cpp	deps/headers/glad/glad.c 
	source/RGraph.cpp 	source/Color.cpp 	source/Keyboard.cpp
	source/Image.cpp 	source/Window.cpp 	source/Texture.cpp
	source/Shader.cpp 	source/Quad.cpp 	source/QuadDrawer.cpp
	source/Sprite.cpp 	source/SpriteDrawer.cpp source/Drawer.cpp
	source/QuadBatcher.cpp 	source/Font.cpp 	source/RenderSurface.cpp
	source/Text.cpp
)

target_include_directories(RG PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/deps/headers)

message("CMAKE_CXX_FLAGS_DEBUG is ${CMAKE_CXX_FLAGS_DEBUG}")
message("CMAKE_CXX_FLAGS_RELEASE is ${CMAKE_CXX_FLAGS_RELEASE}")

#-lm
#target_compile_options(RG PUBLIC)
target_link_libraries(RG glfw freetype stdc++fs)
target_link_libraries(RG ${OPENGL_LIBRARIES})
#OpenGL::GL

#

#For testing
add_executable(Main main.cpp)
target_compile_options(Main PUBLIC)
target_link_libraries(Main RG)
