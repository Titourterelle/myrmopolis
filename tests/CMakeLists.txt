set(TEST_NAME ${PROJECT_NAME}-test)

set(TEST_SRC
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

add_executable(
        ${TEST_NAME}
        ${CORE_SRC}
        ${RENDER_SRC}
        ${TEST_SRC}
)

target_link_libraries(${TEST_NAME} PRIVATE GTest::gtest_main)
gtest_discover_tests(${TEST_NAME})