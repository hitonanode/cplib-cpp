#pragma once
#include <cassert>
#include <vector>

// Binary lifting / `Doubling`
// Complexity: O(NlogN) precalculation / O(logN) per query
// https://atcoder.jp/contests/arc060/submissions/7039451
struct BinaryLifting {
    int N, lgD;

    bool is_valid(int idx) const { return 0 <= idx and idx < N; }

    std::vector<std::vector<int>> mat;
    BinaryLifting() : N(0), lgD(0) {}
    BinaryLifting(const std::vector<int> &to, int lgd = 0) : N(to.size()), lgD(lgd) {
        while ((1LL << lgD) < N) lgD++;
        mat.assign(lgD, std::vector<int>(N));
        mat[0] = to;

        for (int d = 0; d < lgD - 1; d++) {
            for (int i = 0; i < N; i++) {
                mat[d + 1][i] = mat[d][is_valid(mat[d][i]) ? mat[d][i] : i];
            }
        }
    }

    int kth_next(int now, long long k) const {
        assert(k >= 0);
        assert(k < (1LL << lgD));
        for (int d = 0; k and is_valid(now); d++, k >>= 1) {
            if (k & 1) now = mat[d][now];
        }
        return now;
    }

    // Distance from l to [r, \infty)
    // Requirement: mat[0][i] >= r (i = r, r + 1, ...) (monotone)
    int distance(int l, int r) const {
        if (l >= r) return 0;
        int ret = 0;
        for (int d = lgD - 1; d >= 0; d--) {
            if (mat[d][l] < r and is_valid(mat[d][l])) ret += 1 << d, l = mat[d][l];
        }

        if (!is_valid(mat[0][l]) or mat[0][l] >= r) {
            return ret + 1;
        } else {
            return -1; // Unable to reach
        }
    }
};
