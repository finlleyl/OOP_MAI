cmake_minimum_required(VERSION 3.10)
project(lab6)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(TESTS "Build tests" OFF)

add_executable(main
    src/main.cpp
    include/concept.hpp
    include/coords.hpp
    include/fight_manager.hpp
    include/npc.hpp
    include/observer.hpp
    include/visitor.hpp)

target_include_directories(main PRIVATE include)

add_subdirectory(external/googletest)

add_executable(test
    tests/test.cpp
    include/concept.hpp
    include/coords.hpp
    include/fight_manager.hpp
    include/npc.hpp
    include/observer.hpp
    include/visitor.hpp)

target_include_directories(test PRIVATE include)

target_link_libraries(test gtest gtest_main)