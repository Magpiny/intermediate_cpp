#include <memory>
#include <print>

class Animal {
 public:
  Animal() { std::println("Constructor called"); };
  ~Animal() { std::println("Destructor called"); };
};

int main() {
  std::shared_ptr<Animal> shared_ptr1 = std::make_shared<Animal>();
  std::println("Shared by {}", shared_ptr1.use_count());

  {
    std::shared_ptr<Animal> shared_ptr2 = shared_ptr1;
    std::println("Shared by {}", shared_ptr2.use_count());
  }
}
