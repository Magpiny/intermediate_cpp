#include <mutex>
#include <print>
#include <thread>

int counter = 0;
std::mutex mtx;

int increment() {
  for (int i = 0; i < 100'000; ++i) {
    mtx.lock();
    counter++;
    mtx.unlock();
  }
  return counter;
}

int main() {
  std::println("Entering Main thread");

  std::thread t1(increment);
  std::thread t2(increment);

  t1.join();
  t2.join();

  std::println("Final count: {}", counter);

  std::println("Exiting Main thread");

  return 0;
}
