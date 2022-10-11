#pragma once
#include <numeric>
#include <tuple>
#include <utility>
#include <vector>

// UnionFind, able to rewind to the previous state by undo()
template <class S> struct undo_dsu {
    std::vector<int> par, cou;
    std::vector<S> weights;
    std::vector<std::tuple<int, int, S>> history;

    explicit undo_dsu(const std::vector<S> &init)
        : par(init.size()), cou(init.size(), 1), weights(init) {
        std::iota(par.begin(), par.end(), 0);
    }
    explicit undo_dsu(int N) : undo_dsu(std::vector<S>(N, S())) {}
    undo_dsu() : undo_dsu(0) {}

    int find(int x) const { return (par[x] == x) ? x : find(par[x]); }
    bool unite(int x, int y) {
        x = find(x), y = find(y);
        if (cou[x] < cou[y]) std::swap(x, y);
        history.emplace_back(y, cou[x], weights[x]);
        return x != y ? par[y] = x, cou[x] += cou[y], weights[x] += weights[y], true : false;
    }

    void set_weight(int x, S w) {
        x = find(x);
        history.emplace_back(x, cou[x], weights[x]);
        weights[x] = w;
    }

    void undo() {
        weights[par[std::get<0>(history.back())]] = std::get<2>(history.back());
        cou[par[std::get<0>(history.back())]] = std::get<1>(history.back());
        par[std::get<0>(history.back())] = std::get<0>(history.back());
        history.pop_back();
    }

    void reset() {
        while (!history.empty()) undo();
    }

    int count(int x) const { return cou[find(x)]; }

    const S &sum(int x) const { return weights[find(x)]; }

    bool same(int x, int y) const { return find(x) == find(y); }
};
