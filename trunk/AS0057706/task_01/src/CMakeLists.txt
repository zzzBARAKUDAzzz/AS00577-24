cmake_minimum_required(VERSION 3.10)
project(TemperatureSimulation)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем наш исполняемый файл
add_executable(simulation main.cpp)