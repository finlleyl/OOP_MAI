cmake_minimum_required(VERSION 3.10)
project(lab7)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(TESTS "Build tests" OFF)

add_executable(main
    src/main.cpp
    src/NPC.cpp
    src/Elf.cpp
    src/Rogue.cpp
    src/Bear.cpp
    src/FactoryImpl.cpp
    src/Subject.cpp
    src/FightLogObserver.cpp
    src/ConsoleLogObserver.cpp
    src/Map.cpp
    src/FightTask.cpp
    src/ThreadSafeIO.cpp)
    

target_include_directories(main PRIVATE include)

add_subdirectory(external/googletest)

add_executable(test
    tests/test.cpp
    src/NPC.cpp
    src/Elf.cpp
    src/Rogue.cpp
    src/Bear.cpp
    src/FactoryImpl.cpp
    src/Subject.cpp
    src/FightLogObserver.cpp
    src/ConsoleLogObserver.cpp
    src/Map.cpp
    src/FightTask.cpp
    src/ThreadSafeIO.cpp)

target_include_directories(test PRIVATE include)

target_link_libraries(test gtest gtest_main)