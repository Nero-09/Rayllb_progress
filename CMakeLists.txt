cmake_minimum_required(VERSION 3.14)
project(mygame CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(raylib 5 QUIET)
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5)
    FetchContent_MakeAvailable(raylib)
endif()

add_executable(game src/main.cpp)
target_link_libraries(game raylib)