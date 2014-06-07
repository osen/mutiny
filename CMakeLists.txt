cmake_minimum_required(VERSION 2.6)
project(MUTINY)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

if(CMAKE_SYSTEM_NAME MATCHES "OpenBSD")
set(CMAKE_CXX_COMPILER "eg++")
endif(CMAKE_SYSTEM_NAME MATCHES "OpenBSD")

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
set(CMAKE_CXX_FLAGS "/EHsc -O2")
add_definitions(-DWINDOWS)
add_definitions(-DGLEW_STATIC)
include_directories(${MUTINY_SOURCE_DIR}/src ${MUTINY_SOURCE_DIR}/import/include)
link_directories(${MUTINY_SOURCE_DIR}/import/lib)
else()
set(CMAKE_CXX_FLAGS "-g -std=c++0x")
#set(CMAKE_CXX_FLAGS "-O2 -std=c++0x")
include_directories(${MUTINY_SOURCE_DIR}/src /usr/local/include /usr/X11R6/include)
link_directories(/usr/local/lib /usr/X11R6/lib)
endif(CMAKE_SYSTEM_NAME MATCHES "Windows")

add_subdirectory(src/mutiny)
add_subdirectory(src/tools/buccaneer)
add_subdirectory(src/experiment)
add_subdirectory(src/baastud)

