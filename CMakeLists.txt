cmake_minimum_required (VERSION 3.20)
project(shouri VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_compile_options(-Wall -Wextra -Wpedantic -Werror)

add_subdirectory(modules)