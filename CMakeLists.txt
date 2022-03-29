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

# add the executable
add_executable(embedded-fmt src/main.cpp)

#add tests
enable_testing()
add_executable(test-efmt tests/tester.cpp)
target_include_directories(test-efmt PRIVATE src)
add_test(Tester test-efmt)

add_executable(test-basic-formatting tests/tester.cpp)
target_include_directories(test-basic-formatting PRIVATE src)
add_test(Test-basic-formatting test-basic-formatting)

add_executable(test-simple-tests tests/tester.cpp)
target_include_directories(test-simple-tests PRIVATE src)
add_test(Test-simple-tests test-simple-tests)

add_executable(test-edge-test tests/tester.cpp)
target_include_directories(test-edge-test PRIVATE src)
add_test(Test-edge-test test-edge-test)

add_executable(test-basic-hex tests/tester.cpp)
target_include_directories(test-basic-hex PRIVATE src)
add_test(Test-basic-hex test-basic-hex)

add_executable(test-basic-oct tests/tester.cpp)
target_include_directories(test-basic-oct PRIVATE src)
add_test(Test-basic-oct test-basic-oct)