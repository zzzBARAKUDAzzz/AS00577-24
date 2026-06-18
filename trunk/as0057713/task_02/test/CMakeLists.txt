cmake_minimum_required(VERSION 3.10)
project(Task02Tests)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")

# Google Test
add_subdirectory(D:/googletest-1.14.0 ${CMAKE_BINARY_DIR}/googletest)

# Тестируемые исходники
set(SRC_DIR ../src)

add_executable(runTests 
    test_main.cpp
    ${SRC_DIR}/main.cpp
)

target_include_directories(runTests PRIVATE ${SRC_DIR})
target_link_libraries(runTests gtest gtest_main pthread)