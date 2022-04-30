#pragma once
#include "../number/dual_number.hpp"
#include <algorithm>
#include <cassert>
#include <vector>

// Solve Ax = b, where A is n x n (square), lower Hessenberg, and non-singular.
// Complexity: O(n^2)
// Verified: https://atcoder.jp/contests/abc249/tasks/abc249_h
template <class T>
std::vector<T>
solve_lower_hessenberg(const std::vector<std::vector<T>> &A, const std::vector<T> &b) {
    const int N = A.size();
    if (!N) return {};
    assert(int(A[0].size()) == N and int(b.size()) == N);

    using dual = DualNumber<T>;
    std::vector<dual> sol(N);
    for (int h = 0; h < N;) {
        sol[h] = dual(0, 1);
        for (int i = h;; ++i) {
            dual y = b[i];
            for (int j = 0; j <= i; ++j) y -= sol[j] * A[i][j];
            T a = i + 1 < N ? A[i][i + 1] : T();
            if (a == T()) {
                T x0 = y.root();
                while (h <= i) sol[h] = sol[h].eval(x0), ++h;
                break;
            } else {
                sol[i + 1] = y / a;
            }
        }
    }
    std::vector<T> ret(N);
    for (int i = 0; i < N; ++i) ret[i] = sol[i].a;
    return ret;
}

// Solve Ax = b, where A is n x n (square), upper Hessenberg, and non-singular
// Complexity: O(n^2)
template <class T>
std::vector<T> solve_upper_hessenberg(std::vector<std::vector<T>> A, std::vector<T> b) {
    std::reverse(A.begin(), A.end());
    for (auto &v : A) std::reverse(v.begin(), v.end());
    std::reverse(b.begin(), b.end());
    auto ret = solve_lower_hessenberg(A, b);
    std::reverse(ret.begin(), ret.end());
    return ret;
}
