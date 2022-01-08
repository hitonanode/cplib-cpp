#pragma once
#include <deque>

// CUT begin
// Deque keeping (up to 2nd order) moment
// m0 = \sum_i ai, m1 = \sum_i (i * ai), m2 = \sum_i (i^2 * ai)
// Verify: <https://atcoder.jp/contests/otemae2019/submissions/17097802>
// Be careful for overflow
template <typename DTYPE_DEQUE> struct deque_momentum {
    std::deque<DTYPE_DEQUE> deq;
    DTYPE_DEQUE m0, m1, m2;
    deque_momentum() : m0(0), m1(0), m2(0) {}

    int size() const { return int(deq.size()); }
    DTYPE_DEQUE front() const {
        return deq.front();
    } // `front() const` => `&front()` makes faster, but unsafe.
    DTYPE_DEQUE back() const { return deq.back(); }
    void push_back(DTYPE_DEQUE x) noexcept {
        m0 += x;
        long long i = size();
        m1 += x * i;
        m2 += x * i * i; // be careful for overflow
        deq.push_back(x);
    }
    void pop_back() {
        DTYPE_DEQUE x = back();
        deq.pop_back();
        long long i = size();
        m0 -= x;
        m1 -= x * i;
        m2 -= x * i * i; // be careful for overflow
    }
    void push_front(DTYPE_DEQUE x) noexcept {
        m2 += m1 * 2 + m0;
        m1 += m0;
        m0 += x;
        deq.push_front(x);
    }
    void pop_front() {
        DTYPE_DEQUE x0 = front();
        m2 -= m1 * 2 - m0 + x0;
        m1 -= m0 - x0;
        m0 -= x0;
        deq.pop_front();
    }
};
