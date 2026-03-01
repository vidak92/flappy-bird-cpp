cmake_minimum_required(VERSION 4.1)
project(flappy_bird_cpp)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5)
FetchContent_MakeAvailable(raylib)

add_executable(flappy_bird_cpp src/main.cpp)

target_link_libraries(flappy_bird_cpp raylib)
