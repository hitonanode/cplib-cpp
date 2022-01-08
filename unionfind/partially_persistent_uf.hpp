#pragma once
#include <map>
#include <utility>
#include <vector>

// CUT begin
// Partially persistent UnionFind
struct PartiallyPersistentUnionFind {
    std::vector<int> parsz, t_unite;
    std::vector<std::map<int, int>> size_history;
    PartiallyPersistentUnionFind(int N) : parsz(N, 1), t_unite(N, 2000000000), size_history(N) {
        for (int i = 0; i < N; i++) size_history[i][-1] = 1;
    }
    int find(int x, int t) {
        return (t_unite[x] > t) ? x : find(parsz[x], t);
    } // 時刻t以下のマージ操作によって定まる親
    void unite(int x, int y, int t) {
        if ((x = find(x, t)) == (y = find(y, t))) return;
        if (parsz[x] < parsz[y]) std::swap(x, y);
        parsz[x] += parsz[y], parsz[y] = x, t_unite[y] = t;
        size_history[x][t] = parsz[x];
    }
    int size(int x, int t) { return prev(size_history[find(x, t)].upper_bound(t))->second; }
    bool same(int x, int y, int t) { return find(x, t) == find(y, t); }
};
