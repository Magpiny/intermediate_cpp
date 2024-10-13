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

void count21M() {
  for (int i = 0; i < 500000; i++) {
    std::println("value: {}", i);
  }
}

// Testing 1

void count2100K() {
  for (int i = 0; i < 500000; i++) {
    std::println("value: {}", i);
  }
}
int main() {
  std::string myname;
  auto mwanzo = std::chrono::high_resolution_clock::now();

  auto start = std::chrono::high_resolution_clock::now();
  count21M();
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::seconds>(stop - start);
  std::println("Time Taken: {} seconds", duration.count());

  std::this_thread::sleep_for(std::chrono::seconds(2));

  auto begin = std::chrono::high_resolution_clock::now();
  count2100K();
  auto end = std::chrono::high_resolution_clock::now();
  auto timetaken =
      std::chrono::duration_cast<std::chrono::seconds>(end - begin);
  std::println("Duration: {} seconds", timetaken.count());

  auto mwisho = std::chrono::high_resolution_clock::now();
  auto muda = std::chrono::duration_cast<std::chrono::seconds>(mwisho - mwanzo);
  std::println("Duration of the Two threads: {} seconds", muda.count() - 2);

  system("pause");
}
