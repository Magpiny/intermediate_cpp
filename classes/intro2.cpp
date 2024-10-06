#include <iostream>

using std::cout;
using std::string;

// Introducing constructors

class Student {
public:
  string name;
  int age;
  string daro;

  // class constructors
  Student(string names, int ages, string classs) {
    name = names;
    age = ages;
    daro = classs;
  }
  void StudentDetails() {
    cout << "Name: " << name << " Age: " << age << " Class: " << daro
         << std::endl;
  }
};

int main() {
  Student sam = Student("Wanjare Samuel", 14, "8 Niger");
  cout << "Hello " << sam.name << std::endl;
  sam.StudentDetails();
}
