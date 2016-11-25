cmake_minimum_required(VERSION 3.6)

# ==== CONFIGURATION ====

set(TESTS_NAME tests)
set(LIBRARY_NAME framework)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# ==== LIBRARY ====

project(${LIBRARY_NAME})

file(GLOB_RECURSE LIB_FILES lib/*)
file(GLOB_RECURSE INCLUDE_FILES include/*)

include_directories(${PROJECT_SOURCE_DIR}/include)
add_library(${LIBRARY_NAME} ${LIB_FILES} ${INCLUDE_FILES})

# ==== TESTS ====

include(tests/CMakeLists.txt)