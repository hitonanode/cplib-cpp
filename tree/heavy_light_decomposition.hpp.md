---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: graph/test/extended_block_cut_trees.yuki1326.test.cpp
    title: graph/test/extended_block_cut_trees.yuki1326.test.cpp
  - icon: ':heavy_check_mark:'
    path: tree/test/hl_decomposition.test.cpp
    title: tree/test/hl_decomposition.test.cpp
  - icon: ':heavy_check_mark:'
    path: tree/test/hld_subtree_query.test.cpp
    title: tree/test/hld_subtree_query.test.cpp
  - icon: ':heavy_check_mark:'
    path: tree/test/jump_on_tree_hld.test.cpp
    title: tree/test/jump_on_tree_hld.test.cpp
  - icon: ':heavy_check_mark:'
    path: tree/test/vertex-add-path-sum.test.cpp
    title: tree/test/vertex-add-path-sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: tree/test/vertex-add-subtree-sum.test.cpp
    title: tree/test/vertex-add-subtree-sum.test.cpp
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
    #include <utility>\n#include <vector>\n\n// Heavy-light decomposition of trees\
    \ (forest)\n// Based on http://beet-aizu.hatenablog.com/entry/2017/12/12/235950\n\
    struct heavy_light_decomposition {\n    int V;\n    int k;\n    std::vector<std::vector<int>>\
    \ e;\n    std::vector<int> par;         // par[i] = parent of vertex i (Default:\
    \ -1)\n    std::vector<int> depth;       // depth[i] = distance between root and\
    \ vertex i\n    std::vector<int> subtree_sz;  // subtree_sz[i] = size of subtree\
    \ whose root is i\n    std::vector<int> heavy_child; // heavy_child[i] = child\
    \ of vertex i on heavy path (Default: -1)\n    std::vector<int> tree_id;     //\
    \ tree_id[i] = id of tree vertex i belongs to\n    // subtree_begin[i] = aligned\
    \ id for vertex i (consecutive on heavy edges)\n    std::vector<int> subtree_begin,\
    \ subtree_end;\n    std::vector<int> vis_order; // vis_order[subtree_begin[i]]\
    \ = i\n    std::vector<int> head; // head[i] = id of vertex on heavy path of vertex\
    \ i, nearest to root\n\n    heavy_light_decomposition(int n, const std::vector<std::pair<int,\
    \ int>> &edges)\n        : V(n), k(0), e(n), par(n), depth(n), subtree_sz(n),\
    \ heavy_child(n), tree_id(n, -1),\n          subtree_begin(n), subtree_end(n),\
    \ vis_order(0), head(n) {\n        for (auto [u, v] : edges) {\n            assert(u\
    \ != v);\n            e.at(u).emplace_back(v);\n            e.at(v).emplace_back(u);\n\
    \        }\n    }\n\n    void _build_dfs_1(int root) {\n        std::vector<std::pair<int,\
    \ int>> st;\n        par[root] = -1;\n        depth[root] = 0;\n        st.emplace_back(root,\
    \ 0);\n        while (!st.empty()) {\n            int now = st.back().first;\n\
    \            int &i = st.back().second;\n            if (i < (int)e[now].size())\
    \ {\n                int nxt = e[now][i++];\n                if (nxt == par[now])\
    \ continue;\n                par[nxt] = now;\n                depth[nxt] = depth[now]\
    \ + 1;\n                st.emplace_back(nxt, 0);\n            } else {\n     \
    \           st.pop_back();\n                int max_sub_sz = 0;\n            \
    \    subtree_sz[now] = 1;\n                heavy_child[now] = -1;\n          \
    \      for (auto nxt : e[now]) {\n                    if (nxt == par[now]) continue;\n\
    \                    subtree_sz[now] += subtree_sz[nxt];\n                   \
    \ if (max_sub_sz < subtree_sz[nxt]) {\n                        max_sub_sz = subtree_sz[nxt],\
    \ heavy_child[now] = nxt;\n                    }\n                }\n        \
    \    }\n        }\n    }\n\n    void _build_dfs_2(int now, int tree_id_now) {\n\
    \        std::vector<std::pair<int, bool>> st;\n        st.emplace_back(now, true);\n\
    \        head[now] = now;\n\n        while (!st.empty()) {\n            auto [now,\
    \ mode] = st.back();\n            st.pop_back();\n\n            if (mode) {\n\
    \                tree_id[now] = tree_id_now;\n                subtree_begin[now]\
    \ = k++;\n                vis_order.push_back(now);\n\n                st.emplace_back(now,\
    \ false);\n\n                for (int nxt : e[now]) {\n                    if\
    \ (nxt == par[now] or nxt == heavy_child[now]) continue;\n                   \
    \ head[nxt] = nxt;\n                    st.emplace_back(nxt, true);\n        \
    \        }\n\n                if (heavy_child[now] != -1) {\n                \
    \    head[heavy_child[now]] = head[now];\n                    st.emplace_back(heavy_child[now],\
    \ true);\n                }\n            } else {\n                subtree_end[now]\
    \ = k;\n            }\n        }\n    }\n\n    void build(std::vector<int> roots\
    \ = {0}) {\n        int tree_id_now = 0;\n        for (int r : roots) {\n    \
    \        _build_dfs_1(r);\n            _build_dfs_2(r, tree_id_now++);\n     \
    \   }\n    }\n\n    template <class T> std::vector<T> segtree_rearrange(const\
    \ std::vector<T> &data) const {\n        assert(int(data.size()) == V);\n    \
    \    std::vector<T> ret;\n        ret.reserve(vis_order.size());\n        for\
    \ (int v : vis_order) ret.emplace_back(data[v]);\n        return ret;\n    }\n\
    \n    void for_vertex(int u, const std::function<void(int)> &f) const { f(subtree_begin[u]);\
    \ }\n\n    // query for vertices on path [u, v] (INCLUSIVE)\n    void\n    for_each_vertex(int\
    \ u, int v, const std::function<void(int ancestor, int descendant)> &f) const\
    \ {\n        while (true) {\n            if (subtree_begin[u] > subtree_begin[v])\
    \ std::swap(u, v);\n            f(std::max(subtree_begin[head[v]], subtree_begin[u]),\
    \ subtree_begin[v]);\n            if (head[u] == head[v]) break;\n           \
    \ v = par[head[v]];\n        }\n    }\n\n    void for_each_vertex_noncommutative(\n\
    \        int from, int to, const std::function<void(int ancestor, int descendant)>\
    \ &fup,\n        const std::function<void(int ancestor, int descendant)> &fdown)\
    \ const {\n        int u = from, v = to;\n        const int lca = lowest_common_ancestor(u,\
    \ v), dlca = depth[lca];\n        while (u >= 0 and depth[u] > dlca) {\n     \
    \       const int p = (depth[head[u]] > dlca ? head[u] : lca);\n            fup(subtree_begin[p]\
    \ + (p == lca), subtree_begin[u]), u = par[p];\n        }\n        static std::vector<std::pair<int,\
    \ int>> lrs;\n        int sz = 0;\n        while (v >= 0 and depth[v] >= dlca)\
    \ {\n            const int p = (depth[head[v]] >= dlca ? head[v] : lca);\n   \
    \         if (int(lrs.size()) == sz) lrs.emplace_back(0, 0);\n            lrs.at(sz++)\
    \ = {p, v}, v = par.at(p);\n        }\n        while (sz--) fdown(subtree_begin[lrs.at(sz).first],\
    \ subtree_begin[lrs.at(sz).second]);\n    }\n\n    // query for edges on path\
    \ [u, v]\n    void for_each_edge(int u, int v, const std::function<void(int, int)>\
    \ &f) const {\n        while (true) {\n            if (subtree_begin[u] > subtree_begin[v])\
    \ std::swap(u, v);\n            if (head[u] != head[v]) {\n                f(subtree_begin[head[v]],\
    \ subtree_begin[v]);\n                v = par[head[v]];\n            } else {\n\
    \                if (u != v) f(subtree_begin[u] + 1, subtree_begin[v]);\n    \
    \            break;\n            }\n        }\n    }\n\n    // query for vertices\
    \ in subtree rooted at u\n    void for_subtree(int u, const std::function<void(int,\
    \ int)> &f) const {\n        f(subtree_begin[u], subtree_end[u] - 1);\n    }\n\
    \n    // lowest_common_ancestor: O(log V)\n    int lowest_common_ancestor(int\
    \ u, int v) const {\n        assert(tree_id[u] == tree_id[v] and tree_id[u] >=\
    \ 0);\n        while (true) {\n            if (subtree_begin[u] > subtree_begin[v])\
    \ std::swap(u, v);\n            if (head[u] == head[v]) return u;\n          \
    \  v = par[head[v]];\n        }\n    }\n\n    int distance(int u, int v) const\
    \ {\n        assert(tree_id[u] == tree_id[v] and tree_id[u] >= 0);\n        return\
    \ depth[u] + depth[v] - 2 * depth[lowest_common_ancestor(u, v)];\n    }\n\n  \
    \  // Level ancestor, O(log V)\n    // if k-th parent is out of range, return\
    \ -1\n    int kth_parent(int v, int k) const {\n        if (k < 0) return -1;\n\
    \        while (v >= 0) {\n            int h = head.at(v), len = depth.at(v) -\
    \ depth.at(h);\n            if (k <= len) return vis_order.at(subtree_begin.at(v)\
    \ - k);\n            k -= len + 1, v = par.at(h);\n        }\n        return -1;\n\
    \    }\n\n    // Jump on tree, O(log V)\n    int s_to_t_by_k_steps(int s, int\
    \ t, int k) const {\n        if (k < 0) return -1;\n        if (k == 0) return\
    \ s;\n        int lca = lowest_common_ancestor(s, t);\n        if (k <= depth.at(s)\
    \ - depth.at(lca)) return kth_parent(s, k);\n        return kth_parent(t, depth.at(s)\
    \ + depth.at(t) - depth.at(lca) * 2 - k);\n    }\n};\n"
  code: "#pragma once\n#include <algorithm>\n#include <cassert>\n#include <functional>\n\
    #include <queue>\n#include <stack>\n#include <utility>\n#include <vector>\n\n\
    // Heavy-light decomposition of trees (forest)\n// Based on http://beet-aizu.hatenablog.com/entry/2017/12/12/235950\n\
    struct heavy_light_decomposition {\n    int V;\n    int k;\n    std::vector<std::vector<int>>\
    \ e;\n    std::vector<int> par;         // par[i] = parent of vertex i (Default:\
    \ -1)\n    std::vector<int> depth;       // depth[i] = distance between root and\
    \ vertex i\n    std::vector<int> subtree_sz;  // subtree_sz[i] = size of subtree\
    \ whose root is i\n    std::vector<int> heavy_child; // heavy_child[i] = child\
    \ of vertex i on heavy path (Default: -1)\n    std::vector<int> tree_id;     //\
    \ tree_id[i] = id of tree vertex i belongs to\n    // subtree_begin[i] = aligned\
    \ id for vertex i (consecutive on heavy edges)\n    std::vector<int> subtree_begin,\
    \ subtree_end;\n    std::vector<int> vis_order; // vis_order[subtree_begin[i]]\
    \ = i\n    std::vector<int> head; // head[i] = id of vertex on heavy path of vertex\
    \ i, nearest to root\n\n    heavy_light_decomposition(int n, const std::vector<std::pair<int,\
    \ int>> &edges)\n        : V(n), k(0), e(n), par(n), depth(n), subtree_sz(n),\
    \ heavy_child(n), tree_id(n, -1),\n          subtree_begin(n), subtree_end(n),\
    \ vis_order(0), head(n) {\n        for (auto [u, v] : edges) {\n            assert(u\
    \ != v);\n            e.at(u).emplace_back(v);\n            e.at(v).emplace_back(u);\n\
    \        }\n    }\n\n    void _build_dfs_1(int root) {\n        std::vector<std::pair<int,\
    \ int>> st;\n        par[root] = -1;\n        depth[root] = 0;\n        st.emplace_back(root,\
    \ 0);\n        while (!st.empty()) {\n            int now = st.back().first;\n\
    \            int &i = st.back().second;\n            if (i < (int)e[now].size())\
    \ {\n                int nxt = e[now][i++];\n                if (nxt == par[now])\
    \ continue;\n                par[nxt] = now;\n                depth[nxt] = depth[now]\
    \ + 1;\n                st.emplace_back(nxt, 0);\n            } else {\n     \
    \           st.pop_back();\n                int max_sub_sz = 0;\n            \
    \    subtree_sz[now] = 1;\n                heavy_child[now] = -1;\n          \
    \      for (auto nxt : e[now]) {\n                    if (nxt == par[now]) continue;\n\
    \                    subtree_sz[now] += subtree_sz[nxt];\n                   \
    \ if (max_sub_sz < subtree_sz[nxt]) {\n                        max_sub_sz = subtree_sz[nxt],\
    \ heavy_child[now] = nxt;\n                    }\n                }\n        \
    \    }\n        }\n    }\n\n    void _build_dfs_2(int now, int tree_id_now) {\n\
    \        std::vector<std::pair<int, bool>> st;\n        st.emplace_back(now, true);\n\
    \        head[now] = now;\n\n        while (!st.empty()) {\n            auto [now,\
    \ mode] = st.back();\n            st.pop_back();\n\n            if (mode) {\n\
    \                tree_id[now] = tree_id_now;\n                subtree_begin[now]\
    \ = k++;\n                vis_order.push_back(now);\n\n                st.emplace_back(now,\
    \ false);\n\n                for (int nxt : e[now]) {\n                    if\
    \ (nxt == par[now] or nxt == heavy_child[now]) continue;\n                   \
    \ head[nxt] = nxt;\n                    st.emplace_back(nxt, true);\n        \
    \        }\n\n                if (heavy_child[now] != -1) {\n                \
    \    head[heavy_child[now]] = head[now];\n                    st.emplace_back(heavy_child[now],\
    \ true);\n                }\n            } else {\n                subtree_end[now]\
    \ = k;\n            }\n        }\n    }\n\n    void build(std::vector<int> roots\
    \ = {0}) {\n        int tree_id_now = 0;\n        for (int r : roots) {\n    \
    \        _build_dfs_1(r);\n            _build_dfs_2(r, tree_id_now++);\n     \
    \   }\n    }\n\n    template <class T> std::vector<T> segtree_rearrange(const\
    \ std::vector<T> &data) const {\n        assert(int(data.size()) == V);\n    \
    \    std::vector<T> ret;\n        ret.reserve(vis_order.size());\n        for\
    \ (int v : vis_order) ret.emplace_back(data[v]);\n        return ret;\n    }\n\
    \n    void for_vertex(int u, const std::function<void(int)> &f) const { f(subtree_begin[u]);\
    \ }\n\n    // query for vertices on path [u, v] (INCLUSIVE)\n    void\n    for_each_vertex(int\
    \ u, int v, const std::function<void(int ancestor, int descendant)> &f) const\
    \ {\n        while (true) {\n            if (subtree_begin[u] > subtree_begin[v])\
    \ std::swap(u, v);\n            f(std::max(subtree_begin[head[v]], subtree_begin[u]),\
    \ subtree_begin[v]);\n            if (head[u] == head[v]) break;\n           \
    \ v = par[head[v]];\n        }\n    }\n\n    void for_each_vertex_noncommutative(\n\
    \        int from, int to, const std::function<void(int ancestor, int descendant)>\
    \ &fup,\n        const std::function<void(int ancestor, int descendant)> &fdown)\
    \ const {\n        int u = from, v = to;\n        const int lca = lowest_common_ancestor(u,\
    \ v), dlca = depth[lca];\n        while (u >= 0 and depth[u] > dlca) {\n     \
    \       const int p = (depth[head[u]] > dlca ? head[u] : lca);\n            fup(subtree_begin[p]\
    \ + (p == lca), subtree_begin[u]), u = par[p];\n        }\n        static std::vector<std::pair<int,\
    \ int>> lrs;\n        int sz = 0;\n        while (v >= 0 and depth[v] >= dlca)\
    \ {\n            const int p = (depth[head[v]] >= dlca ? head[v] : lca);\n   \
    \         if (int(lrs.size()) == sz) lrs.emplace_back(0, 0);\n            lrs.at(sz++)\
    \ = {p, v}, v = par.at(p);\n        }\n        while (sz--) fdown(subtree_begin[lrs.at(sz).first],\
    \ subtree_begin[lrs.at(sz).second]);\n    }\n\n    // query for edges on path\
    \ [u, v]\n    void for_each_edge(int u, int v, const std::function<void(int, int)>\
    \ &f) const {\n        while (true) {\n            if (subtree_begin[u] > subtree_begin[v])\
    \ std::swap(u, v);\n            if (head[u] != head[v]) {\n                f(subtree_begin[head[v]],\
    \ subtree_begin[v]);\n                v = par[head[v]];\n            } else {\n\
    \                if (u != v) f(subtree_begin[u] + 1, subtree_begin[v]);\n    \
    \            break;\n            }\n        }\n    }\n\n    // query for vertices\
    \ in subtree rooted at u\n    void for_subtree(int u, const std::function<void(int,\
    \ int)> &f) const {\n        f(subtree_begin[u], subtree_end[u] - 1);\n    }\n\
    \n    // lowest_common_ancestor: O(log V)\n    int lowest_common_ancestor(int\
    \ u, int v) const {\n        assert(tree_id[u] == tree_id[v] and tree_id[u] >=\
    \ 0);\n        while (true) {\n            if (subtree_begin[u] > subtree_begin[v])\
    \ std::swap(u, v);\n            if (head[u] == head[v]) return u;\n          \
    \  v = par[head[v]];\n        }\n    }\n\n    int distance(int u, int v) const\
    \ {\n        assert(tree_id[u] == tree_id[v] and tree_id[u] >= 0);\n        return\
    \ depth[u] + depth[v] - 2 * depth[lowest_common_ancestor(u, v)];\n    }\n\n  \
    \  // Level ancestor, O(log V)\n    // if k-th parent is out of range, return\
    \ -1\n    int kth_parent(int v, int k) const {\n        if (k < 0) return -1;\n\
    \        while (v >= 0) {\n            int h = head.at(v), len = depth.at(v) -\
    \ depth.at(h);\n            if (k <= len) return vis_order.at(subtree_begin.at(v)\
    \ - k);\n            k -= len + 1, v = par.at(h);\n        }\n        return -1;\n\
    \    }\n\n    // Jump on tree, O(log V)\n    int s_to_t_by_k_steps(int s, int\
    \ t, int k) const {\n        if (k < 0) return -1;\n        if (k == 0) return\
    \ s;\n        int lca = lowest_common_ancestor(s, t);\n        if (k <= depth.at(s)\
    \ - depth.at(lca)) return kth_parent(s, k);\n        return kth_parent(t, depth.at(s)\
    \ + depth.at(t) - depth.at(lca) * 2 - k);\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: tree/heavy_light_decomposition.hpp
  requiredBy: []
  timestamp: '2025-01-01 21:10:39+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - tree/test/jump_on_tree_hld.test.cpp
  - tree/test/vertex-add-path-sum.test.cpp
  - tree/test/vertex-set-path-composite.test.cpp
  - tree/test/hld_subtree_query.test.cpp
  - tree/test/hl_decomposition.test.cpp
  - tree/test/vertex-add-subtree-sum.test.cpp
  - graph/test/extended_block_cut_trees.yuki1326.test.cpp
