#pragma once
#include <numeric>
#include <stack>
#include <utility>
#include <vector>

// CUT begin
// UnionFind, able to rewind to the previous state by undo()
// Written for Educational Codeforces 62 F, although not verified yet.
struct UndoUnionFind {
    using pint = std::pair<int, int>;
    std::vector<int> par, cou;
    std::stack<std::pair<int, pint>> history;
    UndoUnionFind(int N) : par(N), cou(N, 1) { std::iota(par.begin(), par.end(), 0); }
    int find(int x) { return (par[x] == x) ? x : find(par[x]); }
    void unite(int x, int y) {
        x = find(x), y = find(y);
        if (cou[x] < cou[y]) std::swap(x, y);
        history.emplace(y, pint(par[y], cou[x]));
        if (x != y) par[y] = x, cou[x] += cou[y];
    }
    void undo() {
        cou[par[history.top().first]] = history.top().second.second;
        par[history.top().first] = history.top().second.first;
        history.pop();
    }
    void reset() {
        while (!history.empty()) undo();
    }
    int count(int x) { return cou[find(x)]; }
    bool same(int x, int y) { return find(x) == find(y); }
};
