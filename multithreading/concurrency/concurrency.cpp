#include <iostream>
#include <print>
#include <string>
#include <thread>

using std::string;

void ride_bike(string name) {
  std::println("{} is riding a bike", name);
  std::this_thread::sleep_for(std::chrono::seconds(2));
  std::println("{} has finished riding", name);
}

int main() {
  std::thread thread1(ride_bike, "John");
  std::thread thread2(ride_bike, "Jane");

  thread1.join();
  thread2.join();

  std::cin.get();
}
