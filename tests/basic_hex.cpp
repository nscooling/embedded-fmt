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
void basic_hex() {
  // case 1
  int i{10};
  fmt::print("Hex: {:x}\n", i);
  std::cout << test_string;
  assert(test_string == "Hex: a\n");
  test_string.clear();
  fmt::print("Hex: {:#x}\n", i);
  std::cout << test_string;
  assert(test_string == "Hex: 0xa\n");
  test_string.clear();
  fmt::print("Hex: {:X}\n", i);
  std::cout << test_string;
  assert(test_string == "Hex: A\n");
  test_string.clear();
  fmt::print("Hex: {:#X}\n", i);
  std::cout << test_string;
  assert(test_string == "Hex: 0XA\n");
  test_string.clear();

  i = -1;
  fmt::print("Hex: {:x}\n", i);
  std::cout << test_string;
  assert(test_string == "Hex: ffffffff\n");
  test_string.clear();
  fmt::print("Hex: {:#x}\n", i);
  std::cout << test_string;
  assert(test_string == "Hex: 0xffffffff\n");
  test_string.clear();
  fmt::print("Hex: {:X}\n", i);
  std::cout << test_string;
  assert(test_string == "Hex: FFFFFFFF\n");
  test_string.clear();
  fmt::print("Hex: {:#X}\n", i);
  std::cout << test_string;
  assert(test_string == "Hex: 0XFFFFFFFF\n");
  test_string.clear();
}
} // namespace

int main() { basic_hex(); }
