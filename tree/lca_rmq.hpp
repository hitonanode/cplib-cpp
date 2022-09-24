#pragma once
#include "../sparse_table/rmq_sparse_table.hpp"
#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

struct TreeLCA {
    const int N;
    std::vector<std::vector<int>> to;
    int root;
    TreeLCA(int V = 0) : N(V), to(V), root(-1) {}

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
    void build(int root_) {
        assert(root_ >= 0 and root_ < N);
        if (root == root_) return;
        root = root_;
        subtree_begin.assign(N, 0);
        vis_order.clear();
        vis_order.reserve(N * 2);
        depth.assign(N, 0);
        _build_dfs(root, -1, 0);
        rmq = {vis_order, P{N, -1}};
    }

    bool built() const noexcept { return root >= 0; }

    int lca(int u, int v) const {
        assert(0 <= u and u < N);
        assert(0 <= v and v < N);
        assert(built());

        int a = subtree_begin[u], b = subtree_begin[v];
        if (a > b) std::swap(a, b);
        return rmq.get(a, b + 1).second;
    };

    int path_length(int u, int v) const { return depth[u] + depth[v] - depth[lca(u, v)] * 2; }
};
