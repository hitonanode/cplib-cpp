---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: tree/test/vertex-add-subtree-sum.guni.test.cpp
    title: tree/test/vertex-add-subtree-sum.guni.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://atcoder.jp/contests/abc454/editorial/19112
    - https://codeforces.com/blog/entry/44351
  bundledCode: "#line 2 \"tree/guni.hpp\"\n#include <span>\n#include <type_traits>\n\
    #include <vector>\n\n// Guni / Sack / DSU on tree\n// https://codeforces.com/blog/entry/44351\n\
    // https://atcoder.jp/contests/abc454/editorial/19112\nstruct guni {\n    int\
    \ n;\n    int last_root;\n    std::vector<std::vector<int>> to;\n    std::vector<int>\
    \ sz, ver, st, ft; // subtree size / dfs order / subtree start / subtree fin\n\
    \n    guni(int n_ = 0) : n(n_), last_root(-1), to(n_) {}\n\n    void add_bi_edge(int\
    \ u, int v) { to.at(u).push_back(v), to.at(v).push_back(u); }\n\n    void sdfs(int\
    \ v, int p) { // Build sz / ver / st / ft, and move heavy child to the back\n\
    \        st.at(v) = ver.size(), ver.push_back(v);\n        int heavy_idx = -1;\n\
    \        for (int i = 0; i < int(to.at(v).size()); ++i) {\n            int u =\
    \ to.at(v).at(i);\n            if (u == p) continue;\n            sdfs(u, v);\n\
    \            sz.at(v) += sz.at(u);\n            if (heavy_idx == -1 or sz.at(u)\
    \ > sz.at(to.at(v).at(heavy_idx))) heavy_idx = i;\n        }\n        if (heavy_idx\
    \ != -1) std::swap(to.at(v).at(heavy_idx), to.at(v).back());\n        ft.at(v)\
    \ = ver.size();\n    }\n\n    std::span<const int> subtree(int v) const {\n  \
    \      return std::span<const int>(ver).subspan(st.at(v), ft.at(v) - st.at(v));\n\
    \    }\n\n    template <class F> void call_reset(F &ResetAll, int v) const {\n\
    \        if constexpr (std::is_invocable_v<F &, std::span<const int>>) {\n   \
    \         ResetAll(subtree(v));\n        } else {\n            static_assert(\n\
    \                std::is_invocable_v<F &>,\n                \"ResetAll must be\
    \ callable with std::span<const int> or with no argument\");\n            ResetAll();\n\
    \        }\n    }\n\n    template <class F1, class F2, class F3>\n    void dfs(int\
    \ v, int p, F1 &Add, F2 &ResetAll, F3 &Solve) {\n        const int big_child =\
    \ (!to.at(v).empty() and to.at(v).back() != p) ? to.at(v).back() : -1;\n     \
    \   for (int u : to.at(v)) {\n            if (u != p and u != big_child) {\n \
    \               dfs(u, v, Add, ResetAll, Solve);\n                call_reset(ResetAll,\
    \ u);\n            }\n        }\n        if (big_child != -1) dfs(big_child, v,\
    \ Add, ResetAll, Solve);\n\n        for (int u : to.at(v)) {\n            if (u\
    \ != p and u != big_child) {\n                for (int i = st.at(u); i < ft.at(u);\
    \ ++i) Add(ver.at(i));\n            }\n        }\n        Add(v);\n        Solve(v);\n\
    \    }\n\n    template <class F1, class F2, class F3>\n    void run(const int\
    \ root, F1 Add, F2 ResetAll, F3 Solve) {\n        if (last_root != root) {\n \
    \           last_root = root, ver.clear(), st.resize(n), ft.resize(n), sz.assign(n,\
    \ 1);\n            sdfs(root, -1);\n        }\n        dfs(root, -1, Add, ResetAll,\
    \ Solve);\n        call_reset(ResetAll, root);\n    }\n};\n"
  code: "#pragma once\n#include <span>\n#include <type_traits>\n#include <vector>\n\
    \n// Guni / Sack / DSU on tree\n// https://codeforces.com/blog/entry/44351\n//\
    \ https://atcoder.jp/contests/abc454/editorial/19112\nstruct guni {\n    int n;\n\
    \    int last_root;\n    std::vector<std::vector<int>> to;\n    std::vector<int>\
    \ sz, ver, st, ft; // subtree size / dfs order / subtree start / subtree fin\n\
    \n    guni(int n_ = 0) : n(n_), last_root(-1), to(n_) {}\n\n    void add_bi_edge(int\
    \ u, int v) { to.at(u).push_back(v), to.at(v).push_back(u); }\n\n    void sdfs(int\
    \ v, int p) { // Build sz / ver / st / ft, and move heavy child to the back\n\
    \        st.at(v) = ver.size(), ver.push_back(v);\n        int heavy_idx = -1;\n\
    \        for (int i = 0; i < int(to.at(v).size()); ++i) {\n            int u =\
    \ to.at(v).at(i);\n            if (u == p) continue;\n            sdfs(u, v);\n\
    \            sz.at(v) += sz.at(u);\n            if (heavy_idx == -1 or sz.at(u)\
    \ > sz.at(to.at(v).at(heavy_idx))) heavy_idx = i;\n        }\n        if (heavy_idx\
    \ != -1) std::swap(to.at(v).at(heavy_idx), to.at(v).back());\n        ft.at(v)\
    \ = ver.size();\n    }\n\n    std::span<const int> subtree(int v) const {\n  \
    \      return std::span<const int>(ver).subspan(st.at(v), ft.at(v) - st.at(v));\n\
    \    }\n\n    template <class F> void call_reset(F &ResetAll, int v) const {\n\
    \        if constexpr (std::is_invocable_v<F &, std::span<const int>>) {\n   \
    \         ResetAll(subtree(v));\n        } else {\n            static_assert(\n\
    \                std::is_invocable_v<F &>,\n                \"ResetAll must be\
    \ callable with std::span<const int> or with no argument\");\n            ResetAll();\n\
    \        }\n    }\n\n    template <class F1, class F2, class F3>\n    void dfs(int\
    \ v, int p, F1 &Add, F2 &ResetAll, F3 &Solve) {\n        const int big_child =\
    \ (!to.at(v).empty() and to.at(v).back() != p) ? to.at(v).back() : -1;\n     \
    \   for (int u : to.at(v)) {\n            if (u != p and u != big_child) {\n \
    \               dfs(u, v, Add, ResetAll, Solve);\n                call_reset(ResetAll,\
    \ u);\n            }\n        }\n        if (big_child != -1) dfs(big_child, v,\
    \ Add, ResetAll, Solve);\n\n        for (int u : to.at(v)) {\n            if (u\
    \ != p and u != big_child) {\n                for (int i = st.at(u); i < ft.at(u);\
    \ ++i) Add(ver.at(i));\n            }\n        }\n        Add(v);\n        Solve(v);\n\
    \    }\n\n    template <class F1, class F2, class F3>\n    void run(const int\
    \ root, F1 Add, F2 ResetAll, F3 Solve) {\n        if (last_root != root) {\n \
    \           last_root = root, ver.clear(), st.resize(n), ft.resize(n), sz.assign(n,\
    \ 1);\n            sdfs(root, -1);\n        }\n        dfs(root, -1, Add, ResetAll,\
    \ Solve);\n        call_reset(ResetAll, root);\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: tree/guni.hpp
  requiredBy: []
  timestamp: '2026-04-19 01:24:04+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - tree/test/vertex-add-subtree-sum.guni.test.cpp
