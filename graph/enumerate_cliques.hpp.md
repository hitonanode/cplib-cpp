---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: graph/test/enumerate_cliques.aoj2306.test.cpp
    title: graph/test/enumerate_cliques.aoj2306.test.cpp
  - icon: ':heavy_check_mark:'
    path: graph/test/enumerate_cliques.test.cpp
    title: graph/test/enumerate_cliques.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Enumerate all cliques of given undirected graph
    links:
    - https://judge.yosupo.jp/problem/enumerate_cliques
    - https://www.slideshare.net/wata_orz/ss-12131479
  bundledCode: "#line 2 \"graph/enumerate_cliques.hpp\"\n\n/**\n * @file enumerate_cliques.hpp\n\
    \ * @brief Enumerate all cliques of given undirected graph\n * @author hitonanode\n\
    \ * @date 2023/03/10\n */\n\n#include <algorithm>\n#include <cassert>\n#include\
    \ <numeric>\n#include <queue>\n#include <utility>\n#include <vector>\n\n// Complexity:\
    \ O(2^sqrt(2m) * n)\n// Verify: https://judge.yosupo.jp/problem/enumerate_cliques\
    \ (~1ms for n <= 100, m <= 100)\n// p.15, https://www.slideshare.net/wata_orz/ss-12131479\n\
    struct enumerate_cliques {\n    std::vector<std::vector<int>> to;\n    std::vector<std::pair<int,\
    \ int>> edges;\n\n    int n() const { return to.size(); }\n    int m() const {\
    \ return edges.size(); }\n\n    enumerate_cliques(int n_) : to(n_) {}\n\n    void\
    \ add_bi_edge(int u, int v) {\n        assert(0 <= u and u < n());\n        assert(0\
    \ <= v and v < n());\n        if (u != v) edges.emplace_back(std::minmax(u, v));\n\
    \    }\n\n    // Build `to`\n    void precalc() {\n        std::sort(edges.begin(),\
    \ edges.end());\n        edges.erase(std::unique(edges.begin(), edges.end()),\
    \ edges.end());\n\n        for (auto &vec : to) vec.clear();\n        for (auto\
    \ [u, v] : edges) to.at(u).push_back(v), to.at(v).push_back(u);\n        for (auto\
    \ &vec : to) std::sort(vec.begin(), vec.end());\n    }\n\n    template <class\
    \ F>\n    void bruteforce(const std::vector<int> &cand_vs, int prefix_use, F op)\
    \ const {\n        const int k = cand_vs.size();\n        const int mask_all =\
    \ (1 << k) - 1;\n        std::vector<int> ok_masks(k, mask_all);\n\n        for\
    \ (int i = 0; i < k; ++i) {\n            for (int j = 0; j < i; ++j) {\n     \
    \           int u = cand_vs.at(i), v = cand_vs.at(j);\n                if (!std::binary_search(to.at(u).cbegin(),\
    \ to.at(u).cend(), v)) {\n                    ok_masks.at(i) &= ~(1 << j), ok_masks.at(j)\
    \ &= ~(1 << i);\n                }\n            }\n        }\n\n        std::vector<int>\
    \ seq;\n        if (prefix_use >= 0) seq.push_back(prefix_use);\n        seq.reserve(seq.size()\
    \ + k);\n\n        auto rec = [&](auto &&self, int now, const int last_mask) ->\
    \ void {\n            op(seq);\n            seq.push_back(-1);\n            for\
    \ (int i = now; i < k; ++i) {\n                if ((last_mask >> i) & 1) {\n \
    \                   seq.back() = cand_vs.at(i);\n                    self(self,\
    \ i + 1, last_mask & ok_masks.at(i));\n                }\n            }\n    \
    \        seq.pop_back();\n        };\n        rec(rec, 0, mask_all);\n       \
    \ return;\n    }\n\n    template <class F> void run(F op) {\n        precalc();\n\
    \n        std::vector<int> deg(n()), is_alive(n(), 1);\n        using P = std::pair<int,\
    \ int>;\n        std::priority_queue<P, std::vector<P>, std::greater<P>> pq;\n\
    \        for (int i = 0; i < n(); ++i) deg.at(i) = to.at(i).size(), pq.emplace(deg.at(i),\
    \ i);\n\n        int rem_n = n(), rem_m = m();\n\n        std::vector<int> cand_vs;\n\
    \        while (!pq.empty()) {\n            auto [di, i] = pq.top();\n       \
    \     pq.pop();\n            if (deg.at(i) != di) continue;\n\n            cand_vs.clear();\n\
    \n            if (di * di > rem_m * 2) { // Avoid \"deg[i] = 0\" case\n      \
    \          for (int i = 0; i < n(); ++i) {\n                    if (is_alive.at(i))\
    \ cand_vs.push_back(i);\n                }\n                bruteforce(cand_vs,\
    \ -1, op);\n                break;\n            }\n\n            for (int j :\
    \ to.at(i)) {\n                if (is_alive.at(j)) cand_vs.push_back(j);\n   \
    \         }\n            bruteforce(cand_vs, i, op);\n\n            --rem_n, deg.at(i)\
    \ = 0, is_alive.at(i) = 0;\n            for (int j : cand_vs) --rem_m, --deg.at(j),\
    \ pq.emplace(deg.at(j), j);\n        }\n    }\n};\n"
  code: "#pragma once\n\n/**\n * @file enumerate_cliques.hpp\n * @brief Enumerate\
    \ all cliques of given undirected graph\n * @author hitonanode\n * @date 2023/03/10\n\
    \ */\n\n#include <algorithm>\n#include <cassert>\n#include <numeric>\n#include\
    \ <queue>\n#include <utility>\n#include <vector>\n\n// Complexity: O(2^sqrt(2m)\
    \ * n)\n// Verify: https://judge.yosupo.jp/problem/enumerate_cliques (~1ms for\
    \ n <= 100, m <= 100)\n// p.15, https://www.slideshare.net/wata_orz/ss-12131479\n\
    struct enumerate_cliques {\n    std::vector<std::vector<int>> to;\n    std::vector<std::pair<int,\
    \ int>> edges;\n\n    int n() const { return to.size(); }\n    int m() const {\
    \ return edges.size(); }\n\n    enumerate_cliques(int n_) : to(n_) {}\n\n    void\
    \ add_bi_edge(int u, int v) {\n        assert(0 <= u and u < n());\n        assert(0\
    \ <= v and v < n());\n        if (u != v) edges.emplace_back(std::minmax(u, v));\n\
    \    }\n\n    // Build `to`\n    void precalc() {\n        std::sort(edges.begin(),\
    \ edges.end());\n        edges.erase(std::unique(edges.begin(), edges.end()),\
    \ edges.end());\n\n        for (auto &vec : to) vec.clear();\n        for (auto\
    \ [u, v] : edges) to.at(u).push_back(v), to.at(v).push_back(u);\n        for (auto\
    \ &vec : to) std::sort(vec.begin(), vec.end());\n    }\n\n    template <class\
    \ F>\n    void bruteforce(const std::vector<int> &cand_vs, int prefix_use, F op)\
    \ const {\n        const int k = cand_vs.size();\n        const int mask_all =\
    \ (1 << k) - 1;\n        std::vector<int> ok_masks(k, mask_all);\n\n        for\
    \ (int i = 0; i < k; ++i) {\n            for (int j = 0; j < i; ++j) {\n     \
    \           int u = cand_vs.at(i), v = cand_vs.at(j);\n                if (!std::binary_search(to.at(u).cbegin(),\
    \ to.at(u).cend(), v)) {\n                    ok_masks.at(i) &= ~(1 << j), ok_masks.at(j)\
    \ &= ~(1 << i);\n                }\n            }\n        }\n\n        std::vector<int>\
    \ seq;\n        if (prefix_use >= 0) seq.push_back(prefix_use);\n        seq.reserve(seq.size()\
    \ + k);\n\n        auto rec = [&](auto &&self, int now, const int last_mask) ->\
    \ void {\n            op(seq);\n            seq.push_back(-1);\n            for\
    \ (int i = now; i < k; ++i) {\n                if ((last_mask >> i) & 1) {\n \
    \                   seq.back() = cand_vs.at(i);\n                    self(self,\
    \ i + 1, last_mask & ok_masks.at(i));\n                }\n            }\n    \
    \        seq.pop_back();\n        };\n        rec(rec, 0, mask_all);\n       \
    \ return;\n    }\n\n    template <class F> void run(F op) {\n        precalc();\n\
    \n        std::vector<int> deg(n()), is_alive(n(), 1);\n        using P = std::pair<int,\
    \ int>;\n        std::priority_queue<P, std::vector<P>, std::greater<P>> pq;\n\
    \        for (int i = 0; i < n(); ++i) deg.at(i) = to.at(i).size(), pq.emplace(deg.at(i),\
    \ i);\n\n        int rem_n = n(), rem_m = m();\n\n        std::vector<int> cand_vs;\n\
    \        while (!pq.empty()) {\n            auto [di, i] = pq.top();\n       \
    \     pq.pop();\n            if (deg.at(i) != di) continue;\n\n            cand_vs.clear();\n\
    \n            if (di * di > rem_m * 2) { // Avoid \"deg[i] = 0\" case\n      \
    \          for (int i = 0; i < n(); ++i) {\n                    if (is_alive.at(i))\
    \ cand_vs.push_back(i);\n                }\n                bruteforce(cand_vs,\
    \ -1, op);\n                break;\n            }\n\n            for (int j :\
    \ to.at(i)) {\n                if (is_alive.at(j)) cand_vs.push_back(j);\n   \
    \         }\n            bruteforce(cand_vs, i, op);\n\n            --rem_n, deg.at(i)\
    \ = 0, is_alive.at(i) = 0;\n            for (int j : cand_vs) --rem_m, --deg.at(j),\
    \ pq.emplace(deg.at(j), j);\n        }\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/enumerate_cliques.hpp
  requiredBy: []
  timestamp: '2023-03-10 15:00:17+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - graph/test/enumerate_cliques.aoj2306.test.cpp
  - graph/test/enumerate_cliques.test.cpp
documentation_of: graph/enumerate_cliques.hpp
layout: document
title: "Enumerate cliques \uFF08\u30B0\u30E9\u30D5\u306E\u30AF\u30EA\u30FC\u30AF\u5168\
  \u5217\u6319\uFF09"
---

与えられた $n$ 頂点 $m$ 辺の無向グラフのクリーク（完全グラフとなる部分グラフ）を全列挙する．計算量は $O(2^{\sqrt{2m}} n)$．

## 使用方法

```cpp
int n;  // Num. of vertices
enumerate_cliques ec(n);

for (auto [u, v] : edges) {
    ec.add_bi_edge(u, v);  // 0 <= u, v < n
}

vector<vector<int>> cliques;

auto op = [&](const vector<int> &clique) {
    // `clique` is NOT guranteed to be sorted
    cliques.push_back(clique);
};

ec.run(op);  // op() runs over all cliques
```

## 問題例

- [Library Checker: Enumerate Cliques](https://judge.yosupo.jp/problem/enumerate_cliques)
- [AOJ 2306: Rabbit Party](https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2306)
