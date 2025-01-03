#pragma once
#include <cassert>
#include <vector>

// Preorder tree DFS
// 木を DFS して行きがけ順に頂点を保持する．
// 木を区間に変換する．部分木を構成する頂点は連続して現れるので，部分木の頂点クエリ等に有用．
// heavy_light_decomposition が上位互換
struct preorder_tree_dfs {
    int n; // # of vertices of tree
    int root;
    std::vector<int> subtree_begin, subtree_end;
    std::vector<int> vis_order;

    void _build_dfs(int now, const std::vector<std::vector<int>> &to) {
        subtree_begin[now] = vis_order.size();
        vis_order.push_back(now);
        for (auto nxt : to[now]) {
            if (subtree_begin[nxt] == -1) _build_dfs(nxt, to);
        }
        subtree_end[now] = vis_order.size();
    }

    preorder_tree_dfs() = default;

    preorder_tree_dfs(const std::vector<std::vector<int>> &to, int root)
        : n(to.size()), root(root), subtree_begin(n, -1), subtree_end(n, -1) {
        _build_dfs(root, to);
    }
};
