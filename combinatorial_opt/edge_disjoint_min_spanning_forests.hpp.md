---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://community.topcoder.com/stat?c=problem_statement&pm=14909&rd=17198
    - https://www.codechef.com/submit/HAMEL
    - https://www.slideshare.net/tmaehara/ss-17402143
  bundledCode: "#line 2 \"combinatorial_opt/edge_disjoint_min_spanning_forests.hpp\"\
    \n#include <algorithm>\n#include <cassert>\n#include <numeric>\n#include <utility>\n\
    #include <vector>\n\n// Max size min weight two spanning forests\n// Complexity:\
    \ O(NM + M log M)\n// Reference: https://www.slideshare.net/tmaehara/ss-17402143\n\
    // Verified:\n// - https://www.codechef.com/submit/HAMEL\n// - https://community.topcoder.com/stat?c=problem_statement&pm=14909&rd=17198\n\
    template <class Label, class W = int>\nstd::pair<std::vector<bool>, std::vector<bool>>\n\
    edge_disjoint_min_spanning_forests(const std::vector<std::pair<Label, Label>>\
    \ &edges,\n                                   const std::vector<W> &ws = {}) {\n\
    \    assert(ws.empty() or ws.size() == edges.size());\n    const int M = edges.size();\n\
    \    std::vector<Label> lbl(M * 2);\n    for (int e = 0; e < M; e++) lbl[e * 2]\
    \ = edges[e].first, lbl[e * 2 + 1] = edges[e].second;\n    std::sort(lbl.begin(),\
    \ lbl.end());\n    lbl.erase(std::unique(lbl.begin(), lbl.end()), lbl.end());\n\
    \    const int N = lbl.size();\n\n    std::vector<std::pair<int, int>> uvs(M);\n\
    \    for (int e = 0; e < M; e++) {\n        int u = std::lower_bound(lbl.begin(),\
    \ lbl.end(), edges[e].first) - lbl.begin();\n        int v = std::lower_bound(lbl.begin(),\
    \ lbl.end(), edges[e].second) - lbl.begin();\n        uvs[e] = {u, v};\n    }\n\
    \n    std::vector<int> es(M);\n    std::iota(es.begin(), es.end(), 0);\n    if\
    \ (!ws.empty()) std::sort(es.begin(), es.end(), [&](int i, int j) { return ws[i]\
    \ < ws[j]; });\n\n    std::vector<std::vector<bool>> I(2, std::vector<bool>(M));\n\
    \    std::vector<std::vector<std::pair<int, int>>> to(N);\n\n    int nb_accepted_edges\
    \ = 0;\n    auto accept_edge = [&](int e) {\n        nb_accepted_edges++;\n  \
    \      int u = uvs[e].first, v = uvs[e].second;\n        to[u].emplace_back(v,\
    \ e);\n        to[v].emplace_back(u, e);\n    };\n\n    auto dfs = [&](int head,\
    \ const std::vector<bool> &I) -> std::vector<std::pair<int, int>> {\n        std::vector<int>\
    \ st{head};\n        std::vector<std::pair<int, int>> prv(N, {-1, -1});\n    \
    \    prv[head] = {head, -1};\n        while (!st.empty()) {\n            int now\
    \ = st.back();\n            st.pop_back();\n            for (auto p : to[now])\
    \ {\n                int nxt = p.first, e = p.second;\n                if (!I[e]\
    \ or prv[nxt].first >= 0) continue;\n                prv[nxt] = {now, e}, st.push_back(nxt);\n\
    \            }\n        }\n        return prv;\n    };\n\n    std::vector<int>\
    \ prveid(M, -1), visited(N);\n    std::vector<std::vector<int>> L(2);\n    std::vector<std::vector<std::pair<int,\
    \ int>>> prv(2);\n    for (const int e : es) {\n        if (nb_accepted_edges\
    \ > 2 * (N - 1)) break;\n        const int u = uvs[e].first, v = uvs[e].second;\n\
    \n        bool found = false;\n\n        for (int d = 0; d < 2; d++) {\n     \
    \       prv[d] = dfs(u, I[d]);\n            if (prv[d][v].first < 0) {\n     \
    \           accept_edge(e);\n                I[d][e] = 1;\n                found\
    \ = true;\n                break;\n            }\n        }\n        if (found)\
    \ continue;\n\n        visited.assign(N, 0);\n        visited[u] = 1;\n      \
    \  L[0] = {e}, L[1] = {};\n\n        int ehead = -1;\n        prveid[e] = -1;\n\
    \        for (int i = 0;; i ^= 1) {\n            if (L[i].empty()) break;\n  \
    \          L[i ^ 1].clear();\n            while (!L[i].empty()) {\n          \
    \      const int exy = L[i].back();\n                L[i].pop_back();\n      \
    \          int x = uvs[exy].first, y = uvs[exy].second;\n                if (prv[i][x].first\
    \ < 0 or prv[i][y].first < 0) {\n                    ehead = exy;\n          \
    \          break;\n                }\n                if (!visited[x]) std::swap(x,\
    \ y);\n                while (!visited[y]) {\n                    int nxty = prv[i][y].first,\
    \ nxte = prv[i][y].second;\n                    L[i ^ 1].push_back(nxte);\n  \
    \                  visited[y] = 1;\n                    y = nxty;\n          \
    \          prveid[nxte] = exy;\n                }\n            }\n           \
    \ if (ehead >= 0) {\n                accept_edge(e);\n                int c =\
    \ I[0][ehead];\n                for (; ehead >= 0; ehead = prveid[ehead], c ^=\
    \ 1) {\n                    I[c][ehead] = 1, I[c ^ 1][ehead] = 0;\n          \
    \      }\n                break;\n            }\n        }\n    }\n    return\
    \ {I[0], I[1]};\n}\n"
  code: "#pragma once\n#include <algorithm>\n#include <cassert>\n#include <numeric>\n\
    #include <utility>\n#include <vector>\n\n// Max size min weight two spanning forests\n\
    // Complexity: O(NM + M log M)\n// Reference: https://www.slideshare.net/tmaehara/ss-17402143\n\
    // Verified:\n// - https://www.codechef.com/submit/HAMEL\n// - https://community.topcoder.com/stat?c=problem_statement&pm=14909&rd=17198\n\
    template <class Label, class W = int>\nstd::pair<std::vector<bool>, std::vector<bool>>\n\
    edge_disjoint_min_spanning_forests(const std::vector<std::pair<Label, Label>>\
    \ &edges,\n                                   const std::vector<W> &ws = {}) {\n\
    \    assert(ws.empty() or ws.size() == edges.size());\n    const int M = edges.size();\n\
    \    std::vector<Label> lbl(M * 2);\n    for (int e = 0; e < M; e++) lbl[e * 2]\
    \ = edges[e].first, lbl[e * 2 + 1] = edges[e].second;\n    std::sort(lbl.begin(),\
    \ lbl.end());\n    lbl.erase(std::unique(lbl.begin(), lbl.end()), lbl.end());\n\
    \    const int N = lbl.size();\n\n    std::vector<std::pair<int, int>> uvs(M);\n\
    \    for (int e = 0; e < M; e++) {\n        int u = std::lower_bound(lbl.begin(),\
    \ lbl.end(), edges[e].first) - lbl.begin();\n        int v = std::lower_bound(lbl.begin(),\
    \ lbl.end(), edges[e].second) - lbl.begin();\n        uvs[e] = {u, v};\n    }\n\
    \n    std::vector<int> es(M);\n    std::iota(es.begin(), es.end(), 0);\n    if\
    \ (!ws.empty()) std::sort(es.begin(), es.end(), [&](int i, int j) { return ws[i]\
    \ < ws[j]; });\n\n    std::vector<std::vector<bool>> I(2, std::vector<bool>(M));\n\
    \    std::vector<std::vector<std::pair<int, int>>> to(N);\n\n    int nb_accepted_edges\
    \ = 0;\n    auto accept_edge = [&](int e) {\n        nb_accepted_edges++;\n  \
    \      int u = uvs[e].first, v = uvs[e].second;\n        to[u].emplace_back(v,\
    \ e);\n        to[v].emplace_back(u, e);\n    };\n\n    auto dfs = [&](int head,\
    \ const std::vector<bool> &I) -> std::vector<std::pair<int, int>> {\n        std::vector<int>\
    \ st{head};\n        std::vector<std::pair<int, int>> prv(N, {-1, -1});\n    \
    \    prv[head] = {head, -1};\n        while (!st.empty()) {\n            int now\
    \ = st.back();\n            st.pop_back();\n            for (auto p : to[now])\
    \ {\n                int nxt = p.first, e = p.second;\n                if (!I[e]\
    \ or prv[nxt].first >= 0) continue;\n                prv[nxt] = {now, e}, st.push_back(nxt);\n\
    \            }\n        }\n        return prv;\n    };\n\n    std::vector<int>\
    \ prveid(M, -1), visited(N);\n    std::vector<std::vector<int>> L(2);\n    std::vector<std::vector<std::pair<int,\
    \ int>>> prv(2);\n    for (const int e : es) {\n        if (nb_accepted_edges\
    \ > 2 * (N - 1)) break;\n        const int u = uvs[e].first, v = uvs[e].second;\n\
    \n        bool found = false;\n\n        for (int d = 0; d < 2; d++) {\n     \
    \       prv[d] = dfs(u, I[d]);\n            if (prv[d][v].first < 0) {\n     \
    \           accept_edge(e);\n                I[d][e] = 1;\n                found\
    \ = true;\n                break;\n            }\n        }\n        if (found)\
    \ continue;\n\n        visited.assign(N, 0);\n        visited[u] = 1;\n      \
    \  L[0] = {e}, L[1] = {};\n\n        int ehead = -1;\n        prveid[e] = -1;\n\
    \        for (int i = 0;; i ^= 1) {\n            if (L[i].empty()) break;\n  \
    \          L[i ^ 1].clear();\n            while (!L[i].empty()) {\n          \
    \      const int exy = L[i].back();\n                L[i].pop_back();\n      \
    \          int x = uvs[exy].first, y = uvs[exy].second;\n                if (prv[i][x].first\
    \ < 0 or prv[i][y].first < 0) {\n                    ehead = exy;\n          \
    \          break;\n                }\n                if (!visited[x]) std::swap(x,\
    \ y);\n                while (!visited[y]) {\n                    int nxty = prv[i][y].first,\
    \ nxte = prv[i][y].second;\n                    L[i ^ 1].push_back(nxte);\n  \
    \                  visited[y] = 1;\n                    y = nxty;\n          \
    \          prveid[nxte] = exy;\n                }\n            }\n           \
    \ if (ehead >= 0) {\n                accept_edge(e);\n                int c =\
    \ I[0][ehead];\n                for (; ehead >= 0; ehead = prveid[ehead], c ^=\
    \ 1) {\n                    I[c][ehead] = 1, I[c ^ 1][ehead] = 0;\n          \
    \      }\n                break;\n            }\n        }\n    }\n    return\
    \ {I[0], I[1]};\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: combinatorial_opt/edge_disjoint_min_spanning_forests.hpp
  requiredBy: []
  timestamp: '2021-09-18 18:00:53+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: combinatorial_opt/edge_disjoint_min_spanning_forests.hpp
