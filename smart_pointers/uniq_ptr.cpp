#include <iostream>
#include <memory>
#include <print>

class Dog {
 public:
  Dog() { std::println("Constructor Invoked"); }
  void do_sth() { std::println("Do something great"); };
  ~Dog() { std::println("Destructor Invoked"); }
};

int main() {
  std::println("Learning about smart pointers");
  std::unique_ptr<int> smartptr = std::make_unique<int>(28);

  std::unique_ptr<Dog> mydog = std::make_unique<Dog>();
  mydog->do_sth();

  // std::println() could not output memory address
  std::cout << "Address of the smartptr: " << smartptr << std::endl;
  std::println("smartptr value: {}", *smartptr);
}
