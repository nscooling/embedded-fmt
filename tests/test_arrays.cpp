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


void test_arrays() {
  std::array a{1, 2, 3, 4, 5};
  fmt::print("array<int>: {}\n", a);
  std::cout << test_string;
  assert(test_string == "array<int>: [ 1 2 3 4 5 ]\n");
  test_string.clear();

  std::array b{1.1f, 2.2f, 3.3f, 4.4f, 5.5f};
  fmt::print("array<float>: {}\n", b);
  std::cout << test_string;
  assert(test_string ==
         "array<float>: [ 1.10 2.20 3.30 4.40 5.50 ]\n");
  test_string.clear();

  fmt::print("array<hex>: {:#x}\n", a);
  std::cout << test_string;
  assert(test_string == "array<hex>: [ 0x1 0x2 0x3 0x4 0x5 ]\n");
  test_string.clear();
}

int main(){
  test_arrays();
}
/*
print("Decimal:\t{} {} {:06} {} {:0} {:+} {:d}\n", 1, 2, 3, 0, 0, 4, -1);
Decimal:        1 2 000003 0 0 +4 -1

print("Binary:\t\t{:b} {:#b} {:#b}\n", 10, 10, 4);
Binary:         1010 0b1010 0b100


print("Default:\t{} {:g} {:g}\n", 1.5, 1.5, 1e20);
print("Rounding:\t{:f} {:.0f} {:.22f}\n", 1.5, 1.5, 1.3);
print("Padding:\t{:05.2f} {:.2f} {:5.2f}\n", 1.5, 1.5, 1.5);
print("Scientific:\t{:E} {:e}\n", 1.5, 1.5);
print("Hexadecimal:\t{:a} {:A}\n\n", 1.5, 1.3);

Default:        1.5 1.5 1e+20
Rounding:       1.500000 2 1.3000000000000000444089
Padding:        01.50 1.50  1.50
Scientific:     1.500000E+00 1.500000e+00
Hexadecimal:    0x1.8p+0 0X1.4CCCCCCCCCCCDP+0
*/
