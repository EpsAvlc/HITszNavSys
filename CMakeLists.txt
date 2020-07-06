cmake_minimum_required(VERSION 3.13)
project(Project)

set(CMAKE_CXX_STANDARD 11)

add_library(tools UI/tools.cpp)
add_executable(nav_sys main.cpp)
target_link_libraries(nav_sys
tools
)