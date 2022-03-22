#include <array>
#include <cstddef>
#include <cstdio>
#include <string_view>

// macro to allow redirection of output
#ifndef Putchar
#define Putchar(x) putchar(x)
#endif

namespace embedded::fmt {

// simple character-by-character output
// as string_view may not be NUL terminated
inline void vprint(std::string_view fmt) {
  for (auto c : fmt) {
    Putchar(c);
  }
}

// overload to match NTBS decay
inline void print_arg(const char *p) { vprint(p); }

// overload to match string or string_view
inline void print_arg(std::string_view p) { vprint(p); }

template <typename T> void print_arg(T p) {
  static constexpr std::size_t buff_size{16};
  std::array<char, buff_size> buff{};
  if constexpr (std::is_integral_v<T>) {
    auto count = snprintf(buff.data(), buff.size(), std::numeric_limits<T>::is_signed?"%d":"%u", p);
    vprint(std::string_view(buff.data(), count));
  }
  if constexpr (std::is_floating_point_v<T>) {
    auto count = snprintf(buff.data(), buff.size(), "%f", p);
    vprint(std::string_view(buff.data(), count));
  }
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

template <typename... T> inline void print(std::string_view fmt, T &&...args);

template <typename T1, typename... T2>
inline void vprint(std::string_view fmt, T1 &&p, T2 &&...args) {
  print_arg(p);
  print(fmt, args...);
}

template <typename... T> inline void print(std::string_view fmt, T &&...args) {
  constexpr auto arg_count = sizeof...(T);
  if constexpr (arg_count == 0) {
    vprint(fmt);
  }
  if constexpr (arg_count != 0) {
    if (auto pos = fmt.find('{'); pos == std::string_view::npos) {
      vprint(fmt);
    } else {
      vprint(fmt.substr(0, pos));
      if (auto epos = fmt.find('}'); pos != std::string_view::npos) {
        vprint(fmt.substr(epos + 1), args...);
      }
    }
  }
}

template <typename... T>
inline void println(std::string_view fmt, T &&...args) {
  print(fmt, args...);
  Putchar('\n');
}

} // namespace embedded::fmt
