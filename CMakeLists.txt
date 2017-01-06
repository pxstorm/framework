cmake_minimum_required(VERSION 3.5)

# C++ Options
set(CMAKE_CXX_STANDARD 11)

# Output directory
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# GLFW (http://www.glfw.org/docs/latest/build_guide.html#build_link_cmake_source)
set(GLFW_SOURCE_DIR "external/glfw")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${GLFW_SOURCE_DIR})

# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

# GLEW
set(GLEW_SOURCE_DIR "external/glew")

add_definitions(-DGLEW_STATIC)
include_directories(${GLEW_SOURCE_DIR}/include)

add_subdirectory(${GLEW_SOURCE_DIR})
add_library(
        glew STATIC
        ${GLEW_SOURCE_DIR}/src/glew.c
        ${GLEW_SOURCE_DIR}/include
)

# GLM
set(GLM_SOURCE_DIR "external/glm")
include_directories(${GLM_SOURCE_DIR})

# PXStorm
set(LIBRARY_NAME pxstorm)
project(${LIBRARY_NAME})

file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE INCLUDE_FILES include/*.h)

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/vendors/include
)

add_library(${LIBRARY_NAME} STATIC ${SRC_FILES} ${INCLUDE_FILES})
target_link_libraries(${LIBRARY_NAME} glfw glew ${OPENGL_gl_LIBRARY})

# Tests project
include(tests/CMakeLists.txt)
