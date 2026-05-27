/**
 * ring_buffer_test.cpp
 *
 * Build:
 *   g++ -std=c++17 -O2 -pthread -Wall -Wextra -o ring_buffer_test
 * ring_buffer_test.cpp
 *
 * Run:
 *   ./ring_buffer_test
 */

#include "ring_buffer.hpp"

#include <cassert>
#include <cstdio>
#include <string>
#include <thread>

// ─── helpers ─────────────────────────────────────────────────────────────────

static int pass_count = 0;
#define CHECK(expr)                                                            \
  do {                                                                         \
    if (!(expr)) {                                                             \
      std::fprintf(stderr, "FAIL  %s:%d  %s\n", __FILE__, __LINE__, #expr);    \
      std::exit(1);                                                            \
    }                                                                          \
    ++pass_count;                                                              \
  } while (0)

// ─────────────────────────────────────────────────────────────────────────────
// RingBuffer — single-threaded tests
// ─────────────────────────────────────────────────────────────────────────────

void test_basic() {
  RingBuffer<int, 4> rb;

  CHECK(rb.empty());
  CHECK(!rb.full());
  CHECK(rb.size() == 0);
  CHECK(rb.capacity() == 4);

  CHECK(rb.push(10));
  CHECK(rb.push(20));
  CHECK(rb.push(30));
  CHECK(rb.push(40));
  CHECK(rb.full());
  CHECK(!rb.push(99)); // rejected when full

  int v;
  CHECK(rb.pop(v) && v == 10); // FIFO order
  CHECK(rb.pop(v) && v == 20);
  CHECK(rb.pop(v) && v == 30);
  CHECK(rb.pop(v) && v == 40);
  CHECK(rb.empty());
  CHECK(!rb.pop(v)); // empty pop returns false
}

void test_wrap_around() {
  RingBuffer<int, 4> rb;
  rb.push(1);
  rb.push(2);
  rb.push(3);

  int v;
  rb.pop(v);
  rb.pop(v); // head advances to 2

  rb.push(4);
  rb.push(5); // tail wraps: slots 3, 0
  rb.push(6); // tail = 1 — full

  CHECK(rb.full());
  // Read out in FIFO order: 3, 4, 5, 6
  rb.pop(v);
  CHECK(v == 3);
  rb.pop(v);
  CHECK(v == 4);
  rb.pop(v);
  CHECK(v == 5);
  rb.pop(v);
  CHECK(v == 6);
  CHECK(rb.empty());
}

void test_peek() {
  RingBuffer<int, 4> rb;
  rb.push(7);
  int v;
  CHECK(rb.peek(v) && v == 7);
  CHECK(rb.size() == 1); // peek must not remove

  auto opt = rb.peek();
  CHECK(opt && *opt == 7);
}

void test_optional_pop() {
  RingBuffer<std::string, 4> rb;
  rb.push(std::string("hello"));
  auto r = rb.pop();
  CHECK(r && *r == "hello");
  CHECK(!rb.pop()); // returns nullopt
}

void test_emplace() {
  struct Point {
    int x, y;
  };
  RingBuffer<Point, 4> rb;
  CHECK(rb.emplace(3, 7));
  Point p;
  CHECK(rb.pop(p) && p.x == 3 && p.y == 7);
}

void test_push_overwrite() {
  RingBuffer<int, 4> rb;
  rb.push(1);
  rb.push(2);
  rb.push(3);
  rb.push(4);           // full
  rb.push_overwrite(5); // evicts 1, writes 5
  rb.push_overwrite(6); // evicts 2, writes 6

  int v;
  rb.pop(v);
  CHECK(v == 3);
  rb.pop(v);
  CHECK(v == 4);
  rb.pop(v);
  CHECK(v == 5);
  rb.pop(v);
  CHECK(v == 6);
  CHECK(rb.empty());
}

void test_move_push() {
  RingBuffer<std::string, 4> rb;
  std::string s = "moved";
  CHECK(rb.push(std::move(s)));
  CHECK(s.empty() || true); // moved-from state is valid but unspecified
  std::string out;
  CHECK(rb.pop(out) && out == "moved");
}

void test_random_access_and_iteration() {
  RingBuffer<int, 8> rb;
  rb.push(10);
  rb.push(20);
  rb.push(30);

  CHECK(rb[0] == 10);
  CHECK(rb[1] == 20);
  CHECK(rb[2] == 30);

  int sum = 0;
  for (auto &x : rb)
    sum += x;
  CHECK(sum == 60);
}

void test_clear() {
  RingBuffer<int, 4> rb;
  rb.push(1);
  rb.push(2);
  rb.clear();
  CHECK(rb.empty());
  CHECK(rb.size() == 0);
  CHECK(rb.push(99)); // usable after clear
}

// ─────────────────────────────────────────────────────────────────────────────
// SPSCRingBuffer — multi-threaded producer / consumer
// ─────────────────────────────────────────────────────────────────────────────

void test_spsc_basic() {
  SPSCRingBuffer<int, 4> rb;
  // capacity is N-1 = 3 (one slot kept empty as sentinel)
  CHECK(rb.empty());
  CHECK(!rb.full());

  CHECK(rb.push(1));
  CHECK(rb.push(2));
  CHECK(rb.push(3));
  CHECK(rb.full());
  CHECK(!rb.push(4)); // rejected

  int v;
  CHECK(rb.pop(v) && v == 1);
  CHECK(rb.pop(v) && v == 2);
  CHECK(rb.pop(v) && v == 3);
  CHECK(rb.empty());
  CHECK(!rb.pop(v));
}

void test_spsc_threaded() {
  constexpr int MSGS = 100'000;
  SPSCRingBuffer<int, 1024> rb;

  std::thread producer([&] {
    for (int i = 0; i < MSGS; ++i) {
      while (!rb.push(i)) { /* spin */
      }
    }
  });

  std::thread consumer([&] {
    int expected = 0;
    while (expected < MSGS) {
      int v;
      if (rb.pop(v)) {
        assert(v == expected && "SPSC ordering violated");
        ++expected;
      }
    }
  });

  producer.join();
  consumer.join();
  ++pass_count; // if we reach here without assertion failure, it passed
}

// ─────────────────────────────────────────────────────────────────────────────
// main
// ─────────────────────────────────────────────────────────────────────────────

int main() {
  std::puts("Running ring buffer tests...\n");

  std::puts("── RingBuffer (single-threaded) ──");
  test_basic();
  std::puts("  basic              OK");
  test_wrap_around();
  std::puts("  wrap-around        OK");
  test_peek();
  std::puts("  peek               OK");
  test_optional_pop();
  std::puts("  optional pop       OK");
  test_emplace();
  std::puts("  emplace            OK");
  test_push_overwrite();
  std::puts("  push_overwrite     OK");
  test_move_push();
  std::puts("  move push          OK");
  test_random_access_and_iteration();
  std::puts("  random access     OK");
  test_clear();
  std::puts("  clear              OK");

  std::puts("\n── SPSCRingBuffer (lock-free) ──");
  test_spsc_basic();
  std::puts("  spsc basic         OK");
  test_spsc_threaded();
  std::puts("  spsc threaded      OK");

  std::printf("\nAll %d checks passed.\n", pass_count);
  return 0;
}
