---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: tree/frequency_table_of_tree_distance.hpp
    title: Frequency table of tree distance
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: tree/test/frequency_table_of_tree_distance.stress.test.cpp
    title: tree/test/frequency_table_of_tree_distance.stress.test.cpp
  - icon: ':heavy_check_mark:'
    path: tree/test/frequency_table_of_tree_distance.test.cpp
    title: tree/test/frequency_table_of_tree_distance.test.cpp
  - icon: ':heavy_check_mark:'
    path: tree/test/frequency_table_of_tree_distance_ntt.test.cpp
    title: tree/test/frequency_table_of_tree_distance_ntt.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://yukicoder.me/problems/no/2892
  bundledCode: "#line 2 \"tree/centroid_decomposition.hpp\"\n#include <cassert>\n\
    #include <utility>\n#include <vector>\n\n// Centroid Decomposition\n// Verification:\
    \ https://yukicoder.me/problems/no/2892\n// find_current_centroids(int r, int\
    \ conn_size): Enumerate centroid(s) of the subtree which `r` belongs to.\nstruct\
    \ CentroidDecomposition {\n    int V;\n    std::vector<std::vector<int>> to;\n\
    \nprivate:\n    std::vector<int> is_alive;\n    std::vector<int> subtree_size;\n\
    \n    template <class F> void decompose(int r, int conn_size, F callback) {\n\n\
    \        const int c = find_current_centroids(r, conn_size).first;\n        is_alive.at(c)\
    \ = 0;\n\n        callback(c);\n\n        for (int nxt : to.at(c)) {\n       \
    \     if (!is_alive.at(nxt)) continue;\n            int next_size = subtree_size.at(nxt);\n\
    \            if (subtree_size.at(nxt) > subtree_size.at(c))\n                next_size\
    \ = subtree_size.at(r) - subtree_size.at(c);\n            decompose(nxt, next_size,\
    \ callback);\n        }\n    }\n\npublic:\n    CentroidDecomposition(int v = 0)\
    \ : V(v), to(v), is_alive(v, 1), subtree_size(v) {}\n\n    CentroidDecomposition(int\
    \ v, const std::vector<std::pair<int, int>> &tree_edges)\n        : CentroidDecomposition(v)\
    \ {\n        for (auto e : tree_edges) add_edge(e.first, e.second);\n    }\n\n\
    \    void add_edge(int v1, int v2) {\n        assert(0 <= v1 and v1 < V and 0\
    \ <= v2 and v2 < V);\n        assert(v1 != v2);\n        to.at(v1).push_back(v2),\
    \ to.at(v2).emplace_back(v1);\n    }\n\n    std::pair<int, int> find_current_centroids(int\
    \ r, int conn_size) {\n        assert(is_alive.at(r));\n\n        const int thres\
    \ = conn_size / 2;\n\n        int c1 = -1, c2 = -1;\n\n        auto rec_search\
    \ = [&](auto &&self, int now, int prv) -> void {\n            bool is_centroid\
    \ = true;\n            subtree_size.at(now) = 1;\n            for (int nxt : to.at(now))\
    \ {\n                if (nxt == prv or !is_alive.at(nxt)) continue;\n        \
    \        self(self, nxt, now);\n                subtree_size.at(now) += subtree_size.at(nxt);\n\
    \                if (subtree_size.at(nxt) > thres) is_centroid = false;\n    \
    \        }\n            if (conn_size - subtree_size.at(now) > thres) is_centroid\
    \ = false;\n\n            if (is_centroid) (c1 < 0 ? c1 : c2) = now;\n       \
    \ };\n        rec_search(rec_search, r, -1);\n\n        return {c1, c2};\n   \
    \ }\n\n    template <class F> void run(int r, F callback) {\n        int conn_size\
    \ = 0;\n\n        auto rec = [&](auto &&self, int now, int prv) -> void {\n  \
    \          ++conn_size;\n            is_alive.at(now) = 1;\n\n            for\
    \ (int nxt : to.at(now)) {\n                if (nxt == prv) continue;\n      \
    \          self(self, nxt, now);\n            }\n        };\n        rec(rec,\
    \ r, -1);\n\n        decompose(r, conn_size, callback);\n    }\n\n    std::vector<int>\
    \ centroid_decomposition(int r) {\n        std::vector<int> res;\n        run(r,\
    \ [&](int v) { res.push_back(v); });\n        return res;\n    }\n};\n"
  code: "#pragma once\n#include <cassert>\n#include <utility>\n#include <vector>\n\
    \n// Centroid Decomposition\n// Verification: https://yukicoder.me/problems/no/2892\n\
    // find_current_centroids(int r, int conn_size): Enumerate centroid(s) of the\
    \ subtree which `r` belongs to.\nstruct CentroidDecomposition {\n    int V;\n\
    \    std::vector<std::vector<int>> to;\n\nprivate:\n    std::vector<int> is_alive;\n\
    \    std::vector<int> subtree_size;\n\n    template <class F> void decompose(int\
    \ r, int conn_size, F callback) {\n\n        const int c = find_current_centroids(r,\
    \ conn_size).first;\n        is_alive.at(c) = 0;\n\n        callback(c);\n\n \
    \       for (int nxt : to.at(c)) {\n            if (!is_alive.at(nxt)) continue;\n\
    \            int next_size = subtree_size.at(nxt);\n            if (subtree_size.at(nxt)\
    \ > subtree_size.at(c))\n                next_size = subtree_size.at(r) - subtree_size.at(c);\n\
    \            decompose(nxt, next_size, callback);\n        }\n    }\n\npublic:\n\
    \    CentroidDecomposition(int v = 0) : V(v), to(v), is_alive(v, 1), subtree_size(v)\
    \ {}\n\n    CentroidDecomposition(int v, const std::vector<std::pair<int, int>>\
    \ &tree_edges)\n        : CentroidDecomposition(v) {\n        for (auto e : tree_edges)\
    \ add_edge(e.first, e.second);\n    }\n\n    void add_edge(int v1, int v2) {\n\
    \        assert(0 <= v1 and v1 < V and 0 <= v2 and v2 < V);\n        assert(v1\
    \ != v2);\n        to.at(v1).push_back(v2), to.at(v2).emplace_back(v1);\n    }\n\
    \n    std::pair<int, int> find_current_centroids(int r, int conn_size) {\n   \
    \     assert(is_alive.at(r));\n\n        const int thres = conn_size / 2;\n\n\
    \        int c1 = -1, c2 = -1;\n\n        auto rec_search = [&](auto &&self, int\
    \ now, int prv) -> void {\n            bool is_centroid = true;\n            subtree_size.at(now)\
    \ = 1;\n            for (int nxt : to.at(now)) {\n                if (nxt == prv\
    \ or !is_alive.at(nxt)) continue;\n                self(self, nxt, now);\n   \
    \             subtree_size.at(now) += subtree_size.at(nxt);\n                if\
    \ (subtree_size.at(nxt) > thres) is_centroid = false;\n            }\n       \
    \     if (conn_size - subtree_size.at(now) > thres) is_centroid = false;\n\n \
    \           if (is_centroid) (c1 < 0 ? c1 : c2) = now;\n        };\n        rec_search(rec_search,\
    \ r, -1);\n\n        return {c1, c2};\n    }\n\n    template <class F> void run(int\
    \ r, F callback) {\n        int conn_size = 0;\n\n        auto rec = [&](auto\
    \ &&self, int now, int prv) -> void {\n            ++conn_size;\n            is_alive.at(now)\
    \ = 1;\n\n            for (int nxt : to.at(now)) {\n                if (nxt ==\
    \ prv) continue;\n                self(self, nxt, now);\n            }\n     \
    \   };\n        rec(rec, r, -1);\n\n        decompose(r, conn_size, callback);\n\
    \    }\n\n    std::vector<int> centroid_decomposition(int r) {\n        std::vector<int>\
    \ res;\n        run(r, [&](int v) { res.push_back(v); });\n        return res;\n\
    \    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: tree/centroid_decomposition.hpp
  requiredBy:
  - tree/frequency_table_of_tree_distance.hpp
  timestamp: '2024-09-25 00:42:32+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - tree/test/frequency_table_of_tree_distance.stress.test.cpp
  - tree/test/frequency_table_of_tree_distance_ntt.test.cpp
  - tree/test/frequency_table_of_tree_distance.test.cpp
documentation_of: tree/centroid_decomposition.hpp
layout: document
title: "Centroid decomposition \uFF08\u68EE\u306E\u91CD\u5FC3\u5206\u89E3\uFF09"
---

与えられた森について，指定された頂点に関する連結成分の重心分解を行う．

## 使用方法

```cpp
int v = 0;

// 頂点 v の連結成分を重心分解していく
for (int c : cd.centroid_decomposition(v)) {
    // 頂点 c を削除する
}
```

## 問題例

- [No.2892 Lime and Karin - yukicoder](https://yukicoder.me/problems/no/2892)
