cmake_minimum_required(VERSION 3.17)
project(sieci)

set(CMAKE_CXX_STANDARD 14)
#add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors)
include_directories(
        include
)

set(SOURCE_FILES
        #src/storage_types.cpp
        src/package.cpp)

add_executable(sieci ${SOURCE_FILES} main.cpp)
