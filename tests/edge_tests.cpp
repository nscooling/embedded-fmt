#include <cassert>
#include <iostream>
#include <string>

std::string test_string{};
auto Putstr = [&str = test_string](auto c) { str += c; };
[[maybe_unused]] auto print_test_string = [](auto &str) {
  for (auto c : str) {
    putchar('.'), putchar(c);
  }
};

#define Putchar(x) Putstr(x)

#include "efmt.hpp"
using namespace embedded;

namespace {
void edge_tests() {
  puts(">>> Edge cases");

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

  // outliers (5) -  empty string
  fmt::print("");
  std::cout << test_string;
  assert(test_string == "");
  test_string.clear();
}
} // namespace

int main() { edge_tests(); }
