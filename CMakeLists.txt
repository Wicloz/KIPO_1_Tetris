cmake_minimum_required(VERSION 3.9)
project(KIPO_1_Tetris)
find_package (Threads)
set(CMAKE_CXX_STANDARD 17)

add_executable(KIPO_1_Tetris src/main.cpp src/Tetris.cpp lib/Tetris.h src/ThreadPool.cpp lib/ThreadPool.h)

target_link_libraries (KIPO_1_Tetris ${CMAKE_THREAD_LIBS_INIT})