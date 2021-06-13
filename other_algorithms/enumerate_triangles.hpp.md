---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: other_algorithms/test/enumerate_triangles.test.cpp
    title: other_algorithms/test/enumerate_triangles.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://www.slideshare.net/catupper/trianguler
  bundledCode: "#line 2 \"other_algorithms/enumerate_triangles.hpp\"\n#include <cassert>\n\
    #include <utility>\n#include <vector>\n\n// CUT begin\n// Enumerate triangles\n\
    // Complexity: O(N + M \\sqrt{M})\n// Reference:\n// - https://www.slideshare.net/catupper/trianguler\n\
    struct EnumerateTriangles {\n    int V;\n    std::vector<int> deg;\n    std::vector<std::vector<int>>\
    \ to;\n    std::vector<std::pair<int, int>> edges;\n    EnumerateTriangles(int\
    \ N = 0) : V(N), deg(N), to(N) {}\n    void add_edge(int s, int t) {\n       \
    \ assert(s >= 0 and s < V);\n        assert(t >= 0 and t < V);\n        assert(s\
    \ != t);\n        edges.emplace_back(s, t);\n        deg[s]++, deg[t]++;\n   \
    \ }\n    template <class F> void run(F f) {\n        auto comp = [&](int i, int\
    \ j) { return deg[i] != deg[j] ? deg[i] < deg[j] : i < j; };\n        for (auto\
    \ p : edges) {\n            int s = p.first, t = p.second;\n            if (comp(s,\
    \ t)) {\n                to[s].push_back(t);\n            } else {\n         \
    \       to[t].push_back(s);\n            }\n        }\n        std::vector<char>\
    \ flag(V);\n        for (int i = 0; i < V; i++) {\n            for (auto j : to[i])\
    \ flag[j] = 1;\n            for (auto j : to[i]) {\n                for (auto\
    \ k : to[j]) {\n                    if (flag[k]) f(i, j, k);\n               \
    \ }\n            }\n            for (auto j : to[i]) flag[j] = 0;\n        }\n\
    \    }\n};\n"
  code: "#pragma once\n#include <cassert>\n#include <utility>\n#include <vector>\n\
    \n// CUT begin\n// Enumerate triangles\n// Complexity: O(N + M \\sqrt{M})\n//\
    \ Reference:\n// - https://www.slideshare.net/catupper/trianguler\nstruct EnumerateTriangles\
    \ {\n    int V;\n    std::vector<int> deg;\n    std::vector<std::vector<int>>\
    \ to;\n    std::vector<std::pair<int, int>> edges;\n    EnumerateTriangles(int\
    \ N = 0) : V(N), deg(N), to(N) {}\n    void add_edge(int s, int t) {\n       \
    \ assert(s >= 0 and s < V);\n        assert(t >= 0 and t < V);\n        assert(s\
    \ != t);\n        edges.emplace_back(s, t);\n        deg[s]++, deg[t]++;\n   \
    \ }\n    template <class F> void run(F f) {\n        auto comp = [&](int i, int\
    \ j) { return deg[i] != deg[j] ? deg[i] < deg[j] : i < j; };\n        for (auto\
    \ p : edges) {\n            int s = p.first, t = p.second;\n            if (comp(s,\
    \ t)) {\n                to[s].push_back(t);\n            } else {\n         \
    \       to[t].push_back(s);\n            }\n        }\n        std::vector<char>\
    \ flag(V);\n        for (int i = 0; i < V; i++) {\n            for (auto j : to[i])\
    \ flag[j] = 1;\n            for (auto j : to[i]) {\n                for (auto\
    \ k : to[j]) {\n                    if (flag[k]) f(i, j, k);\n               \
    \ }\n            }\n            for (auto j : to[i]) flag[j] = 0;\n        }\n\
    \    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: other_algorithms/enumerate_triangles.hpp
  requiredBy: []
  timestamp: '2021-06-13 19:44:51+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - other_algorithms/test/enumerate_triangles.test.cpp
documentation_of: other_algorithms/enumerate_triangles.hpp
layout: document
title: "\u7121\u5411\u30B0\u30E9\u30D5\u306B\u542B\u307E\u308C\u308B\u4E09\u89D2\u5F62\
  \u306E\u5217\u6319"
---

頂点数 $N$，辺数 $M$ の無向単純グラフで辺 $(s, t), (t, u), (u, s)$ が全て存在するような相異なる 3 頂点 $(s, t, u)$ の三つ組を全列挙する．時間計算量は $O(N + M \sqrt{M})$．なお完全グラフの場合に三角形は実際に $O(M \sqrt{M})$ 個できる．

## 使用方法

```cpp
EnumerateTriangles graph(N);
for (auto [u, v] : edges) graph.add_edge(u, v);
auto f = [&](int i, int j, int k) { ret += solve_problem(i, j, k); }; // 三角形の各頂点番号を引数にとる
graph.run(f);
```

## リンク

- [Library Checker: Enumerate Triangles](https://judge.yosupo.jp/problem/enumerate_triangles)
- [catupper さんの解説](https://www.slideshare.net/catupper/trianguler)
