set(TEST_NAME ${PROJECT_NAME}-test)

set(TEST_SRC
        core/simulation/map_generator_test.cpp
)

# Google Test
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.18.0
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)
include(GoogleTest)

add_executable(${TEST_NAME} ${TEST_SRC})

target_include_directories(${TEST_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src/core ${PROJECT_SOURCE_DIR}/src/render)
target_link_libraries(${TEST_NAME} PRIVATE ${CORE_NAME})
target_link_libraries(${TEST_NAME} PRIVATE ${RENDER_LIB_NAME})

target_link_libraries(${TEST_NAME} PRIVATE GTest::gtest_main)
gtest_discover_tests(${TEST_NAME})