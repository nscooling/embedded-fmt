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
void basic_oct() {
  puts("///////////////////////////////////////////////////////////");
  int i{10};
  fmt::print("Oct: {:o}\n", i);
  std::cout << test_string;
  assert(test_string == "Oct: 12\n");
  test_string.clear();
  fmt::print("Oct: {:#o}\n", i);
  std::cout << test_string;
  assert(test_string == "Oct: 012\n");
  test_string.clear();
}

} // namespace

int main() { basic_oct(); }
