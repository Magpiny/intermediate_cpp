#include <charconv>
#include <expected>
#include <print>
#include <string>

std::expected<int, std::string> parse_number(const std::string &str) {
  int result{};
  auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), result);

  if (ec == std::errc::invalid_argument)
    return std::unexpected("Not a number: " + str);
  if (ec == std::errc::result_out_of_range)
    return std::unexpected("Out of int range: " + str);
  if (ptr != str.data() + str.size())
    return std::unexpected("Trailing characters: " + str);

  return result;
};

std::expected<int, std::string> sqr(int number) { return number * number; }

int main() {
  auto res = parse_number("-14qwe2")
                 .and_then([](int x) { return sqr(x); })
                 .transform([](int x) { return x + 10; });

  if (res) {
    std::println("Final: {}", *res);
  } else {
    std::println("{}", res.error());
  }
}
