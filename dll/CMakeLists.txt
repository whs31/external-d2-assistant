cmake_minimum_required(VERSION 3.5)

project(internal VERSION 0.1 LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB CPP_SOURCES
    src/*
)

add_library(internal SHARED ${CPP_SOURCES})

message(".dll compiled successfully")
