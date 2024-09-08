cmake_minimum_required(VERSION 3.10)
project(lab0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(TESTS "Build tests" OFF)

add_executable(main src/main.cpp)

target_include_directories(main PRIVATE include)

if (TESTS)
    enable_testing()

    add_subdirectory(external/googletest)

    add_executable(test tests/function_test.cpp src/function.cpp)

    target_link_libraries(test gtest gtest_main)

    add_test(NAME test_my_function COMMAND test)
endif()
