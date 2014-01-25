cmake_minimum_required(VERSION 2.6)
project(MUTINY)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

#set(CMAKE_CXX_COMPILER "eg++")
set(CMAKE_CXX_FLAGS "-g -std=c++0x")

include_directories(${MUTINY_SOURCE_DIR}/src /usr/local/include /usr/X11R6/include)
link_directories(/usr/local/lib /usr/X11R6/lib)

add_subdirectory(src/mutiny)
add_subdirectory(src/tools/buccaneer)
add_subdirectory(src/experiment)
add_subdirectory(src/baastud)

