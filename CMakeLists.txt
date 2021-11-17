cmake_minimum_required(VERSION 3.1)

project(hw3)

#aux_source_directory(. SRC_LIST)

set(hw3_SRC main.cpp functions.cpp class.cpp )
set(hw3_HDR functions.h class.h )

#add_library(vector STATIC ${hw3_SRC} ${hw3_HDR})
add_executable(${PROJECT_NAME} ${hw3_SRC} ${hw3_HDR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 /std:c++14")