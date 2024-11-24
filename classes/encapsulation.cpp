#include <iostream>
#include <print>
using std::string;
// Encapsulation
// We'll make use of getters and setters

class Human
{
private:
  string Name;
  int Age;

public:
  // class constructor
  Human(string name, int age)
    : Name(name)
    , Age(age) {};

  // setters and getters
  void setName(string name) { Name = name; } // setter
  string getName() { return Name; }          // getter
};

int
main()
{
  Human human1 = Human("Sam Okoth", 67);
  human1.setName("John Waluke");
  std::println("Hello {}", human1.getName());
}
