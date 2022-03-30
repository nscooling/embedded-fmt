#include <cassert>
#include <iostream>
#include <string>
#include "efmt.hpp"
using namespace embedded;


int main() {
  puts("");
  // fmt::print_binary(1);puts("");
  // fmt::print_binary(2);puts("");
  // fmt::print_binary(3);puts("");
  // fmt::print_binary(4);puts("");
  // fmt::print_binary(5);puts("");
  // fmt::print_binary(6);puts("");
  // fmt::print_binary(7);puts("");
  // fmt::print_binary(8);puts("");
  // fmt::print_binary(9);puts("");
  // fmt::print_binary(10);puts("");
  // fmt::print_binary(11);puts("");
  // fmt::print_binary(12);puts("");
  // fmt::print_binary(13);puts("");
  // fmt::print_binary(14);puts("");
  // fmt::print_binary(15);puts("");
  fmt::print("{:b}", 10);puts("");
  fmt::print("{:#b}", 10);puts("");
  
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
