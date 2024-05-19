# CMakeList.txt: проект CMake для aisd_lab3; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
add_executable (aisd_lab3 "aisd_lab3.cpp" "aisd_lab3.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET aisd_lab3 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
