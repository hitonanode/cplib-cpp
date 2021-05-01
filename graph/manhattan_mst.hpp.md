---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: graph/test/manhattan_mst.test.cpp
    title: graph/test/manhattan_mst.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://judge.yosupo.jp/problem/manhattanmst,
    - https://www.codechef.com/problems/HKRMAN
  bundledCode: "#line 2 \"graph/manhattan_mst.hpp\"\n#include <algorithm>\n#include\
    \ <map>\n#include <numeric>\n#include <tuple>\n#include <vector>\n\n// CUT begin\n\
    // Manhattan MST: \u4E8C\u6B21\u5143\u5E73\u9762\u4E0A\u306E\u9802\u70B9\u305F\
    \u3061\u306E\u30DE\u30F3\u30CF\u30C3\u30BF\u30F3\u8DDD\u96E2\u306B\u3088\u308B\
    \ minimum spanning tree \u306E O(N) \u672C\u306E\u5019\u88DC\u8FBA\u3092\u5217\
    \u6319\n// Complexity: O(N log N)\n// output: [(weight_uv, u, v), ...]\n// Verified:\
    \ https://judge.yosupo.jp/problem/manhattanmst, https://www.codechef.com/problems/HKRMAN\n\
    // Reference:\n// [1] H. Zhou, N. Shenoy, W. Nicholls,\n//     \"Efficient minimum\
    \ spanning tree construction without Delaunay triangulation,\"\n//     Information\
    \ Processing Letters, 81(5), 271-276, 2002.\ntemplate <typename T> std::vector<std::tuple<T,\
    \ int, int>> manhattan_mst(std::vector<T> xs, std::vector<T> ys) {\n    const\
    \ int n = xs.size();\n    std::vector<int> idx(n);\n    std::iota(idx.begin(),\
    \ idx.end(), 0);\n    std::vector<std::tuple<T, int, int>> ret;\n    for (int\
    \ s = 0; s < 2; s++) {\n        for (int t = 0; t < 2; t++) {\n            auto\
    \ cmp = [&](int i, int j) { return xs[i] + ys[i] < xs[j] + ys[j]; };\n       \
    \     std::sort(idx.begin(), idx.end(), cmp);\n            std::map<T, int> sweep;\n\
    \            for (int i : idx) {\n                for (auto it = sweep.lower_bound(-ys[i]);\
    \ it != sweep.end(); it = sweep.erase(it)) {\n                    int j = it->second;\n\
    \                    if (xs[i] - xs[j] < ys[i] - ys[j]) break;\n             \
    \       ret.emplace_back(std::abs(xs[i] - xs[j]) + std::abs(ys[i] - ys[j]), i,\
    \ j);\n                }\n                sweep[-ys[i]] = i;\n            }\n\
    \            std::swap(xs, ys);\n        }\n        for (auto &x : xs) x = -x;\n\
    \    }\n    std::sort(ret.begin(), ret.end());\n    return ret;\n}\n"
  code: "#pragma once\n#include <algorithm>\n#include <map>\n#include <numeric>\n\
    #include <tuple>\n#include <vector>\n\n// CUT begin\n// Manhattan MST: \u4E8C\u6B21\
    \u5143\u5E73\u9762\u4E0A\u306E\u9802\u70B9\u305F\u3061\u306E\u30DE\u30F3\u30CF\
    \u30C3\u30BF\u30F3\u8DDD\u96E2\u306B\u3088\u308B minimum spanning tree \u306E\
    \ O(N) \u672C\u306E\u5019\u88DC\u8FBA\u3092\u5217\u6319\n// Complexity: O(N log\
    \ N)\n// output: [(weight_uv, u, v), ...]\n// Verified: https://judge.yosupo.jp/problem/manhattanmst,\
    \ https://www.codechef.com/problems/HKRMAN\n// Reference:\n// [1] H. Zhou, N.\
    \ Shenoy, W. Nicholls,\n//     \"Efficient minimum spanning tree construction\
    \ without Delaunay triangulation,\"\n//     Information Processing Letters, 81(5),\
    \ 271-276, 2002.\ntemplate <typename T> std::vector<std::tuple<T, int, int>> manhattan_mst(std::vector<T>\
    \ xs, std::vector<T> ys) {\n    const int n = xs.size();\n    std::vector<int>\
    \ idx(n);\n    std::iota(idx.begin(), idx.end(), 0);\n    std::vector<std::tuple<T,\
    \ int, int>> ret;\n    for (int s = 0; s < 2; s++) {\n        for (int t = 0;\
    \ t < 2; t++) {\n            auto cmp = [&](int i, int j) { return xs[i] + ys[i]\
    \ < xs[j] + ys[j]; };\n            std::sort(idx.begin(), idx.end(), cmp);\n \
    \           std::map<T, int> sweep;\n            for (int i : idx) {\n       \
    \         for (auto it = sweep.lower_bound(-ys[i]); it != sweep.end(); it = sweep.erase(it))\
    \ {\n                    int j = it->second;\n                    if (xs[i] -\
    \ xs[j] < ys[i] - ys[j]) break;\n                    ret.emplace_back(std::abs(xs[i]\
    \ - xs[j]) + std::abs(ys[i] - ys[j]), i, j);\n                }\n            \
    \    sweep[-ys[i]] = i;\n            }\n            std::swap(xs, ys);\n     \
    \   }\n        for (auto &x : xs) x = -x;\n    }\n    std::sort(ret.begin(), ret.end());\n\
    \    return ret;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/manhattan_mst.hpp
  requiredBy: []
  timestamp: '2021-05-01 20:55:29+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - graph/test/manhattan_mst.test.cpp
documentation_of: graph/manhattan_mst.hpp
layout: document
title: "Manhattan MST \uFF08\u4E8C\u6B21\u5143\u5E73\u9762\u4E0A\u306E\u9802\u70B9\
  \u305F\u3061\u306E\u30DE\u30F3\u30CF\u30C3\u30BF\u30F3\u8DDD\u96E2\u306B\u3088\u308B\
  \u6700\u5C0F\u5168\u57DF\u6728\u69CB\u6210\uFF09"
---

$N$ 個の頂点の $x$, $y$ 座標を与えると，候補となる $O(N)$ 本の辺を（重み，端点 1，端点 2）の形式で列挙する．時間計算量 $O(N \log N)$．

## 使用方法

```cpp
vector<int> xs(N), ys(N);
for (int i = 0; i < N; i++) cin >> xs[i] >> ys[i];

UnionFind uf(N);
long long mst_weight = 0;
vector<pair<int, int>> mst_edges;
for (auto [w, i, j] : manhattan_mst(xs, ys)) {
    if (uf.unite(i, j)) {
        mst_weight += w;
        mst_edges.emplace_back(i, j);
    }
}
```

## 問題例

- [Library Checker - Manhattan MST](https://judge.yosupo.jp/problem/manhattanmst)
- [CodeChef - Hackerman](https://www.codechef.com/problems/HKRMAN)
