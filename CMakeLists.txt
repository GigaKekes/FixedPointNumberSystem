cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

project(FixedPoint)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(FixedPoint main.cpp ${SRC_FILES})
target_include_directories(FixedPoint PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
