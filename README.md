
[![CMake](https://github.com/nscooling/embedded-fmt/actions/workflows/cmake.yml/badge.svg)](https://github.com/nscooling/embedded-fmt/actions/workflows/cmake.yml)

# embedded-fmt

Inspired by the very excellent [fmt](https://github.com/fmtlib/fmt) header only library and the introduction of [std::format](https://en.cppreference.com/w/cpp/utility/format/format) in C++20.

Required to run in deeply embedded systems (freestanding) with minimal memory overheads.

Requires C++17 support.

## Goals
A halfway-house between snprintf and cout.
* Only use `putchar` and `snprintf` from Cstdlib
* No used of `<iostream`>
* No dynamic memory allocation
* header only
* only scalar type support
* simple formatting
