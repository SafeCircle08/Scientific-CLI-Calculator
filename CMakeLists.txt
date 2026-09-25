cmake_minimum_required(VERSION 3.31)
project(command_line_calculator C)

set(CMAKE_C_STANDARD 23)

add_executable(
        command_line_calculator
        src/main.c
        src/calculator.c
        src/parser.c
        include/calculator.h
        include/parser.h
        include/Node.h
        src/Node.c
        include/error.h
        src/error.c
)

target_include_directories(
        command_line_calculator
        PRIVATE
        include
)