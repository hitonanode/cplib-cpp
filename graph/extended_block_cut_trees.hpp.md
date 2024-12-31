---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: graph/test/extended_block_cut_trees.test.cpp
    title: graph/test/extended_block_cut_trees.test.cpp
  - icon: ':heavy_check_mark:'
    path: graph/test/extended_block_cut_trees.yuki1326.test.cpp
    title: graph/test/extended_block_cut_trees.yuki1326.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://ssrs-cp.github.io/cp_library/graph/extended_block_cut_tree.hpp.html
    - https://x.com/noshi91/status/1529858538650374144
  bundledCode: "#line 2 \"graph/extended_block_cut_trees.hpp\"\n\n#include <cassert>\n\
    #include <utility>\n#include <vector>\n\n// Construct block cut tree (or forest)\
    \ from a given graph\n// Complexity: O(N + M), N = |vertices|, M = |edges|\n//\
    \ based on this idea: https://x.com/noshi91/status/1529858538650374144\n// based\
    \ on this implementation: https://ssrs-cp.github.io/cp_library/graph/extended_block_cut_tree.hpp.html\n\
    struct extended_block_cut_trees {\n    int N;                            // number\
    \ of vertices\n    int B;                            // number of blocks\n   \
    \ std::vector<std::vector<int>> to; // (0, ..., N - 1): vertices, (N, ..., N +\
    \ B - 1): blocks\n\n    extended_block_cut_trees(int N, const std::vector<std::pair<int,\
    \ int>> &edges)\n        : N(N), B(0), to(N) {\n        std::vector<std::vector<int>>\
    \ adj(N);\n        for (auto [u, v] : edges) {\n            if (u != v) adj.at(u).push_back(v),\
    \ adj.at(v).push_back(u);\n        }\n\n        std::vector<int> dfs_next(N, -1),\
    \ dist(N, -1), back_cnt(N);\n\n        auto rec1 = [&](auto &&self, int now) ->\
    \ void {\n            for (int nxt : adj[now]) {\n                if (dist[nxt]\
    \ == -1) {\n                    dist[nxt] = dist[now] + 1;\n                 \
    \   dfs_next[now] = nxt;\n                    self(self, nxt);\n             \
    \       back_cnt[now] += back_cnt[nxt];\n                } else if (dist[nxt]\
    \ < dist[now] - 1) {\n                    ++back_cnt[now];\n                 \
    \   --back_cnt[dfs_next[nxt]];\n                }\n            }\n        };\n\
    \n        for (int i = 0; i < N; ++i) {\n            if (dist[i] == -1) dist[i]\
    \ = 0, rec1(rec1, i);\n        }\n\n        std::vector<bool> used(N);\n\n   \
    \     auto rec2 = [&](auto &&self, int now, int current_b) -> void {\n       \
    \     used[now] = true;\n            bool ok = false;\n\n            for (int\
    \ nxt : adj[now]) {\n                if (dist[nxt] == dist[now] + 1 and !used[nxt])\
    \ {\n                    if (back_cnt[nxt] > 0) {\n                        if\
    \ (!ok) {\n                            ok = true;\n                          \
    \  add_edge(now, current_b);\n                        }\n                    \
    \    self(self, nxt, current_b);\n                    } else {\n             \
    \           to.push_back({});\n                        ++B;\n                \
    \        add_edge(now, B - 1);\n                        self(self, nxt, B - 1);\n\
    \                    }\n                }\n            }\n\n            if (!ok\
    \ and dist[now] > 0) { add_edge(now, current_b); }\n        };\n\n        for\
    \ (int i = 0; i < N; ++i) {\n            if (dist[i] == 0) { rec2(rec2, i, B -\
    \ 1); }\n            if (adj[i].empty()) {\n                to.push_back({});\n\
    \                ++B;\n                add_edge(i, B - 1);\n            }\n  \
    \      }\n    }\n\n    int size() const { return N + B; }\n\n    bool is_articulation_point(int\
    \ vertex) const {\n        assert(0 <= vertex and vertex < N);\n        return\
    \ to[vertex].size() > 1;\n    }\n\n    int block_size(int block) const {\n   \
    \     assert(0 <= block and block < B);\n        return to[N + block].size();\n\
    \    }\n\n    const std::vector<int> &block_vertices(int block) const {\n    \
    \    assert(0 <= block and block < B);\n        return to[N + block];\n    }\n\
    \n    std::vector<std::vector<int>> biconnected_components() const {\n       \
    \ return std::vector<std::vector<int>>(to.begin() + N, to.end());\n    }\n\n \
    \   // first < N (vertices), second >= N (blocks)\n    std::vector<std::pair<int,\
    \ int>> get_edges() const {\n        std::vector<std::pair<int, int>> edges;\n\
    \        for (int i = 0; i < N; ++i) {\n            for (int j : to[i]) edges.emplace_back(i,\
    \ j);\n        }\n        return edges;\n    }\n\nprivate:\n    void add_edge(int\
    \ vertex, int block) {\n        assert(0 <= vertex and vertex < N);\n        assert(0\
    \ <= block and block < B);\n        to[vertex].push_back(N + block);\n       \
    \ to[N + block].push_back(vertex);\n    }\n};\n"
  code: "#pragma once\n\n#include <cassert>\n#include <utility>\n#include <vector>\n\
    \n// Construct block cut tree (or forest) from a given graph\n// Complexity: O(N\
    \ + M), N = |vertices|, M = |edges|\n// based on this idea: https://x.com/noshi91/status/1529858538650374144\n\
    // based on this implementation: https://ssrs-cp.github.io/cp_library/graph/extended_block_cut_tree.hpp.html\n\
    struct extended_block_cut_trees {\n    int N;                            // number\
    \ of vertices\n    int B;                            // number of blocks\n   \
    \ std::vector<std::vector<int>> to; // (0, ..., N - 1): vertices, (N, ..., N +\
    \ B - 1): blocks\n\n    extended_block_cut_trees(int N, const std::vector<std::pair<int,\
    \ int>> &edges)\n        : N(N), B(0), to(N) {\n        std::vector<std::vector<int>>\
    \ adj(N);\n        for (auto [u, v] : edges) {\n            if (u != v) adj.at(u).push_back(v),\
    \ adj.at(v).push_back(u);\n        }\n\n        std::vector<int> dfs_next(N, -1),\
    \ dist(N, -1), back_cnt(N);\n\n        auto rec1 = [&](auto &&self, int now) ->\
    \ void {\n            for (int nxt : adj[now]) {\n                if (dist[nxt]\
    \ == -1) {\n                    dist[nxt] = dist[now] + 1;\n                 \
    \   dfs_next[now] = nxt;\n                    self(self, nxt);\n             \
    \       back_cnt[now] += back_cnt[nxt];\n                } else if (dist[nxt]\
    \ < dist[now] - 1) {\n                    ++back_cnt[now];\n                 \
    \   --back_cnt[dfs_next[nxt]];\n                }\n            }\n        };\n\
    \n        for (int i = 0; i < N; ++i) {\n            if (dist[i] == -1) dist[i]\
    \ = 0, rec1(rec1, i);\n        }\n\n        std::vector<bool> used(N);\n\n   \
    \     auto rec2 = [&](auto &&self, int now, int current_b) -> void {\n       \
    \     used[now] = true;\n            bool ok = false;\n\n            for (int\
    \ nxt : adj[now]) {\n                if (dist[nxt] == dist[now] + 1 and !used[nxt])\
    \ {\n                    if (back_cnt[nxt] > 0) {\n                        if\
    \ (!ok) {\n                            ok = true;\n                          \
    \  add_edge(now, current_b);\n                        }\n                    \
    \    self(self, nxt, current_b);\n                    } else {\n             \
    \           to.push_back({});\n                        ++B;\n                \
    \        add_edge(now, B - 1);\n                        self(self, nxt, B - 1);\n\
    \                    }\n                }\n            }\n\n            if (!ok\
    \ and dist[now] > 0) { add_edge(now, current_b); }\n        };\n\n        for\
    \ (int i = 0; i < N; ++i) {\n            if (dist[i] == 0) { rec2(rec2, i, B -\
    \ 1); }\n            if (adj[i].empty()) {\n                to.push_back({});\n\
    \                ++B;\n                add_edge(i, B - 1);\n            }\n  \
    \      }\n    }\n\n    int size() const { return N + B; }\n\n    bool is_articulation_point(int\
    \ vertex) const {\n        assert(0 <= vertex and vertex < N);\n        return\
    \ to[vertex].size() > 1;\n    }\n\n    int block_size(int block) const {\n   \
    \     assert(0 <= block and block < B);\n        return to[N + block].size();\n\
    \    }\n\n    const std::vector<int> &block_vertices(int block) const {\n    \
    \    assert(0 <= block and block < B);\n        return to[N + block];\n    }\n\
    \n    std::vector<std::vector<int>> biconnected_components() const {\n       \
    \ return std::vector<std::vector<int>>(to.begin() + N, to.end());\n    }\n\n \
    \   // first < N (vertices), second >= N (blocks)\n    std::vector<std::pair<int,\
    \ int>> get_edges() const {\n        std::vector<std::pair<int, int>> edges;\n\
    \        for (int i = 0; i < N; ++i) {\n            for (int j : to[i]) edges.emplace_back(i,\
    \ j);\n        }\n        return edges;\n    }\n\nprivate:\n    void add_edge(int\
    \ vertex, int block) {\n        assert(0 <= vertex and vertex < N);\n        assert(0\
    \ <= block and block < B);\n        to[vertex].push_back(N + block);\n       \
    \ to[N + block].push_back(vertex);\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/extended_block_cut_trees.hpp
  requiredBy: []
  timestamp: '2024-12-31 22:44:37+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - graph/test/extended_block_cut_trees.test.cpp
  - graph/test/extended_block_cut_trees.yuki1326.test.cpp
