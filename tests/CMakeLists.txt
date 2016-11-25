project(${TESTS_NAME})

file(GLOB_RECURSE SRC_FILES tests/src/*)
add_executable(${TESTS_NAME} ${SRC_FILES})

target_link_libraries(${TESTS_NAME} ${LIBRARY_NAME})