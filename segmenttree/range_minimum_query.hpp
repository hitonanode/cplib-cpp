#pragma once
#include <iostream>
#include <limits>
#include <vector>

// CUT begin
// Range Minimum Query
// - RangeMinimumQuery<T, defaultT>(int N = 0) : Initialize array x = [defaultT, ..., defaultT] of
// length N, O(N)
// - RangeMinimumQuery<T, defaultT>(const std::vector<T> &vals) : Initialize array x by [vals[0],
// ..., vals[-1]], O(N)
// - update(int pos, T val) : x[pos] <- val, O(log N)
// - get(int begin, int end) : Get min(x_begin, ..., x_(end - 1)), O(log N)
template <typename T, T defaultT = std::numeric_limits<T>::max() / 2> struct RangeMinimumQuery {
    int N;
    int head;
    std::vector<T> x;
    T _get(int begin, int end, int pos, int l, int r) const {
        if (r <= begin or l >= end) return defaultT;
        if (l >= begin and r <= end) return x[pos];
        return std::min(_get(begin, end, 2 * pos + 1, l, (l + r) / 2),
                        _get(begin, end, 2 * pos + 2, (l + r) / 2, r));
    }
    RangeMinimumQuery(int N = 0) : N(N) {
        int N_tmp = 1;
        while (N_tmp < N) N_tmp <<= 1;
        x.assign(N_tmp * 2, defaultT), head = N_tmp - 1;
    }
    void _build(const std::vector<T> &vals) {
        std::copy(vals.begin(), vals.end(), x.begin() + head);
        for (int i = head - 1; i >= 0; i--) x[i] = std::min(x[i * 2 + 1], x[i * 2 + 2]);
    }
    RangeMinimumQuery(const std::vector<T> &vals) : N(vals.size()) {
        int N_tmp = 1;
        while (N_tmp < N) N_tmp <<= 1;
        x.assign(N_tmp * 2, defaultT), head = N_tmp - 1;
        _build(vals);
    }
    void update(int pos, T val) {
        pos += head, x[pos] = val;
        while (pos) pos = (pos - 1) / 2, x[pos] = std::min(x[pos * 2 + 1], x[pos * 2 + 2]);
    }
    T get(int begin, int end) const { return _get(begin, end, 0, 0, (int)x.size() / 2); }
    friend std::ostream &operator<<(std::ostream &os, const RangeMinimumQuery &s) {
        os << '[';
        for (int i = 0; i < s.N; i++) os << s.get(i, i + 1) << ',';
        return os << ']';
    }
};