documentation_of: tree/guni.hpp
layout: document
title: "Guni (Sack) / DSU on tree \uFF08\u6839\u4ED8\u304D\u6728\u306E\u5168\u3066\
  \u306E\u90E8\u5206\u6728\u3092\u7D4C\u7531\u3059\u308B\u3088\u3046\u306A\u9802\u70B9\
  \u8FFD\u52A0\u30FB\u524A\u9664\u64CD\u4F5C\u5217\u306E\u751F\u6210\uFF09"
---

## できること

頂点数 $n$ の根付き木について，頂点集合の部分集合の列 $S = (S\_0, \ldots, S\_m)$ で，以下を満たすものを構築する．

- $S\_0 = S\_m = \emptyset$
- $\| S\_i \oplus S\_\{i + 1\} \| = 1$ （ $S\_\{i + 1\}$ は $S\_i$ から一個の頂点を追加または削除したもの）
- 各部分木について，それに含まれる頂点集合と $S\_k$ が一致するような $k$ が存在する
- $m =  O(n \log n)$

本コードはこのような $S$ の一つを implicit に構築する．根付き木の全ての部分木に関する特定の問題を全ての部分木に対して解く必要があるような状況で，効率的な実装に役立つ．

## 原理

木の上で DFS し，行きがけに頂点追加・帰りがけに頂点削除を行うのが基本方針だが，一部の頂点には複数回訪問する点で通常の DFS とは異なる．

