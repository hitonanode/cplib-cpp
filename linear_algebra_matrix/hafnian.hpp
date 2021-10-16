#pragma once
#include "../set_power_series/subset_convolution.hpp"
#include <vector>

// Count perfect matchings of undirected graph (Hafnian of the matrix)
// Assumption: mat[i][j] == mat[j][i], mat[i][i] == 0
// Complexity: O(n^2 2^n)
// [1] A. Björklund, "Counting Perfect Matchings as Fast as Ryser,
//     Proc. of 23rd ACM-SIAM symposium on Discrete Algorithms, pp.914-921, 2012.
template <class T> T hafnian(const std::vector<std::vector<T>> &mat) {
    const int N = mat.size();
    if (N % 2) return 0;
    std::vector<std::vector<std::vector<T>>> B(N, std::vector<std::vector<T>>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) B[i][j] = std::vector<T>{mat[i][j]};
    }

    std::vector<int> pc(1 << (N / 2));
    std::vector<std::vector<int>> pc2i(N / 2 + 1);
    for (int i = 0; i < int(pc.size()); i++) {
        pc[i] = __builtin_popcount(i);
        pc2i[pc[i]].push_back(i);
    }

    std::vector<T> h{1};
    for (int i = 1; i < N / 2; i++) {
        int r1 = N - i * 2, r2 = r1 + 1;
        auto h_add = subset_convolution(h, B[r2][r1]);
        h.insert(h.end(), h_add.begin(), h_add.end());

        std::vector<std::vector<std::vector<T>>> B1(r1), B2(r1);
        for (int j = 0; j < r1; j++) {
            B1[j] = build_zeta_(i, B[r1][j]);
            B2[j] = build_zeta_(i, B[r2][j]);
        }

        for (int j = 0; j < r1; j++) {
            for (int k = 0; k < j; k++) {
                auto Sijk1 = get_moebius_of_prod_(B1[j], B2[k]);
                auto Sijk2 = get_moebius_of_prod_(B1[k], B2[j]);
                for (int s = 0; s < int(Sijk2.size()); s++) Sijk1[s] += Sijk2[s];
                B[j][k].insert(B[j][k].end(), Sijk1.begin(), Sijk1.end());
            }
        }
    }
    T ret = 0;
    for (int i = 0; i < int(h.size()); i++) ret += h[i] * B[1][0][h.size() - 1 - i];
    return ret;
}
