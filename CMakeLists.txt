cmake_minimum_required(VERSION 3.9)
project(KIPO_1_Tetris)

set(CMAKE_CXX_STANDARD 11)

add_executable(KIPO_1_Tetris src/main.cpp src/Tetris.cpp lib/Tetris.h)

set(BUILD_SHARED_LIBS OFF)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")
