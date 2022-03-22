#include <array>
#include <cstddef>
#include <cstdio>
#include <string_view>

#ifndef Putchar
#define Putchar(x) putchar(x)
#endif

namespace embedded::fmt {

inline void vprint(std::string_view fmt) {
    for(auto c : fmt){
        Putchar(c);
    }
}

inline void print_arg(const char* p) { vprint(p); }

inline void print_arg(std::string_view p) { vprint(p); }

template <typename T>
void print_arg(T p) {
    static constexpr std::size_t buff_size{16};
    std::array<char, buff_size> buff{};
    if constexpr (std::is_integral_v<T>) {
        snprintf(buff.data(), buff.size(), "%d", p);
    }
    if constexpr (std::is_floating_point_v<T>) {
        snprintf(buff.data(), buff.size(), "%f", p);
    }
    buff.back() = '\0';  // guartentee NTBS
    vprint(std::string_view(buff.data(), buff.size()));
}

// #include <charconv>
// template <typename T>
// void print_arg(T p) {
//     static constexpr std::size_t buff_size{16};
//     std::array<char, buff_size> buff{};
//     if (auto [ptr, ec] =
//             std::to_chars(buff.data(), buff.data() + buff.size(), T(p));
//         ec == std::errc()) {
//         vprint( std::string_view( buff.data(), std::uint32_t(ptr -
//         buff.data() ) ) );
//     }
// }

template <typename... T>
inline void print(std::string_view fmt, T&&... args);

template <typename T1, typename... T2>
inline void vprint(std::string_view fmt, T1&& p, T2&&... args) {
    print_arg(p);
    print(fmt, args...);
}

template <typename... T>
inline void print(std::string_view fmt, T&&... args) {
    if (auto pos = fmt.find('{'); pos == std::string_view::npos) {
        vprint(fmt);
    } else {
        vprint(fmt.substr(0, pos));
        if (auto epos = fmt.find('}'); pos != std::string_view::npos) {
            vprint(fmt.substr(epos + 1), args...);
        }
    }
}

template <typename... T>
inline void println(std::string_view fmt, T&&... args) {
    print(fmt, args...);
    putchar('\n');
}

}  // namespace embedded::fmt
