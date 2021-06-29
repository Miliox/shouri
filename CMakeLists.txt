cmake_minimum_required (VERSION 3.20)
project(shouri VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
add_compile_options(-Wall -Wextra -Wpedantic -Werror -Wno-gnu-anonymous-struct)

add_subdirectory(modules)