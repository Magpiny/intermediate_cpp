/**
 * Ring Buffer implementation
 * SIMPLE ONE
 *
 */

#include <optional>
#include <print>
#include <vector>

class RingBuffer {
  std::vector<int> buffer;
  std::size_t head = 0;
  std::size_t tail = 0;
  std::size_t count = 0;
  std::size_t capacity = 0;

public:
  explicit RingBuffer(std::size_t size) : buffer(size), capacity(size) {};

  // add some content
  bool push(int value) {
    if (count == capacity) {
      return false;
    }
    buffer[head] = value;
    head = (head + 1) % capacity;
    count++;
    return true;
  };

  std::optional<int> pop() {
    if (count == 0) {
      return std::nullopt;
    }
    int value = buffer[tail];
    tail = (tail + 1) % capacity;
    count--;
    return value;
  };

  // cool helpers
  bool is_Empty() { return count == 0; };
  bool is_full() { return count == capacity; };
  std::size_t size() { return count; };
  std::size_t container_size() { return capacity; };
};

int main() {
  RingBuffer rb(4);
  rb.push(20);
  rb.push(250);
  rb.push(400);
  rb.push(30);

  std::println("Our ring buffer type size is: {}", rb.container_size());

  return 0;
}
