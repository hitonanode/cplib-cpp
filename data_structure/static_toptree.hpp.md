---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: data_structure/test/static_toptree.test.cpp
    title: data_structure/test/static_toptree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://atcoder.jp/contests/abc351/submissions/52777033
  bundledCode: "#line 2 \"data_structure/static_toptree.hpp\"\n#include <cassert>\n\
    #include <utility>\n#include <vector>\n\n// Structure of static top tree\n// https://atcoder.jp/contests/abc351/submissions/52777033\n\
    struct static_toptree_structure {\n    enum NodeType {\n        Vertex,\n    \
    \    Compress,\n        Rake,\n        AddEdge,\n        AddVertex,\n    };\n\n\
    \    const std::vector<std::vector<int>> &to;\n    std::vector<int> par;\n   \
    \ std::vector<int> heavy_child; // heavy_child[i] = child of i on heavy path\n\
    \n    // toptree data\n    int stt_root = -1;\n    std::vector<int> P, L, R;\n\
    \    std::vector<NodeType> T;\n\nprivate:\n    int hld_dfs(int now, int prv) {\n\
    \        int sz = 1, max_sz = 0;\n        for (int nxt : to.at(now)) {\n     \
    \       if (nxt == prv) continue;\n            par.at(nxt) = now;\n          \
    \  int sub_sz = hld_dfs(nxt, now);\n            sz += sub_sz;\n            if\
    \ (max_sz < sub_sz) max_sz = sub_sz, heavy_child.at(now) = nxt;\n        }\n \
    \       return sz;\n    }\n\n    int create(int k, int l, int r, NodeType t) {\n\
    \        if (k == -1) {\n            k = P.size();\n            P.push_back(-1),\
    \ L.push_back(l), R.push_back(r), T.push_back(t);\n        } else {\n        \
    \    P.at(k) = -1, L.at(k) = l, R.at(k) = r, T.at(k) = t;\n        }\n\n     \
    \   if (l != -1) P.at(l) = k;\n        if (r != -1) P.at(r) = k;\n\n        return\
    \ k;\n    }\n\n    std::pair<int, int> merge(const std::vector<std::pair<int,\
    \ int>> &a, NodeType t) {\n        if (a.size() == 1) return a.front();\n\n  \
    \      int u = 0;\n        for (auto &[idx, sz] : a) u += sz;\n\n        std::vector<std::pair<int,\
    \ int>> left, right;\n        for (const auto &[idx, sz] : a) {\n            (u\
    \ > sz ? left : right).emplace_back(idx, sz), u -= sz * 2;\n        }\n\n    \
    \    auto [left_idx, left_sz] = merge(left, t);\n        auto [right_idx, right_sz]\
    \ = merge(right, t);\n\n        return {create(-1, left_idx, right_idx, t), left_sz\
    \ + right_sz};\n    }\n\n    std::pair<int, int> compress(int i) {\n        std::vector<std::pair<int,\
    \ int>> chs{add_vertex(i)};\n        while (heavy_child.at(i) != -1) {\n     \
    \       i = heavy_child.at(i);\n            chs.push_back(add_vertex(i));\n  \
    \      }\n\n        return merge(chs, Compress);\n    }\n\n    std::pair<int,\
    \ int> rake(int i) {\n        std::vector<std::pair<int, int>> chs;\n        for\
    \ (int j : to.at(i)) {\n            if (j == par.at(i) or j == heavy_child.at(i))\
    \ continue;\n            chs.push_back(add_edge(j));\n        }\n\n        return\
    \ chs.empty() ? std::make_pair(-1, 0) : merge(chs, Rake);\n    }\n\n    std::pair<int,\
    \ int> add_edge(int i) {\n        auto [c, sz] = compress(i);\n        return\
    \ {create(-1, c, -1, AddEdge), sz};\n    }\n\n    std::pair<int, int> add_vertex(int\
    \ i) {\n        auto [c, sz] = rake(i);\n        return {create(i, c, -1, c ==\
    \ -1 ? Vertex : AddVertex), sz + 1};\n    }\n\npublic:\n    static_toptree_structure(const\
    \ std::vector<std::vector<int>> &to, int root) : to(to) {\n\n        const int\
    \ n = to.size();\n\n        par.assign(n, -1), heavy_child.assign(n, -1);\n\n\
    \        hld_dfs(root, -1);\n\n        P.assign(n, -1), L.assign(n, -1), R.assign(n,\
    \ -1), T.assign(n, Vertex);\n\n        stt_root = compress(root).first;\n    }\n\
    \n    int size() const { return P.size(); }\n\n    // Top tree \u306E\u5E30\u308A\
    \u304C\u3051\u9806\u306B f() \u3092\u547C\u3076\n    // \u30C7\u30FC\u30BF\u306E\
    \u521D\u671F\u5316\u306A\u3069\u306B\u5229\u7528\u53EF\u80FD\n    template <class\
    \ Callback> void dfs_postorder(Callback f) const {\n        auto rec = [&](auto\
    \ &&self, int now) -> void {\n            if (L.at(now) != -1) self(self, L.at(now));\n\
    \            if (R.at(now) != -1) self(self, R.at(now));\n            f(now);\n\
    \        };\n        rec(rec, stt_root);\n    }\n\n    // Top tree \u306E v \u304B\
    \u3089\u6839\uFF08!= \u3082\u3068\u306E\u6728\u306E\u6839\uFF09\u307E\u3067\u306E\
    \u30D1\u30B9\u4E0A\u3067 f() \u3092\u547C\u3076\n    // \u4E00\u70B9\u66F4\u65B0\
    \u306A\u3069\u306B\u5229\u7528\u53EF\u80FD\n    template <class Callback> void\
    \ path_to_root(int v, Callback f) const {\n        while (v != -1) f(v), v = P.at(v);\n\
    \    }\n};\n\n// Static top tree\ntemplate <class TreeDP> struct static_toptree\
    \ {\n\n    using Point = typename TreeDP::Point;\n    using Path = typename TreeDP::Path;\n\
    \n    const static_toptree_structure &stts;\n    TreeDP &tree_dp;\n\n    std::vector<Point>\
    \ point;\n    std::vector<Path> path;\n\nprivate:\n    void _update(int i) {\n\
    \        if (stts.T.at(i) == static_toptree_structure::Vertex) {\n           \
    \ path.at(i) = tree_dp.vertex(i);\n        } else if (stts.T.at(i) == static_toptree_structure::Compress)\
    \ {\n            path.at(i) = tree_dp.compress(path.at(stts.L.at(i)), path.at(stts.R.at(i)));\n\
    \        } else if (stts.T.at(i) == static_toptree_structure::Rake) {\n      \
    \      point.at(i) = tree_dp.rake(point.at(stts.L.at(i)), point.at(stts.R.at(i)));\n\
    \        } else if (stts.T.at(i) == static_toptree_structure::AddEdge) {\n   \
    \         point.at(i) = tree_dp.add_edge(path.at(stts.L.at(i)));\n        } else\
    \ if (stts.T.at(i) == static_toptree_structure::AddVertex) {\n            path.at(i)\
    \ = tree_dp.add_vertex(point.at(stts.L.at(i)), i);\n        } else {\n       \
    \     assert(false);\n        }\n    }\n\npublic:\n    static_toptree(const static_toptree_structure\
    \ &stts, TreeDP &tree_dp)\n        : stts(stts), tree_dp(tree_dp), point(stts.size()),\
    \ path(stts.size()) {\n        stts.dfs_postorder([&](int k) { _update(k); });\n\
    \    }\n\n    void set(int i) {\n        stts.path_to_root(i, [&](int k) { _update(k);\
    \ });\n    }\n\n    Path all_prod() const { return path.at(stts.stt_root); }\n\
    \n    // Not verified yet\n    Path get_subtree(int i) const {\n        Path res\
    \ = path.at(i);\n        while (true) {\n            const int p = stts.P.at(i);\n\
    \            if (p == -1 or stts.T.at(p) != static_toptree_structure::Compress)\
    \ break;\n\n            if (stts.L.at(p) == i) res = tree_dp.compress(res, path.at(stts.R.at(p)));\n\
    \            i = p;\n        }\n\n        return res;\n    }\n};\n\n/*\nstruct\
    \ tree_dp {\n    struct Point;  // Point Cluster\n    struct Path;  // Path Cluster\n\
    \n    Path vertex(int i);\n\n    Path compress(const Path &p, const Path &c);\n\
    \n    Point rake(const Point &l, const Point &r);\n\n    Point add_edge(const\
    \ Path &d);\n\n    Path add_vertex(const Point &d, int i);\n};\n\nvector<vector<int>>\
    \ to(n);\nint root;\n\nconst static_toptree_structure stts(to, root);\n\ntree_dp\
    \ dp;\nstatic_toptree tree(stts, dp);\n*/\n"
  code: "#pragma once\n#include <cassert>\n#include <utility>\n#include <vector>\n\
    \n// Structure of static top tree\n// https://atcoder.jp/contests/abc351/submissions/52777033\n\
    struct static_toptree_structure {\n    enum NodeType {\n        Vertex,\n    \
    \    Compress,\n        Rake,\n        AddEdge,\n        AddVertex,\n    };\n\n\
    \    const std::vector<std::vector<int>> &to;\n    std::vector<int> par;\n   \
    \ std::vector<int> heavy_child; // heavy_child[i] = child of i on heavy path\n\
    \n    // toptree data\n    int stt_root = -1;\n    std::vector<int> P, L, R;\n\
    \    std::vector<NodeType> T;\n\nprivate:\n    int hld_dfs(int now, int prv) {\n\
    \        int sz = 1, max_sz = 0;\n        for (int nxt : to.at(now)) {\n     \
    \       if (nxt == prv) continue;\n            par.at(nxt) = now;\n          \
    \  int sub_sz = hld_dfs(nxt, now);\n            sz += sub_sz;\n            if\
    \ (max_sz < sub_sz) max_sz = sub_sz, heavy_child.at(now) = nxt;\n        }\n \
    \       return sz;\n    }\n\n    int create(int k, int l, int r, NodeType t) {\n\
    \        if (k == -1) {\n            k = P.size();\n            P.push_back(-1),\
    \ L.push_back(l), R.push_back(r), T.push_back(t);\n        } else {\n        \
    \    P.at(k) = -1, L.at(k) = l, R.at(k) = r, T.at(k) = t;\n        }\n\n     \
    \   if (l != -1) P.at(l) = k;\n        if (r != -1) P.at(r) = k;\n\n        return\
    \ k;\n    }\n\n    std::pair<int, int> merge(const std::vector<std::pair<int,\
    \ int>> &a, NodeType t) {\n        if (a.size() == 1) return a.front();\n\n  \
    \      int u = 0;\n        for (auto &[idx, sz] : a) u += sz;\n\n        std::vector<std::pair<int,\
    \ int>> left, right;\n        for (const auto &[idx, sz] : a) {\n            (u\
    \ > sz ? left : right).emplace_back(idx, sz), u -= sz * 2;\n        }\n\n    \
    \    auto [left_idx, left_sz] = merge(left, t);\n        auto [right_idx, right_sz]\
    \ = merge(right, t);\n\n        return {create(-1, left_idx, right_idx, t), left_sz\
    \ + right_sz};\n    }\n\n    std::pair<int, int> compress(int i) {\n        std::vector<std::pair<int,\
    \ int>> chs{add_vertex(i)};\n        while (heavy_child.at(i) != -1) {\n     \
    \       i = heavy_child.at(i);\n            chs.push_back(add_vertex(i));\n  \
    \      }\n\n        return merge(chs, Compress);\n    }\n\n    std::pair<int,\
    \ int> rake(int i) {\n        std::vector<std::pair<int, int>> chs;\n        for\
    \ (int j : to.at(i)) {\n            if (j == par.at(i) or j == heavy_child.at(i))\
    \ continue;\n            chs.push_back(add_edge(j));\n        }\n\n        return\
    \ chs.empty() ? std::make_pair(-1, 0) : merge(chs, Rake);\n    }\n\n    std::pair<int,\
    \ int> add_edge(int i) {\n        auto [c, sz] = compress(i);\n        return\
    \ {create(-1, c, -1, AddEdge), sz};\n    }\n\n    std::pair<int, int> add_vertex(int\
    \ i) {\n        auto [c, sz] = rake(i);\n        return {create(i, c, -1, c ==\
    \ -1 ? Vertex : AddVertex), sz + 1};\n    }\n\npublic:\n    static_toptree_structure(const\
    \ std::vector<std::vector<int>> &to, int root) : to(to) {\n\n        const int\
    \ n = to.size();\n\n        par.assign(n, -1), heavy_child.assign(n, -1);\n\n\
    \        hld_dfs(root, -1);\n\n        P.assign(n, -1), L.assign(n, -1), R.assign(n,\
    \ -1), T.assign(n, Vertex);\n\n        stt_root = compress(root).first;\n    }\n\
    \n    int size() const { return P.size(); }\n\n    // Top tree \u306E\u5E30\u308A\
    \u304C\u3051\u9806\u306B f() \u3092\u547C\u3076\n    // \u30C7\u30FC\u30BF\u306E\
    \u521D\u671F\u5316\u306A\u3069\u306B\u5229\u7528\u53EF\u80FD\n    template <class\
    \ Callback> void dfs_postorder(Callback f) const {\n        auto rec = [&](auto\
    \ &&self, int now) -> void {\n            if (L.at(now) != -1) self(self, L.at(now));\n\
    \            if (R.at(now) != -1) self(self, R.at(now));\n            f(now);\n\
    \        };\n        rec(rec, stt_root);\n    }\n\n    // Top tree \u306E v \u304B\
    \u3089\u6839\uFF08!= \u3082\u3068\u306E\u6728\u306E\u6839\uFF09\u307E\u3067\u306E\
    \u30D1\u30B9\u4E0A\u3067 f() \u3092\u547C\u3076\n    // \u4E00\u70B9\u66F4\u65B0\
    \u306A\u3069\u306B\u5229\u7528\u53EF\u80FD\n    template <class Callback> void\
    \ path_to_root(int v, Callback f) const {\n        while (v != -1) f(v), v = P.at(v);\n\
    \    }\n};\n\n// Static top tree\ntemplate <class TreeDP> struct static_toptree\
    \ {\n\n    using Point = typename TreeDP::Point;\n    using Path = typename TreeDP::Path;\n\
    \n    const static_toptree_structure &stts;\n    TreeDP &tree_dp;\n\n    std::vector<Point>\
    \ point;\n    std::vector<Path> path;\n\nprivate:\n    void _update(int i) {\n\
    \        if (stts.T.at(i) == static_toptree_structure::Vertex) {\n           \
    \ path.at(i) = tree_dp.vertex(i);\n        } else if (stts.T.at(i) == static_toptree_structure::Compress)\
    \ {\n            path.at(i) = tree_dp.compress(path.at(stts.L.at(i)), path.at(stts.R.at(i)));\n\
    \        } else if (stts.T.at(i) == static_toptree_structure::Rake) {\n      \
    \      point.at(i) = tree_dp.rake(point.at(stts.L.at(i)), point.at(stts.R.at(i)));\n\
    \        } else if (stts.T.at(i) == static_toptree_structure::AddEdge) {\n   \
    \         point.at(i) = tree_dp.add_edge(path.at(stts.L.at(i)));\n        } else\
    \ if (stts.T.at(i) == static_toptree_structure::AddVertex) {\n            path.at(i)\
    \ = tree_dp.add_vertex(point.at(stts.L.at(i)), i);\n        } else {\n       \
    \     assert(false);\n        }\n    }\n\npublic:\n    static_toptree(const static_toptree_structure\
    \ &stts, TreeDP &tree_dp)\n        : stts(stts), tree_dp(tree_dp), point(stts.size()),\
    \ path(stts.size()) {\n        stts.dfs_postorder([&](int k) { _update(k); });\n\
    \    }\n\n    void set(int i) {\n        stts.path_to_root(i, [&](int k) { _update(k);\
    \ });\n    }\n\n    Path all_prod() const { return path.at(stts.stt_root); }\n\
    \n    // Not verified yet\n    Path get_subtree(int i) const {\n        Path res\
    \ = path.at(i);\n        while (true) {\n            const int p = stts.P.at(i);\n\
    \            if (p == -1 or stts.T.at(p) != static_toptree_structure::Compress)\
    \ break;\n\n            if (stts.L.at(p) == i) res = tree_dp.compress(res, path.at(stts.R.at(p)));\n\
    \            i = p;\n        }\n\n        return res;\n    }\n};\n\n/*\nstruct\
    \ tree_dp {\n    struct Point;  // Point Cluster\n    struct Path;  // Path Cluster\n\
    \n    Path vertex(int i);\n\n    Path compress(const Path &p, const Path &c);\n\
    \n    Point rake(const Point &l, const Point &r);\n\n    Point add_edge(const\
    \ Path &d);\n\n    Path add_vertex(const Point &d, int i);\n};\n\nvector<vector<int>>\
    \ to(n);\nint root;\n\nconst static_toptree_structure stts(to, root);\n\ntree_dp\
    \ dp;\nstatic_toptree tree(stts, dp);\n*/\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/static_toptree.hpp
  requiredBy: []
  timestamp: '2024-05-05 13:48:11+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - data_structure/test/static_toptree.test.cpp
