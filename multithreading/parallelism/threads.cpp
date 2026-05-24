#include <chrono>
#include <functional>
#include <print>
#include <string>
#include <thread>

void worker1(int id) {
  std::println("Thread {} started", id);
  std::this_thread::sleep_for(std::chrono::seconds(3));
  std::println("Thread {} ended", id);
}

void worker2(int t_id, const std::string &thread_name) {
  std::println("Thread {} started", t_id);
  std::println("{} running inside Thread {}", thread_name, t_id);
  std::this_thread::sleep_for(std::chrono::seconds(3));
  std::println("Thread {} ended", t_id);
}

int main() {
  std::println("Main Thread started running");
  std::string wname = "Worker 2";

  std::thread t1(worker1, 1);
  std::thread t2(worker2, 2, std::cref(wname));
  std::thread t3([](int id) { std::println("Thread started running", id); }, 3);
  std::println("Main Thread started running");

  t1.join();
  t2.join();

  std::this_thread::sleep_for(std::chrono::seconds(3));

  std::println("Main Thread finished running!");
}
