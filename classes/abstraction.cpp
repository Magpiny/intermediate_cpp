#include <print>
#include <string>

// Abstract class

class AbstractCar {
  // pure virtual functiom
  virtual void move() = 0;

  // Virtual destructor to ensure proper cleanup of derived class objects
public:
  virtual ~AbstractCar() {};
};

class Vehicle : AbstractCar {
  std::string PlateNumber;
  int milage;
  std::string make;

public:
  Vehicle(std::string plateNo, int dc, std::string vtype)
      : PlateNumber(plateNo), milage(dc), make(vtype) {};

  void carinfo() {
    if (milage > 65000) {
      std::println("{}: {} is too unroadworthy vehicle", make, PlateNumber);
    } else {
      std::println("{}: {} still runs smoothly", make, PlateNumber);
    }
  }
  // Implementation of the pure virtual function
  void move() override { std::println("It is moving: abstrct overide"); }
};

int main() {
  Vehicle car0 = Vehicle("KDD 678H", 23444, "Subaru");
  Vehicle car1 = Vehicle("KVD 178U", 83455, "Lexus");
  Vehicle car2 = Vehicle("KHF 491H", 13644, "Audi");

  car0.carinfo();
  car1.carinfo();
  car2.carinfo();

  car0.move();
}
