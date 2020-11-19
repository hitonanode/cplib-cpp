#pragma once
#include "../segmenttree/binary_indexed_tree.hpp"
#include <algorithm>
#include <cassert>
#include <numeric>
#include <vector>

// Offline solver to find k-th smallest elements in continuous subsequences
// - Problem statement: <https://judge.yosupo.jp/problem/range_kth_smallest>
// - Complexity: O((N + Q) lg(N + Q))
struct range_kth_smallest {
    int N;
    std::vector<int> idx;
    std::vector<int> QL, QR, QK;
    template <typename T> range_kth_smallest(const std::vector<T> A) : N(A.size()) {
        idx.resize(N);
        std::iota(idx.begin(), idx.end(), 0);
        std::sort(idx.begin(), idx.end(), [&](int l, int r) { return A[l] < A[r]; });
    }

    // Add a query to find (k + 1)-th smallest value in [l, r)
    void add_query(int l, int r, int k) {
        assert(l >= 0 and l <= r and r <= N);
        assert(r - l > k);
        QL.push_back(l), QR.push_back(r), QK.push_back(k);
    }

    // Solve all queries: ret[q] = (position of the K[q]-th smallest element in [L[q], R[q]))
    std::vector<int> _ret_arg;
    std::vector<int> solve() {
        const int Q = QL.size();
        std::vector<int> lo(Q, 0), hi(Q, N);
        std::vector<std::vector<int>> vs(N);
        while (true) {
            bool stop = true;
            for (int q = 0; q < Q; q++) {
                if (lo[q] + 1 < hi[q]) {
                    stop = false;
                    vs[(lo[q] + hi[q]) / 2].emplace_back(q);
                }
            }
            if (stop) break;
            BIT<int> bit(N);
            for (int t = 0; t < N; t++) {
                for (auto q : vs[t]) (bit.sum(QR[q]) - bit.sum(QL[q]) <= QK[q] ? lo[q] : hi[q]) = t;
                bit.add(idx[t] + 1, 1);
                vs[t].clear();
            }
        }
        _ret_arg.resize(Q);
        for (int i = 0; i < Q; i++) _ret_arg[i] = idx[lo[i]];
        return _ret_arg;
    }
};
