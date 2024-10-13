#include <iostream>
#include <mutex>
#include <print>
#include <string>
#include <thread>

using std::string;

std::mutex bike_mutex;

void ride_bike(string name) {
  std::unique_lock<std::mutex> bike_lock(bike_mutex);
  std::println("{} is riding a bike", name);
  std::this_thread::sleep_for(std::chrono::seconds(2));
  std::println("{} has finished riding", name);
  bike_lock.unlock();
}

void drive_car(string name) {
  std::lock_guard<std::mutex> bike_lock(bike_mutex);
  std::println("{} is riding a bike", name);
  std::this_thread::sleep_for(std::chrono::seconds(2));
  std::println("{} has finished riding", name);
}

int main() {
  std::thread thread1(ride_bike, "John");
  std::thread thread2(ride_bike, "Jane");

  std::thread thread3(drive_car, "Wangwe");
  std::thread thread4(drive_car, "Magpiny");

  thread1.join();
  thread2.join();

  thread3.join();
  thread4.join();

  std::cin.get();
}
