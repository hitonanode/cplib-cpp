---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/b-flow.hpp
    title: combinatorial_opt/b-flow.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/test/b_flow.test.cpp
    title: combinatorial_opt/test/b_flow.test.cpp
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/test/mcf_costscaling.bflow.test.cpp
    title: combinatorial_opt/test/mcf_costscaling.bflow.test.cpp
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/test/mcf_costscaling.test.cpp
    title: combinatorial_opt/test/mcf_costscaling.test.cpp
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/test/mcf_costscaling.yuki1615.test.cpp
    title: combinatorial_opt/test/mcf_costscaling.yuki1615.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://people.orie.cornell.edu/dpw/orie633/
  bundledCode: "#line 2 \"combinatorial_opt/mcf_costscaling.hpp\"\n#include <cassert>\n\
    #include <vector>\n\n// Cost scaling\n// https://people.orie.cornell.edu/dpw/orie633/\n\
    template <class Cap, class Cost, int SCALING = 1, int REFINEMENT_ITER = 20>\n\
    struct mcf_costscaling {\n    mcf_costscaling() = default;\n    mcf_costscaling(int\
    \ n) : _n(n), to(n), b(n), p(n) {}\n\n    int _n;\n    std::vector<Cap> cap;\n\
    \    std::vector<Cost> cost;\n    std::vector<int> opposite;\n    std::vector<std::vector<int>>\
    \ to;\n    std::vector<Cap> b;\n    std::vector<Cost> p;\n\n    int add_edge(int\
    \ from_, int to_, Cap cap_, Cost cost_) {\n        assert(0 <= from_ and from_\
    \ < _n);\n        assert(0 <= to_ and to_ < _n);\n        assert(0 <= cap_);\n\
    \        cost_ *= (_n + 1);\n        const int e = int(cap.size());\n        to[from_].push_back(e);\n\
    \        cap.push_back(cap_);\n        cost.push_back(cost_);\n        opposite.push_back(to_);\n\
    \n        to[to_].push_back(e + 1);\n        cap.push_back(0);\n        cost.push_back(-cost_);\n\
    \        opposite.push_back(from_);\n        return e / 2;\n    }\n    void add_supply(int\
    \ v, Cap supply) { b[v] += supply; }\n    void add_demand(int v, Cap demand) {\
    \ add_supply(v, -demand); }\n\n    template <typename RetCost = Cost> RetCost\
    \ solve() {\n        Cost eps = 1;\n        std::vector<int> que;\n        for\
    \ (const auto c : cost) {\n            while (eps <= -c) eps <<= SCALING;\n  \
    \      }\n        for (; eps >>= SCALING;) {\n            auto no_admissible_cycle\
    \ = [&]() -> bool {\n                for (int i = 0; i < _n; i++) {\n        \
    \            if (b[i]) return false;\n                }\n                std::vector<Cost>\
    \ pp = p;\n                for (int iter = 0; iter < REFINEMENT_ITER; iter++)\
    \ {\n                    bool flg = false;\n                    for (int e = 0;\
    \ e < int(cap.size()); e++) {\n                        if (!cap[e]) continue;\n\
    \                        int i = opposite[e ^ 1], j = opposite[e];\n         \
    \               if (pp[j] > pp[i] + cost[e] + eps)\n                         \
    \   pp[j] = pp[i] + cost[e] + eps, flg = true;\n                    }\n      \
    \              if (!flg) return p = pp, true;\n                }\n           \
    \     return false;\n            };\n            if (no_admissible_cycle()) continue;\
    \ // Refine\n\n            for (int e = 0; e < int(cap.size()); e++) {\n     \
    \           const int i = opposite[e ^ 1], j = opposite[e];\n                const\
    \ Cost cp_ij = cost[e] + p[i] - p[j];\n                if (cap[e] and cp_ij <\
    \ 0)\n                    b[i] -= cap[e], b[j] += cap[e], cap[e ^ 1] += cap[e],\
    \ cap[e] = 0;\n            }\n            que.clear();\n            int qh = 0;\n\
    \            for (int i = 0; i < _n; i++) {\n                if (b[i] > 0) que.push_back(i);\n\
    \            }\n            std::vector<int> iters(_n);\n            while (qh\
    \ < int(que.size())) {\n                const int i = que[qh++];\n           \
    \     for (; iters[i] < int(to[i].size()) and b[i]; ++iters[i]) { // Push\n  \
    \                  int e = to[i][iters[i]];\n                    if (!cap[e])\
    \ continue;\n                    int j = opposite[e];\n                    Cost\
    \ cp_ij = cost[e] + p[i] - p[j];\n                    if (cp_ij >= 0) continue;\n\
    \                    Cap f = b[i] > cap[e] ? cap[e] : b[i];\n                \
    \    if (b[j] <= 0 and b[j] + f > 0) que.push_back(j);\n                    b[i]\
    \ -= f, b[j] += f, cap[e] -= f, cap[e ^ 1] += f;\n                }\n\n      \
    \          if (b[i] > 0) { // Relabel\n                    bool flg = false;\n\
    \                    for (int e : to[i]) {\n                        if (!cap[e])\
    \ continue;\n                        Cost x = p[opposite[e]] - cost[e] - eps;\n\
    \                        if (!flg or x > p[i]) flg = true, p[i] = x;\n       \
    \             }\n                    que.push_back(i), iters[i] = 0;\n       \
    \         }\n            }\n        }\n        RetCost ret = 0;\n        for (int\
    \ e = 0; e < int(cap.size()); e += 2) ret += RetCost(cost[e]) * cap[e ^ 1];\n\
    \        return ret / (_n + 1);\n    }\n    std::vector<Cost> potential() const\
    \ {\n        std::vector<Cost> ret = p, c0 = cost;\n        for (auto &x : ret)\
    \ x /= (_n + 1);\n        for (auto &x : c0) x /= (_n + 1);\n        while (true)\
    \ {\n            bool flg = false;\n            for (int i = 0; i < _n; i++) {\n\
    \                for (const auto e : to[i]) {\n                    if (!cap[e])\
    \ continue;\n                    int j = opposite[e];\n                    auto\
    \ y = ret[i] + c0[e];\n                    if (ret[j] > y) ret[j] = y, flg = true;\n\
    \                }\n            }\n            if (!flg) break;\n        }\n \
    \       return ret;\n    }\n    struct edge {\n        int from, to;\n       \
    \ Cap cap, flow;\n        Cost cost;\n    };\n    edge get_edge(int e) const {\n\
    \        int m = cap.size() / 2;\n        assert(e >= 0 and e < m);\n        return\
    \ {opposite[e * 2 + 1], opposite[e * 2], cap[e * 2] + cap[e * 2 + 1], cap[e *\
    \ 2 + 1],\n                cost[e * 2] / (_n + 1)};\n    }\n    std::vector<edge>\
    \ edges() const {\n        int m = cap.size() / 2;\n        std::vector<edge>\
    \ result(m);\n        for (int i = 0; i < m; i++) result[i] = get_edge(i);\n \
    \       return result;\n    }\n};\n"
  code: "#pragma once\n#include <cassert>\n#include <vector>\n\n// Cost scaling\n\
    // https://people.orie.cornell.edu/dpw/orie633/\ntemplate <class Cap, class Cost,\
    \ int SCALING = 1, int REFINEMENT_ITER = 20>\nstruct mcf_costscaling {\n    mcf_costscaling()\
    \ = default;\n    mcf_costscaling(int n) : _n(n), to(n), b(n), p(n) {}\n\n   \
    \ int _n;\n    std::vector<Cap> cap;\n    std::vector<Cost> cost;\n    std::vector<int>\
    \ opposite;\n    std::vector<std::vector<int>> to;\n    std::vector<Cap> b;\n\
    \    std::vector<Cost> p;\n\n    int add_edge(int from_, int to_, Cap cap_, Cost\
    \ cost_) {\n        assert(0 <= from_ and from_ < _n);\n        assert(0 <= to_\
    \ and to_ < _n);\n        assert(0 <= cap_);\n        cost_ *= (_n + 1);\n   \
    \     const int e = int(cap.size());\n        to[from_].push_back(e);\n      \
    \  cap.push_back(cap_);\n        cost.push_back(cost_);\n        opposite.push_back(to_);\n\
    \n        to[to_].push_back(e + 1);\n        cap.push_back(0);\n        cost.push_back(-cost_);\n\
    \        opposite.push_back(from_);\n        return e / 2;\n    }\n    void add_supply(int\
    \ v, Cap supply) { b[v] += supply; }\n    void add_demand(int v, Cap demand) {\
    \ add_supply(v, -demand); }\n\n    template <typename RetCost = Cost> RetCost\
    \ solve() {\n        Cost eps = 1;\n        std::vector<int> que;\n        for\
    \ (const auto c : cost) {\n            while (eps <= -c) eps <<= SCALING;\n  \
    \      }\n        for (; eps >>= SCALING;) {\n            auto no_admissible_cycle\
    \ = [&]() -> bool {\n                for (int i = 0; i < _n; i++) {\n        \
    \            if (b[i]) return false;\n                }\n                std::vector<Cost>\
    \ pp = p;\n                for (int iter = 0; iter < REFINEMENT_ITER; iter++)\
    \ {\n                    bool flg = false;\n                    for (int e = 0;\
    \ e < int(cap.size()); e++) {\n                        if (!cap[e]) continue;\n\
    \                        int i = opposite[e ^ 1], j = opposite[e];\n         \
    \               if (pp[j] > pp[i] + cost[e] + eps)\n                         \
    \   pp[j] = pp[i] + cost[e] + eps, flg = true;\n                    }\n      \
    \              if (!flg) return p = pp, true;\n                }\n           \
    \     return false;\n            };\n            if (no_admissible_cycle()) continue;\
    \ // Refine\n\n            for (int e = 0; e < int(cap.size()); e++) {\n     \
    \           const int i = opposite[e ^ 1], j = opposite[e];\n                const\
    \ Cost cp_ij = cost[e] + p[i] - p[j];\n                if (cap[e] and cp_ij <\
    \ 0)\n                    b[i] -= cap[e], b[j] += cap[e], cap[e ^ 1] += cap[e],\
    \ cap[e] = 0;\n            }\n            que.clear();\n            int qh = 0;\n\
    \            for (int i = 0; i < _n; i++) {\n                if (b[i] > 0) que.push_back(i);\n\
    \            }\n            std::vector<int> iters(_n);\n            while (qh\
    \ < int(que.size())) {\n                const int i = que[qh++];\n           \
    \     for (; iters[i] < int(to[i].size()) and b[i]; ++iters[i]) { // Push\n  \
    \                  int e = to[i][iters[i]];\n                    if (!cap[e])\
    \ continue;\n                    int j = opposite[e];\n                    Cost\
    \ cp_ij = cost[e] + p[i] - p[j];\n                    if (cp_ij >= 0) continue;\n\
    \                    Cap f = b[i] > cap[e] ? cap[e] : b[i];\n                \
    \    if (b[j] <= 0 and b[j] + f > 0) que.push_back(j);\n                    b[i]\
    \ -= f, b[j] += f, cap[e] -= f, cap[e ^ 1] += f;\n                }\n\n      \
    \          if (b[i] > 0) { // Relabel\n                    bool flg = false;\n\
    \                    for (int e : to[i]) {\n                        if (!cap[e])\
    \ continue;\n                        Cost x = p[opposite[e]] - cost[e] - eps;\n\
    \                        if (!flg or x > p[i]) flg = true, p[i] = x;\n       \
    \             }\n                    que.push_back(i), iters[i] = 0;\n       \
    \         }\n            }\n        }\n        RetCost ret = 0;\n        for (int\
    \ e = 0; e < int(cap.size()); e += 2) ret += RetCost(cost[e]) * cap[e ^ 1];\n\
    \        return ret / (_n + 1);\n    }\n    std::vector<Cost> potential() const\
    \ {\n        std::vector<Cost> ret = p, c0 = cost;\n        for (auto &x : ret)\
    \ x /= (_n + 1);\n        for (auto &x : c0) x /= (_n + 1);\n        while (true)\
    \ {\n            bool flg = false;\n            for (int i = 0; i < _n; i++) {\n\
    \                for (const auto e : to[i]) {\n                    if (!cap[e])\
    \ continue;\n                    int j = opposite[e];\n                    auto\
    \ y = ret[i] + c0[e];\n                    if (ret[j] > y) ret[j] = y, flg = true;\n\
    \                }\n            }\n            if (!flg) break;\n        }\n \
    \       return ret;\n    }\n    struct edge {\n        int from, to;\n       \
    \ Cap cap, flow;\n        Cost cost;\n    };\n    edge get_edge(int e) const {\n\
    \        int m = cap.size() / 2;\n        assert(e >= 0 and e < m);\n        return\
    \ {opposite[e * 2 + 1], opposite[e * 2], cap[e * 2] + cap[e * 2 + 1], cap[e *\
    \ 2 + 1],\n                cost[e * 2] / (_n + 1)};\n    }\n    std::vector<edge>\
    \ edges() const {\n        int m = cap.size() / 2;\n        std::vector<edge>\
    \ result(m);\n        for (int i = 0; i < m; i++) result[i] = get_edge(i);\n \
    \       return result;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: combinatorial_opt/mcf_costscaling.hpp
  requiredBy:
  - combinatorial_opt/b-flow.hpp
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - combinatorial_opt/test/mcf_costscaling.test.cpp
  - combinatorial_opt/test/mcf_costscaling.yuki1615.test.cpp
  - combinatorial_opt/test/mcf_costscaling.bflow.test.cpp
  - combinatorial_opt/test/b_flow.test.cpp
