cmake_minimum_required(VERSION 4.2.3)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(myrmopolis)

set(CORE_NAME ${PROJECT_NAME}_core)
set(CLI_NAME ${PROJECT_NAME}_cli)

# Lib CORE
find_package(nlohmann_json REQUIRED)

file(GLOB_RECURSE CORE_SRC_FILES src/core/*.cpp)

add_library(${CORE_NAME} ${CORE_SRC_FILES})

target_include_directories(${CORE_NAME} PUBLIC src/core/include PRIVATE src/core)
target_link_libraries(${CORE_NAME} PRIVATE nlohmann_json::nlohmann_json)

# Exe CLI
add_executable(${CLI_NAME} src/apps/cli/main.cpp)
target_link_libraries(${CLI_NAME} PRIVATE ${CORE_NAME})
