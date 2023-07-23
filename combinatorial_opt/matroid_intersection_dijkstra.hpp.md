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
    \ n\n    std::vector<T> &potential     // Potential, size n, updated\n) {\n  \
    \  const int n = I.size();\n\n    assert((int)m1.size() == n);\n    assert((int)m2.size()\
    \ == n);\n    assert((int)weight.size() == n);\n    assert((int)potential.size()\
    \ == n);\n\n    m1.set(I);\n    m2.set(I);\n\n    {\n        int arghi = -1;\n\
    \        for (int e = 0; e < n; ++e) {\n            if (I.at(e)) continue;\n \
    \           if (arghi < 0 or weight.at(arghi) < weight.at(e)) arghi = e;\n   \
    \     }\n        if (arghi < 0) return false;\n        if (m1.circuit(arghi).empty()\
    \ and m2.circuit(arghi).empty()) {\n            I.at(arghi) = true;\n        \
    \    return true;\n        }\n    }\n\n    auto l = [&](int e) -> T { return e\
    \ < n ? (I.at(e) ? weight.at(e) : -weight.at(e)) : T(); };\n    auto pot = [&](int\
    \ e) -> T { return e < n ? potential.at(e) : T(); };\n    auto edge_len = [&](int\
    \ s, int t) -> T { return l(t) - pot(t) + pot(s); };\n\n    const int gs = n,\
    \ gt = n + 1;\n    std::vector<int> on_set;\n    for (int e = 0; e < n; ++e) {\n\
    \        if (I.at(e)) on_set.push_back(e);\n    }\n\n    // Find minimum weight\
    \ (& minimum num. of vertices) gs-gt path\n    using Dist = std::pair<T, int>;\
    \ // (sum of weights, num. of vertices)\n    std::vector<Dist> dp(gt + 1, {-1,\
    \ -1});\n    std::vector<int> prv(gt + 1, -1); // prv[i] >= 0 => i is reachable\
    \ (i != gs)\n\n    using Tpl = std::pair<Dist, int>;\n    std::priority_queue<Tpl,\
    \ std::vector<Tpl>, std::greater<Tpl>> pq; // (dist, len, now)\n    std::vector<std::vector<int>>\
    \ to(dp.size());\n\n    for (int e = 0; e < n; ++e) {\n        if (I.at(e)) continue;\n\
    \n        const auto c1 = m1.circuit(e), c2 = m2.circuit(e);\n\n        if (c1.empty())\
    \ {\n            to.at(e).push_back(gt);\n            for (int f : on_set) to.at(e).push_back(f);\n\
    \        }\n        for (int f : c1) {\n            if (f != e) to.at(e).push_back(f);\n\
    \        }\n\n        if (c2.empty()) {\n            dp.at(e) = Dist{edge_len(gs,\
    \ e), 1};\n            prv.at(e) = gs;\n            pq.emplace(dp.at(e), e);\n\
    \        }\n        for (int f : c2) {\n            if (f != e) to.at(f).push_back(e);\n\
    \        }\n    }\n\n    while (!pq.empty()) {\n        const auto [dnow, now]\
    \ = pq.top();\n        pq.pop();\n        if (prv.at(now) >= 0 and dp.at(now)\
    \ < dnow) continue;\n\n        for (int nxt : to.at(now)) {\n            const\
    \ auto w = edge_len(now, nxt);\n            // if (w < T() and now < n and nxt\
    \ < n) assert(false); // for debug\n\n            Dist dnxt(dnow.first + w, dnow.second\
    \ + 1);\n\n            if (prv.at(nxt) < 0 or dnxt < dp.at(nxt)) {\n         \
    \       dp.at(nxt) = dnxt;\n                prv.at(nxt) = now;\n             \
    \   if (nxt != gt) pq.emplace(dnxt, nxt);\n            }\n        }\n    }\n\n\
    \    if (prv.at(gt) < 0) return false;\n\n    for (int e = 0; e < n; ++e) {\n\
    \        auto [dist, len] = dp.at(e);\n        if (len >= 0) potential.at(e) +=\
    \ dist;\n    }\n\n    for (int e = prv.at(gt); e != gs; e = prv.at(e)) {\n   \
    \     potential.at(e) -= l(e);\n        I.at(e) = !I.at(e);\n    }\n\n    return\
    \ true;\n}\n"
  code: "#pragma once\n\n#include <cassert>\n#include <queue>\n#include <vector>\n\
    \n// Find maximum weight size k + 1 intersection of two matroids using Dijkstra's\
    \ algorithm\n// Return `true` iff larger intersection is found.\n// Complexity:\
    \ O(Cn + nk log n) (C: circuit query)\ntemplate <class Matroid1, class Matroid2,\
    \ class T = int>\nbool augment_matroid_intersection_dijkstra(\n    Matroid1 &m1,\
    \                 // Matroid, size n, updated\n    Matroid2 &m2,             \
    \    // Matroid, size n, updated\n    std::vector<bool> &I,         // Size k\
    \ maximum weight intersection, size n, updated\n    const std::vector<T> &weight,\
    \ // Weights of elements, size n\n    std::vector<T> &potential     // Potential,\
    \ size n, updated\n) {\n    const int n = I.size();\n\n    assert((int)m1.size()\
    \ == n);\n    assert((int)m2.size() == n);\n    assert((int)weight.size() == n);\n\
    \    assert((int)potential.size() == n);\n\n    m1.set(I);\n    m2.set(I);\n\n\
    \    {\n        int arghi = -1;\n        for (int e = 0; e < n; ++e) {\n     \
    \       if (I.at(e)) continue;\n            if (arghi < 0 or weight.at(arghi)\
    \ < weight.at(e)) arghi = e;\n        }\n        if (arghi < 0) return false;\n\
    \        if (m1.circuit(arghi).empty() and m2.circuit(arghi).empty()) {\n    \
    \        I.at(arghi) = true;\n            return true;\n        }\n    }\n\n \
    \   auto l = [&](int e) -> T { return e < n ? (I.at(e) ? weight.at(e) : -weight.at(e))\
    \ : T(); };\n    auto pot = [&](int e) -> T { return e < n ? potential.at(e) :\
    \ T(); };\n    auto edge_len = [&](int s, int t) -> T { return l(t) - pot(t) +\
    \ pot(s); };\n\n    const int gs = n, gt = n + 1;\n    std::vector<int> on_set;\n\
    \    for (int e = 0; e < n; ++e) {\n        if (I.at(e)) on_set.push_back(e);\n\
    \    }\n\n    // Find minimum weight (& minimum num. of vertices) gs-gt path\n\
    \    using Dist = std::pair<T, int>; // (sum of weights, num. of vertices)\n \
    \   std::vector<Dist> dp(gt + 1, {-1, -1});\n    std::vector<int> prv(gt + 1,\
    \ -1); // prv[i] >= 0 => i is reachable (i != gs)\n\n    using Tpl = std::pair<Dist,\
    \ int>;\n    std::priority_queue<Tpl, std::vector<Tpl>, std::greater<Tpl>> pq;\
    \ // (dist, len, now)\n    std::vector<std::vector<int>> to(dp.size());\n\n  \
    \  for (int e = 0; e < n; ++e) {\n        if (I.at(e)) continue;\n\n        const\
    \ auto c1 = m1.circuit(e), c2 = m2.circuit(e);\n\n        if (c1.empty()) {\n\
    \            to.at(e).push_back(gt);\n            for (int f : on_set) to.at(e).push_back(f);\n\
    \        }\n        for (int f : c1) {\n            if (f != e) to.at(e).push_back(f);\n\
    \        }\n\n        if (c2.empty()) {\n            dp.at(e) = Dist{edge_len(gs,\
    \ e), 1};\n            prv.at(e) = gs;\n            pq.emplace(dp.at(e), e);\n\
    \        }\n        for (int f : c2) {\n            if (f != e) to.at(f).push_back(e);\n\
    \        }\n    }\n\n    while (!pq.empty()) {\n        const auto [dnow, now]\
    \ = pq.top();\n        pq.pop();\n        if (prv.at(now) >= 0 and dp.at(now)\
    \ < dnow) continue;\n\n        for (int nxt : to.at(now)) {\n            const\
    \ auto w = edge_len(now, nxt);\n            // if (w < T() and now < n and nxt\
    \ < n) assert(false); // for debug\n\n            Dist dnxt(dnow.first + w, dnow.second\
    \ + 1);\n\n            if (prv.at(nxt) < 0 or dnxt < dp.at(nxt)) {\n         \
    \       dp.at(nxt) = dnxt;\n                prv.at(nxt) = now;\n             \
    \   if (nxt != gt) pq.emplace(dnxt, nxt);\n            }\n        }\n    }\n\n\
    \    if (prv.at(gt) < 0) return false;\n\n    for (int e = 0; e < n; ++e) {\n\
    \        auto [dist, len] = dp.at(e);\n        if (len >= 0) potential.at(e) +=\
    \ dist;\n    }\n\n    for (int e = prv.at(gt); e != gs; e = prv.at(e)) {\n   \
    \     potential.at(e) -= l(e);\n        I.at(e) = !I.at(e);\n    }\n\n    return\
    \ true;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: combinatorial_opt/matroid_intersection_dijkstra.hpp
  requiredBy: []
  timestamp: '2023-07-23 15:18:37+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - combinatorial_opt/test/matroid_intersection_dijkstra.aoj_grl_2_b.test.cpp
  - combinatorial_opt/test/matroid_intersection_dijkstra.aoj1605.test.cpp
