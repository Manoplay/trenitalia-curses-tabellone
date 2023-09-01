cmake_minimum_required(VERSION 3.25)
project(trenitab)

set(CMAKE_CXX_STANDARD 23)

find_package(Curses REQUIRED)
find_package(CURL REQUIRED)

include_directories(${CURSES_INCLUDE_DIR})
include_directories(${CURL_INCLUDE_DIR})

add_executable(trenitab main.cpp tabellone.cpp)

target_link_libraries(trenitab ${CURSES_LIBRARIES})
target_link_libraries(trenitab ${CURL_LIBRARIES})