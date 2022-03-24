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

void simple_tests();
void edge_tests();

void basic_formatting();

void basic_oct();

void basic_hex() {
  puts("///////////////////////////////////////////////////////////");
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

int main() {
  simple_tests();
  edge_tests();
  basic_formatting();
  basic_hex();
  basic_oct();
  puts("///////////////////////////////////////////////////////////");
  std::array a{1, 2, 3, 4, 5};
  fmt::print("array<int>: {}\n", a);
  std::cout << test_string;
  assert(test_string == "array<int>: [ 1 2 3 4 5 ]\n");
  test_string.clear();

  std::array b{1.1f, 2.2f, 3.3f, 4.4f, 5.5f};
  fmt::print("array<float>: {}\n", b);
  std::cout << test_string;
  assert(test_string ==
         "array<float>: [ 1.100000 2.200000 3.300000 4.400000 5.500000 ]\n");
  test_string.clear();

  fmt::print('.');
  std::cout << test_string;
  assert(test_string == ".");
  test_string.clear();
  puts("");

  fmt::print("array<hex>: {:#x}\n", a);
  std::cout << test_string;
  assert(test_string == "array<hex>: [ 0x1 0x2 0x3 0x4 0x5 ]\n");
  test_string.clear();
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

void simple_tests() {
  puts(">>> Simple cases");

  // case 1 - simple string
  fmt::print("Hello, world!\n");
  std::cout << test_string;
  assert(test_string == "Hello, world!\n");
  test_string.clear();
  // case 2 - simple string
  fmt::print("Hello, {}\n", "world!");
  std::cout << test_string;
  // assert(test_string == "Hello, world!\n");
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
}

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

  // outliers (4) -  empty string
  fmt::print("");
  std::cout << test_string;
  assert(test_string == "");
  test_string.clear();
}

void basic_formatting() {
  puts(">>> Basic Format Arguments");
  // case 3
  fmt::print("int: {}\n", 42);
  std::cout << test_string;
  assert(test_string == "int: 42\n");
  test_string.clear();
  // case 3
  fmt::print("int: {: }\n", 42);
  std::cout << test_string;
  assert(test_string == "int:  42\n");
  test_string.clear();
  // case 3
  fmt::print("int: {: }\n", 42U);
  std::cout << test_string;
  assert(test_string == "int:  42\n");
  test_string.clear();
  // case 3
  fmt::print("int: { }\n", -42);
  std::cout << test_string;
  assert(test_string == "int: -42\n");
  test_string.clear();
  // case 3
  fmt::print("int: {: }\n", -42);
  std::cout << test_string;
  assert(test_string == "int: -42\n");
  test_string.clear();
}

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
