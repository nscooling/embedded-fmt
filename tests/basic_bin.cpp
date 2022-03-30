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
void basic_binary() {
  // case 1
  int i{10};
  fmt::print("Bin: {:b}\n", i);
  std::cout << test_string;
  assert(test_string == "Bin: 1010\n");
  test_string.clear();
  // case 2
  fmt::print("Bin: {:#b}\n", i);
  std::cout << test_string;
  assert(test_string == "Bin: 0b1010\n");
  test_string.clear();
}
} // namespace

int main() { basic_binary(); }
