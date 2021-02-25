#pragma once
#include "../sparse_table/rmq_sparse_table.hpp"
#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

struct TreeLCA {
    const int N;
    std::vector<std::vector<int>> to;
    bool built;
    TreeLCA(int V = 0) : N(V), to(V), built(false) {}

    void add_edge(int u, int v) {
        assert(0 <= u and u < N);
        assert(0 <= v and v < N);
        assert(u != v);
        to[u].push_back(v);
        to[v].push_back(u);
    }

    using P = std::pair<int, int>;
    std::vector<int> subtree_begin;
    std::vector<P> vis_order;
    std::vector<int> depth;
    void _build_dfs(int now, int prv, int dnow) {
        subtree_begin[now] = vis_order.size();
        vis_order.emplace_back(dnow, now);
        depth[now] = dnow;
        for (auto &&nxt : to[now]) {
            if (nxt != prv) {
                _build_dfs(nxt, now, dnow + 1);
                vis_order.emplace_back(dnow, now);
            }
        }
    }

    StaticRMQ<P> rmq;
    void build(int root = 0) {
        assert(root >= 0 and root < N);
        built = true;
        subtree_begin.resize(N);
        vis_order.reserve(N * 2);
        depth.resize(N);
        _build_dfs(root, -1, 0);
        rmq = {vis_order, P{N, -1}};
    }

    int lca(int u, int v) {
        assert(0 <= u and u < N);
        assert(0 <= v and v < N);
        if (!built) build();

        auto a = subtree_begin[u], b = subtree_begin[v];
        if (a > b) std::swap(a, b);
        return rmq.get(a, b + 1).second;
    };
};
