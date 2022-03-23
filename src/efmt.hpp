#include <array>
#include <cstddef>
#include <cstdio>
#include <string_view>
#include <limits>

// macro to allow redirection of output
#ifndef Putchar
#define Putchar(x) putchar(x)
#endif

namespace embedded::fmt {

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

template <typename T>
constexpr const char *signed_arg([[maybe_unused]] T p, Format_string const &fmt_str) {
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

template <typename T> inline void print_arg(T p, Format_string const &fmt_str) {
  static constexpr std::size_t buff_size{16};
  std::array<char, buff_size> buff{};
  if constexpr (std::is_integral_v<T>) {
    auto arg_fmt = signed_arg(p, fmt_str);
    auto count = snprintf(buff.data(), buff.size(), arg_fmt, p);
    vprint(std::string_view(buff.data(), static_cast<std::size_t>(count)));
  }
  if constexpr (std::is_floating_point_v<T>) {
    auto count = snprintf(buff.data(), buff.size(), "%f", p);
    vprint(std::string_view(buff.data(), static_cast<std::size_t>(count)));
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

constexpr Format_string parse_format_string(std::string_view fmt_str) {
  if (fmt_str[0] != ':')
    return {};
  using namespace std::literals;
  Format_string str{};
  if (fmt_str == ": "sv){
    str.sign_space = true;
    return str;
  }
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
  if constexpr (arg_count == 0) {
    vprint(fmt);
  }
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
  }
}

template <typename... T>
inline void println(std::string_view fmt, T &&...args) {
  print(fmt, args...);
  Putchar('\n');
}

} // namespace embedded::fmt
