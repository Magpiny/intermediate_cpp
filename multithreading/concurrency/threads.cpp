#include <chrono>
#include <numeric>
#include <print>
#include <string>
#include <thread>

/**
 * LEARNING: MULTHREADING IN CPPP
 * THIS IS A TEST CASE WITHOUT THREADS
 *
 *  Check for threading.cpp for intro
 *
 */

void count21M(int size) {
  for (int i = 0; i < size; i++) {
    std::println("value: {}", i);
  }
}

// Testing 1

void count2100K(int size) {
  for (int i = 0; i < size; i++) {
    std::println("value: {}", i);
  }
}

int main() {
  std::string myname;

  auto start = std::chrono::high_resolution_clock::now();
  std::thread thread1(count21M, 500000);
  std::thread thread2(count2100K, 500000);

  thread1.join();
  thread2.join();
  auto end = std::chrono::high_resolution_clock::now();

  auto timetaken =
      std::chrono::duration_cast<std::chrono::seconds>(end - start);
  std::println("Duration of the Two threads: {} seconds", timetaken.count());

  system("pause>nul");
}
