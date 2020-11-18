#pragma once
#include <numeric>
#include <utility>
#include <vector>

// CUT begin
// Weighted UnionFind
template <typename T> struct WeightedUnionFind {
    std::vector<int> par, sz;
    std::vector<T> pot;
    WeightedUnionFind(int N = 0) : par(N), sz(N, 1), pot(N) { std::iota(par.begin(), par.end(), 0); }
    int find(int x) {
        if (par[x] != x) {
            int r = find(par[x]);
            pot[x] = pot[x] + pot[par[x]], par[x] = r;
        }
        return par[x];
    }
    bool unite(int s, int t, T rel_diff) {
        // Relate s and t by t = s + rel_diff
        // Return false iff contradiction happens.
        rel_diff = rel_diff + weight(s) + (-weight(t));
        if ((s = find(s)) == (t = find(t))) return rel_diff == 0;
        if (sz[s] < sz[t]) std::swap(s, t), rel_diff = -rel_diff;
        par[t] = s, sz[s] += sz[t], pot[t] = rel_diff;
        return true;
    }
    T weight(int x) {
        find(x);
        return pot[x];
    }
    T diff(int s, int t) { return weight(t) + (-weight(s)); }
    int count(int x) { return sz[find(x)]; }
    bool same(int s, int t) { return find(s) == find(t); }
};

// sample data structure T for WeightedUnionFind<T>
/*
struct Monoid {
    int data;
    Monoid() : data(0) {}
    Monoid(int d) : data(d) {}
    Monoid operator+(const Monoid &x) const { return Monoid(this->data + x.data); }
    Monoid operator-() const { return Monoid(-data); }
    bool operator==(const Monoid &x) const { return data == x.data; }
};
WeightedUnionFind<Monoid> wuf(10000);
*/
