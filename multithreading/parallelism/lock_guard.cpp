#include <chrono>
#include <mutex>
#include <print>
#include <thread>

double balance{1'000.00};
std::mutex mtx;

void deposit(int times) {
  for (int i = 0; i < times; ++i) {
    std::lock_guard<std::mutex> lock(mtx);
    balance += 100;
    std::println("Deposit 100 New balance: {:.2f}", balance);
  }
};
void withdraw(int times) {
  for (int i = 0; i < times; ++i) {
    std::lock_guard<std::mutex> lock(mtx);
    if (balance > 150) {
      balance -= 150;
      std::println("Withdraw: 150| Balance {:.2f}", balance);
    } else {
      std::println("Insufficient funds! | Please top up your account!");
    }
  }
};

void audit(int times) {
  for (int i = 0; i < times; ++i) {
    std::lock_guard<std::mutex> lock(mtx);
    std::println("Account Balance: {:.2f}", balance);
  }
  std::this_thread::sleep_for(std::chrono::seconds(1));
};

int main() {
  std::println("Main thread started\n");

  std::thread t1(deposit, 8);
  std::thread t2(withdraw, 6);
  std::thread t3(audit, 5);

  t1.join();
  t2.join();
  t3.join();

  std::println("Final Balance: {:.2f}", balance);

  std::println("Main thread Ended\n");
};
