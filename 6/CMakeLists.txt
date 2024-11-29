cmake_minimum_required(VERSION 3.10)
project(lab6)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)
FetchContent_MakeAvailable(googletest)

set(COMMON_SOURCES
    src/gamemanager.cpp
    src/npc.cpp
    src/factory.cpp
    src/battlevisitor.cpp
    src/observer.cpp
)

set(HEADERS
    include/gamemanager.h
    include/npc.h
    include/factory.h
    include/battlevisitor.h
    include/observer.h
)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(game_create src/main.cpp ${COMMON_SOURCES})
add_executable(game_load src/main_load.cpp ${COMMON_SOURCES})

add_executable(unit_tests
    tests/test_main.cpp
    tests/test_npc.cpp
    tests/test_battle.cpp
    tests/test_factory.cpp
    ${COMMON_SOURCES}
)

target_link_libraries(unit_tests GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(unit_tests)