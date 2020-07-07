cmake_minimum_required(VERSION 3.13)
project(Project)

SET(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_STANDARD 11)

add_library(tools UI/tools.cpp)

add_library(CUI_LIB UI/button.cpp)
target_link_libraries(CUI_LIB tools)

add_library(campus_graph campus_graph.cpp)
target_link_libraries(campus_graph
CUI_LIB
)

add_executable(nav_sys main.cpp)
target_link_libraries(nav_sys
campus_graph
pthread
)