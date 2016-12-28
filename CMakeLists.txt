cmake_minimum_required(VERSION 3.5)

# ==== CONFIGURATION ====

set(TESTS_NAME tests)
set(LIBRARY_NAME framework)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# ==== LIBRARY ====

project(${LIBRARY_NAME})

file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE INCLUDE_FILES include/*.h)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/vendors/include
)

link_directories(
    ${EXECUTABLE_OUTPUT_PATH}
    ${PROJECT_SOURCE_DIR}/vendors/lib
)

add_library(${LIBRARY_NAME} ${SRC_FILES} ${INCLUDE_FILES})

target_link_libraries(${LIBRARY_NAME}
    libGLEW.a
    GL
)

# ==== TESTS ====

include(tests/CMakeLists.txt)
