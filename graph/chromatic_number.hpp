#pragma once
#include <numeric>
#include <vector>

// CUT begin
// (vertex) chromatic number: （頂点）彩色数
// Verified: https://judge.yosupo.jp/problem/chromatic_number, https://atcoder.jp/contests/abc187/tasks/abc187_f
// Reference:
// [1] A. Bjorklund and T. Husfeldt, "Inclusion--Exclusion Algorithms for Counting Set Partitions,"
//     2006 47th Annual IEEE Symposium on Foundations of Computer Science (FOCS'06).
// - https://www.slideshare.net/wata_orz/ss-12131479
template <typename MODINT, typename Int> int ChromaticNumber(const std::vector<Int> &edge) {
    const int V = edge.size(), S = 1 << V;
    if (V == 0) return 0;
    std::vector<MODINT> f(S), g(S);
    for (int s = 0; s < S; s++) g[s] = (__builtin_popcount(s) & 1) ? 1 : -1;
    f[0] = 1;
    for (int s = 1; s < S; s++) {
        int i = __builtin_ctz(s);
        f[s] = f[s - (1 << i)] + f[(s - (1 << i)) & ~edge[i]];
    }
    for (int k = 1; k < V; k++) {
        for (int s = 0; s < S; s++) g[s] *= f[s];
        if (std::accumulate(g.begin(), g.end(), MODINT(0)).val) return k;
    }
    return V;
};
