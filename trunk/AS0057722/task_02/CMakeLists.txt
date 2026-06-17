cmake_minimum_required(VERSION 3.15)

project(task_02_temperature_tests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(model src/model.cpp src/model.h)

add_executable(task_02 src/main.cpp)
target_link_libraries(task_02 model)

enable_testing()

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(test_model test/test_model.cpp)
target_link_libraries(test_model model gtest_main)

include(GoogleTest)
gtest_discover_tests(test_model)