documentation_of: combinatorial_opt/matroid_intersection_dijkstra.hpp
layout: document
title: Weighted matroid intersection using Dijkstra's algorithm
---

重み付きマトロイド交叉（交差）問題 (matroid intersection) のソルバ．二つのマトロイド $M\_{1} = (E, \mathcal{I}\_{1}), M_{2} = (E, \mathcal{I}\_{2})$ とそのサイズ $k$ 最大重み共通独立集合 $I\_k$ ，および $I\_k$ の導出に使われたポテンシャルを入力とし，サイズ $k + 1$ の最大重み共通独立集合を求めるか，これが存在しないことを示す．引数として与えたポテンシャルは適宜更新される．

計算量は $n = \|E\|$，マトロイドクラスのサーキットクエリ一回あたりの計算量を $c$ として $O(nc + nk \log n)$ である．ポテンシャルの利用により内部で解く最短経路問題の辺重みを全て非負にでき，高速な Dijkstra 法を利用できる．ただしコンテストでの実用上は Bellman–Ford 法ベースの `matroid_intersection_augment()` の方が高速に動作するようである．

## 使用方法

```cpp
UserDefinedMatroid m1, m2;
vector<T> weight(n);
vector<T> potential(n);
vector<bool> I(n);

assert(m1.size() == n);
assert(m2.size() == n);

while (augment_matroid_intersection_dijkstra(m1, m2, I, weight, potential)) {
    continue;
}
```

## 問題例

- [AOJ GRL_2_B: 最小全域有向木](https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_B) 分割マトロイドとグラフマトロイドの重み付き交差でも解ける．
- [AOJ 1605: Bridge Construction Planning （橋の建造計画）](https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1605&lang=ja) 分割マトロイドとグラフマトロイドの重み付き交差．
- [2021 ICPC Asia Taiwan Online Programming Contest I. ICPC Kingdom - Codeforces](http://codeforces.com/gym/103373/problem/I) 横断マトロイドとグラフマトロイドの重み付き交差（横断マトロイドを考える代わりに辺を仮想的に増やし，分割マトロイドと解釈することも可能）．

## 文献・リンク集

- [1] C. Brezovec, G. Cornuéjols, and F. Glover, "Two algorithms for weighted matroid intersection,"
  Mathematical Programming, 36(1), 39-53, 1986.
