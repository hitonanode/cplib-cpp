---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
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
  bundledCode: "#line 2 \"combinatorial_opt/matroid_intersection_dijkstra.hpp\"\n\n\
    #include <cassert>\n#include <queue>\n#include <vector>\n\n// Find maximum weight\
    \ size k + 1 intersection of two matroids using Dijkstra's algorithm\n// Return\
    \ `true` iff larger intersection is found.\n// Complexity: O(Cn + nk log n) (C:\
    \ circuit query)\ntemplate <class Matroid1, class Matroid2, class T = int>\nbool\
    \ augment_matroid_intersection_dijkstra(\n    Matroid1 &m1,                 //\
    \ Matroid, size n, updated\n    Matroid2 &m2,                 // Matroid, size\
    \ n, updated\n    std::vector<bool> &I,         // Size k maximum weight intersection,\
    \ size n, updated\n    const std::vector<T> &weight, // Weights of elements, size\
    \ n\n    std::vector<T> &potential     // Potential, size n + 2, updated\n) {\n\
    \    const int n = I.size();\n\n    assert((int)m1.size() == n);\n    assert((int)m2.size()\
    \ == n);\n    assert((int)weight.size() == n);\n    assert(potential.empty() or\
    \ ((int)potential.size() == n) or ((int)potential.size() == n + 2));\n\n    m1.set(I);\n\
    \    m2.set(I);\n\n    potential.resize(n + 2);\n\n    auto l = [&](int e) ->\
    \ T { return e < n ? (I.at(e) ? weight.at(e) : -weight.at(e)) : T(); };\n    auto\
    \ edge_len = [&](int s, int t) -> T { return l(t) - potential.at(t) + potential.at(s);\
    \ };\n\n    // Find minimum length (& minimum num. of vertices) gs-gt path\n \
    \   const int gs = n, gt = n + 1;\n    std::vector<std::vector<int>> to(gt + 1);\n\
    \n    bool has_gs_edge = false, has_gt_edge = false;\n\n    for (int e = 0; e\
    \ < n; ++e) {\n        if (I.at(e)) continue;\n\n        const auto c1 = m1.circuit(e),\
    \ c2 = m2.circuit(e);\n\n        if (c1.empty()) {\n            to.at(e).push_back(gt);\n\
    \            if (!has_gt_edge) {\n                has_gt_edge = true;\n      \
    \          potential.at(gt) = potential.at(e);\n            }\n            if\
    \ (T el = edge_len(e, gt); el < T()) potential.at(gt) += el;\n        }\n    \
    \    for (int f : c1) {\n            if (f != e) to.at(e).push_back(f);\n    \
    \    }\n\n        if (c2.empty()) {\n            to.at(gs).push_back(e);\n   \
    \         if (!has_gs_edge) {\n                has_gs_edge = true;\n         \
    \       potential.at(gs) = potential.at(e) - l(e);\n            }\n          \
    \  if (T el = edge_len(gs, e); el < T()) potential.at(gs) -= el;\n        }\n\
    \        for (int f : c2) {\n            if (f != e) to.at(f).push_back(e);\n\
    \        }\n    }\n\n    if (const T e0 = potential.at(gs); e0 != T()) {\n   \
    \     for (auto &p : potential) p -= e0;\n    }\n\n    if (!has_gs_edge or !has_gt_edge)\
    \ return false;\n\n    std::vector<bool> potential_fixed(gt + 1);\n\n    T potential_add_unfixed_es\
    \ = T();\n\n    auto fix_potential = [&](int e) -> void {\n        assert(!potential_fixed.at(e));\n\
    \        potential_fixed.at(e) = true;\n        potential.at(e) += potential_add_unfixed_es;\n\
    \    };\n\n    std::priority_queue<std::pair<T, int>, std::vector<std::pair<T,\
    \ int>>, std::greater<>> pq;\n    std::vector<T> dijkstra(gt + 1);\n    std::vector<int>\
    \ prv(gt + 1, -1);\n\n    pq.emplace(T(), gs);\n\n    while (!pq.empty()) {\n\
    \        const int e = pq.top().second;\n        pq.pop();\n        if (potential_fixed.at(e))\
    \ continue;\n        if (e != gs) potential_add_unfixed_es = edge_len(prv.at(e),\
    \ e);\n\n        std::vector<std::pair<int, int>> push_cands;\n\n        auto\
    \ rec = [&](auto &&self, int cur) -> bool {\n            if (cur == gt) return\
    \ true;\n            fix_potential(cur);\n\n            for (int nxt : to.at(cur))\
    \ {\n                if (potential_fixed.at(nxt)) continue;\n\n              \
    \  const T len = edge_len(cur, nxt) - potential_add_unfixed_es;\n            \
    \    // if (len < T()) std::cerr << cur << ' ' << nxt << ' ' << len << std::endl;\n\
    \                assert(len >= T());\n\n                if (len == T()) {\n  \
    \                  prv.at(nxt) = cur;\n                    if (self(self, nxt))\
    \ return true;\n                } else {\n                    if (prv.at(nxt)\
    \ == -1 or potential_add_unfixed_es + len < dijkstra.at(nxt)) {\n            \
    \            dijkstra.at(nxt) = potential_add_unfixed_es + len;\n            \
    \            prv.at(nxt) = cur;\n                        push_cands.emplace_back(nxt,\
    \ cur);\n                    }\n                }\n            }\n           \
    \ return false;\n        };\n        if (rec(rec, e)) break;\n\n        for (auto\
    \ [nxt, now] : push_cands) {\n            if (prv.at(nxt) == now) pq.emplace(dijkstra.at(nxt),\
    \ nxt);\n        }\n    }\n\n    for (int e = 0; e < gt + 1; ++e) {\n        if\
    \ (!potential_fixed.at(e)) fix_potential(e);\n    }\n\n    if (prv.at(gt) < 0)\
    \ return false;\n\n    prv.assign(gt + 1, -1);\n    std::queue<int> q;\n    q.push(gs);\n\
    \n    for (int now = q.front(); now != gt; now = q.front()) {\n        q.pop();\n\
    \        for (int nxt : to.at(now)) {\n            if (prv.at(nxt) == -1 and edge_len(now,\
    \ nxt) == T()) {\n                prv.at(nxt) = now;\n                q.push(nxt);\n\
    \            }\n        }\n    }\n\n    for (int e = prv.at(gt); e != gs; e =\
    \ prv.at(e)) {\n        potential.at(e) -= l(e);\n        I.at(e) = !I.at(e);\n\
    \    }\n\n    return true;\n}\n"
  code: "#pragma once\n\n#include <cassert>\n#include <queue>\n#include <vector>\n\
    \n// Find maximum weight size k + 1 intersection of two matroids using Dijkstra's\
    \ algorithm\n// Return `true` iff larger intersection is found.\n// Complexity:\
    \ O(Cn + nk log n) (C: circuit query)\ntemplate <class Matroid1, class Matroid2,\
    \ class T = int>\nbool augment_matroid_intersection_dijkstra(\n    Matroid1 &m1,\
    \                 // Matroid, size n, updated\n    Matroid2 &m2,             \
    \    // Matroid, size n, updated\n    std::vector<bool> &I,         // Size k\
    \ maximum weight intersection, size n, updated\n    const std::vector<T> &weight,\
    \ // Weights of elements, size n\n    std::vector<T> &potential     // Potential,\
    \ size n + 2, updated\n) {\n    const int n = I.size();\n\n    assert((int)m1.size()\
    \ == n);\n    assert((int)m2.size() == n);\n    assert((int)weight.size() == n);\n\
    \    assert(potential.empty() or ((int)potential.size() == n) or ((int)potential.size()\
    \ == n + 2));\n\n    m1.set(I);\n    m2.set(I);\n\n    potential.resize(n + 2);\n\
    \n    auto l = [&](int e) -> T { return e < n ? (I.at(e) ? weight.at(e) : -weight.at(e))\
    \ : T(); };\n    auto edge_len = [&](int s, int t) -> T { return l(t) - potential.at(t)\
    \ + potential.at(s); };\n\n    // Find minimum length (& minimum num. of vertices)\
    \ gs-gt path\n    const int gs = n, gt = n + 1;\n    std::vector<std::vector<int>>\
    \ to(gt + 1);\n\n    bool has_gs_edge = false, has_gt_edge = false;\n\n    for\
    \ (int e = 0; e < n; ++e) {\n        if (I.at(e)) continue;\n\n        const auto\
    \ c1 = m1.circuit(e), c2 = m2.circuit(e);\n\n        if (c1.empty()) {\n     \
    \       to.at(e).push_back(gt);\n            if (!has_gt_edge) {\n           \
    \     has_gt_edge = true;\n                potential.at(gt) = potential.at(e);\n\
    \            }\n            if (T el = edge_len(e, gt); el < T()) potential.at(gt)\
    \ += el;\n        }\n        for (int f : c1) {\n            if (f != e) to.at(e).push_back(f);\n\
    \        }\n\n        if (c2.empty()) {\n            to.at(gs).push_back(e);\n\
    \            if (!has_gs_edge) {\n                has_gs_edge = true;\n      \
    \          potential.at(gs) = potential.at(e) - l(e);\n            }\n       \
    \     if (T el = edge_len(gs, e); el < T()) potential.at(gs) -= el;\n        }\n\
    \        for (int f : c2) {\n            if (f != e) to.at(f).push_back(e);\n\
    \        }\n    }\n\n    if (const T e0 = potential.at(gs); e0 != T()) {\n   \
    \     for (auto &p : potential) p -= e0;\n    }\n\n    if (!has_gs_edge or !has_gt_edge)\
    \ return false;\n\n    std::vector<bool> potential_fixed(gt + 1);\n\n    T potential_add_unfixed_es\
    \ = T();\n\n    auto fix_potential = [&](int e) -> void {\n        assert(!potential_fixed.at(e));\n\
    \        potential_fixed.at(e) = true;\n        potential.at(e) += potential_add_unfixed_es;\n\
    \    };\n\n    std::priority_queue<std::pair<T, int>, std::vector<std::pair<T,\
    \ int>>, std::greater<>> pq;\n    std::vector<T> dijkstra(gt + 1);\n    std::vector<int>\
    \ prv(gt + 1, -1);\n\n    pq.emplace(T(), gs);\n\n    while (!pq.empty()) {\n\
    \        const int e = pq.top().second;\n        pq.pop();\n        if (potential_fixed.at(e))\
    \ continue;\n        if (e != gs) potential_add_unfixed_es = edge_len(prv.at(e),\
    \ e);\n\n        std::vector<std::pair<int, int>> push_cands;\n\n        auto\
    \ rec = [&](auto &&self, int cur) -> bool {\n            if (cur == gt) return\
    \ true;\n            fix_potential(cur);\n\n            for (int nxt : to.at(cur))\
    \ {\n                if (potential_fixed.at(nxt)) continue;\n\n              \
    \  const T len = edge_len(cur, nxt) - potential_add_unfixed_es;\n            \
    \    // if (len < T()) std::cerr << cur << ' ' << nxt << ' ' << len << std::endl;\n\
    \                assert(len >= T());\n\n                if (len == T()) {\n  \
    \                  prv.at(nxt) = cur;\n                    if (self(self, nxt))\
    \ return true;\n                } else {\n                    if (prv.at(nxt)\
    \ == -1 or potential_add_unfixed_es + len < dijkstra.at(nxt)) {\n            \
    \            dijkstra.at(nxt) = potential_add_unfixed_es + len;\n            \
    \            prv.at(nxt) = cur;\n                        push_cands.emplace_back(nxt,\
    \ cur);\n                    }\n                }\n            }\n           \
    \ return false;\n        };\n        if (rec(rec, e)) break;\n\n        for (auto\
    \ [nxt, now] : push_cands) {\n            if (prv.at(nxt) == now) pq.emplace(dijkstra.at(nxt),\
    \ nxt);\n        }\n    }\n\n    for (int e = 0; e < gt + 1; ++e) {\n        if\
    \ (!potential_fixed.at(e)) fix_potential(e);\n    }\n\n    if (prv.at(gt) < 0)\
    \ return false;\n\n    prv.assign(gt + 1, -1);\n    std::queue<int> q;\n    q.push(gs);\n\
    \n    for (int now = q.front(); now != gt; now = q.front()) {\n        q.pop();\n\
    \        for (int nxt : to.at(now)) {\n            if (prv.at(nxt) == -1 and edge_len(now,\
    \ nxt) == T()) {\n                prv.at(nxt) = now;\n                q.push(nxt);\n\
    \            }\n        }\n    }\n\n    for (int e = prv.at(gt); e != gs; e =\
    \ prv.at(e)) {\n        potential.at(e) -= l(e);\n        I.at(e) = !I.at(e);\n\
    \    }\n\n    return true;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: combinatorial_opt/matroid_intersection_dijkstra.hpp
  requiredBy: []
  timestamp: '2023-07-23 18:26:21+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - combinatorial_opt/test/matroid_intersection_dijkstra.aoj_grl_2_b.test.cpp
  - combinatorial_opt/test/matroid_intersection_dijkstra.aoj1605.test.cpp
