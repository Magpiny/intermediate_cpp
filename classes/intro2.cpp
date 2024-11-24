#include <iostream>
#include <print>
using std::cout;
using std::string;

// Introducing constructors

class Student
{
public:
  string name;
  int age;
  string daro;

  // class constructors / constructor function
  Student(string names, int ages, string classs)
  {

    name = names;
    age = ages;
    daro = classs;
  }
  void StudentDetails()
  {
    std::println("Name:{} Age: {} Class: {}", name, age, daro);
  }
};

int
main()
{
  Student sam = Student("Wanjare Samuel", 14, "8 Niger");
  std::println("Hello {}", sam.name);
  sam.StudentDetails();
}
