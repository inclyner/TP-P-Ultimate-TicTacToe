cmake_minimum_required(VERSION 3.21)
project(tp C)

set(CMAKE_C_STANDARD 99)

add_executable(tp main.c utils.c utils.h matdin.c matdin.h)
