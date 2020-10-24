#pragma once
#include <cassert>
#include <vector>

// CUT begin
// Fast Walsh-Hadamard transform
// Tutorials: <https://codeforces.com/blog/entry/71899>
//            <https://csacademy.com/blog/fast-fourier-transform-and-variations-of-it>
template <typename T, typename F>
void walsh_hadamard(std::vector<T>& seq, F f)
{
    const int n = seq.size();
    assert(__builtin_popcount(n) == 1);
    for (int w = 1; w < n; w *= 2) {
        for (int i = 0; i < n; i += w * 2) {
            for (int j = 0; j < w; j++) {
                f(seq[i + j], seq[i + j + w]);
            }
        }
    }
}

template <typename T, typename F1, typename F2>
std::vector<T> walsh_hadamard_conv(std::vector<T> x, std::vector<T> y, F1 f, F2 finv)
{
    const int n = x.size();
    assert(__builtin_popcount(n) == 1);
    assert(x.size() == y.size());
    if (x == y) {
        walsh_hadamard(x, f), y = x;
    } else {
        walsh_hadamard(x, f), walsh_hadamard(y, f);
    }
    for (size_t i = 0; i < x.size(); i++) {
        x[i] *= y[i];
    }
    walsh_hadamard(x, finv);
    return x;
}

// bitwise xor convolution
// ret[i] = \sum_j x[j] * y[i ^ j]
// if T is integer, ||x||_1 * ||y||_1 * 2 < numeric_limits<T>::max()
template <typename T>
std::vector<T> xorconv(std::vector<T> x, std::vector<T> y)
{
    auto f = [](T& lo, T& hi) {
        T c = lo + hi;
        hi = lo - hi, lo = c;
    };
    auto finv = [](T& lo, T& hi) {
        T c = lo + hi;
        hi = (lo - hi) / 2, lo = c / 2;  // Reconsider high complexity of division when T is ModInt
    };
    return walsh_hadamard_conv(x, y, f, finv);
}

// bitwise and conolution
// ret[i] = \sum_{(j & k) == i} x[j] * y[k]
template <typename T>
std::vector<T> andconv(std::vector<T> x, std::vector<T> y)
{
    return walsh_hadamard_conv(
        x, y, [](T& lo, T& hi) { lo += hi; }, [](T& lo, T& hi) { lo -= hi; });
}

// bitwise or convolution
// ret[i] = \sum_{(j | k) == i} x[j] * y[k]
template <typename T>
std::vector<T> orconv(std::vector<T> x, std::vector<T> y)
{
    return walsh_hadamard_conv(
        x, y, [](T& lo, T& hi) { hi += lo; }, [](T& lo, T& hi) { hi -= lo; });
}
