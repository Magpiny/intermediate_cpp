#include <print>
#include <string>
#include <vector>

typedef std::string str;

struct Student
{
  str name;
  int age;
  str mclass;
};

typedef std::vector<Student> vec;
int
main()
{
  vec stud1 = { Student("Sam", 23, "4 Blue") };

  std::println("Vector test: 123", );
}