documentation_of: graph/extended_block_cut_trees.hpp
layout: document
title: "Extended block cut tree \uFF08Block cut tree \u306E\u4E9C\u7A2E\uFF09"
---

与えられた $n$ 頂点 $m$ 辺の無向グラフに対する block cut tree （のようなもの）を構築する．計算量は $O(n + m)$．

詳細な仕様は以下の通り．

- 入力グラフの二重連結成分数を $k$ とすると，頂点数 $n + k$ のグラフ（特に，森）を構築する．
  - **通常の block cut tree との相違点として，関節点ではない頂点も構築されたグラフに含まれる．**
- 頂点番号 $0, \ldots, n - 1$ が入力グラフの各頂点， $n, \ldots, n + k - 1$ が入力グラフの各二重連結成分に対応する．
- 頂点 $v$ が二重連結成分 $i$ に含まれるとき，頂点 $v$ と $n + i$ の間に辺が張られる．
- このコードにおいて，次数 0 の頂点（孤立点）はそれ単独で二重連結成分と見なされる．
  - したがって，入力グラフの全ての頂点が一つ以上の二重連結成分に属することになる．

なお，出力されるグラフは以下の性質を満たす．

- 一般に出力されるグラフは森．特に入力グラフが連結ならば出力されるグラフも連結（木）．
- 入力グラフの頂点 $v$ が関節点であることは，出力されるグラフの頂点 $v$ の次数が $2$ 以上であることと同値．

