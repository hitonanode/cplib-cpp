---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: unionfind/test/potentialized_unionfind.test.cpp
    title: unionfind/test/potentialized_unionfind.test.cpp
  - icon: ':heavy_check_mark:'
    path: unionfind/test/potentialized_unionfind_F2.yuki1420.test.cpp
    title: unionfind/test/potentialized_unionfind_F2.yuki1420.test.cpp
  - icon: ':heavy_check_mark:'
    path: unionfind/test/potentialized_unionfind_int.aoj3142.test.cpp
    title: unionfind/test/potentialized_unionfind_int.aoj3142.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"unionfind/potentialized_unionfind.hpp\"\n#include <numeric>\n\
    #include <utility>\n#include <vector>\n\n// Potentialized UnionFind (Weighted\
    \ UnionFind)\ntemplate <class S> struct PotentializedUnionFind {\n    std::vector<int>\
    \ par, sz;\n    std::vector<S> pot;\n    PotentializedUnionFind(int N = 0) : par(N),\
    \ sz(N, 1), pot(N) {\n        std::iota(par.begin(), par.end(), 0);\n    }\n \
    \   int find(int x) {\n        if (par[x] != x) {\n            int r = find(par[x]);\n\
    \            pot[x] = pot[x] + pot[par[x]], par[x] = r;\n        }\n        return\
    \ par[x];\n    }\n    bool unite(int s, int t, S rel_diff) {\n        // Relate\
    \ s and t by f[t] = f[s] + rel_diff\n        // Return false iff contradiction\
    \ happens.\n        rel_diff = rel_diff + weight(s) + (-weight(t));\n        if\
    \ ((s = find(s)) == (t = find(t))) return rel_diff == 0;\n        if (sz[s] <\
    \ sz[t]) std::swap(s, t), rel_diff = -rel_diff;\n        par[t] = s, sz[s] +=\
    \ sz[t], pot[t] = rel_diff;\n        return true;\n    }\n    S weight(int x)\
    \ { return find(x), pot[x]; }\n    S diff(int s, int t) { return weight(t) + (-weight(s));\
    \ } // return f[t] - f[s]\n    int count(int x) { return sz[find(x)]; }\n    bool\
    \ same(int s, int t) { return find(s) == find(t); }\n};\n"
  code: "#pragma once\n#include <numeric>\n#include <utility>\n#include <vector>\n\
    \n// Potentialized UnionFind (Weighted UnionFind)\ntemplate <class S> struct PotentializedUnionFind\
    \ {\n    std::vector<int> par, sz;\n    std::vector<S> pot;\n    PotentializedUnionFind(int\
    \ N = 0) : par(N), sz(N, 1), pot(N) {\n        std::iota(par.begin(), par.end(),\
    \ 0);\n    }\n    int find(int x) {\n        if (par[x] != x) {\n            int\
    \ r = find(par[x]);\n            pot[x] = pot[x] + pot[par[x]], par[x] = r;\n\
    \        }\n        return par[x];\n    }\n    bool unite(int s, int t, S rel_diff)\
    \ {\n        // Relate s and t by f[t] = f[s] + rel_diff\n        // Return false\
    \ iff contradiction happens.\n        rel_diff = rel_diff + weight(s) + (-weight(t));\n\
    \        if ((s = find(s)) == (t = find(t))) return rel_diff == 0;\n        if\
    \ (sz[s] < sz[t]) std::swap(s, t), rel_diff = -rel_diff;\n        par[t] = s,\
    \ sz[s] += sz[t], pot[t] = rel_diff;\n        return true;\n    }\n    S weight(int\
    \ x) { return find(x), pot[x]; }\n    S diff(int s, int t) { return weight(t)\
    \ + (-weight(s)); } // return f[t] - f[s]\n    int count(int x) { return sz[find(x)];\
    \ }\n    bool same(int s, int t) { return find(s) == find(t); }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: unionfind/potentialized_unionfind.hpp
  requiredBy: []
  timestamp: '2024-10-02 23:55:49+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - unionfind/test/potentialized_unionfind_int.aoj3142.test.cpp
  - unionfind/test/potentialized_unionfind_F2.yuki1420.test.cpp
  - unionfind/test/potentialized_unionfind.test.cpp
documentation_of: unionfind/potentialized_unionfind.hpp
layout: document
title: "Potentialized UnionFind \uFF08\u91CD\u307F\u4ED8\u304D UnionFind\uFF09"
---

2個の要素間の重みづけが可能な UnionFind．

## 使用方法

ポテンシャルが（ふつうの）整数の場合．

```cpp
PotentializedUnionFind<int> uf(N);
uf.unite(s, t, diff);  // f[t] = f[s] + diff を要請．これまでの要請と矛盾すれば false を返す．

auto x = uf.diff(s, t);  // f[t] - f[s] （として考えられる値の一つ）を出力．
```

ポテンシャルが $\mathbb{F}_{2}$ 上のベクトルの場合．

```cpp
PotentializedUnionFind<Nimber> uf(N);
```

## 問題例

- [No.1420 国勢調査 (Easy) - yukicoder](https://yukicoder.me/problems/no/1420) $\mathbb{F}_2$ 上のベクトル．
- [AtCoder Beginner Contest 373 D - Hidden Weights](https://atcoder.jp/contests/abc373/tasks/abc373_d)
