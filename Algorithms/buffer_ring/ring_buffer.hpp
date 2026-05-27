#pragma once

/**
 * ring_buffer.hpp
 *
 * Two ring buffer implementations:
 *
 *   RingBuffer<T, N>        — single-threaded, stack-allocated, full-featured
 *   SPSCRingBuffer<T, N>    — lock-free single-producer / single-consumer
 *
 * Both use a compile-time capacity N (must be a power of 2 for SPSC).
 * Zero heap allocation. Header-only. C++17.
 *
 * Usage:
 *   RingBuffer<int, 8> rb;
 *   rb.push(42);
 *   int v; rb.pop(v);
 *
 *   SPSCRingBuffer<int, 16> spsc;   // producer thread
 *   spsc.push(99);                  // consumer thread
 *   int v; spsc.pop(v);
 */

#include <array>
#include <atomic>
#include <cstddef>
#include <optional>
#include <type_traits>
#include <utility>

// ─────────────────────────────────────────────────────────────────────────────
// 1.  RingBuffer<T, N>  —  single-threaded
// ─────────────────────────────────────────────────────────────────────────────

template <typename T, std::size_t N>
class RingBuffer {
    static_assert(N > 0, "RingBuffer capacity must be > 0");

public:
    // ── Capacity ─────────────────────────────────────────────────────────────

    [[nodiscard]] constexpr std::size_t capacity() const noexcept { return N; }
    [[nodiscard]] std::size_t           size()     const noexcept { return count_; }
    [[nodiscard]] bool                  empty()    const noexcept { return count_ == 0; }
    [[nodiscard]] bool                  full()     const noexcept { return count_ == N; }

    // ── Write ─────────────────────────────────────────────────────────────────

    /**
     * Copy-push. Returns false if the buffer is full (element is not inserted).
     */
    bool push(const T& val) {
        if (full()) return false;
        buf_[tail_] = val;
        tail_       = advance(tail_);
        ++count_;
        return true;
    }

    /**
     * Move-push. Returns false if the buffer is full.
     */
    bool push(T&& val) {
        if (full()) return false;
        buf_[tail_] = std::move(val);
        tail_       = advance(tail_);
        ++count_;
        return true;
    }

    /**
     * In-place construct at the tail slot.
     * Returns false if full; the forwarded args are left intact.
     */
    template <typename... Args>
    bool emplace(Args&&... args) {
        if (full()) return false;
        buf_[tail_] = T{std::forward<Args>(args)...};
        tail_       = advance(tail_);
        ++count_;
        return true;
    }

    /**
     * Overwrite push: if full, silently evict the oldest element and write.
     * Useful for rolling-log / telemetry patterns.
     */
    void push_overwrite(T val) {
        if (full()) {
            head_ = advance(head_);   // evict oldest
        } else {
            ++count_;
        }
        buf_[tail_] = std::move(val);
        tail_       = advance(tail_);
    }

    // ── Read ──────────────────────────────────────────────────────────────────

    /**
     * Dequeue into `out`. Returns false if empty.
     */
    bool pop(T& out) {
        if (empty()) return false;
        out   = std::move(buf_[head_]);
        head_ = advance(head_);
        --count_;
        return true;
    }

    /**
     * Dequeue and return as std::optional. Returns std::nullopt if empty.
     */
    std::optional<T> pop() {
        if (empty()) return std::nullopt;
        T val = std::move(buf_[head_]);
        head_ = advance(head_);
        --count_;
        return val;
    }

    /**
     * Inspect the oldest element without removing it.
     * Returns false if empty.
     */
    bool peek(T& out) const {
        if (empty()) return false;
        out = buf_[head_];
        return true;
    }

    /**
     * Inspect as optional.
     */
    [[nodiscard]] std::optional<T> peek() const {
        if (empty()) return std::nullopt;
        return buf_[head_];
    }

    // ── Drain / reset ─────────────────────────────────────────────────────────

    void clear() noexcept {
        head_ = tail_ = count_ = 0;
    }

    // ── Random access (logical index 0 = oldest) ──────────────────────────────

    T& operator[](std::size_t i) noexcept {
        return buf_[(head_ + i) % N];
    }
    const T& operator[](std::size_t i) const noexcept {
        return buf_[(head_ + i) % N];
    }

    // ── Forward iterator ──────────────────────────────────────────────────────

    struct Iterator {
        RingBuffer* rb;
        std::size_t idx;
        T&          operator*()  const { return rb->buf_[(rb->head_ + idx) % N]; }
        Iterator&   operator++()       { ++idx; return *this; }
        bool        operator!=(const Iterator& o) const { return idx != o.idx; }
    };

