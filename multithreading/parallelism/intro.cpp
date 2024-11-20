#include <chrono>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

void heavy_computation(std::vector<long long> &result, int start, int end) {
  long long sum = 0;
  for (int i = start; i < end; ++i) {
    // Simulate some heavy computation
    for (int j = 0; j < 10000; ++j) {
      sum += i * j;
    }
  }
  result[start / (end - start)] = sum;
}

int main() {
  const int SIZE = 1000;
  std::vector<long long> result(4, 0);

  // Single-threaded version
  auto start_single = std::chrono::high_resolution_clock::now();
  heavy_computation(result, 0, SIZE);
  auto end_single = std::chrono::high_resolution_clock::now();
  auto duration_single = std::chrono::duration_cast<std::chrono::milliseconds>(
      end_single - start_single);

  // Multi-threaded version
  auto start_multi = std::chrono::high_resolution_clock::now();
  std::thread t1(heavy_computation, std::ref(result), 0, SIZE / 4);
  std::thread t2(heavy_computation, std::ref(result), SIZE / 4, SIZE / 2);
  std::thread t3(heavy_computation, std::ref(result), SIZE / 2, 3 * SIZE / 4);
  std::thread t4(heavy_computation, std::ref(result), 3 * SIZE / 4, SIZE);

  t1.join();
  t2.join();
  t3.join();
  t4.join();

  auto end_multi = std::chrono::high_resolution_clock::now();
  auto duration_multi = std::chrono::duration_cast<std::chrono::milliseconds>(
      end_multi - start_multi);

  std::cout << "Single-threaded time: " << duration_single.count() << " ms\n";
  std::cout << "Multi-threaded time: " << duration_multi.count() << " ms\n";

  return 0;
}
