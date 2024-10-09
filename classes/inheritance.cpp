#include <print>
#include <string>

using std::string;
using std::println;

class Animal {
virtual void animal_details() = 0;

protected:
  int age;
  string color;
  string name;

public:
  Animal(int Age, string colour, string Name)
      : age(Age), color(colour), name(Name) {};

    void setSize(int Age){
        age = Age;
    }
    int getAge(){
        return age;
    }

  virtual ~Animal() {};
};

class CAT : public Animal {
  int legs;

protected:
  string breed;

public:
  CAT(int age, string color, string name, int Legs, string Breed)
      : Animal(age, color, name), legs(Legs), breed(Breed) {};

    void animal_details() override{
        println("Animal Name: {}", name);
        println("Animal Age: {}yrs old", age);
        println("Animal Colour: {}", color);
        println("Animal Breed: {}", breed);
        println("Animal Number of Legs: {}", legs);
        println("");
    }

};

int main() {
    CAT mycat(3,"white","Cute Bunny", 4, "Brazillian");
    CAT kitten = CAT(1, "grey", "Cute Sussy", 4, "Mexican");

    // Display CATs details
    mycat.animal_details();
    kitten.animal_details();
    println("Kitten is {} years old", kitten.getAge());
}

