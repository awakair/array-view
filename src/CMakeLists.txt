cmake_minimum_required(VERSION 3.12)

project(
        labwork5
        VERSION 1.0
        DESCRIPTION "C++ Year 2023 labwork5"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF) 
add_compile_options(-Wall -Wextra -Werror -pedantic-errors)

add_subdirectory(uint17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
enable_testing()
add_subdirectory(tests)
