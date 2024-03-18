cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

project(GraphGenerator)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(GraphGenerator main.cpp ${SRC_FILES})
target_include_directories(GraphGenerator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
