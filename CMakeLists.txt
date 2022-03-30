cmake_minimum_required(VERSION 3.18)

# set the project name
project(embedded-fmt)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
        # -Werror
        $<$<CONFIG:DEBUG>:-g3>
        $<$<CONFIG:DEBUG>:-Og>
        $<$<CONFIG:RELEASE>:-O3>
    )
endif()

include_directories(include/embedded-fmt)

# add the executable
add_executable(embedded-fmt src/main.cpp)

#add tests
enable_testing()
add_subdirectory(tests)
