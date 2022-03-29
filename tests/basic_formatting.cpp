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
void basic_formatting() {
  puts(">>> Basic Format Arguments");
  // case 1
  fmt::print("int: {}\n", 42);
  std::cout << test_string;
  assert(test_string == "int: 42\n");
  test_string.clear();
  // case 2
  fmt::print("int: {: }\n", 42);
  std::cout << test_string;
  assert(test_string == "int:  42\n");
  test_string.clear();
  // case 3
  fmt::print("int: {: }\n", 42U);
  std::cout << test_string;
  assert(test_string == "int:  42\n");
  test_string.clear();
  // case 4
  fmt::print("int: { }\n", -42);
  std::cout << test_string;
  assert(test_string == "int: -42\n");
  test_string.clear();
  // case 5
  fmt::print("int: {: }\n", -42);
  std::cout << test_string;
  assert(test_string == "int: -42\n");
  test_string.clear();
}
} // namespace

int main() { basic_formatting(); }
