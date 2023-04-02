cmake_minimum_required(VERSION 3.5)

project(External VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick)

set(PROJECT_SOURCES
   main.cpp
   src/qml/qml.qrc
   fonts/fonts.qrc
   resources/resources.qrc

   # MEMORY
   src/memory/loop.hxx src/memory/loop.cxx
   src/memory/memtools.hxx src/memory/memtools.cxx

   # GUI
)

add_subdirectory(submodules)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(External
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(External
        ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(External
  PRIVATE Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Quick
  Qonsole
  Qit
)

set_target_properties(External PROPERTIES
    WIN32_EXECUTABLE TRUE
)

install(TARGETS External
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
