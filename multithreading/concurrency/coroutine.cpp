#include <generator>
#include <print>

std::generator<int> number_generator(int count) {
  for (int i = 0; i < count; ++i) {
    co_yield i;
  }
}

int main() {
  std::println("Number generator started");

  for (int num : number_generator(10)) {

    std::println("Received: {}", num);
  }

  std::println("Number generator ended");
}
