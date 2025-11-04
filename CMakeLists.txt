cmake_minimum_required(VERSION 3.10)
project(SnakeGame)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-g -O0")

add_executable(snake_game snake_game.cpp)

if(WIN32)
    target_compile_definitions(snake_game PRIVATE _WIN32)
endif()