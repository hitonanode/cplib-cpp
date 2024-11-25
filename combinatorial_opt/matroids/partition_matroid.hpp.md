---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/test/matroid_intersection.aoj1605.test.cpp
    title: combinatorial_opt/test/matroid_intersection.aoj1605.test.cpp
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/test/matroid_intersection.aoj_grl_2_b.test.cpp
    title: combinatorial_opt/test/matroid_intersection.aoj_grl_2_b.test.cpp
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/test/matroid_intersection_dijkstra.aoj1605.test.cpp
    title: combinatorial_opt/test/matroid_intersection_dijkstra.aoj1605.test.cpp
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/test/matroid_intersection_dijkstra.aoj_grl_2_b.test.cpp
    title: combinatorial_opt/test/matroid_intersection_dijkstra.aoj_grl_2_b.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"combinatorial_opt/matroids/partition_matroid.hpp\"\n#include\
    \ <cassert>\n#include <vector>\n\n// Partition matroid (partitional matroid) :\
    \ direct sum of uniform matroids\nclass PartitionMatroid {\n    using Element\
    \ = int;\n    int M;\n    std::vector<std::vector<Element>> parts;\n    std::vector<int>\
    \ belong;\n    std::vector<int> R;\n    std::vector<int> cnt;\n    std::vector<std::vector<Element>>\
    \ circuits;\n\npublic:\n    // parts: partition of [0, 1, ..., M - 1]\n    //\
    \ R: only R[i] elements from parts[i] can be chosen for each i.\n    PartitionMatroid(int\
    \ M, const std::vector<std::vector<int>> &parts_, const std::vector<int> &R_)\n\
    \        : M(M), parts(parts_), belong(M, -1), R(R_) {\n        assert(parts.size()\
    \ == R.size());\n        for (int i = 0; i < int(parts.size()); i++) {\n     \
    \       for (Element e : parts[i]) belong[e] = i;\n        }\n        for (Element\
    \ e = 0; e < M; e++) {\n            // assert(belong[e] != -1);\n            if\
    \ (belong[e] == -1) {\n                belong[e] = parts.size();\n           \
    \     parts.push_back({e});\n                R.push_back(1);\n            }\n\
    \        }\n    }\n    int size() const { return M; }\n\n    template <class State>\
    \ void set(const State &I) {\n        cnt = R;\n        for (int e = 0; e < M;\
    \ e++) {\n            if (I[e]) cnt[belong[e]]--;\n        }\n        circuits.assign(cnt.size(),\
    \ {});\n        for (int e = 0; e < M; e++) {\n            if (I[e] and cnt[belong[e]]\
    \ == 0) circuits[belong[e]].push_back(e);\n        }\n    }\n\n    std::vector<Element>\
    \ circuit(const Element e) const {\n        assert(0 <= e and e < M);\n      \
    \  int p = belong[e];\n        if (cnt[p] == 0) {\n            auto ret = circuits[p];\n\
    \            ret.push_back(e);\n            return ret;\n        }\n        return\
    \ {};\n    }\n};\n"
  code: "#pragma once\n#include <cassert>\n#include <vector>\n\n// Partition matroid\
    \ (partitional matroid) : direct sum of uniform matroids\nclass PartitionMatroid\
    \ {\n    using Element = int;\n    int M;\n    std::vector<std::vector<Element>>\
    \ parts;\n    std::vector<int> belong;\n    std::vector<int> R;\n    std::vector<int>\
    \ cnt;\n    std::vector<std::vector<Element>> circuits;\n\npublic:\n    // parts:\
    \ partition of [0, 1, ..., M - 1]\n    // R: only R[i] elements from parts[i]\
    \ can be chosen for each i.\n    PartitionMatroid(int M, const std::vector<std::vector<int>>\
    \ &parts_, const std::vector<int> &R_)\n        : M(M), parts(parts_), belong(M,\
    \ -1), R(R_) {\n        assert(parts.size() == R.size());\n        for (int i\
    \ = 0; i < int(parts.size()); i++) {\n            for (Element e : parts[i]) belong[e]\
    \ = i;\n        }\n        for (Element e = 0; e < M; e++) {\n            // assert(belong[e]\
    \ != -1);\n            if (belong[e] == -1) {\n                belong[e] = parts.size();\n\
    \                parts.push_back({e});\n                R.push_back(1);\n    \
    \        }\n        }\n    }\n    int size() const { return M; }\n\n    template\
    \ <class State> void set(const State &I) {\n        cnt = R;\n        for (int\
    \ e = 0; e < M; e++) {\n            if (I[e]) cnt[belong[e]]--;\n        }\n \
    \       circuits.assign(cnt.size(), {});\n        for (int e = 0; e < M; e++)\
    \ {\n            if (I[e] and cnt[belong[e]] == 0) circuits[belong[e]].push_back(e);\n\
    \        }\n    }\n\n    std::vector<Element> circuit(const Element e) const {\n\
    \        assert(0 <= e and e < M);\n        int p = belong[e];\n        if (cnt[p]\
    \ == 0) {\n            auto ret = circuits[p];\n            ret.push_back(e);\n\
    \            return ret;\n        }\n        return {};\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: combinatorial_opt/matroids/partition_matroid.hpp
  requiredBy: []
  timestamp: '2021-09-01 23:53:05+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - combinatorial_opt/test/matroid_intersection_dijkstra.aoj_grl_2_b.test.cpp
  - combinatorial_opt/test/matroid_intersection_dijkstra.aoj1605.test.cpp
  - combinatorial_opt/test/matroid_intersection.aoj1605.test.cpp
  - combinatorial_opt/test/matroid_intersection.aoj_grl_2_b.test.cpp
documentation_of: combinatorial_opt/matroids/partition_matroid.hpp
layout: document
title: "Partition matroid \uFF08\u5206\u5272\u30DE\u30C8\u30ED\u30A4\u30C9\uFF09"
---

$e = 0, \dots, M - 1$ からなる $M$ 要素の集合 $E$ の分割 $E$ = $E_1 \cup \dots \cup E_K \, (E_i \cap E_j = \varnothing (i \neq j))$と，分割された各部分集合に対する上限要素数 $R_k \ge 0 \, (k = 0, \dots, K - 1)$ によって定められるマトロイド：

$\displaystyle
\mathcal{I} = \{ I \subset E \mid |I \cup E_k| \le R_k \, (k = 0, \dots, K - 1) \}.
$

## 使用例

```cpp
vector<vector<int>> grp; // 登場しない要素があってもよい（それらは制約なしとして扱われる）
grp.push_back({0, 2, 5});
grp.push_back({1, 3});
vector<int> lim{2, 1};
PartitionMatroid M(6, grp, lim);

assert(M.size() == 6);
vector<bool> I(6);
I[0] = I[1] = I[2] = 1;
M.set(I);
assert((M.circuit(5) == vector<int>{0, 2, 5}));
```
