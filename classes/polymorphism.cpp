#include <print>
#include <string>

using namespace std;

class Fish
{
protected:
  string name;

  virtual void fish_details() = 0;

public:
  string type;
  int weight;

  Fish(string n, string t, int w)
    : name(n)
    , type(t)
    , weight(w) {};

  void set_name(string name) { name = name; }

  string get_name() { return name; }

  virtual ~Fish() {};
};

class Tilapia : public Fish
{
public:
  string size;

  Tilapia(string nm, string typ, int weight, string size)
    : Fish(nm, typ, weight)
    , size(size) {};

  void fish_details() override
  {
    // polymorphism in action:
    println("Fish Name: {}", name);
    println("Fish Type: {}", type);
    println("Fish Weight: {}", weight);
    println("Fish Size: {}", size);
  }
};

void
getFishName(Tilapia& tilap)
{
  println("My Fish Name: {}", tilap.get_name());
}

int
main()
{
  Tilapia tilap = Tilapia("Ngege", "lake", 4, "medium");
  getFishName(tilap);
  println("Fish Two {}", tilap.get_name());
  tilap.fish_details();
}
