cmake_minimum_required(VERSION 3.10)
project(os_hw1 C)

set(CMAKE_C_STANDARD 99)

add_executable(os_hw1 disk.c disk.h fs.c fs.h testcase.c validate.h validate.o)