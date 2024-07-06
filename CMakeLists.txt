cmake_minimum_required(VERSION 3.14)

project(HW7)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CXX_EXTENSIONS NO)


include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(
    list_tests
    list_tests.cpp
)

add_executable(
    vector_tests
    vector_tests.cpp
)

enable_testing()

target_link_libraries(
    list_tests
    GTest::gtest_main
)

target_link_libraries(
    vector_tests
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(list_tests)
gtest_discover_tests(vector_tests)
