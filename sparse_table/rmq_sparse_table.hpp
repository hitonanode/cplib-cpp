#pragma once
#include <algorithm>
#include <cassert>
#include <vector>

// Range Minimum Query for static sequence by sparse table
// Complexity: O(NlogN) for precalculation, O(1) per query
template<typename T>
struct StaticRMQ {
    inline T func(const T &l, const T &r) {
        return std::min<T>(l, r);
    }
    int N, lgN;
    T defaultT;
    std::vector<std::vector<T>> data;
    std::vector<int> lgx_table;
    StaticRMQ(const std::vector<T> &sequence, T defaultT) : N(sequence.size()), defaultT(defaultT)
    {
        lgx_table.resize(N + 1);
        for (int i = 2; i < N + 1; i++) lgx_table[i] = lgx_table[i >> 1] + 1;
        lgN = lgx_table[N] + 1;
        data.assign(lgN, std::vector<T>(N, defaultT));
        data[0] = sequence;
        for (int d = 1; d < lgN; d++) {
            for (int i = 0; i + (1 << d) <= N; i++) {
                data[d][i] = func(data[d - 1][i], data[d - 1][i + (1 << (d - 1))]);
            }
        }
    }
    T get(int l, int r) { // [l, r), 0-indexed
        assert(l >= 0 and r <= N);
        if (l >= r) return defaultT;
        int d = lgx_table[r - l];
        return func(data[d][l], data[d][r - (1 << d)]);
    }
};
