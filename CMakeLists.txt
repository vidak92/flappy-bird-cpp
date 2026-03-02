cmake_minimum_required(VERSION 4.1)

if(EMSCRIPTEN)
    set(CMAKE_OSX_ARCHITECTURES "")  # avoids -arch errors
endif()

project(flappy_bird_cpp)

if(CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
    set(PLATFORM Web CACHE STRING "" FORCE)
endif()

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5)
FetchContent_MakeAvailable(raylib)

if(EMSCRIPTEN)
    set(PLATFORM "Web" CACHE STRING "" FORCE)

    add_executable(flappy_bird_cpp src/main.cpp
            src/Game.cpp
            src/Game.h
            src/Player.cpp
            src/Player.h
            src/Config.cpp
            src/Config.h
            src/Sprite.cpp
            src/Sprite.h
            src/Utils.cpp
            src/Utils.h
            src/PipePair.cpp
            src/PipePair.h
    )

    target_link_libraries(flappy_bird_cpp raylib)
    set_target_properties(flappy_bird_cpp PROPERTIES SUFFIX ".html")
    target_link_options(flappy_bird_cpp PRIVATE
            "--preload-file" "${CMAKE_SOURCE_DIR}/res@res"
            "-sASYNCIFY"
            "--shell-file=${CMAKE_SOURCE_DIR}/web/minimal_shell.html"
    )
else ()
    set(PLATFORM "Desktop" CACHE STRING "" FORCE)

    add_executable(flappy_bird_cpp src/main.cpp
            src/Game.cpp
            src/Game.h
            src/Player.cpp
            src/Player.h
            src/Config.cpp
            src/Config.h
            src/Sprite.cpp
            src/Sprite.h
            src/Utils.cpp
            src/Utils.h
            src/PipePair.cpp
            src/PipePair.h
    )

    target_link_libraries(flappy_bird_cpp raylib)
endif()
