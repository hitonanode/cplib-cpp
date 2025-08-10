---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: graph/test/minimum_steiner_tree.test.cpp
    title: graph/test/minimum_steiner_tree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://judge.yosupo.jp/problem/minimum_steiner_tree
  bundledCode: "#line 2 \"graph/minimum_steiner_tree.hpp\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <queue>\n#include <tuple>\n#include <utility>\n#include\
    \ <vector>\n\n// Minimum Steiner tree of undirected connected graph\n// n vertices,\
    \ m edges, k terminals\n// Complexity: O(3^k n + 2^k m log m)\n// Verify: https://judge.yosupo.jp/problem/minimum_steiner_tree\n\
    template <class T>\nstd::pair<T, std::vector<int>>\nMinimumSteinerTree(int n,\
    \ const std::vector<std::tuple<int, int, T>> &edges,\n                   const\
    \ std::vector<int> &terminals) {\n\n    if (n <= 1 or terminals.size() <= 1) return\
    \ {T{}, {}};\n    assert(!edges.empty());\n\n    std::vector<std::vector<std::tuple<int,\
    \ int, T>>> to(n);\n    for (int i = 0; i < (int)edges.size(); ++i) {\n      \
    \  auto [u, v, w] = edges[i];\n        assert(w >= 0);\n        to.at(u).emplace_back(v,\
    \ i, w);\n        to.at(v).emplace_back(u, i, w);\n    }\n    const int k = terminals.size();\n\
    \n    std::vector<T> dp(n << k);\n    std::vector<int> prv(n << k, -1);\n\n  \
    \  auto f = [&](int i, int s) -> int {\n        assert(0 <= s and s < (1 << k));\n\
    \        return (i << k) + s;\n    };\n\n    for (int i = 0; i < n; ++i) prv.at(f(i,\
    \ 0)) = f(i, 0);\n\n    for (int j = 0; j < k; ++j) {\n        const int i = terminals.at(j);\n\
    \        prv.at(f(i, 1 << j)) = f(i, 0);\n    }\n\n    for (int s = 0; s < (1\
    \ << k); ++s) {\n        for (int i = 0; i < n; ++i) {\n            for (int t\
    \ = (s - 1) & s; t; t = (t - 1) & s) {\n                if (prv.at(f(i, t)) ==\
    \ -1) continue;\n                if (prv.at(f(i, s ^ t)) == -1) continue;\n  \
    \              const T new_cost = dp.at(f(i, t)) + dp.at(f(i, s ^ t));\n     \
    \           if (new_cost < dp.at(f(i, s)) or prv.at(f(i, s)) == -1) {\n      \
    \              dp.at(f(i, s)) = new_cost;\n                    prv.at(f(i, s))\
    \ = f(i, t);\n                    assert(s >= t);\n                }\n       \
    \     }\n        }\n\n        using P = std::pair<T, int>;\n        std::priority_queue<P,\
    \ std::vector<P>, std::greater<>> pq;\n\n        for (int i = 0; i < n; ++i) {\n\
    \            if (prv.at(f(i, s)) != -1) pq.emplace(dp.at(f(i, s)), i);\n     \
    \   }\n\n        while (!pq.empty()) {\n            auto [cost, i] = pq.top();\n\
    \            pq.pop();\n            if (dp.at(f(i, s)) < cost) continue;\n   \
    \         for (auto [j, edge_id, w] : to.at(i)) {\n                if (prv.at(f(j,\
    \ s)) != -1 and dp.at(f(j, s)) <= cost + w) continue;\n                dp.at(f(j,\
    \ s)) = cost + w;\n                prv.at(f(j, s)) = f(edge_id, s);\n        \
    \        pq.emplace(dp.at(f(j, s)), j);\n            }\n        }\n    }\n\n \
    \   T ans = dp.at(f(0, (1 << k) - 1));\n    int argmin = 0;\n    for (int i =\
    \ 1; i < n; ++i) {\n        if (dp.at(f(i, (1 << k) - 1)) < ans) {\n         \
    \   ans = dp.at(f(i, (1 << k) - 1));\n            argmin = i;\n        }\n   \
    \ }\n\n    std::vector<int> used_edges;\n\n    auto rec = [&](auto &&self, int\
    \ cur) -> void {\n        const int mask = cur & ((1 << k) - 1);\n        if (!mask)\
    \ return;\n        const int i = cur >> k;\n        const int prv_mask = prv.at(cur)\
    \ & ((1 << k) - 1);\n        if (prv_mask == 0) return;\n\n        if (mask ==\
    \ prv_mask) {\n            const int edge_id = prv.at(cur) >> k;\n           \
    \ used_edges.emplace_back(edge_id);\n            const int nxt = i ^ std::get<0>(edges.at(edge_id))\
    \ ^ std::get<1>(edges.at(edge_id));\n            self(self, f(nxt, mask));\n \
    \       } else {\n            self(self, f(i, prv_mask));\n            self(self,\
    \ f(i, mask ^ prv_mask));\n        }\n    };\n    rec(rec, f(argmin, (1 << k)\
    \ - 1));\n\n    std::sort(used_edges.begin(), used_edges.end());\n\n    return\
    \ {ans, used_edges};\n}\n"
  code: "#pragma once\n\n#include <algorithm>\n#include <cassert>\n#include <queue>\n\
    #include <tuple>\n#include <utility>\n#include <vector>\n\n// Minimum Steiner\
    \ tree of undirected connected graph\n// n vertices, m edges, k terminals\n//\
    \ Complexity: O(3^k n + 2^k m log m)\n// Verify: https://judge.yosupo.jp/problem/minimum_steiner_tree\n\
    template <class T>\nstd::pair<T, std::vector<int>>\nMinimumSteinerTree(int n,\
    \ const std::vector<std::tuple<int, int, T>> &edges,\n                   const\
    \ std::vector<int> &terminals) {\n\n    if (n <= 1 or terminals.size() <= 1) return\
    \ {T{}, {}};\n    assert(!edges.empty());\n\n    std::vector<std::vector<std::tuple<int,\
    \ int, T>>> to(n);\n    for (int i = 0; i < (int)edges.size(); ++i) {\n      \
    \  auto [u, v, w] = edges[i];\n        assert(w >= 0);\n        to.at(u).emplace_back(v,\
    \ i, w);\n        to.at(v).emplace_back(u, i, w);\n    }\n    const int k = terminals.size();\n\
    \n    std::vector<T> dp(n << k);\n    std::vector<int> prv(n << k, -1);\n\n  \
    \  auto f = [&](int i, int s) -> int {\n        assert(0 <= s and s < (1 << k));\n\
    \        return (i << k) + s;\n    };\n\n    for (int i = 0; i < n; ++i) prv.at(f(i,\
    \ 0)) = f(i, 0);\n\n    for (int j = 0; j < k; ++j) {\n        const int i = terminals.at(j);\n\
    \        prv.at(f(i, 1 << j)) = f(i, 0);\n    }\n\n    for (int s = 0; s < (1\
    \ << k); ++s) {\n        for (int i = 0; i < n; ++i) {\n            for (int t\
    \ = (s - 1) & s; t; t = (t - 1) & s) {\n                if (prv.at(f(i, t)) ==\
    \ -1) continue;\n                if (prv.at(f(i, s ^ t)) == -1) continue;\n  \
    \              const T new_cost = dp.at(f(i, t)) + dp.at(f(i, s ^ t));\n     \
    \           if (new_cost < dp.at(f(i, s)) or prv.at(f(i, s)) == -1) {\n      \
    \              dp.at(f(i, s)) = new_cost;\n                    prv.at(f(i, s))\
    \ = f(i, t);\n                    assert(s >= t);\n                }\n       \
    \     }\n        }\n\n        using P = std::pair<T, int>;\n        std::priority_queue<P,\
    \ std::vector<P>, std::greater<>> pq;\n\n        for (int i = 0; i < n; ++i) {\n\
    \            if (prv.at(f(i, s)) != -1) pq.emplace(dp.at(f(i, s)), i);\n     \
    \   }\n\n        while (!pq.empty()) {\n            auto [cost, i] = pq.top();\n\
    \            pq.pop();\n            if (dp.at(f(i, s)) < cost) continue;\n   \
    \         for (auto [j, edge_id, w] : to.at(i)) {\n                if (prv.at(f(j,\
    \ s)) != -1 and dp.at(f(j, s)) <= cost + w) continue;\n                dp.at(f(j,\
    \ s)) = cost + w;\n                prv.at(f(j, s)) = f(edge_id, s);\n        \
    \        pq.emplace(dp.at(f(j, s)), j);\n            }\n        }\n    }\n\n \
    \   T ans = dp.at(f(0, (1 << k) - 1));\n    int argmin = 0;\n    for (int i =\
    \ 1; i < n; ++i) {\n        if (dp.at(f(i, (1 << k) - 1)) < ans) {\n         \
    \   ans = dp.at(f(i, (1 << k) - 1));\n            argmin = i;\n        }\n   \
    \ }\n\n    std::vector<int> used_edges;\n\n    auto rec = [&](auto &&self, int\
    \ cur) -> void {\n        const int mask = cur & ((1 << k) - 1);\n        if (!mask)\
    \ return;\n        const int i = cur >> k;\n        const int prv_mask = prv.at(cur)\
    \ & ((1 << k) - 1);\n        if (prv_mask == 0) return;\n\n        if (mask ==\
    \ prv_mask) {\n            const int edge_id = prv.at(cur) >> k;\n           \
    \ used_edges.emplace_back(edge_id);\n            const int nxt = i ^ std::get<0>(edges.at(edge_id))\
    \ ^ std::get<1>(edges.at(edge_id));\n            self(self, f(nxt, mask));\n \
    \       } else {\n            self(self, f(i, prv_mask));\n            self(self,\
    \ f(i, mask ^ prv_mask));\n        }\n    };\n    rec(rec, f(argmin, (1 << k)\
    \ - 1));\n\n    std::sort(used_edges.begin(), used_edges.end());\n\n    return\
    \ {ans, used_edges};\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/minimum_steiner_tree.hpp
  requiredBy: []
  timestamp: '2025-08-10 22:59:17+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - graph/test/minimum_steiner_tree.test.cpp
documentation_of: graph/minimum_steiner_tree.hpp
layout: document
title: "Minimum Steiner tree \uFF08\u6700\u5C0F\u30B7\u30E5\u30BF\u30A4\u30CA\u30FC\
  \u6728\uFF09"
---

各辺重みが非負の $n$ 頂点 $m$ 辺無向グラフとその $k$ 個の頂点からなるターミナル集合を入力として，最小シュタイナー木を $O(3^k n + 2^k m \log m)$ で求める．

## 使用方法

```cpp
int N;
vector<tuple<int, int, long long>> edges;
vector<int> terminals;

const auto [total_cost, used_edge_ids] = MinimumSteinerTree(N, edges, terminals);
```

## 問題例

- [Library Checker - Minimum Steiner Tree](https://judge.yosupo.jp/problem/minimum_steiner_tree)
- [No.114 遠い未来 - yukicoder](https://yukicoder.me/problems/no/114)