Heavy-light decomposition を行う．ある頂点 $v$ に到達した際，以下の手続きを行う：

1. $v$ と light edge で繋がる子の部分木全てについて再帰的に DFS する
2. $v$ と heavy edge で繋がる子の部分木について再帰的に DFS する（ただし， 手順 6. の削除操作を省く）
3. $v$ light edge で繋がる子の部分木に含まれる全頂点を追加する
4. 頂点 $v$ を追加する
5. （ $S\_v$ ができる）
6. $v$ の部分木に含まれる全頂点を削除する

このアルゴリズムは以下の背景により $O(n \log n)$ である：

- 手順 3. の計算量は weighted-union heuristic （いわゆるマージテク）により $O(n \log n)$ である．
- 各頂点が手順 6. で削除対象になる回数は，その頂点から根への単純パスに存在する（distinct な） heavy path の本数と一致するので， 6. の計算量は $O(n \log n)$ である．

## 使用方法

根付き木の全ての部分木について「部分木を構成する頂点の `id` の 2 乗和」は以下のように実装できる（本テクニックを使用するまでもない例だが）．

```cpp
int N, root;
vector<pair<int, int>> edges(N - 1);

guni g(N);
for (auto [u, v] : edges) g.add_bi_edge(u, v);

std::vector<long long> ret(N);
long long sum_of_i_quads = 0;

auto Add = [&](int i) { sum_of_i_quads += (long long)i * i; };
auto ResetAll = [&](std::span<const int> view) {
    for (int i : view) sum_of_i_quads -= (long long)i * i;
};
auto Solve = [&](int i) { ret.at(i) = sum_of_i_quads; };

g.run(0, Add, ResetAll, Solve);
```

`ResetAll` は次のどちらでもよい．

- `ResetAll(std::span<const int> view)` : 削除すべき全頂点を受け取る
- `ResetAll()` : 何も受け取らない（全削除が $O(1)$ でできる場合など）

## 問題例

- [Library Checker: Vertex Add Subtree Sum](https://judge.yosupo.jp/problem/vertex_add_subtree_sum)
- [Codeforces Round 862 (Div. 2) E. There Should Be a Lot of Maximums](https://codeforces.com/contest/1805/problem/E)
- [AtCoder Beginner Contest 454 G - Mode in the Subtree](https://atcoder.jp/contests/abc454/tasks/abc454_g)

## 文献・リンク集

- [[Tutorial] Sack (dsu on tree) - Codeforces](https://codeforces.com/blog/entry/44351)
- [DSU on Tree - Speaker Deck](https://speakerdeck.com/camypaper/dsu-on-tree)
- [解説 - キーサイト・テクノロジープログラミングコンテスト（AtCoder Beginner Contest 454）](https://atcoder.jp/contests/abc454/editorial/19112)
