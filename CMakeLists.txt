cmake_minimum_required(VERSION 3.14)
project(Schelling)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH})


find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(SDL2Test ${SDL2_INCLUDE_DIRS})

add_executable(Schelling main.cpp engine/engine.cpp engine/engine.h engine/cell/cell.cpp engine/cell/cell.h engine/cell/home_status.cpp engine/cell/mood_status.cpp)
target_link_libraries(Schelling ${SDL2_LIBRARIES})