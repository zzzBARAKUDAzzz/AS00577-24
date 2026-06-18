cmake_minimum_required(VERSION 3.10)
project(TemperatureControl)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source directory
include_directories(src)
file(GLOB SRC_FILES src/*.cpp)

# Main executable
add_executable(temperature_control ${SRC_FILES})

# Testing
enable_testing()

# Find Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Test executable
add_executable(test_temperature_control 
    test/test_temperature_control.cpp
    ${SRC_FILES}
)

target_link_libraries(test_temperature_control 
    ${GTEST_LIBRARIES}
    pthread
)

add_test(NAME TemperatureControlTest 
    COMMAND test_temperature_control
)

# Coverage flags (for gcov/lcov)
if(CMAKE_BUILD_TYPE STREQUAL "Coverage")
    target_compile_options(test_temperature_control PRIVATE --coverage)
    target_link_libraries(test_temperature_control PRIVATE --coverage)
endif()