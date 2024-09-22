#pragma once
#include <cassert>
#include <vector>

// Fast Walsh-Hadamard transform and its abstraction
// Tutorials: <https://codeforces.com/blog/entry/71899>
//            <https://csacademy.com/blog/fast-fourier-transform-and-variations-of-it>
template <typename T, typename F> void abstract_fwht(std::vector<T> &seq, F f) {
    const int n = seq.size();
    assert(__builtin_popcount(n) == 1);
    for (int w = 1; w < n; w *= 2) {
        for (int i = 0; i < n; i += w * 2) {
            for (int j = 0; j < w; j++) { f(seq[i + j], seq[i + j + w]); }
        }
    }
}

template <typename T, typename F1, typename F2>
std::vector<T> bitwise_conv(std::vector<T> x, std::vector<T> y, F1 f, F2 finv) {
    const int n = x.size();
    assert(__builtin_popcount(n) == 1);
    assert(x.size() == y.size());
    if (x == y) {
        abstract_fwht(x, f), y = x;
    } else {
        abstract_fwht(x, f), abstract_fwht(y, f);
    }
    for (size_t i = 0; i < x.size(); i++) { x[i] *= y[i]; }
    abstract_fwht(x, finv);
    return x;
}

// bitwise xor convolution (FWHT-based)
// ret[i] = \sum_j x[j] * y[i ^ j]
// if T is integer, ||x||_1 * ||y||_1 * 2 < numeric_limits<T>::max()
template <typename T> std::vector<T> xorconv(std::vector<T> x, std::vector<T> y) {
    auto f = [](T &lo, T &hi) {
        T c = lo + hi;
        hi = lo - hi, lo = c;
    };
    auto finv = [](T &lo, T &hi) {
        T c = lo + hi;
        hi = (lo - hi) / 2,
        lo = c / 2; // Reconsider HEAVY complexity of division by 2 when T is ModInt
    };
    return bitwise_conv(x, y, f, finv);
}

// bitwise AND conolution
// ret[i] = \sum_{(j & k) == i} x[j] * y[k]
template <typename T> std::vector<T> andconv(std::vector<T> x, std::vector<T> y) {
    return bitwise_conv(x, y, [](T &lo, T &hi) { lo += hi; }, [](T &lo, T &hi) { lo -= hi; });
}

// bitwise OR convolution
// ret[i] = \sum_{(j | k) == i} x[j] * y[k]
template <typename T> std::vector<T> orconv(std::vector<T> x, std::vector<T> y) {
    return bitwise_conv(x, y, [](T &lo, T &hi) { hi += lo; }, [](T &lo, T &hi) { hi -= lo; });
}
