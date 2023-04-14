cmake_minimum_required(VERSION 3.15)

project(internal VERSION 0.1 LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include_directories(src)

file(GLOB CPP_SOURCES
    src/*
    src/dota/managers/*
    src/memory/*
)

add_library(internal SHARED ${CPP_SOURCES})

message(".dll compiled successfully")