layout: document
title: "Edge disjoint minimum spanning forests \uFF08\u7121\u5411\u30B0\u30E9\u30D5\
  \u306B\u304A\u3051\u308B\u6700\u5927\u8FBA\u6570\u6700\u5C0F\u91CD\u307F\u306E\u8FBA\
  \u7D20\u306A\u4E8C\u3064\u306E\u5168\u57DF\u68EE\uFF09"
---

$n$ 頂点 $m$ 辺の重み付き無向グラフを入力として，辺を共有しない二つの全域森であって辺数の和が最大となるもののうち重み最小のものを一つ構築する．
本実装の計算量は重み付きのとき $O(nm + m \log m)$，重みなしのとき $O(nm)$．

## アルゴリズムの概要

アルゴリズムの大枠は [Matroid union （マトロイドの合併） \| cplib-cpp](https://hitonanode.github.io/cplib-cpp/combinatorial_opt/matroid_union.hpp) と同様．

## 使用方法

```cpp
vector<pint> edges;
vector<int> weights;
while (M--) {
    int u, v, w;
    cin >> u >> v >> w;
    edges.emplace_back(u, v);
    weights.push_back(w);
}
vector<bool> I1, I2;
tie(I1, I2) = edge_disjoint_min_spanning_forests(edges); // 重みなし
tie(I1, I2) = edge_disjoint_min_spanning_forests(edges, w); // 重み付き
```

返り値の `I1`, `I2` はともに長さ $m$ のベクトル．`I1[e]` の値が `true` のとき，$e$ 本目の辺が一つ目の全域森に含まれていることを示す（`I2` の解釈も同様）．

## 問題例

- [Hamel Paths \| CodeChef](https://www.codechef.com/problems/HAMEL) $n \le 64, m \le n(n - 1) / 2$, 最大 64 ケース．
- [2018 TCO Round 3A 1000 ColoringEdgesDiv1](https://community.topcoder.com/stat?c=problem_statement&pm=14909&rd=17198) $n \le 1000, m = 3n/2$

## 参考文献・リンク

- [様々な全域木問題](https://www.slideshare.net/tmaehara/ss-17402143)
- [1] J. Roskind & R. E. Tarjan, 
  "A note on finding minimum-cost edge-disjoint spanning trees,"
  Mathematics of Operations Research, 10(4), 701-708, 1985.
  - 一般に $k$ 個の全域森にグラフを分割する $O(m \log m + k^2 n^2)$ のアルゴリズムが存在するらしい．
