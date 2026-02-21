cmake_minimum_required(VERSION 4.2.3)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ants)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(${PROJECT_NAME} app/main.cpp ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE include)