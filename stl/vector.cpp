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
  std::vector<int> numbers{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
  std::vector<str> fruits = { "mangoe", "guava", "apple", "avocado" };

  vec stud1 = { { "Sam", 24, "4 Blue" },   { "John", 21, "4 Green" },
                { "Mathew", 23, "4 Red" }, { "Mike", 20, "4 Red" },
                { "Paul", 22, "4 Green" }, { "Horace", 24, "4 Blue" } };

  // Add an element to a vector
  stud1.push_back({ "Luke", 22, "Green" });

  // Filter out students from red class/stream

  for (const auto& student : stud1) {
    if (student.mclass == "4 Red")
      std::println("Name: {} Age: {} Class: {}",
                   student.name,
                   student.age,
                   student.mclass);
  }

  std::println("Vector test: {}", stud1.at(1).name);
  std::println("Number of students: {}", stud1.size());
}