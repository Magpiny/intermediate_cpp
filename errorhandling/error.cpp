// Errors using std::expected

#include <expected>
#include <print>
#include <string>

std::expected<int, std::string> divide(int a, int b) {
  if (b == 0) {
    return std::unexpected("Divide by zero error!");
  }
  return a / b;
}

int main() {
  auto result = divide(10, 2);

  if (result.has_value()) {
    std::println("Result: {}", result.value());
  } else {
    std::println("Error: {}", result.error());
  }

  auto bad = divide(10, 0);
  if (!bad) {
    std::println("Error: {}", bad.error());
  }

  return 0;
}
