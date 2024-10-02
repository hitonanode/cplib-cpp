#pragma once
#include <numeric>
#include <utility>
#include <vector>

// Potentialized UnionFind (Weighted UnionFind)
template <class S> struct PotentializedUnionFind {
    std::vector<int> par, sz;
    std::vector<S> pot;
    PotentializedUnionFind(int N = 0) : par(N), sz(N, 1), pot(N) {
        std::iota(par.begin(), par.end(), 0);
    }
    int find(int x) {
        if (par[x] != x) {
            int r = find(par[x]);
            pot[x] = pot[x] + pot[par[x]], par[x] = r;
        }
        return par[x];
    }
    bool unite(int s, int t, S rel_diff) {
        // Relate s and t by f[t] = f[s] + rel_diff
        // Return false iff contradiction happens.
        rel_diff = rel_diff + weight(s) + (-weight(t));
        if ((s = find(s)) == (t = find(t))) return rel_diff == 0;
        if (sz[s] < sz[t]) std::swap(s, t), rel_diff = -rel_diff;
        par[t] = s, sz[s] += sz[t], pot[t] = rel_diff;
        return true;
    }
    S weight(int x) { return find(x), pot[x]; }
    S diff(int s, int t) { return weight(t) + (-weight(s)); } // return f[t] - f[s]
    int count(int x) { return sz[find(x)]; }
    bool same(int s, int t) { return find(s) == find(t); }
};
