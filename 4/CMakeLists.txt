cmake_minimum_required(VERSION 3.10)
project(figures)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем Google Test через FetchContent
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Добавляем директорию с заголовочными файлами
include_directories(${PROJECT_SOURCE_DIR}/include)

# Тесты
enable_testing()
add_executable(tests tests/figure_tests.cpp)
target_link_libraries(tests GTest::gtest_main)

# Основной исполняемый файл с Figure
add_executable(figures_app src/main.cpp)

# Дополнительный исполняемый файл с конкретным типом
add_executable(trapezoid_app src/main_trapezoid.cpp)

include(GoogleTest)
gtest_discover_tests(tests) 