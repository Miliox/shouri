cmake_minimum_required (VERSION 3.20)
project(app)

file(GLOB INCLUDES include/**.hpp)
file(GLOB SOURCES src/**.cpp)

add_executable(${PROJECT_NAME} ${INCLUDES} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC include)