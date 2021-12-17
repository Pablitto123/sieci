cmake_minimum_required(VERSION 3.17)
project(sieci)

set(CMAKE_CXX_STANDARD 14)

include_directories(
        include
)

set(SOURCE_FILES
        src/storage.cpp
        )

add_executable(sieci ${SOURCE_FILES} main.cpp)
