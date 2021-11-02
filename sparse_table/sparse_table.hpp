#pragma once
#include <cassert>
#include <vector>

// CUT begin
// Static sequence sparse table
// Complexity: O(NlogN) for precalculation, O(1) per query
template <class S, S (*op)(S, S), S (*e)()> struct sparse_table {
    int N, lgN;
    std::vector<std::vector<S>> d;
    std::vector<int> lgx_table;
    sparse_table() {}
    sparse_table(const std::vector<S> &sequence) : N(sequence.size()) {
        lgx_table.resize(N + 1);
        for (int i = 2; i < N + 1; ++i) lgx_table[i] = lgx_table[i >> 1] + 1;
        lgN = lgx_table[N] + 1;
        d.assign(lgN, std::vector<S>(N, e()));
        d[0] = sequence;
        for (int h = 1; h < lgN; ++h) {
            for (int i = 0; i + (1 << h) <= N; ++i) {
                d[h][i] = op(d[h - 1][i], d[h - 1][i + (1 << (h - 1))]);
            }
        }
    }
    S prod(int l, int r) const { // [l, r), 0-indexed
        assert(l >= 0 and r <= N);
        if (l >= r) return e();
        int h = lgx_table[r - l];
        return op(d[h][l], d[h][r - (1 << h)]);
    }
};
