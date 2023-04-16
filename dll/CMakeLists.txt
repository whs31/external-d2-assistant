cmake_minimum_required(VERSION 3.15)

project(internal VERSION 0.1 LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

include_directories(src lib)



file(GLOB CPP_SOURCES
    src/networking/*
    src/*
    src/dota/managers/*
    src/dota/entity/*
    src/dota/shared/*
    src/dota/convar/*

    src/memory/*

    lib/minhook/include/*
    lib/minhook/src/*
)

add_library(internal SHARED
    ${CPP_SOURCES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE ws2_32)

message(".dll compiled successfully")

