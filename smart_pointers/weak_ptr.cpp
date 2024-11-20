#include <memory>
#include <print>

class Cat {
  Cat() { std::println("Cat Constructor"); }
  ~Cat() { std::println("Cat Destructor"); }
};

int main() {
  std::weak_ptr<int> wk_ptr = std::make_shared<int>(28);
  std::println("Weak pointer value is: {}" wk_pt :.use_count());
}
