#pragma once
#include <cassert>
#include <algorithm>
#include <vector>

// CUT begin
// Disjoint sparse table
// <https://discuss.codechef.com/t/tutorial-disjoint-sparse-table/17404>
// <https://drken1215.hatenablog.com/entry/2018/09/08/162600>
// Complexity: O(NlogN) for precalculation, O(1) per query
// - get(l, r): return op(x_l, ..., x_{r - 1})
template <typename T, typename F>
struct DisjointSparseTable
{
    int N, sz;
    F f;
    std::vector<std::vector<T>> data;
    static int _msb(int x) noexcept
    {
        return x == 0 ? 0 : (__builtin_clz(x) ^ 31);
    }
    DisjointSparseTable() = default;
    DisjointSparseTable(const std::vector<T> &seq, F op) : N(seq.size()), f(op)
    {
        sz = 1 << (_msb(N - 1) + 1);
        data.assign(_msb(sz) + 1, std::vector<T>(sz));
        std::copy(seq.begin(), seq.end(), data[0].begin());

        for (int h = 1, half = 2; half < N; h++, half <<= 1)
        {
            for (int i = half; i < sz; i += half * 2)
            {
                data[h][i - 1] = data[0][i - 1];
                for (int j = i - 2; j >= i - half; j--)
                {
                    data[h][j] = f(data[0][j], data[h][j + 1]);
                }
                data[h][i] = data[0][i];
                for (int j = i + 1; j < i + half; j++)
                {
                    data[h][j] = f(data[h][j - 1], data[0][j]);
                }
            }
        }
    }
    // [l, r), 0-indexed
    T get(int l, int r)
    {
        assert(l >= 0 and r <= N and l < r);
        if (l + 1 == r) return data[0][l];
        int h = _msb(l ^ (r - 1));
        return f(data[h][l], data[h][r - 1]);
    }
};
