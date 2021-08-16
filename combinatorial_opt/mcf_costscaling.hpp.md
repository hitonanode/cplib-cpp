---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/light_forward_list.hpp
    title: data_structure/light_forward_list.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/test/mcf_costscaling.test.cpp
    title: combinatorial_opt/test/mcf_costscaling.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://people.orie.cornell.edu/dpw/orie633/
    - https://yukicoder.me/submissions/680169
  bundledCode: "#line 2 \"data_structure/light_forward_list.hpp\"\n#include <vector>\n\
    \n// CUT begin\n// Simple forward_list for MLE-sensitive situations\n// Verify:\
    \ <http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D>\ntemplate\
    \ <typename T> struct light_forward_list {\n    static std::vector<unsigned> ptr;\n\
    \    static std::vector<T> val;\n    unsigned head;\n    light_forward_list()\
    \ : head(0) {}\n    void push_front(T x) {\n        ptr.push_back(head), val.push_back(x);\n\
    \        head = ptr.size() - 1;\n    }\n    struct iterator {\n        unsigned\
    \ p;\n        iterator operator++() { return {p = ptr[p]}; }\n        T &operator*()\
    \ { return val[p]; }\n        bool operator!=(const iterator &rhs) { return p\
    \ != rhs.p; }\n    };\n    iterator begin() { return {head}; }\n    iterator end()\
    \ { return {0}; }\n};\ntemplate <typename T> std::vector<unsigned> light_forward_list<T>::ptr\
    \ = {0};\ntemplate <typename T> std::vector<T> light_forward_list<T>::val = {T()};\n\
    #line 3 \"combinatorial_opt/mcf_costscaling.hpp\"\n#include <cassert>\n#include\
    \ <limits>\n#include <queue>\n\n// Cost scaling\n// https://people.orie.cornell.edu/dpw/orie633/\n\
    // Implementation idea: https://yukicoder.me/submissions/680169\ntemplate <class\
    \ Cap, class Cost> struct mcf_costscaling {\n    mcf_costscaling() = default;\n\
    \    mcf_costscaling(int n) : _n(n), to(n), b(n), p(n) {\n        static_assert(std::numeric_limits<Cap>::max()\
    \ > 0, \"max() must be greater than 0\");\n    }\n\n    int _n;\n    std::vector<Cap>\
    \ cap;\n    std::vector<Cost> cost;\n    std::vector<int> opposite;\n    std::vector<light_forward_list<int>>\
    \ to;\n    std::vector<Cap> b;\n    std::vector<Cost> p;\n\n    void add_edge(int\
    \ from_, int to_, Cap cap_, Cost cost_) {\n        assert(0 <= from_ && from_\
    \ < _n);\n        assert(0 <= to_ && to_ < _n);\n        assert(0 <= cap_);\n\
    \        assert(0 <= cost_);\n        cost_ *= (_n + 1);\n\n        int e = int(cap.size());\n\
    \        to[from_].push_front(e);\n        cap.push_back(cap_);\n        cost.push_back(cost_);\n\
    \        opposite.push_back(to_);\n\n        to[to_].push_front(e + 1);\n    \
    \    cap.push_back(0);\n        cost.push_back(-cost_);\n        opposite.push_back(from_);\n\
    \    }\n    void add_supply(int v, Cap supply) { b[v] += supply; }\n    void add_demand(int\
    \ v, Cap demand) { add_supply(v, -demand); }\n\n    Cost flow(int SCALING = 1)\
    \ {\n        Cost eps = 1;\n        for (const auto c : cost) {\n            while\
    \ (eps <= -c) eps <<= SCALING;\n        }\n        for (; eps >>= SCALING;) {\n\
    \            for (int e = 0; e < int(cap.size()); e += 2) {\n                const\
    \ int i = opposite[e ^ 1], j = opposite[e];\n                const Cost cp_ij\
    \ = cost[e] + p[i] - p[j];\n                if (cap[e] and cp_ij < 0) {\n    \
    \                b[i] -= cap[e], b[j] += cap[e], cap[e ^ 1] += cap[e], cap[e]\
    \ = 0;\n                } else if (cap[e ^ 1] and cp_ij > 0) {\n             \
    \       b[i] += cap[e ^ 1], b[j] -= cap[e ^ 1], cap[e] += cap[e ^ 1], cap[e ^\
    \ 1] = 0;\n                }\n            }\n            std::queue<int> q;\n\
    \            for (int i = 0; i < _n; i++) {\n                if (b[i] > 0) q.push(i);\n\
    \            }\n            while (q.size()) {\n                const int i =\
    \ q.front();\n                q.pop();\n                for (auto e : to[i]) {\
    \ // Push\n                    if (!cap[e]) continue;\n                    int\
    \ j = opposite[e];\n                    Cost cp_ij = cost[e] + p[i] - p[j];\n\
    \                    if (cp_ij >= 0) continue;\n                    Cap f = b[i]\
    \ > cap[e] ? cap[e] : b[i];\n                    if (b[j] <= 0 and b[j] + f >\
    \ 0) q.push(j);\n                    b[i] -= f, b[j] += f, cap[e] -= f, cap[e\
    \ ^ 1] += f;\n                    if (!b[i]) break;\n                }\n\n   \
    \             if (b[i] > 0) { // Relabel\n                    bool flg = false;\n\
    \                    for (int e : to[i]) {\n                        if (!cap[e])\
    \ continue;\n                        Cost x = p[opposite[e]] - cost[e] - eps;\n\
    \                        if (!flg or x > p[i]) flg = true, p[i] = x;\n       \
    \             }\n                    q.push(i);\n                }\n         \
    \   }\n        }\n        Cost ret = 0;\n        for (int e = 0; e < int(cap.size());\
    \ e += 2) ret += cost[e] * cap[e ^ 1];\n        return ret / (_n + 1);\n    }\n\
    };\n"
  code: "#pragma once\n#include \"../data_structure/light_forward_list.hpp\"\n#include\
    \ <cassert>\n#include <limits>\n#include <queue>\n\n// Cost scaling\n// https://people.orie.cornell.edu/dpw/orie633/\n\
    // Implementation idea: https://yukicoder.me/submissions/680169\ntemplate <class\
    \ Cap, class Cost> struct mcf_costscaling {\n    mcf_costscaling() = default;\n\
    \    mcf_costscaling(int n) : _n(n), to(n), b(n), p(n) {\n        static_assert(std::numeric_limits<Cap>::max()\
    \ > 0, \"max() must be greater than 0\");\n    }\n\n    int _n;\n    std::vector<Cap>\
    \ cap;\n    std::vector<Cost> cost;\n    std::vector<int> opposite;\n    std::vector<light_forward_list<int>>\
    \ to;\n    std::vector<Cap> b;\n    std::vector<Cost> p;\n\n    void add_edge(int\
    \ from_, int to_, Cap cap_, Cost cost_) {\n        assert(0 <= from_ && from_\
    \ < _n);\n        assert(0 <= to_ && to_ < _n);\n        assert(0 <= cap_);\n\
    \        assert(0 <= cost_);\n        cost_ *= (_n + 1);\n\n        int e = int(cap.size());\n\
    \        to[from_].push_front(e);\n        cap.push_back(cap_);\n        cost.push_back(cost_);\n\
    \        opposite.push_back(to_);\n\n        to[to_].push_front(e + 1);\n    \
    \    cap.push_back(0);\n        cost.push_back(-cost_);\n        opposite.push_back(from_);\n\
    \    }\n    void add_supply(int v, Cap supply) { b[v] += supply; }\n    void add_demand(int\
    \ v, Cap demand) { add_supply(v, -demand); }\n\n    Cost flow(int SCALING = 1)\
    \ {\n        Cost eps = 1;\n        for (const auto c : cost) {\n            while\
    \ (eps <= -c) eps <<= SCALING;\n        }\n        for (; eps >>= SCALING;) {\n\
    \            for (int e = 0; e < int(cap.size()); e += 2) {\n                const\
    \ int i = opposite[e ^ 1], j = opposite[e];\n                const Cost cp_ij\
    \ = cost[e] + p[i] - p[j];\n                if (cap[e] and cp_ij < 0) {\n    \
    \                b[i] -= cap[e], b[j] += cap[e], cap[e ^ 1] += cap[e], cap[e]\
    \ = 0;\n                } else if (cap[e ^ 1] and cp_ij > 0) {\n             \
    \       b[i] += cap[e ^ 1], b[j] -= cap[e ^ 1], cap[e] += cap[e ^ 1], cap[e ^\
    \ 1] = 0;\n                }\n            }\n            std::queue<int> q;\n\
    \            for (int i = 0; i < _n; i++) {\n                if (b[i] > 0) q.push(i);\n\
    \            }\n            while (q.size()) {\n                const int i =\
    \ q.front();\n                q.pop();\n                for (auto e : to[i]) {\
    \ // Push\n                    if (!cap[e]) continue;\n                    int\
    \ j = opposite[e];\n                    Cost cp_ij = cost[e] + p[i] - p[j];\n\
    \                    if (cp_ij >= 0) continue;\n                    Cap f = b[i]\
    \ > cap[e] ? cap[e] : b[i];\n                    if (b[j] <= 0 and b[j] + f >\
    \ 0) q.push(j);\n                    b[i] -= f, b[j] += f, cap[e] -= f, cap[e\
    \ ^ 1] += f;\n                    if (!b[i]) break;\n                }\n\n   \
    \             if (b[i] > 0) { // Relabel\n                    bool flg = false;\n\
    \                    for (int e : to[i]) {\n                        if (!cap[e])\
    \ continue;\n                        Cost x = p[opposite[e]] - cost[e] - eps;\n\
    \                        if (!flg or x > p[i]) flg = true, p[i] = x;\n       \
    \             }\n                    q.push(i);\n                }\n         \
    \   }\n        }\n        Cost ret = 0;\n        for (int e = 0; e < int(cap.size());\
    \ e += 2) ret += cost[e] * cap[e ^ 1];\n        return ret / (_n + 1);\n    }\n\
    };\n"
  dependsOn:
  - data_structure/light_forward_list.hpp
  isVerificationFile: false
  path: combinatorial_opt/mcf_costscaling.hpp
  requiredBy: []
  timestamp: '2021-08-17 02:37:56+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - combinatorial_opt/test/mcf_costscaling.test.cpp
documentation_of: combinatorial_opt/mcf_costscaling.hpp
layout: document
title: "Cost scaling minimum cost flow (Goldberg, Tarjan) \uFF08\u30B3\u30B9\u30C8\
  \u30B9\u30B1\u30FC\u30EA\u30F3\u30B0\u306B\u3088\u308B\u6700\u5C0F\u8CBB\u7528\u6D41\
  \uFF09"
---

コストスケーリングによる最小費用流．問題に実行可能解が存在しない場合無限ループに陥ること，またコストを $n + 1$ 倍にする前処理を行うのでオーバーフローに注意．

## Reference

- [1] A. V. Goldberg and R. E. Tarjan, "Finding minimum-cost circulations by successive approximation,"
      Mathematics of Operations Research, 15(3), 430-466, 1990.
- [ORIE 633: Network Flows](https://people.orie.cornell.edu/dpw/orie633/)
