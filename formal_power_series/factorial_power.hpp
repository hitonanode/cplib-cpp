#pragma once
#include "../convolution/ntt.hpp"
#include <algorithm>
#include <vector>

// CUT begin
// Convert factorial power -> sampling
// [y[0], y[1], ..., y[N - 1]] -> \sum_i a_i x^\underline{i}
// Complexity: O(N log N)
template <class T> std::vector<T> factorial_to_ys(const std::vector<T> &as) {
    const int N = as.size();
    std::vector<T> exp(N, 1);
    for (int i = 1; i < N; i++) exp[i] = T(i).facinv();
    auto ys = nttconv(as, exp);
    ys.resize(N);
    for (int i = 0; i < N; i++) ys[i] *= T(i).fac();
    return ys;
}

// Convert sampling -> factorial power
// [y[0], y[1], ..., y[N - 1]] -> \sum_i a_i x^\underline{i}
// Complexity: O(N log N)
template <class T> std::vector<T> ys_to_factorial(std::vector<T> ys) {
    const int N = ys.size();
    for (int i = 1; i < N; i++) ys[i] *= T(i).facinv();
    std::vector<T> expinv(N, 1);
    for (int i = 1; i < N; i++) expinv[i] = T(i).facinv() * (i % 2 ? -1 : 1);
    auto as = nttconv(ys, expinv);
    as.resize(N);
    return as;
}

// Compute factorial power series of f(x + shift) from that of f(x)
// Complexity: O(N log N)
template <class T> std::vector<T> shift_of_factorial(const std::vector<T> &as, T shift) {
    const int N = as.size();
    std::vector<T> b(N, 1), c(N, 1);
    for (int i = 1; i < N; i++) b[i] = b[i - 1] * (shift - i + 1) * T(i).inv();
    for (int i = 0; i < N; i++) c[i] = as[i] * T(i).fac();
    std::reverse(c.begin(), c.end());
    auto ret = nttconv(b, c);
    ret.resize(N);
    std::reverse(ret.begin(), ret.end());
    for (int i = 0; i < N; i++) ret[i] *= T(i).facinv();
    return ret;
}

// Compute y[c], ..., y[c + width - 1] from y[0], ..., y[N - 1] where y = f(x) is poly of up to (N - 1)-th
// degree Complexity: O(N log N)
template <class T> std::vector<T> shift_of_sampling_points(const std::vector<T> ys, T c, int width) {
    auto as = ys_to_factorial(ys);
    as = shift_of_factorial(as, c);
    as.resize(width);
    auto ret = factorial_to_ys(as);
    return ret;
}
