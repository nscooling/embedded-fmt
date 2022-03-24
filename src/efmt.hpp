#include <array>
#include <cstddef>
#include <cstdio>
#include <limits>
#include <string_view>

// macro to allow redirection of output
#ifndef Putchar
#define Putchar(x) putchar(x)
#endif

namespace embedded::fmt {

template <typename... T> inline void print(std::string_view fmt, T &&...args);

struct Format_string {
  enum struct Base { dec, bin, oct, hex };
  bool sign_space{false};
  bool show_base{false};
  bool base_as_uc{false};
  Base base{Base::dec};
};

// simple character-by-character output
// as string_view may not be NUL terminated
inline void vprint(std::string_view fmt) {
  for (auto c : fmt) {
    Putchar(c);
  }
}

// No plans to do any string formatting
// overload to match NTBS decay
inline void print_arg(const char *p,
                      [[maybe_unused]] Format_string const &fmt_str) {
  vprint(p);
}

// overload to match string or string_view
inline void print_arg(std::string_view p,
                      [[maybe_unused]] Format_string const &fmt_str) {
  vprint(p);
}

//
// Integral parsing
//

template <typename T, std::enable_if_t<std::is_integral_v<T>, bool> = true>
constexpr const char *parse_fmt_args([[maybe_unused]] T p,
                                     Format_string const &fmt_str) {
  switch (fmt_str.base) {
  case Format_string::Base::hex:
    return fmt_str.show_base ? (fmt_str.base_as_uc ? "%#X" : "%#x")
                             : (fmt_str.base_as_uc ? "%X" : "%x");
  case Format_string::Base::oct:
    return fmt_str.show_base ? "%#o" : "%o";
  case Format_string::Base::bin:
    // return fmt_str.show_base ? (fmt_str.base_as_uc?"%#X":"%#x") :
    // (fmt_str.base_as_uc?"%X":"%x");
  case Format_string::Base::dec:
    if constexpr (std::numeric_limits<T>::is_signed)
      return fmt_str.sign_space && (p > 0) ? " %d" : "%d";
    if constexpr (!std::numeric_limits<T>::is_signed)
      return fmt_str.sign_space ? " %u" : "%u";
  }
  return "";
}

//
// Floating point parsing
//

template <typename T,
          std::enable_if_t<std::is_floating_point_v<T>, bool> = true>
constexpr const char *
parse_fmt_args([[maybe_unused]] T p,
               [[maybe_unused]] Format_string const &fmt_str) {
  // TODO
  return "%f";
}

//
// print the argument using formatting
//
template <typename T> inline void print_arg(T p, Format_string const &fmt_str) {
  static constexpr std::size_t buff_size{16};
  std::array<char, buff_size> buff{};
  auto const arg_fmt = parse_fmt_args(p, fmt_str);
  auto const count = snprintf(buff.data(), buff.size(), arg_fmt, p);
  vprint(std::string_view(buff.data(), static_cast<std::size_t>(count)));
}

template <typename T, std::size_t sz>
inline void print_arg(std::array<T, sz> const &t,
                      Format_string const &fmt_str) {
  fmt::print("[ ");
  for (auto x : t) {
    print_arg(x, fmt_str);
    fmt::print(" ");
  }
  fmt::print("]");
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

constexpr Format_string parse_format_string(std::string_view fmt_str) {
  if (fmt_str[0] != ':')
    return {};
  Format_string str{};
  auto c_ptr = &fmt_str[1];
  if (*c_ptr == '#') {
    str.show_base = true;
    ++c_ptr;
  }
  switch (*c_ptr) {
  case 'B':
    str.base_as_uc = true;
    [[fallthrough]];
  case 'b':
    str.base = Format_string::Base::bin;
    break;
  case 'X':
    str.base_as_uc = true;
    [[fallthrough]];
  case 'x':
    str.base = Format_string::Base::hex;
    break;
  case 'o':
    str.base = Format_string::Base::oct;
    break;
  case ' ':
    str.sign_space = true;
    break;
  }
  return str;
}

template <typename T1, typename... T2>
inline void vprint(std::string_view fmt, std::string_view fmt_str, T1 &&p,
                   T2 &&...args) {
  auto fmt_string = parse_format_string(fmt_str);
  print_arg(p, fmt_string);
  print(fmt, args...);
}

template <typename... T> inline void print(std::string_view fmt, T &&...args) {
  constexpr auto arg_count = sizeof...(T);
  if constexpr (arg_count != 0) {
    if (auto pos = fmt.find('{'); pos == std::string_view::npos) {
      vprint(fmt);
    } else {
      vprint(fmt.substr(0, pos));
      if (auto epos = fmt.find('}'); pos != std::string_view::npos) {
        vprint(fmt.substr(epos + 1), fmt.substr(pos + 1, epos - pos - 1),
               args...);
      }
    }
  } else {
    vprint(fmt);
  }
}

template <typename... T>
inline void println(std::string_view fmt, T &&...args) {
  print(fmt, args...);
  Putchar('\n');
}

void print(char c) { Putchar(c); }
} // namespace embedded::fmt
