#pragma once
#include "../formal_power_series/linear_recurrence.hpp"
#include <chrono>
#include <random>
#include <vector>

template <typename ModInt> std::vector<ModInt> gen_random_vector(int len) {
    static std::mt19937 mt(std::chrono::steady_clock::now().time_since_epoch().count());
    static std::uniform_int_distribution<int> rnd(1, ModInt::mod() - 1);
    std::vector<ModInt> ret(len);
    for (auto &x : ret) x = rnd(mt);
    return ret;
};

// Probabilistic algorithm to find a solution of linear equation Ax = b if exists.
// Complexity: O(n T(n) + n^2)
// Reference:
// [1] W. Eberly, E. Kaltofen, "On randomized Lanczos algorithms," Proc. of international symposium on
//     Symbolic and algebraic computation, 176-183, 1997.
template <typename Matrix, typename T>
std::vector<T> linear_system_solver_lanczos(const Matrix &A, const std::vector<T> &b) {
    assert(A.height() == int(b.size()));
    const int M = A.height(), N = A.width();

    const std::vector<T> D1 = gen_random_vector<T>(N), D2 = gen_random_vector<T>(M),
                         v = gen_random_vector<T>(N);
    auto applyD1 = [&D1](std::vector<T> v) {
        for (int i = 0; i < int(v.size()); i++) v[i] *= D1[i];
        return v;
    };
    auto applyD2 = [&D2](std::vector<T> v) {
        for (int i = 0; i < int(v.size()); i++) v[i] *= D2[i];
        return v;
    };
    auto applyAtilde = [&](std::vector<T> v) -> std::vector<T> {
        v = applyD1(v);
        v = A.prod(v);
        v = applyD2(v);
        v = A.prod_left(v);
        v = applyD1(v);
        return v;
    };
    auto dot = [&](const std::vector<T> &vl, const std::vector<T> &vr) -> T {
        return std::inner_product(vl.begin(), vl.end(), vr.begin(), T(0));
    };
    auto scalar_vec = [&](const T &x, std::vector<T> vec) -> std::vector<T> {
        for (auto &v : vec) v *= x;
        return vec;
    };

    auto btilde1 = applyD1(A.prod_left(applyD2(b))), btilde2 = applyAtilde(v);
    std::vector<T> btilde(N);
    for (int i = 0; i < N; i++) btilde[i] = btilde1[i] + btilde2[i];

    std::vector<T> w0 = btilde, v1 = applyAtilde(w0);
    std::vector<T> wm1(w0.size()), v0(v1.size());
    T t0 = dot(v1, w0), gamma = dot(btilde, w0) / t0, tm1 = 1;
    std::vector<T> x = scalar_vec(gamma, w0);
    while (true) {
        if (!t0 or !std::count_if(w0.begin(), w0.end(), [](T x) { return x != T(0); })) break;
        T alpha = dot(v1, v1) / t0, beta = dot(v1, v0) / tm1;
        std::vector<T> w1(N);
        for (int i = 0; i < N; i++) w1[i] = v1[i] - alpha * w0[i] - beta * wm1[i];
        std::vector<T> v2 = applyAtilde(w1);
        T t1 = dot(w1, v2);
        gamma = dot(btilde, w1) / t1;
        for (int i = 0; i < N; i++) x[i] += gamma * w1[i];

        wm1 = w0, w0 = w1;
        v0 = v1, v1 = v2;
        tm1 = t0, t0 = t1;
    }
    for (int i = 0; i < N; i++) x[i] -= v[i];
    return applyD1(x);
}

// Probabilistic algorithm to calculate determinant of matrices
// Complexity: O(n T(n) + n^2)
// Reference:
// [1] D. H. Wiedmann, "Solving sparse linear equations over finite fields,"
//     IEEE Trans. on Information Theory, 32(1), 54-62, 1986.
template <class Matrix, class Tp> Tp blackbox_determinant(const Matrix &M) {
    assert(M.height() == M.width());
    const int N = M.height();
    std::vector<Tp> b = gen_random_vector<Tp>(N), u = gen_random_vector<Tp>(N),
                    D = gen_random_vector<Tp>(N);
    std::vector<Tp> uMDib(2 * N);
    for (int i = 0; i < 2 * N; i++) {
        uMDib[i] = std::inner_product(u.begin(), u.end(), b.begin(), Tp(0));
        for (int j = 0; j < N; j++) b[j] *= D[j];
        b = M.prod(b);
    }
    auto ret = find_linear_recurrence<Tp>(uMDib);
    Tp det = ret.second.back() * (N % 2 ? -1 : 1);
    Tp ddet = 1;
    for (auto d : D) ddet *= d;
    return det / ddet;
}

// Complexity: O(n T(n) + n^2)
template <class Matrix, class Tp>
std::vector<Tp> reversed_minimal_polynomial_of_matrix(const Matrix &M) {
    assert(M.height() == M.width());
    const int N = M.height();
    std::vector<Tp> b = gen_random_vector<Tp>(N), u = gen_random_vector<Tp>(N);
    std::vector<Tp> uMb(2 * N);
    for (int i = 0; i < 2 * N; i++) {
        uMb[i] = std::inner_product(u.begin(), u.end(), b.begin(), Tp());
        b = M.prod(b);
    }
    auto ret = find_linear_recurrence<Tp>(uMb);
    return ret.second;
}

// Calculate A^k b
// Complexity: O(n^2 log k + n T(n))
// Verified: https://www.codechef.com/submit/COUNTSEQ2
template <class Matrix, class Tp>
std::vector<Tp> blackbox_matrix_pow_vec(const Matrix &A, long long k, std::vector<Tp> b) {
    assert(A.width() == int(b.size()));
    assert(k >= 0);

    std::vector<Tp> rev_min_poly = reversed_minimal_polynomial_of_matrix<Matrix, Tp>(A);
    std::vector<Tp> remainder = monomial_mod_polynomial<Tp>(k, rev_min_poly);

    std::vector<Tp> ret(b.size());
    for (Tp c : remainder) {
        for (int d = 0; d < int(b.size()); ++d) ret[d] += b[d] * c;
        b = A.prod(b);
    }
    return ret;
}
