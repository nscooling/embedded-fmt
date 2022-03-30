#add tests
add_executable(test-efmt tester.cpp)
target_include_directories(test-efmt PRIVATE src)
add_test(Tester test-efmt)

add_executable(test-basic-formatting basic_formatting.cpp)
target_include_directories(test-basic-formatting PRIVATE src)
add_test(Test-basic-formatting test-basic-formatting)

add_executable(test-simple-tests simple_tests.cpp)
target_include_directories(test-simple-tests PRIVATE src)
add_test(Test-simple-tests test-simple-tests)

add_executable(test-edge-test edge_tests.cpp)
target_include_directories(test-edge-test PRIVATE src)
add_test(Test-edge-test test-edge-test)

add_executable(test-basic-hex basic_hex.cpp)
target_include_directories(test-basic-hex PRIVATE src)
add_test(Test-basic-hex test-basic-hex)

add_executable(test-basic-oct basic_oct.cpp)
target_include_directories(test-basic-oct PRIVATE src)
add_test(Test-basic-oct test-basic-oct)

add_executable(test-arrays test_arrays.cpp)
target_include_directories(test-arrays PRIVATE src)
add_test(Test-arrays test-arrays)

add_executable(test-basic-bin basic_bin.cpp)
target_include_directories(test-basic-bin PRIVATE src)
add_test(Test-basic-bin test-basic-bin)
