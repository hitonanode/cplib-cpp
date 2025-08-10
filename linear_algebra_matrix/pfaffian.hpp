#pragma once

#include <utility>
#include <vector>

// Calculate Pfaffian of Matrix
// requirement: T is field, M is skew-symmetric
// Complexity: O(n^3)
// Implementation is based on Nachia-san's submission https://judge.yosupo.jp/submission/278787
template <class T> T Pfaffian(const std::vector<std::vector<T>> &M) {
    const int n = M.size();
    if (n % 2) return T{};

    auto mat = M;
    T res{1};

    for (int s = 0; s < n; s += 2) {
        {
            int t = s + 1;
            while (t < n and mat[s][t] == T{}) ++t;
            if (t == n) return T{};

            if (t != s + 1) {
                for (int i = s; i < n; ++i) std::swap(mat[s + 1][i], mat[t][i]);
                for (int i = s; i < n; ++i) std::swap(mat[i][s + 1], mat[i][t]);
                res = -res;
            }
        }

        res *= mat[s][s + 1];

        const T w = mat[s][s + 1].inv();

        for (int i = s + 1; i < n; ++i) mat[s][i] *= w;
        for (int i = s + 1; i < n; ++i) mat[i][s] *= w;

        // mat[s+2:, s+2:] += mat[:, s] ^ mat[s + 1, :]
        for (int i = s + 2; i < n; ++i) {
            for (int j = s + 2; j < n; ++j) {
                // mat[i][j] += mat[i][s] * mat[s + 1][j] - mat[i][s + 1] * mat[s][j];
                mat[i][j] += mat[s + 1][i] * mat[s][j] - mat[s][i] * mat[s + 1][j];
            }
        }
    }

    return res;
}
