#include "efmt.hpp"

using namespace embedded;

int main() {
    fmt::print("Hello, world! 1\n");
    fmt::println("Hello, world! 2");
    fmt::print("Hello, {} {}\n", "world!", 3);
    fmt::print("Default format: {} {} {}\n", 42, 1.2f, 2);
    puts("");
}
