#include <iostream>
#include <type_traits>

template <typename T, int Size> class Calculator {
public:
  // Variadic template method to multiply any number of arguments
  template <typename... Args> T multiply(Args... args) {
    static_assert((std::is_arithmetic<Args>::value && ...),
                  "All arguments must be numbers");
    return multiplyHelper(args...);
  }

  // Method to get the size
  constexpr int get_size() const { return Size; }

private:
  // Helper function for multiply
  template <typename Arg> T multiplyHelper(Arg arg) {
    return static_cast<T>(arg);
  }

  template <typename Arg, typename... Args>
  T multiplyHelper(Arg first, Args... rest) {
    return static_cast<T>(first) * multiplyHelper(rest...);
  }
};

// Example usage
int main() {
  Calculator<double, 3> calc;

  std::cout << "Product: " << calc.multiply(2, 3.5, 4, 8, 9.6) << std::endl;
  std::cout << "Size: " << calc.get_size() << std::endl;

  Calculator<int, 5> calc2;
  std::cout << "Product: " << calc2.multiply(1, 2, 3, 4, 5) << std::endl;
  std::cout << "Size: " << calc2.get_size() << std::endl;

  return 0;
}