documentation_of: data_structure/static_toptree.hpp
layout: document
title: Static top tree
---

いわゆる Static top tree を扱う．根付き木の部分木に関する各種演算をクエリあたり $O(n \log n)$ で行える．

## 原理

Static top tree のしくみについては [解説 - AtCoder Beginner Contest 351](https://atcoder.jp/contests/abc351/editorial/9868) 等も併せて参照されたい．

Static top tree は，根付き木をもとに平衡二分木を構築する．平衡二分木の各頂点には `PointCluster` と `PathCluster` の 2 種類のデータ構造のいずれかが載る．

例えば，入力として以下の根付き木（ $0$ が根）を与えた場合に構築される static top tree を下に示す．ここで入力の木の辺のうち二重線は heavy-light decomposition (HLD) の heavy edge, 破線は light edge を示す．

![入力](https://gist.githubusercontent.com/hitonanode/330e4c27e0fb231f82cafaba541bbe19/raw/d9ce4a3b4fdda25e8cb9380c65ead5475cce18e6/static-top-tree-example-input-graph.svg)

![出力](https://gist.githubusercontent.com/hitonanode/330e4c27e0fb231f82cafaba541bbe19/raw/d9ce4a3b4fdda25e8cb9380c65ead5475cce18e6/static-top-tree-example-output-graph.svg)

出力の辺のうち実線は PathCluster, 破線は PointCluster が親頂点に伝播されることをそれぞれ意味する．

図から分かるように，HLD の heavy path は PathCluster として管理され， compress 処理によってマージされる．また， light edge で親と繋がる子頂点たちは PointCluster として管理され， rake 処理によってマージされる．これらの処理を問題に応じてうまく考案・実装してやる必要がある．

## 使用方法

まず，以下のように `Point` クラス・ `Path` クラスと `vertex()` / `compress()` / `rake()` / `add_edge()` / `add_vertex()` メソッドを持つクラスを定義する（ `static` はなくても可）．

```cpp
struct tree_dp {
    // Point Cluster
    struct Point {};

    // Path Cluster
    struct Path {};

    Path vertex(int i);

    static Path compress(const Path &parent, const Path &child);

    static Point rake(const Point &l, const Point &r);

    static Point add_edge(const Path &d);

    Path add_vertex(const Point &d, int i);
};
```

その後，以下の手順で構築・利用する．

```cpp
// 前準備
vector<vector<int>> to;  // 隣接リスト
int root = 0;

// 構築
const static_toptree_structure stts(to, root);
tree_dp dp;
static_toptree tree(stts, dp);

// 利用
tree.set(u); // 頂点 u に更新があった場合に呼ぶ

auto p = tree.all_prod();  // 根に関して値取得
```

## 問題例

- [AtCoder Beginner Contest 351 G - Hash on Tree](https://atcoder.jp/contests/abc351/tasks/abc351_g)
- [Library Checker: Point Set Tree Path Composite Sum (Fixed Root)](https://judge.yosupo.jp/problem/point_set_tree_path_composite_sum_fixed_root)
