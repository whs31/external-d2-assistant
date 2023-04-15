cmake_minimum_required(VERSION 3.5)

project(External VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick)

include_directories(src/cpp)
file(GLOB_RECURSE CPP_SOURCES
    src/cpp/memory/*
    src/cpp/launch/*
    src/cpp/gui/*
)

set(PROJECT_SOURCES
    main.cpp
    src/entry.hpp    src/entry.cpp
    src/cpp/staticconfig.h

    src/qml/qml.qrc
    resources/resources.qrc
)

add_subdirectory(dll)

add_executable(External
    ${PROJECT_SOURCES}
    ${CPP_SOURCES}
)

target_link_libraries(External
    PRIVATE Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Quick
)

set_target_properties(External PROPERTIES
    WIN32_EXECUTABLE TRUE
)

install(TARGETS External
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

message(".exe compiled successfully")
