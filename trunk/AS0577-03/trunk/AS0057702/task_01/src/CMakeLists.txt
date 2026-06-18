# CMakeList.txt: проект CMake для bez1lab; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
add_executable (bez1lab "bez1lab.cpp" "bez1lab.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET bez1lab PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
