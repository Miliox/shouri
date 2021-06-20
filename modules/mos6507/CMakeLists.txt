cmake_minimum_required (VERSION 3.20)
project(mos6507)

set(INCLUDES
    include/r8.hpp
    include/regs.hpp
    include/isa.hpp)

set(SOURCES
    src/isa.cpp)

set(TESTS
    test/isa_tests.cpp
    test/main.cpp)

add_library(${PROJECT_NAME} STATIC ${INCLUDES} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC include)

# Unit Tests
set(TEST_PROJECT_NAME "${PROJECT_NAME}_test")
add_executable(${TEST_PROJECT_NAME} ${INCLUDES} ${SOURCES} ${TESTS})
target_link_libraries(${TEST_PROJECT_NAME} PUBLIC gtest)
target_include_directories(${TEST_PROJECT_NAME} PUBLIC include)