## 使用方法

```cpp
int n;  // Num. of vertices
vector<pair<int, int>> edges;

const extended_block_cut_trees bct(n, edges);

int b = bct.B;  // Num. of blocks
vector<vector<int>> bct_to = bct.to;
assert(n + b == (int)bct_to.size());

// 得られた block cut tree を heavy-light decomposition などに使う場合
HeavyLightDecomposition hld(bct.size());
for (auto [i, j] : bct.get_edges()) hld.add_edge(i, j);
```

## 問題例

- [Library Checker: Biconnected Components](https://judge.yosupo.jp/problem/biconnected_components)
- [No.1326 ふたりのDominator - yukicoder](https://yukicoder.me/problems/no/1326)
  - 無向グラフにおいて指定された 2 頂点間の任意のパスが含む頂点の集合は， block cut tree でその 2 頂点間のパス上に存在する頂点の集合と一致する．
- [AtCoder Beginner Contest 318 G - Typical Path Problem](https://atcoder.jp/contests/abc318/tasks/abc318_g)
- [AtCoder Beginner Contest 334 G - Christmas Color Grid 2](https://atcoder.jp/contests/abc334/tasks/abc334_g)
- [灘校文化祭コンテスト 2022 Day2 H - Tourist on Graph](https://atcoder.jp/contests/nadafes2022_day2/tasks/nadafes2022_day2_h)
- [Codeforces Round 606 (Div. 1, based on Technocup 2020 Elimination Round 4) B. Two Fairs - Codeforces](https://codeforces.com/contest/1276/problem/B)
- [2022-2023 Winter Petrozavodsk Camp, Day 2: GP of ainta I. Visiting Friend - Codeforces](https://codeforces.com/gym/104427/problem/I)

## 参考文献・リンク

- [Block-cut tree - ei1333の日記](https://ei1333.hateblo.jp/entry/2020/03/25/010057)
- [My Algorithm : kopricky アルゴリズムライブラリ](https://kopricky.github.io/code/GraphDecomposition/articulation.html)
- [拡張 Block Cut Tree | cp_library](https://ssrs-cp.github.io/cp_library/graph/extended_block_cut_tree.hpp.html)
- [Xユーザーの熨斗袋さん: 「G = (V, E) に対する Block Cut Tree、G の2-点連結成分全体を C として...](https://x.com/noshi91/status/1529858538650374144)
