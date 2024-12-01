#pragma once
#include <vector>

// Computes the sum of the k-th powers
// Complexity:
// - O(k) per query,
// - O(k^2) precomputation (can be reduced to O(k log k) with FFT)
template <class MODINT> struct kth_power_sum {

    // generating function:  x / (e^x - 1) + x
    // NOTE: use B(1) = 1/2 definition
    std::vector<MODINT> bernoulli;

    kth_power_sum() = default;

    void expand() {
        if (bernoulli.empty()) {
            bernoulli = {1};
        } else {
            const int k = bernoulli.size();
            MODINT x(0);
            for (int i = 0; i < k; ++i) { x = -x + bernoulli[i] * MODINT::binom(k + 1, i); }
            bernoulli.push_back(x / (k + 1));
        }
    }

    // Calculate 1^k + 2^k + ... + n^k
    // Based on Faulhaber's formula:
    // S_k(n) = 1 / (k + 1) * sum_{j=0}^{k} B_j * C(k + 1, j) * n^(k + 1 - j)

    template <class T> MODINT prefix_sum(int k, const T &n) {
        while ((int)bernoulli.size() <= k) expand();

        MODINT ret(0), np(1);
        for (int j = k; j >= 0; --j) {
            np *= n;
            ret += MODINT::binom(k + 1, j) * bernoulli[j] * np;
        }
        return ret / (k + 1);
    }
};