documentation_of: combinatorial_opt/mcf_costscaling.hpp
layout: document
title: "Minimum cost flow (cost scaling, Goldberg & Tarjan) \uFF08\u30B3\u30B9\u30C8\
  \u30B9\u30B1\u30FC\u30EA\u30F3\u30B0\u306B\u3088\u308B\u6700\u5C0F\u8CBB\u7528\u6D41\
  \uFF09"
---

コストスケーリングによる最小費用流．問題に実行可能解が存在しない場合無限ループに陥りうること，またコストを $n + 1$ 倍にする前処理を行うのでオーバーフローに注意．頂点数が多く流量が少ないようなケースなどでは最短路反復法の方が高速かもしれない．

## 使用方法

[AC Library の `mcf_graph`](https://atcoder.github.io/ac-library/production/document_ja/mincostflow.html) にインターフェースを寄せている．

```cpp
mcf_costscaling<Cap, Cost, 1, 20> mcf(N);

mcf.add_supply(s, flow);
mcf.add_demand(t, -flow);
mcf.add_edge(u, v, cap, cost);

auto ret = mcf.solve<__int128>();
vector<Cost> potential = mcf.potential();
auto ei = mcf.get_edge(i);
auto edges = mcf.get_edges();
```

## ヒューリスティックによる高速化

コストスケーリングには多くのヒューリスティックによる高速化手法が知られている．本コードでは [2] で price refinement と呼称されるテクニックをパラメータチューニング可能な形式で導入している（[プログラミングコンテストにおける提出を観察する](https://yukicoder.me/problems/no/1615/submissions?status=AC)と，このテクニックを導入している例は多い）．

### Price refinement

アルゴリズムの各ステップで，$2\epsilon$-optimal なフロー $f$ とポテンシャル $p$ の組が与えられたとき，$\epsilon$-optimal なフローとポテンシャルの組を新たに求めたい．これは本来のアルゴリズムでは push-relabel を実施すること等によって行われるが，状況によっては $f$ を更新することなく $p$ をうまく取り直すだけでこれが実現できることがある．具体的には，各辺のコストに $\epsilon$ のバイアスを加えた残余グラフ上のポテンシャルについて Bellman-Ford のアルゴリズムを実行し，負閉路が存在しなければそのときの解 $p'$ が所望の $p$ となる．

Bellman-Ford のアルゴリズムは愚直に実行すると $O(nm)$ の計算量を要するが，プログラミングコンテストではしばしば最大反復回数を本来の $n$ から小さい（$10$ 程度やそれ以下の）値に減らし，この回数のうちで $p'$ が求められた場合のみ price refinement を適用する高速化手法が見られる．本コードではテンプレート第 4 引数で最大反復回数をパラメータとして与える．

## 問題例

- [Library Checker: Minimum cost b-flow](https://judge.yosupo.jp/problem/min_cost_b_flow)
- [AtCoder Library Practice Contest E - MinCostFlow](https://atcoder.jp/contests/practice2/tasks/practice2_e)
- [No.1615 Double Down - yukicoder](https://yukicoder.me/problems/no/1615) （非想定解）

## Reference

- [1] A. V. Goldberg and R. E. Tarjan, "Finding minimum-cost circulations by successive approximation,"
      Mathematics of Operations Research, 15(3), 430-466, 1990.
- [2] A. V. Goldberg, "An Efficient Implementation of a Scaling Minimum-Cost Flow Algorithm,"
      Journal of algorithms, 22(1), 1-29, 1997.
- [3] U, Bünnagel, B Korte, J Vygen,
      "Efficient implementation of the Goldberg-Tarjan minimum-cost flow algorithm,"
      Optimization Methods and Software, 10(2), 157-174, 1998.
- [ORIE 633: Network Flows](https://people.orie.cornell.edu/dpw/orie633/)
