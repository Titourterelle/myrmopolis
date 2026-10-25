cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(myrmopolis)

set(CORE_NAME ${PROJECT_NAME}-core)
set(RENDER_NAME ${PROJECT_NAME}-render)

# Lib CORE
find_package(nlohmann_json REQUIRED)

file(GLOB_RECURSE CORE_SRC_FILES src/core/*.cpp)

add_library(${CORE_NAME} ${CORE_SRC_FILES})

target_include_directories(${CORE_NAME} PUBLIC src/core/include PRIVATE src/core)
target_link_libraries(${CORE_NAME} PRIVATE nlohmann_json::nlohmann_json)

# Exe RENDER
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

file(GLOB_RECURSE RENDER_SRC_FILES src/apps/render/*.cpp)

add_executable(${RENDER_NAME} ${RENDER_SRC_FILES})
target_compile_features(${RENDER_NAME} PRIVATE cxx_std_23)

target_link_libraries(${RENDER_NAME} PRIVATE ${CORE_NAME})
target_link_libraries(${RENDER_NAME} PRIVATE SFML::Graphics)

# Installation
include(GNUInstallDirs)
install(TARGETS ${RENDER_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY assets/ DESTINATION ${CMAKE_INSTALL_DATADIR}/myrmopolis)
