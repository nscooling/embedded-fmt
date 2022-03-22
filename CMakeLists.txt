cmake_minimum_required(VERSION 3.18)

# set the project name
project(embedded-fmt)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(embedded-fmt src/main.cpp)