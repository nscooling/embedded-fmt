#include <cassert>
#include <iostream>
#include <string>

std::string test_string{};
auto Putstr = [&str = test_string](auto c) { str += c; };
auto print_test_string = [](auto& str){ for(auto c:str) { putchar('.'), putchar(c); }};

#define Putchar(x) Putstr(x)

#include "efmt.hpp"
using namespace embedded;

int main() {

  // case 1 - simple string
  fmt::print("Hello, world!\n");
  std::cout << test_string;
  assert(test_string == "Hello, world!\n");
  test_string.clear();
  // case 2 - simple string
  fmt::print("Hello, {}\n", "world!");
  std::cout << test_string;
  assert(test_string == "Hello, world!\n");
  test_string.clear();
  // case 3
  fmt::print("int: {}\n", 42);
  std::cout << test_string;
  assert(test_string == "int: 42\n");
  test_string.clear();
  // case 4
  fmt::print("float: {}\n", 1.2f);
  std::cout << test_string;
  assert(test_string == "float: 1.200000\n");
  test_string.clear();
    // case 5
  fmt::print("unsigned: {}\n", static_cast<unsigned int>(0xFFFF'FFFFU));
  std::cout << test_string;
  assert(test_string == "unsigned: 4294967295\n");
  test_string.clear();
    // case 6
  fmt::print("signed: {}\n", static_cast<int>(0xFFFF'FFFF));
  std::cout << test_string;
  assert(test_string == "signed: -1\n");
  test_string.clear();
  ///////////////////////////////////////////////////////////

  // outliers (1) - arg but no {}
  fmt::print("int: \n", 42);
  std::cout << test_string;
  assert(test_string == "int: \n");
  test_string.clear();
  // outliers (2) -  {} but no arg
  fmt::print("int: {}\n");
  std::cout << test_string;
  assert(test_string == "int: {}\n");
  test_string.clear();
  // outliers (3) -  {} but no arg
  fmt::print("int: {} {}\n", 42);
  std::cout << test_string;
  assert(test_string == "int: 42 {}\n");
  test_string.clear();
  // outliers (4) -  {} but no arg
  fmt::print("int: {}\n", 42, 24);
  std::cout << test_string;
  assert(test_string == "int: 42\n");
  test_string.clear();
  puts("");
}