    struct ConstIterator {
        const RingBuffer* rb;
        std::size_t       idx;
        const T&          operator*()  const { return rb->buf_[(rb->head_ + idx) % N]; }
        ConstIterator&    operator++()       { ++idx; return *this; }
        bool              operator!=(const ConstIterator& o) const { return idx != o.idx; }
    };

    Iterator      begin()       { return {this, 0}; }
    Iterator      end()         { return {this, count_}; }
    ConstIterator begin() const { return {this, 0}; }
    ConstIterator end()   const { return {this, count_}; }

private:
    std::array<T, N> buf_{};
    std::size_t      head_  = 0;
    std::size_t      tail_  = 0;
    std::size_t      count_ = 0;

    // Modulo advance — compiler replaces with bitwise AND when N is power-of-2.
    static constexpr std::size_t advance(std::size_t idx) noexcept {
        return (idx + 1) % N;
    }
};


// ─────────────────────────────────────────────────────────────────────────────
// 2.  SPSCRingBuffer<T, N>  —  lock-free, single-producer / single-consumer
// ─────────────────────────────────────────────────────────────────────────────
//
// Rules:
//   • Exactly ONE thread calls push() — the "producer".
//   • Exactly ONE thread calls pop()  — the "consumer".
//   • N must be a power of 2 so modulo collapses to a bitwise AND.
//   • One slot is always kept empty as a sentinel (effective capacity = N-1).
//
// Memory ordering rationale:
//   • tail_ is written by the producer and read by the consumer.
//     Producer stores with release; consumer loads with acquire.
//   • head_ is written by the consumer and read by the producer.
//     Consumer stores with release; producer loads with acquire.
//   This ensures that element writes by the producer are visible to the
//   consumer before the tail index update is observed.
//
// ─────────────────────────────────────────────────────────────────────────────

template <typename T, std::size_t N>
class SPSCRingBuffer {
    static_assert(N > 0 && (N & (N - 1)) == 0,
                  "SPSCRingBuffer capacity N must be a power of 2");

public:
    [[nodiscard]] constexpr std::size_t capacity() const noexcept { return N - 1; }

    [[nodiscard]] bool empty() const noexcept {
        return head_.load(std::memory_order_acquire)
            == tail_.load(std::memory_order_acquire);
    }

    [[nodiscard]] bool full() const noexcept {
        return next(tail_.load(std::memory_order_relaxed))
            == head_.load(std::memory_order_acquire);
    }

    // ── Producer side ─────────────────────────────────────────────────────────

    /** Copy-push. Returns false if full. Called only by the producer thread. */
    bool push(const T& val) {
        const std::size_t t = tail_.load(std::memory_order_relaxed);
        const std::size_t nt = next(t);
        if (nt == head_.load(std::memory_order_acquire))
            return false;               // full
        buf_[t] = val;
        tail_.store(nt, std::memory_order_release);
        return true;
    }

    /** Move-push. Returns false if full. Called only by the producer thread. */
    bool push(T&& val) {
        const std::size_t t = tail_.load(std::memory_order_relaxed);
        const std::size_t nt = next(t);
        if (nt == head_.load(std::memory_order_acquire))
            return false;
        buf_[t] = std::move(val);
        tail_.store(nt, std::memory_order_release);
        return true;
    }

    // ── Consumer side ─────────────────────────────────────────────────────────

    /** Dequeue into `out`. Returns false if empty. Called only by consumer thread. */
    bool pop(T& out) {
        const std::size_t h = head_.load(std::memory_order_relaxed);
        if (h == tail_.load(std::memory_order_acquire))
            return false;               // empty
        out = std::move(buf_[h]);
        head_.store(next(h), std::memory_order_release);
        return true;
    }

    /** Dequeue as optional. Called only by consumer thread. */
    std::optional<T> pop() {
        const std::size_t h = head_.load(std::memory_order_relaxed);
        if (h == tail_.load(std::memory_order_acquire))
            return std::nullopt;
        T val = std::move(buf_[h]);
        head_.store(next(h), std::memory_order_release);
        return val;
    }

    /** Peek without removing. Called only by consumer thread. */
    bool peek(T& out) const {
        const std::size_t h = head_.load(std::memory_order_relaxed);
        if (h == tail_.load(std::memory_order_acquire))
            return false;
        out = buf_[h];
        return true;
    }

private:
    // Separate cache lines to prevent false sharing between producer and consumer.
    alignas(64) std::atomic<std::size_t> tail_{0};
    alignas(64) std::atomic<std::size_t> head_{0};
    std::array<T, N>                     buf_{};

    static constexpr std::size_t next(std::size_t idx) noexcept {
        return (idx + 1) & (N - 1);   // power-of-2 fast path
    }
};
