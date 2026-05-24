#include <atomic>
#include <chrono>
#include <print>
#include <thread>

std::atomic<double> balance{1000.0};

/**Operation,   Meaning,Example
++ / --,        Increment / Decrement,counter++
+= / -=,        Add / Subtract,counter += 10
load(),         Read the value safely,int x = counter.load()
store(),        Write a value safely,counter.store(100)
fetch_add(),    Add and return old value,auto old = counter.fetch_add(5)
fetch_sub(),    Subtract and return old value,counter.fetch_sub(3)
compare_exchange,Advanced (CAS),Used in lock-free algorithms

*/

void deposit(int times) {
  for (int i = 0; i < times; ++i) {
    balance += 100.0;
    std::println("[Deposit]   +100  →  {:.2f}", balance.load());
  }
}

void withdraw(int times) {
  for (int i = 0; i < times; ++i) {
    double current = balance.load();
    if (current >= 150.0) {
      balance -= 150.0;
      std::println("[Withdraw]  -150  →  {:.2f}", balance.load());
    } else {
      std::println("[Withdraw]  FAILED");
    }
  }
}

int main() {
  std::println("Atomic Bank Simulation Started\n");

  std::thread t1(deposit, 8);
  std::thread t2(withdraw, 6);
  std::println("Threads 1 and 2 created\n");
  std::this_thread::sleep_for(std::chrono::seconds(1));

  t1.join();
  t2.join();

  std::println("\nFinal Balance = {:.2f}", balance.load());
}
