#pragma once
#include "../formal_power_series/sum_of_exponential_times_polynomial.hpp"
#include "sieve.hpp"
#include <cassert>
#include <cmath>
#include <vector>

// CUT begin
// Dirichlet product (convolution)
// - a[i] = f(i) (1-origin)
// - A[i - 1] = f(1) + ... + f(i)
// - invA[i - 1] = f(1) + ... + f(N / i)
// Reference:
// https://maspypy.com/dirichlet-%e7%a9%8d%e3%81%a8%e3%80%81%e6%95%b0%e8%ab%96%e9%96%a2%e6%95%b0%e3%81%ae%e7%b4%af%e7%a9%8d%e5%92%8c
template <class T> struct arithmetic_cumsum {
    long long N;
    int K, L;
    bool _verify_shape(const arithmetic_cumsum &x) const {
        return N == x.N and K == x.K and L == x.L;
    }

    std::vector<T> a, A, invA;
    arithmetic_cumsum(long long N_) : N(N_) {
        K = ceill(std::max(sqrtl(N_), powl(N_ / (N_ > 1 ? log2l(N_) : 1.), 2.0 / 3)));
        L = (N_ + K - 1) / K;
        a.resize(K), A.resize(K), invA.resize(L);
    }
    T at(int i) const { // a[i]
        assert(i >= 1 and i <= K);
        return a[i - 1];
    }
    T sum(long long i) const { // a[1] + ... + a[i]
        assert(i >= 1 and i <= N);
        if (i <= K) return A[i - 1];
        long long j = N / i;
        assert(j >= 1 and j <= L);
        return invA[j - 1];
    }

    arithmetic_cumsum operator+(const arithmetic_cumsum &x) const {
        assert(N == x.N and K == x.K and L == x.L);
        auto ret = *this;
        for (int i = 0; i < ret.K; ++i) {
            ret.a[i] += x.a[i];
            ret.A[i] += x.A[i];
        }
        for (int i = 0; i < ret.L; ++i) ret.invA[i] += x.invA[i];
        return ret;
    }

    arithmetic_cumsum operator-(const arithmetic_cumsum &x) const {
        assert(N == x.N and K == x.K and L == x.L);
        auto ret = *this;
        for (int i = 0; i < ret.K; ++i) {
            ret.a[i] -= x.a[i];
            ret.A[i] -= x.A[i];
        }
        for (int i = 0; i < ret.L; ++i) ret.invA[i] -= x.invA[i];
        return ret;
    }
    // Dirichlet product (convolution)
    arithmetic_cumsum operator*(const arithmetic_cumsum &y) const {
        assert(_verify_shape(y));
        const arithmetic_cumsum &x = *this;
        arithmetic_cumsum ret(x.N);
        for (int i = 1; i <= x.K; ++i) {
            for (int j = 1; i * j <= x.K; ++j) ret.a[i * j - 1] += x.at(i) * y.at(j);
        }
        ret.A = ret.a;
        for (int i = 1; i < ret.K; i++) ret.A[i] += ret.A[i - 1];

        for (int l = 1; l <= x.L; ++l) {
            const long long n = x.N / l;
            long long i = 1;
            for (; i * i <= n; ++i) {
                ret.invA[l - 1] += x.at(i) * y.sum(n / i) + x.sum(n / i) * y.at(i);
            }
            ret.invA[l - 1] -= x.sum(i - 1) * y.sum(i - 1);
        }
        return ret;
    }

    bool operator==(const arithmetic_cumsum &y) const {
        return _verify_shape(y) and a == y.a and A == y.A and invA == y.invA;
    }

    arithmetic_cumsum operator/(const arithmetic_cumsum &y) const { // Division (*this) / y
        assert(_verify_shape(y));
        const arithmetic_cumsum &x = *this;
        arithmetic_cumsum ret(x.N);
        assert(y.at(1) != 0);
        const auto y1inv = 1 / y.at(1);
        ret.a = x.a;
        for (int i = 1; i <= x.K; ++i) {
            ret.a[i - 1] *= y1inv;
            for (int j = 2; i * j <= x.K; ++j) ret.a[i * j - 1] -= ret.at(i) * y.at(j);
        }
        ret.A = ret.a;
        for (int i = 2; i <= x.K; ++i) ret.A[i - 1] += ret.A[i - 2];

        for (int l = x.L; l; --l) {
            const long long n = x.N / l;
            if (n <= K) {
                ret.invA[l - 1] = ret.sum(n);
            } else {
                ret.invA[l - 1] = 0;
                long long i = 1;
                T tmp = 0;
                for (; i * i <= n; ++i) {
                    tmp += y.at(i) * ret.sum(n / i) + y.sum(n / i) * ret.at(i);
                }
                tmp -= y.sum(i - 1) * ret.sum(i - 1);
                ret.invA[l - 1] = (x.sum(n) - tmp) * y1inv;
            }
        }
        return ret;
    }

    static arithmetic_cumsum identity(long long n) { // [1, 0, ..., 0]
        arithmetic_cumsum ret(n);
        ret.a[0] = 1;
        ret.A.assign(ret.K, 1);
        ret.invA.assign(ret.L, 1);
        return ret;
    }
};

