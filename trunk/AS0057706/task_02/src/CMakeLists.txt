cmake_minimum_required(VERSION 3.14)
project(Lab2_Simulation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем флаги для анализа покрытия (gcov)
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -O0 -g")
endif()

# Скачиваем Google Test напрямую из гитхаба во время сборки
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Собираем основное приложение
add_executable(simulation main.cpp models.hpp)

# Собираем тесты из папки test
add_executable(run_tests ../test/test.cpp models.hpp)
target_link_libraries(run_tests PRIVATE gtest_main)

# Включаем поддержку тестов в CMake
enable_testing()
add_test(NAME CoreModelsTest COMMAND run_tests)