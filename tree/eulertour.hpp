#pragma once
#include <cassert>
#include <vector>

// CUT begin
// Preorder Euler Tour
// （行きがけ順，部分木の頂点クエリ等に有用）
struct PreorderEulerTour {
    int V; // # of vertices of tree
    int root;
    std::vector<std::vector<int>> edges;
    std::vector<int> subtree_begin, subtree_end;
    std::vector<int> vis_order;

    void _build_dfs(int now, int prv) {
        subtree_begin[now] = vis_order.size();
        vis_order.push_back(now);
        for (auto nxt : edges[now])
            if (nxt != prv) _build_dfs(nxt, now);
        subtree_end[now] = vis_order.size();
    }
    PreorderEulerTour() = default;
    PreorderEulerTour(const std::vector<std::vector<int>> &to, int root)
        : V(to.size()), root(root), edges(to) {
        assert(root >= 0 and root < V);
        subtree_begin.resize(V);
        subtree_end.resize(V);
        _build_dfs(root, -1);
    }
};
