cmake_minimum_required (VERSION 3.20)
project(app)

file(GLOB INCLUDES include/**.hpp)
file(GLOB SOURCES src/**.cpp)

# Application
add_executable(${PROJECT_NAME} ${INCLUDES} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} PUBLIC fmt)

# Unit Tests
add_executable(unit_test test/main.cpp)
target_link_libraries(unit_test PUBLIC gtest)