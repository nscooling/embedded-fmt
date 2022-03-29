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
void basic() {
  // case 2 - simple string
  fmt::print("Hello, {}\n", "world!");
  std::cout << test_string;
  assert(test_string == "Hello, world!\n");
  test_string.clear();
}
} // namespace

int main() { basic(); }
