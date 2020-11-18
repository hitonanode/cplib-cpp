#pragma once
#include "sparse_table/sparse_table.hpp"
#include <cassert>
#include <vector>

// CUT begin
// Static matrix sparse table
// Complexity; O(HWlogHlogW) for precalculation, O(1) per query
template <typename T, typename F> struct SparseTable2D {
    int H, lgH, W;
    T defaultT;
    F func;
    std::vector<std::vector<SparseTable<T, F>>> data;
    std::vector<int> lgx_table;
    SparseTable2D(F func) : func(func) {}
    SparseTable2D(const std::vector<std::vector<T>> &matrix, T defaultT, F func) : defaultT(defaultT), func(func) {
        H = matrix.size(), W = (matrix.size() ? matrix[0].size() : 0);
        lgx_table.resize(H + 1);
        for (int i = 2; i < H + 1; i++) lgx_table[i] = lgx_table[i >> 1] + 1;
        lgH = lgx_table[H] + 1;
        data.resize(lgH);
        for (auto v : matrix) data[0].emplace_back(SparseTable<T, F>(v, defaultT, func));
        for (int d = 1; d < lgH; d++) {
            for (int i = 0; i + (1 << d) <= H; i++) {
                std::vector<T> v(W);
                for (int j = 0; j < W; j++) v[j] = func(data[d - 1][i].data[0][j], data[d - 1][i + (1 << (d - 1))].data[0][j]);
                data[d].emplace_back(SparseTable<T, F>(v, defaultT, func));
            }
        }
    }
    T get(int xl, int xr, int yl, int yr) {
        assert(xl >= 0 and xr <= H and yl >= 0 and yr <= W);
        if (xl >= xr) return defaultT;
        int d = lgx_table[xr - xl];
        return func(data[d][xl].get(yl, yr), data[d][xr - (1 << d)].get(yl, yr));
    }
};
