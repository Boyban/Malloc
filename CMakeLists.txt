cmake_minimum_required(VERSION 3.9)
project(PSU_2017_malloc)

set(CMAKE_CXX_STANDARD 11)

add_executable(PSU_2017_malloc
        include/malloc.h
        src/block_tools.c
        src/calloc.c
        src/free.c
        src/malloc.c
        src/realloc.c
        src/show_alloc_mem.c)
