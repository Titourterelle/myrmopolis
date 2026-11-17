cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(myrmopolis)

set(CORE_NAME ${PROJECT_NAME}-core)
set(RENDER_NAME ${PROJECT_NAME}-render)

set(CORE_SRC
        ${CMAKE_SOURCE_DIR}/src/core/environment/ant.cpp
        ${CMAKE_SOURCE_DIR}/src/core/environment/anthill_tile.cpp
        ${CMAKE_SOURCE_DIR}/src/core/environment/board.cpp
        ${CMAKE_SOURCE_DIR}/src/core/environment/colony.cpp
        ${CMAKE_SOURCE_DIR}/src/core/environment/land_tile.cpp
        ${CMAKE_SOURCE_DIR}/src/core/environment/tile.cpp
        ${CMAKE_SOURCE_DIR}/src/core/manager/config_manager.cpp
        ${CMAKE_SOURCE_DIR}/src/core/simulation/map_generator.cpp
        ${CMAKE_SOURCE_DIR}/src/core/simulation/simulation.cpp
)
set(RENDER_SRC
        ${CMAKE_SOURCE_DIR}/src/render/hex_grid.cpp
        ${CMAKE_SOURCE_DIR}/src/render/progress_bar.cpp
        ${CMAKE_SOURCE_DIR}/src/render/render_config_manager.cpp
        ${CMAKE_SOURCE_DIR}/src/render/render_observer.cpp
)

include(FetchContent)

# Lib CORE
find_package(nlohmann_json REQUIRED)

add_library(${CORE_NAME} ${CORE_SRC})

target_include_directories(${CORE_NAME} PUBLIC src/core/include PRIVATE src/core)
target_link_libraries(${CORE_NAME} PRIVATE nlohmann_json::nlohmann_json)

# Exe RENDER
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(
        ${RENDER_NAME}
        src/render/main.cpp
        ${RENDER_SRC}
)

target_link_libraries(${RENDER_NAME} PRIVATE ${CORE_NAME})
target_link_libraries(${RENDER_NAME} PRIVATE SFML::Graphics)

# Installation
include(GNUInstallDirs)
install(TARGETS ${RENDER_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY assets/ DESTINATION ${CMAKE_INSTALL_DATADIR}/myrmopolis)
