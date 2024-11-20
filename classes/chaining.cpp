// Method chaining in cpp
// LESSONS: Method Chaining and string concatenation
//
#include <iostream>
#include <print>
#include <sstream>
#include <string>

typedef std::string str;

class Man
{
  str fname;
  int age;
  str prof;

public:
  Man(str h_name, int h_age, str h_prof)
    : fname(h_name)
    , age(h_age)
    , prof(h_prof) {};

  str get_details()
  {
    std::ostringstream oss;
    oss << fname << " DETAILS: \n"
        << " Age: " << age << " Profession: " << prof;
    return oss.str();
  }
};

class Human
{
  str fname;
  int age;
  str prof;

public:
  Human()
    : fname("")
    , age(0)
    , prof("") {};

  Human& set_name(str hname)
  {
    fname = hname;
    return *this;
  }

  Human& set_age(int hage)
  {
    age = hage;
    return *this;
  }

  Human& set_proff(str profession)
  {
    prof = profession;
    return *this;
  }

  str get_details()
  {
    std::ostringstream oss;
    oss << fname << " DETAILS: \n"
        << " Age: " << age << " Profession: " << prof;
    return oss.str();
  }
};

int
main()
{
  Human one;

  Human three;
  three.set_name("Jack");
  three.set_proff("Doctor");
  three.set_age(34);

  Man two("Magpiny", 29, "Software Engineer");
  Man* four = new Man("Kasam", 28, "Farmer");

  str det =
    one.set_name("Wanjman").set_age(21).set_proff("Developer").get_details();

  std::println("{}", three.get_details());
  std::println("{}", two.get_details());

  std::println("{}" four->get_details());
  std::println("{}", det);
}