documentation_of: tree/heavy_light_decomposition.hpp
layout: document
title: "Heavy-light decomposition \uFF08HLD, \u6728\u306E\u91CD\u8EFD\u5206\u89E3\uFF09"
---

木の重軽分解を行い，列に対する処理を木上のパスや部分木に含まれる全ての頂点に拡張した処理や，最小共通祖先の効率的な計算を可能にする．前処理 $O(n)$．

## 使用方法

### 前処理

```cpp
int n;  // 頂点数
vector<pair<int, int>> edges;

heavy_light_decomposition hld(n, edges);
hld.build();  // O(N)
```

### 木に対する基本的なクエリ

以下，すべてクエリ $O(\log n)$．

```cpp
cout << hld.lowest_common_ancestor(a, b) << '\n'; // (a, b) の最長共通祖先
cout << hld.kth_parent(a, k) << '\n';  // 頂点 a の k 世代親
cout << hld.distance(a, b) << '\n';  // 2 頂点 a, b の距離
cout << hld.s_to_t_by_k_steps(s, t, k) << '\n'; // 頂点 s から t 方向に k 歩動いた頂点
```

### セグメント木などを利用した木上パスクエリへの対応

```cpp
// 各頂点の情報
std::vector<S> vertices_info(n);

// HLD の分解順を考慮したセグメント木の初期化
// セグメント木上で，分解されたパス上の要素は「根方向のものから順に」連続して並ぶことに注意
atcoder::segtree<S, op, e> segtree(hld.segtree_rearrange(vertices_info));

// 頂点 from から頂点 to へのパス（両端点を含む）上の要素合成クエリ
S ret = e();
auto func = [&](int u, int v) { ret = op(ret, segtree.prod(u, v + 1)); };
hld.for_each_vertex(from, to, func);
```

## 問題例

- [Library Checker: Lowest Common Ancestor](https://judge.yosupo.jp/problem/lca)
- [Library Checker: Vertex Add Subtree Sum](https://judge.yosupo.jp/problem/vertex_add_subtree_sum)
- [いろはちゃんコンテスト Day2 K - 虫取り](https://atcoder.jp/contests/iroha2019-day2/tasks/iroha2019_day2_k)
  - 部分木クエリとパスクエリの両方が使われる．

## 参考文献・リンク

- [Easiest HLD with subtree queries - Codeforces](https://codeforces.com/blog/entry/53170)