// zeta(s) = [1, 1, 1, ...]
template <class T> arithmetic_cumsum<T> zeta_cumsum(long long n) {
    arithmetic_cumsum<T> ret(n);
    ret.a.assign(ret.K, 1);
    for (int k = 1; k <= ret.K; k++) ret.A[k - 1] = k;
    for (int l = 1; l <= ret.L; l++) ret.invA[l - 1] = n / l;
    return ret;
}

// zeta(s - 1) = [1, 2, 3, ...]
template <class T> arithmetic_cumsum<T> zeta_shift_1_cumsum(long long n) {
    arithmetic_cumsum<T> ret(n);
    for (int i = 0; i < ret.K; ++i) {
        ret.a[i] = i + 1;
        ret.A[i] = T(i + 1) * (i + 2) / 2;
    }
    for (int l = 1; l <= ret.L; ++l) {
        T u = n / l;
        ret.invA[l - 1] = u * (u + 1) / 2;
    }
    return ret;
}

// zeta(s - k) = [1^k, 2^k, 3^k, ...]
template <class T> arithmetic_cumsum<T> zeta_shift_cumsum(long long n, int k) {
    if (k == 0) return zeta_cumsum<T>(n);
    if (k == 1) return zeta_shift_1_cumsum<T>(n);
    arithmetic_cumsum<T> ret(n);
    auto init_pows = Sieve(k).enumerate_kth_pows<T>(k, k);
    for (int i = 1; i <= ret.K; ++i) {
        ret.a[i - 1] = T(i).pow(k);
        ret.A[i] = ret.a[i] + (i ? ret.A[i - 1] : 0);
    }
    for (int l = 0; l < ret.L; ++l) {
        ret.invA[l] = sum_of_exponential_times_polynomial<T>(1, init_pows, n / (l + 1) + 1);
    }
    return ret;
}

// Euler totient phi function phi(s) = zeta(s - 1) / zeta(s)
template <class T> arithmetic_cumsum<T> euler_phi_cumsum(long long n) {
    return zeta_shift_1_cumsum<T>(n) / zeta_cumsum<T>(n);
}

// 約数関数の累積和
// sigma_k (n) = \sum_{d \mid n} d^k
template <class T> arithmetic_cumsum<T> divisor_func_cumsum(long long n, int k) {
    return zeta_shift_cumsum<T>(n, k) * zeta_cumsum<T>(n);
}

// Cumulative sum of Moebius function (: Mertens function)
template <class T> arithmetic_cumsum<T> moebius_func_cumsum(long long n) {
    return arithmetic_cumsum<T>::identity(n) / zeta_cumsum<T>(n);
}