documentation_of: combinatorial_opt/matroid_intersection_dijkstra.hpp
layout: document
title: Weighted matroid intersection using Dijkstra's algorithm
---

重み付きマトロイド交叉（交差）問題 (matroid intersection) のソルバ．二つのマトロイド $M\_{1} = (E, \mathcal{I}\_{1}), M_{2} = (E, \mathcal{I}\_{2})$ とそのサイズ $k$ 最大重み共通独立集合 $I\_k$ ，および $I\_k$ の導出に使われたポテンシャルを入力とし，サイズ $k + 1$ の最大重み共通独立集合を求めるか，これが存在しないことを示す．引数として与えたポテンシャルは適宜更新される．

計算量は $n = \|E\|$，マトロイドクラスのサーキットクエリ一回あたりの計算量を $c$ として $O(nc + nk \log n)$ である．ポテンシャルの利用により内部で解く最短経路問題の辺重みを全て非負にでき，高速な Dijkstra 法を利用できる．

## 使用方法

```cpp
UserDefinedMatroid m1, m2;
vector<T> weight(n);
vector<T> potential(n + 2);  // 2 個の補助頂点のポテンシャルの情報も持つ
vector<bool> I(n);

assert(m1.size() == n);
assert(m2.size() == n);

while (augment_matroid_intersection_dijkstra(m1, m2, I, weight, potential)) {
    continue;
}
```

## 問題例

- [AOJ GRL_2_B: 最小全域有向木](https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_B) 分割マトロイドとグラフマトロイドの重み付き交差でも解ける．
- [Deltix Round, Summer 2021 H. DIY Tree - Codeforces](https://codeforces.com/contest/1556/problem/H) グラフマトロイドと分割マトロイドの最小重み共通独立集合問題に帰着される．
- [AOJ 1605: Bridge Construction Planning （橋の建造計画）](https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1605&lang=ja) 分割マトロイドとグラフマトロイドの重み付き交差．
- [2021 ICPC Asia Taiwan Online Programming Contest I. ICPC Kingdom - Codeforces](http://codeforces.com/gym/103373/problem/I) 横断マトロイドとグラフマトロイドの重み付き交差（横断マトロイドを考える代わりに辺を仮想的に増やし，分割マトロイドと解釈することも可能）．

## 文献・リンク集

- [1] C. Brezovec, G. Cornuéjols, and F. Glover, "Two algorithms for weighted matroid intersection,"
  Mathematical Programming, 36(1), 39-53, 1986.
