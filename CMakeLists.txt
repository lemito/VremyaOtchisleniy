cmake_minimum_required(VERSION 3.27)
project(magic)

# list(APPEND CMAKE_C_FLAGS "-lm -Wall -Wextra -std=c99 -g -fno-sanitize-recover=all -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment")

# set(CMAKE_C_FLAGS_LABS "-lm  -Wall -Wextra -std=c99 -g   -fno-sanitize-recover=all -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment"
#     CACHE STRING "Compiler flags in labs build"
#     FORCE)

add_executable(magic main.cpp)
target_link_libraries(magic m)