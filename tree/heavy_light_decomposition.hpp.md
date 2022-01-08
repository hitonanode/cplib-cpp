---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: tree/test/hl_decomposition.test.cpp
    title: tree/test/hl_decomposition.test.cpp
  - icon: ':heavy_check_mark:'
    path: tree/test/vertex-add-path-sum.test.cpp
    title: tree/test/vertex-add-path-sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: tree/test/vertex-set-path-composite.test.cpp
    title: tree/test/vertex-set-path-composite.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - http://beet-aizu.hatenablog.com/entry/2017/12/12/235950
  bundledCode: "#line 2 \"tree/heavy_light_decomposition.hpp\"\n#include <algorithm>\n\
    #include <cassert>\n#include <functional>\n#include <queue>\n#include <stack>\n\
    #include <utility>\n#include <vector>\n\n// CUT begin\n// Heavy-Light Decomposition\
    \ of trees\n// Based on http://beet-aizu.hatenablog.com/entry/2017/12/12/235950\n\
    struct HeavyLightDecomposition {\n    int V;\n    int k;\n    int nb_heavy_path;\n\
    \    std::vector<std::vector<int>> e;\n    std::vector<int> par;         // par[i]\
    \ = parent of vertex i (Default: -1)\n    std::vector<int> depth;       // depth[i]\
    \ = distance between root and vertex i\n    std::vector<int> subtree_sz;  // subtree_sz[i]\
    \ = size of subtree whose root is i\n    std::vector<int> heavy_child; // heavy_child[i]\
    \ = child of vertex i on heavy path (Default: -1)\n    std::vector<int> tree_id;\
    \     // tree_id[i] = id of tree vertex i belongs to\n    std::vector<int> aligned_id,\
    \ aligned_id_inv; // aligned_id[i] =  aligned id for vertex i (consecutive on\
    \ heavy edges)\n    std::vector<int> head;          // head[i] = id of vertex\
    \ on heavy path of vertex i, nearest to root\n    std::vector<int> head_ids; \
    \     // consist of head vertex id's\n    std::vector<int> heavy_path_id; // heavy_path_id[i]\
    \ = heavy_path_id for vertex [i]\n\n    HeavyLightDecomposition(int sz = 0)\n\
    \        : V(sz), k(0), nb_heavy_path(0), e(sz), par(sz), depth(sz), subtree_sz(sz),\
    \ heavy_child(sz), tree_id(sz, -1), aligned_id(sz), aligned_id_inv(sz), head(sz),\
    \ heavy_path_id(sz, -1) {}\n    void add_edge(int u, int v) {\n        e[u].emplace_back(v);\n\
    \        e[v].emplace_back(u);\n    }\n\n    void _build_dfs(int root) {\n   \
    \     std::stack<std::pair<int, int>> st;\n        par[root] = -1;\n        depth[root]\
    \ = 0;\n        st.emplace(root, 0);\n        while (!st.empty()) {\n        \
    \    int now = st.top().first;\n            int& i = st.top().second;\n      \
    \      if (i < (int)e[now].size()) {\n                int nxt = e[now][i++];\n\
    \                if (nxt == par[now]) continue;\n                par[nxt] = now;\n\
    \                depth[nxt] = depth[now] + 1;\n                st.emplace(nxt,\
    \ 0);\n            } else {\n                st.pop();\n                int max_sub_sz\
    \ = 0;\n                subtree_sz[now] = 1;\n                heavy_child[now]\
    \ = -1;\n                for (auto nxt : e[now]) {\n                    if (nxt\
    \ == par[now]) continue;\n                    subtree_sz[now] += subtree_sz[nxt];\n\
    \                    if (max_sub_sz < subtree_sz[nxt]) max_sub_sz = subtree_sz[nxt],\
    \ heavy_child[now] = nxt;\n                }\n            }\n        }\n    }\n\
    \n    void _build_bfs(int root, int tree_id_now) {\n        std::queue<int> q({root});\n\
    \        while (!q.empty()) {\n            int h = q.front();\n            q.pop();\n\
    \            head_ids.emplace_back(h);\n            for (int now = h; now != -1;\
    \ now = heavy_child[now]) {\n                tree_id[now] = tree_id_now;\n   \
    \             aligned_id[now] = k++;\n                aligned_id_inv[aligned_id[now]]\
    \ = now;\n                heavy_path_id[now] = nb_heavy_path;\n              \
    \  head[now] = h;\n                for (int nxt : e[now])\n                  \
    \  if (nxt != par[now] and nxt != heavy_child[now]) q.push(nxt);\n           \
    \ }\n            nb_heavy_path++;\n        }\n    }\n\n    void build(std::vector<int>\
    \ roots = {0}) {\n        int tree_id_now = 0;\n        for (auto r : roots) {\n\
    \            _build_dfs(r);\n            _build_bfs(r, tree_id_now++);\n     \
    \   }\n    }\n\n    template <typename Monoid> std::vector<Monoid> segtree_rearrange(const\
    \ std::vector<Monoid>& data) const {\n        assert(int(data.size()) == V);\n\
    \        std::vector<Monoid> ret;\n        ret.reserve(V);\n        for (int i\
    \ = 0; i < V; i++) ret.emplace_back(data[aligned_id_inv[i]]);\n        return\
    \ ret;\n    }\n\n    // query for vertices on path [u, v] (INCLUSIVE)\n    void\
    \ for_each_vertex(int u, int v, const std::function<void(int ancestor, int descendant)>&\
    \ f) const {\n        while (true) {\n            if (aligned_id[u] > aligned_id[v])\
    \ std::swap(u, v);\n            f(std::max(aligned_id[head[v]], aligned_id[u]),\
    \ aligned_id[v]);\n            if (head[u] == head[v]) break;\n            v =\
    \ par[head[v]];\n        }\n    }\n\n    void for_each_vertex_noncommutative(int\
    \ from, int to, const std::function<void(int ancestor, int descendant)>& fup,\
    \ const std::function<void(int ancestor, int descendant)>& fdown) const {\n  \
    \      int u = from, v = to;\n        const int lca = lowest_common_ancestor(u,\
    \ v), dlca = depth[lca];\n        while (u >= 0 and depth[u] > dlca) {\n     \
    \       const int p = (depth[head[u]] > dlca ? head[u] : lca);\n            fup(aligned_id[p]\
    \ + (p == lca), aligned_id[u]), u = par[p];\n        }\n        std::vector<std::pair<int,\
    \ int>> lrs;\n        while (v >= 0 and depth[v] >= dlca) {\n            const\
    \ int p = (depth[head[v]] >= dlca ? head[v] : lca);\n            lrs.emplace_back(p,\
    \ v), v = par[p];\n        }\n        std::reverse(lrs.begin(), lrs.end());\n\
    \        for (const auto& lr : lrs) fdown(aligned_id[lr.first], aligned_id[lr.second]);\n\
    \    }\n\n    // query for edges on path [u, v]\n    void for_each_edge(int u,\
    \ int v, const std::function<void(int, int)>& f) const {\n        while (true)\
    \ {\n            if (aligned_id[u] > aligned_id[v]) std::swap(u, v);\n       \
    \     if (head[u] != head[v]) {\n                f(aligned_id[head[v]], aligned_id[v]);\n\
    \                v = par[head[v]];\n            } else {\n                if (u\
    \ != v) f(aligned_id[u] + 1, aligned_id[v]);\n                break;\n       \
    \     }\n        }\n    }\n\n    // lowest_common_ancestor: O(logV)\n    int lowest_common_ancestor(int\
    \ u, int v) const {\n        assert(tree_id[u] == tree_id[v] and tree_id[u] >=\
    \ 0);\n        while (true) {\n            if (aligned_id[u] > aligned_id[v])\
    \ std::swap(u, v);\n            if (head[u] == head[v]) return u;\n          \
    \  v = par[head[v]];\n        }\n    }\n\n    int distance(int u, int v) const\
    \ {\n        assert(tree_id[u] == tree_id[v] and tree_id[u] >= 0);\n        return\
    \ depth[u] + depth[v] - 2 * depth[lowest_common_ancestor(u, v)];\n    }\n};\n"
  code: "#pragma once\n#include <algorithm>\n#include <cassert>\n#include <functional>\n\
    #include <queue>\n#include <stack>\n#include <utility>\n#include <vector>\n\n\
    // CUT begin\n// Heavy-Light Decomposition of trees\n// Based on http://beet-aizu.hatenablog.com/entry/2017/12/12/235950\n\
    struct HeavyLightDecomposition {\n    int V;\n    int k;\n    int nb_heavy_path;\n\
    \    std::vector<std::vector<int>> e;\n    std::vector<int> par;         // par[i]\
    \ = parent of vertex i (Default: -1)\n    std::vector<int> depth;       // depth[i]\
    \ = distance between root and vertex i\n    std::vector<int> subtree_sz;  // subtree_sz[i]\
    \ = size of subtree whose root is i\n    std::vector<int> heavy_child; // heavy_child[i]\
    \ = child of vertex i on heavy path (Default: -1)\n    std::vector<int> tree_id;\
    \     // tree_id[i] = id of tree vertex i belongs to\n    std::vector<int> aligned_id,\
    \ aligned_id_inv; // aligned_id[i] =  aligned id for vertex i (consecutive on\
    \ heavy edges)\n    std::vector<int> head;          // head[i] = id of vertex\
    \ on heavy path of vertex i, nearest to root\n    std::vector<int> head_ids; \
    \     // consist of head vertex id's\n    std::vector<int> heavy_path_id; // heavy_path_id[i]\
    \ = heavy_path_id for vertex [i]\n\n    HeavyLightDecomposition(int sz = 0)\n\
    \        : V(sz), k(0), nb_heavy_path(0), e(sz), par(sz), depth(sz), subtree_sz(sz),\
    \ heavy_child(sz), tree_id(sz, -1), aligned_id(sz), aligned_id_inv(sz), head(sz),\
    \ heavy_path_id(sz, -1) {}\n    void add_edge(int u, int v) {\n        e[u].emplace_back(v);\n\
    \        e[v].emplace_back(u);\n    }\n\n    void _build_dfs(int root) {\n   \
    \     std::stack<std::pair<int, int>> st;\n        par[root] = -1;\n        depth[root]\
    \ = 0;\n        st.emplace(root, 0);\n        while (!st.empty()) {\n        \
    \    int now = st.top().first;\n            int& i = st.top().second;\n      \
    \      if (i < (int)e[now].size()) {\n                int nxt = e[now][i++];\n\
    \                if (nxt == par[now]) continue;\n                par[nxt] = now;\n\
    \                depth[nxt] = depth[now] + 1;\n                st.emplace(nxt,\
    \ 0);\n            } else {\n                st.pop();\n                int max_sub_sz\
    \ = 0;\n                subtree_sz[now] = 1;\n                heavy_child[now]\
    \ = -1;\n                for (auto nxt : e[now]) {\n                    if (nxt\
    \ == par[now]) continue;\n                    subtree_sz[now] += subtree_sz[nxt];\n\
    \                    if (max_sub_sz < subtree_sz[nxt]) max_sub_sz = subtree_sz[nxt],\
    \ heavy_child[now] = nxt;\n                }\n            }\n        }\n    }\n\
    \n    void _build_bfs(int root, int tree_id_now) {\n        std::queue<int> q({root});\n\
    \        while (!q.empty()) {\n            int h = q.front();\n            q.pop();\n\
    \            head_ids.emplace_back(h);\n            for (int now = h; now != -1;\
    \ now = heavy_child[now]) {\n                tree_id[now] = tree_id_now;\n   \
    \             aligned_id[now] = k++;\n                aligned_id_inv[aligned_id[now]]\
    \ = now;\n                heavy_path_id[now] = nb_heavy_path;\n              \
    \  head[now] = h;\n                for (int nxt : e[now])\n                  \
    \  if (nxt != par[now] and nxt != heavy_child[now]) q.push(nxt);\n           \
    \ }\n            nb_heavy_path++;\n        }\n    }\n\n    void build(std::vector<int>\
    \ roots = {0}) {\n        int tree_id_now = 0;\n        for (auto r : roots) {\n\
    \            _build_dfs(r);\n            _build_bfs(r, tree_id_now++);\n     \
    \   }\n    }\n\n    template <typename Monoid> std::vector<Monoid> segtree_rearrange(const\
    \ std::vector<Monoid>& data) const {\n        assert(int(data.size()) == V);\n\
    \        std::vector<Monoid> ret;\n        ret.reserve(V);\n        for (int i\
    \ = 0; i < V; i++) ret.emplace_back(data[aligned_id_inv[i]]);\n        return\
    \ ret;\n    }\n\n    // query for vertices on path [u, v] (INCLUSIVE)\n    void\
    \ for_each_vertex(int u, int v, const std::function<void(int ancestor, int descendant)>&\
    \ f) const {\n        while (true) {\n            if (aligned_id[u] > aligned_id[v])\
    \ std::swap(u, v);\n            f(std::max(aligned_id[head[v]], aligned_id[u]),\
    \ aligned_id[v]);\n            if (head[u] == head[v]) break;\n            v =\
    \ par[head[v]];\n        }\n    }\n\n    void for_each_vertex_noncommutative(int\
    \ from, int to, const std::function<void(int ancestor, int descendant)>& fup,\
    \ const std::function<void(int ancestor, int descendant)>& fdown) const {\n  \
    \      int u = from, v = to;\n        const int lca = lowest_common_ancestor(u,\
    \ v), dlca = depth[lca];\n        while (u >= 0 and depth[u] > dlca) {\n     \
    \       const int p = (depth[head[u]] > dlca ? head[u] : lca);\n            fup(aligned_id[p]\
    \ + (p == lca), aligned_id[u]), u = par[p];\n        }\n        std::vector<std::pair<int,\
    \ int>> lrs;\n        while (v >= 0 and depth[v] >= dlca) {\n            const\
    \ int p = (depth[head[v]] >= dlca ? head[v] : lca);\n            lrs.emplace_back(p,\
    \ v), v = par[p];\n        }\n        std::reverse(lrs.begin(), lrs.end());\n\
    \        for (const auto& lr : lrs) fdown(aligned_id[lr.first], aligned_id[lr.second]);\n\
    \    }\n\n    // query for edges on path [u, v]\n    void for_each_edge(int u,\
    \ int v, const std::function<void(int, int)>& f) const {\n        while (true)\
    \ {\n            if (aligned_id[u] > aligned_id[v]) std::swap(u, v);\n       \
    \     if (head[u] != head[v]) {\n                f(aligned_id[head[v]], aligned_id[v]);\n\
    \                v = par[head[v]];\n            } else {\n                if (u\
    \ != v) f(aligned_id[u] + 1, aligned_id[v]);\n                break;\n       \
    \     }\n        }\n    }\n\n    // lowest_common_ancestor: O(logV)\n    int lowest_common_ancestor(int\
    \ u, int v) const {\n        assert(tree_id[u] == tree_id[v] and tree_id[u] >=\
    \ 0);\n        while (true) {\n            if (aligned_id[u] > aligned_id[v])\
    \ std::swap(u, v);\n            if (head[u] == head[v]) return u;\n          \
    \  v = par[head[v]];\n        }\n    }\n\n    int distance(int u, int v) const\
    \ {\n        assert(tree_id[u] == tree_id[v] and tree_id[u] >= 0);\n        return\
    \ depth[u] + depth[v] - 2 * depth[lowest_common_ancestor(u, v)];\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: tree/heavy_light_decomposition.hpp
  requiredBy: []
  timestamp: '2021-06-06 15:23:40+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - tree/test/hl_decomposition.test.cpp
  - tree/test/vertex-set-path-composite.test.cpp
  - tree/test/vertex-add-path-sum.test.cpp
documentation_of: tree/heavy_light_decomposition.hpp
layout: document
redirect_from:
- /library/tree/heavy_light_decomposition.hpp
- /library/tree/heavy_light_decomposition.hpp.html
title: tree/heavy_light_decomposition.hpp
---
