---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: graph/test/max_weight_independent_set.aoj3519.test.cpp
    title: graph/test/max_weight_independent_set.aoj3519.test.cpp
  - icon: ':heavy_check_mark:'
    path: graph/test/max_weight_independent_set.lc.test.cpp
    title: graph/test/max_weight_independent_set.lc.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3519
    - https://www.slideshare.net/wata_orz/ss-12131479,
  bundledCode: "#line 2 \"graph/max_weight_independent_set.hpp\"\n#include <algorithm>\n\
    #include <cassert>\n#include <stack>\n#include <vector>\n\n// Maximum weight independent\
    \ set\n// Requirement: n <= 63\n// Complexity: exponential, O(1.381^n n)\n// Reference:\
    \ https://www.slideshare.net/wata_orz/ss-12131479, p.34\n// Verified: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3519\n\
    template <class Weight> struct max_weight_independent_set {\n    int V; // # of\
    \ vertices\n    std::vector<long long> conn;\n    std::vector<Weight> ws;\n\n\
    \    long long solution_set; // Solution set is saved here: use (1) / not use\
    \ (0)\n    Weight eval_solution;   // optimal value\n\nprivate:\n    long long\
    \ state;\n    Weight eval_state;\n    long long avail;\n    void mis_dfs() {\n\
    \        std::stack<int, std::vector<int>> st;\n        for (bool retry = true;\
    \ retry;) { // Pruning\n            retry = false;\n            for (int i = 0;\
    \ i < V; i++) {\n                if (avail & (1LL << i)) {\n                 \
    \   int nb = __builtin_popcountll(avail & conn[i]);\n                    if (nb\
    \ == 0) {\n                        st.emplace(i), avail -= 1LL << i, state |=\
    \ 1LL << i;\n                        eval_state += ws[i];\n                  \
    \      retry = true;\n                    }\n                    if (nb == 1)\
    \ {\n                        int j = __builtin_ctzll(avail & conn[i]);\n     \
    \                   if (ws[i] >= ws[j]) {\n                            st.emplace(i),\
    \ avail -= 1LL << i, state |= 1LL << i;\n                            eval_state\
    \ += ws[i];\n                            retry = true;\n                     \
    \       st.emplace(j), avail &= ~(1LL << j);\n                        }\n    \
    \                }\n                }\n            }\n        }\n\n        if\
    \ (eval_state > eval_solution) eval_solution = eval_state, solution_set = state;\n\
    \n        int d = -1, n = -1;\n        for (int i = 0; i < V; i++) {\n       \
    \     if (avail & (1LL << i)) {\n                int c = __builtin_popcountll(avail\
    \ & conn[i]);\n                if (c > d) d = c, n = i;\n            }\n     \
    \   }\n\n        if (d >= 0) {\n            long long nxt = avail & conn[n];\n\
    \            avail -= 1LL << n;\n            mis_dfs();\n            state |=\
    \ 1LL << n;\n            eval_state += ws[n];\n            avail &= ~nxt;\n  \
    \          mis_dfs();\n            avail |= nxt;\n            avail |= 1LL <<\
    \ n;\n            state &= ~(1LL << n);\n            eval_state -= ws[n];\n  \
    \      }\n\n        for (; st.size(); st.pop()) {\n            int i = st.top();\n\
    \            avail |= 1LL << i;\n            if ((state >> i) & 1LL) state -=\
    \ 1LL << i, eval_state -= ws[i];\n        }\n    }\n\npublic:\n    max_weight_independent_set(const\
    \ int V)\n        : V(V), conn(V), ws(V, Weight(1)), solution_set(0), eval_solution(Weight()),\
    \ state(0),\n          eval_state(Weight()), avail((1LL << V) - 1) {}\n    max_weight_independent_set(const\
    \ std::vector<Weight> &ws_)\n        : max_weight_independent_set(ws_.size())\
    \ {\n        ws = ws_;\n    }\n\n    void add_edge(int u, int v) {\n        assert(u\
    \ != v);\n        assert(0 <= u and u < V);\n        assert(0 <= v and v < V);\n\
    \        conn[u] |= 1LL << v;\n        conn[v] |= 1LL << u;\n    }\n\n    Weight\
    \ solve() {\n        state = 0, eval_state = Weight(), avail = (1LL << V) - 1;\n\
    \        solution_set = 0, eval_solution = Weight();\n        mis_dfs();\n   \
    \     return eval_solution;\n    }\n};\n"
  code: "#pragma once\n#include <algorithm>\n#include <cassert>\n#include <stack>\n\
    #include <vector>\n\n// Maximum weight independent set\n// Requirement: n <= 63\n\
    // Complexity: exponential, O(1.381^n n)\n// Reference: https://www.slideshare.net/wata_orz/ss-12131479,\
    \ p.34\n// Verified: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3519\n\
    template <class Weight> struct max_weight_independent_set {\n    int V; // # of\
    \ vertices\n    std::vector<long long> conn;\n    std::vector<Weight> ws;\n\n\
    \    long long solution_set; // Solution set is saved here: use (1) / not use\
    \ (0)\n    Weight eval_solution;   // optimal value\n\nprivate:\n    long long\
    \ state;\n    Weight eval_state;\n    long long avail;\n    void mis_dfs() {\n\
    \        std::stack<int, std::vector<int>> st;\n        for (bool retry = true;\
    \ retry;) { // Pruning\n            retry = false;\n            for (int i = 0;\
    \ i < V; i++) {\n                if (avail & (1LL << i)) {\n                 \
    \   int nb = __builtin_popcountll(avail & conn[i]);\n                    if (nb\
    \ == 0) {\n                        st.emplace(i), avail -= 1LL << i, state |=\
    \ 1LL << i;\n                        eval_state += ws[i];\n                  \
    \      retry = true;\n                    }\n                    if (nb == 1)\
    \ {\n                        int j = __builtin_ctzll(avail & conn[i]);\n     \
    \                   if (ws[i] >= ws[j]) {\n                            st.emplace(i),\
    \ avail -= 1LL << i, state |= 1LL << i;\n                            eval_state\
    \ += ws[i];\n                            retry = true;\n                     \
    \       st.emplace(j), avail &= ~(1LL << j);\n                        }\n    \
    \                }\n                }\n            }\n        }\n\n        if\
    \ (eval_state > eval_solution) eval_solution = eval_state, solution_set = state;\n\
    \n        int d = -1, n = -1;\n        for (int i = 0; i < V; i++) {\n       \
    \     if (avail & (1LL << i)) {\n                int c = __builtin_popcountll(avail\
    \ & conn[i]);\n                if (c > d) d = c, n = i;\n            }\n     \
    \   }\n\n        if (d >= 0) {\n            long long nxt = avail & conn[n];\n\
    \            avail -= 1LL << n;\n            mis_dfs();\n            state |=\
    \ 1LL << n;\n            eval_state += ws[n];\n            avail &= ~nxt;\n  \
    \          mis_dfs();\n            avail |= nxt;\n            avail |= 1LL <<\
    \ n;\n            state &= ~(1LL << n);\n            eval_state -= ws[n];\n  \
    \      }\n\n        for (; st.size(); st.pop()) {\n            int i = st.top();\n\
    \            avail |= 1LL << i;\n            if ((state >> i) & 1LL) state -=\
    \ 1LL << i, eval_state -= ws[i];\n        }\n    }\n\npublic:\n    max_weight_independent_set(const\
    \ int V)\n        : V(V), conn(V), ws(V, Weight(1)), solution_set(0), eval_solution(Weight()),\
    \ state(0),\n          eval_state(Weight()), avail((1LL << V) - 1) {}\n    max_weight_independent_set(const\
    \ std::vector<Weight> &ws_)\n        : max_weight_independent_set(ws_.size())\
    \ {\n        ws = ws_;\n    }\n\n    void add_edge(int u, int v) {\n        assert(u\
    \ != v);\n        assert(0 <= u and u < V);\n        assert(0 <= v and v < V);\n\
    \        conn[u] |= 1LL << v;\n        conn[v] |= 1LL << u;\n    }\n\n    Weight\
    \ solve() {\n        state = 0, eval_state = Weight(), avail = (1LL << V) - 1;\n\
    \        solution_set = 0, eval_solution = Weight();\n        mis_dfs();\n   \
    \     return eval_solution;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/max_weight_independent_set.hpp
  requiredBy: []
  timestamp: '2022-05-01 19:26:34+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - graph/test/max_weight_independent_set.lc.test.cpp
  - graph/test/max_weight_independent_set.aoj3519.test.cpp
documentation_of: graph/max_weight_independent_set.hpp
layout: document
title: "Max weight independent set \uFF08\u91CD\u307F\u6700\u5927\u72EC\u7ACB\u96C6\
  \u5408\uFF09"
---

$N$ 頂点の単純無向グラフの重み最大独立集合の一つを求める指数時間アルゴリズム．時間計算量 $O(1.381^n n)$．頂点重みの和が最大なので，サイズ最大とは限らない．

## 使用方法

```cpp
vector<long long> weight(N);

max_weight_independent_set<long long> graph(weight);
// max_weight_independent_set<long long> graph(N); // と宣言すると重み 1 （= 重みなし）のケースを解く
while (M--) {
    int u, v;
    cin >> u >> v;
    solver.add_edge(u, v);
}
long long max_weight = solver.solve();
long long mask = solver.solution_set;
```

## 問題例

- [AOJ 3519: Breakup](https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3519)
