#pragma once
#include <cassert>
#include <tuple>
#include <vector>

// CUT begin
// Offline sum of linear segments
template <class T> struct offline_sum_of_linear {
    int N;
    std::vector<T> ret;
    std::vector<std::tuple<int, int, T, T>> upds;
    offline_sum_of_linear(int N_) : N(N_), ret(N_) {}

    // Add f0 + df * (x - l) to A[x] for x in [l, r)
    void add_linear(int l, int r, T f0, T df) {
        assert(0 <= l and l <= r and r <= N);
        if (l < r) upds.emplace_back(l, r, f0, df);
    }
    void run() {
        if (upds.empty()) return;
        std::vector<T> tmp(N + 1);
        int l, r;
        T f0, df;
        for (const auto &q : upds) {
            std::tie(l, r, f0, df) = q;
            tmp[l + 1] += df;
            tmp[r] -= df;
        }
        for (int i = 0; i < N; i++) tmp[i + 1] += tmp[i];
        for (const auto &q : upds) {
            std::tie(l, r, f0, df) = q;
            tmp[l] += f0;
            tmp[r] -= f0 + (r - l - 1) * df;
        }
        upds.clear();
        for (int i = 0; i < N; i++) tmp[i + 1] += tmp[i], ret[i] += tmp[i];
    }
    T operator[](int i) {
        assert(0 <= i and i < N);
        return run(), ret[i];
    }
    std::vector<T> vals() { return run(), ret; }
    int size() const { return N; }
    template <class OStream>
    friend OStream &operator<<(OStream &os, const offline_sum_of_linear &x) {
        auto y = x;
        y.run();
        os << '[';
        for (auto v : y.ret) os << v << ',';
        return os << ']';
    }
};
