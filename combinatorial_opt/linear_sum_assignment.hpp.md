---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"combinatorial_opt/linear_sum_assignment.hpp\"\n#include\
    \ <cassert>\n#include <tuple>\n#include <vector>\n\nnamespace linear_sum_assignment\
    \ {\n\ntemplate <class T>\nT augment(int nr, int nc, const std::vector<std::vector<T>>\
    \ &C, std::vector<T> &f,\n          std::vector<T> &g, int s, std::vector<int>\
    \ &mate, std::vector<int> &mate_inv) {\n\n    assert(0 <= s and s < nr);\n   \
    \ assert(mate.at(s) < 0);\n\n    static std::vector<T> dist;\n    static std::vector<int>\
    \ prv;\n    dist.resize(nc);\n    prv.resize(nc);\n\n    f.at(s) = C.at(s).at(0)\
    \ - g.at(0);\n    for (int j = 1; j < nc; ++j) f.at(s) = std::min(f.at(s), C.at(s).at(j)\
    \ - g.at(j));\n\n    for (int j = 0; j < nc; ++j) {\n        dist.at(j) = C.at(s).at(j)\
    \ - f.at(s) - g.at(j);\n        prv.at(j) = s;\n    }\n\n    std::vector<bool>\
    \ done(nc);\n\n    int t = -1;\n    std::vector<int> stk;\n\n    while (t == -1)\
    \ {\n        int j1 = -1;\n        for (int j = 0; j < nc; ++j) {\n          \
    \  if (done.at(j)) continue;\n            if (j1 == -1 or dist.at(j) < dist.at(j1)\
    \ or\n                (dist.at(j) == dist.at(j1) and mate_inv.at(j) < 0)) {\n\
    \                j1 = j;\n            }\n        }\n\n        if (j1 == -1) return\
    \ false;\n\n        if (mate_inv.at(j1) < 0) {\n            t = j1;\n        \
    \    break;\n        }\n\n        done.at(j1) = 1;\n        stk = {j1};\n\n  \
    \      while (!stk.empty()) {\n            const int i = mate_inv.at(stk.back());\n\
    \            if (i < 0) {\n                t = stk.back();\n                break;\n\
    \            }\n            stk.pop_back();\n\n            for (int j = 0; j <\
    \ nc; ++j) {\n                if (done.at(j)) continue;\n\n                const\
    \ T len = C.at(i).at(j) - f.at(i) - g.at(j);\n\n                if (dist.at(j)\
    \ > dist.at(j1) + len) {\n                    dist.at(j) = dist.at(j1) + len;\n\
    \                    prv.at(j) = i;\n                }\n\n                if (len\
    \ == T()) {\n                    stk.push_back(j);\n                    done.at(j)\
    \ = 1;\n                }\n            }\n        }\n    }\n\n    const T len\
    \ = dist.at(t);\n\n    f.at(s) += len;\n\n    T ret = len;\n\n    for (int j =\
    \ 0; j < nc; ++j) {\n        if (!done.at(j)) continue;\n\n        g.at(j) -=\
    \ len - dist.at(j);\n        if (mate_inv.at(j) >= 0) {\n            f.at(mate_inv.at(j))\
    \ += len - dist.at(j);\n        } else {\n            ret -= len - dist.at(j);\n\
    \        }\n    }\n\n    for (int cur = t; cur >= 0;) {\n        const int i =\
    \ prv.at(cur);\n        mate_inv.at(cur) = i;\n        if (i == -1) break;\n \
    \       std::swap(cur, mate.at(i));\n    }\n\n    return ret;\n}\n\n// Complexity:\
    \ O(nr^2 nc)\ntemplate <class T>\nstd::tuple<T, std::vector<int>, std::vector<T>,\
    \ std::vector<T>>\n_solve(int nr, int nc, const std::vector<std::vector<T>> &C)\
    \ {\n\n    assert(nr <= nc);\n\n    std::vector<int> mate(nr, -1);\n    std::vector<int>\
    \ mate_inv(nc, -1);\n    std::vector<T> f(nr), g(nc); // dual variables, f[i]\
    \ + g[j] <= C[i][j] holds\n\n    if (nr == 0 or nc == 0) return {T(), mate, f,\
    \ g};\n\n    if (nr == nc) {\n        // Column reduction\n        for (int j\
    \ = nc - 1; j >= 0; --j) {\n            g.at(j) = C.at(0).at(j) - f.at(0);\n \
    \           int imin = 0;\n            for (int i = 1; i < nr; ++i) {\n      \
    \          if (g.at(j) > C.at(i).at(j) - f.at(i)) {\n                    imin\
    \ = i;\n                    g.at(j) = C.at(i).at(j) - f.at(i);\n             \
    \   }\n            }\n\n            if (mate.at(imin) < 0) {\n               \
    \ mate.at(imin) = j;\n                mate_inv.at(j) = imin;\n            } else\
    \ if (g.at(j) < g.at(mate.at(imin))) {\n                mate_inv.at(mate.at(imin))\
    \ = -1;\n                mate.at(imin) = j;\n                mate_inv.at(j) =\
    \ imin;\n            }\n        }\n\n        // Reduction transfer (can be omitted)\n\
    \        if (nc > 1) {\n            for (int i = 0; i < nr; ++i) {\n         \
    \       if (mate.at(i) < 0) continue;\n                T best = C.at(i).at(0)\
    \ - g.at(0), second_best = C.at(i).at(1) - g.at(1);\n                int argbest\
    \ = 0;\n                if (best > second_best) std::swap(best, second_best),\
    \ argbest = 1;\n\n                for (int j = 2; j < nc; ++j) {\n           \
    \         if (T val = C.at(i).at(j) - g.at(j); val < best) {\n               \
    \         second_best = best;\n                        best = val;\n         \
    \               argbest = j;\n                    } else if (val < second_best)\
    \ {\n                        second_best = val;\n                    }\n     \
    \           }\n\n                g.at(argbest) -= second_best - best;\n      \
    \          f.at(i) = second_best;\n            }\n        }\n\n        // Augmenting\
    \ row reduction: not implemented\n    }\n\n    // Augmentation\n    for (int i\
    \ = 0; i < nr; ++i) {\n        if (mate.at(i) < 0) augment(nr, nc, C, f, g, i,\
    \ mate, mate_inv);\n    }\n\n    T ret = 0;\n    for (int i = 0; i < nr; ++i)\
    \ ret += C.at(i).at(mate.at(i));\n\n    return {ret, mate, std::move(f), std::move(g)};\n\
    }\n\n// Jonker\u2013Volgenant algorithm: find minimum weight assignment\n// Dual\
    \ problem (nr == nc): maximize sum(f) + sum(g) s.t. f_i + g_j <= C_ij\n// Complexity:\
    \ O(nr nc min(nr, nc))\ntemplate <class T>\nstd::tuple<T, std::vector<int>, std::vector<T>,\
    \ std::vector<T>>\nsolve(int nr, int nc, const std::vector<std::vector<T>> &C)\
    \ {\n\n    const bool transpose = (nr > nc);\n\n    if (!transpose) return _solve(nr,\
    \ nc, C);\n\n    std::vector trans(nc, std::vector<T>(nr));\n\n    for (int i\
    \ = 0; i < nr; ++i) {\n        for (int j = 0; j < nc; ++j) trans.at(j).at(i)\
    \ = C.at(i).at(j);\n    }\n\n    auto [v, mate, f, g] = _solve(nc, nr, trans);\n\
    \n    std::vector<int> mate2(nr, -1);\n    for (int j = 0; j < nc; ++j) {\n  \
    \      if (mate.at(j) >= 0) mate2.at(mate.at(j)) = j;\n    }\n\n    return {v,\
    \ mate2, g, f};\n}\n\n} // namespace linear_sum_assignment\n"
  code: "#pragma once\n#include <cassert>\n#include <tuple>\n#include <vector>\n\n\
    namespace linear_sum_assignment {\n\ntemplate <class T>\nT augment(int nr, int\
    \ nc, const std::vector<std::vector<T>> &C, std::vector<T> &f,\n          std::vector<T>\
    \ &g, int s, std::vector<int> &mate, std::vector<int> &mate_inv) {\n\n    assert(0\
    \ <= s and s < nr);\n    assert(mate.at(s) < 0);\n\n    static std::vector<T>\
    \ dist;\n    static std::vector<int> prv;\n    dist.resize(nc);\n    prv.resize(nc);\n\
    \n    f.at(s) = C.at(s).at(0) - g.at(0);\n    for (int j = 1; j < nc; ++j) f.at(s)\
    \ = std::min(f.at(s), C.at(s).at(j) - g.at(j));\n\n    for (int j = 0; j < nc;\
    \ ++j) {\n        dist.at(j) = C.at(s).at(j) - f.at(s) - g.at(j);\n        prv.at(j)\
    \ = s;\n    }\n\n    std::vector<bool> done(nc);\n\n    int t = -1;\n    std::vector<int>\
    \ stk;\n\n    while (t == -1) {\n        int j1 = -1;\n        for (int j = 0;\
    \ j < nc; ++j) {\n            if (done.at(j)) continue;\n            if (j1 ==\
    \ -1 or dist.at(j) < dist.at(j1) or\n                (dist.at(j) == dist.at(j1)\
    \ and mate_inv.at(j) < 0)) {\n                j1 = j;\n            }\n       \
    \ }\n\n        if (j1 == -1) return false;\n\n        if (mate_inv.at(j1) < 0)\
    \ {\n            t = j1;\n            break;\n        }\n\n        done.at(j1)\
    \ = 1;\n        stk = {j1};\n\n        while (!stk.empty()) {\n            const\
    \ int i = mate_inv.at(stk.back());\n            if (i < 0) {\n               \
    \ t = stk.back();\n                break;\n            }\n            stk.pop_back();\n\
    \n            for (int j = 0; j < nc; ++j) {\n                if (done.at(j))\
    \ continue;\n\n                const T len = C.at(i).at(j) - f.at(i) - g.at(j);\n\
    \n                if (dist.at(j) > dist.at(j1) + len) {\n                    dist.at(j)\
    \ = dist.at(j1) + len;\n                    prv.at(j) = i;\n                }\n\
    \n                if (len == T()) {\n                    stk.push_back(j);\n \
    \                   done.at(j) = 1;\n                }\n            }\n      \
    \  }\n    }\n\n    const T len = dist.at(t);\n\n    f.at(s) += len;\n\n    T ret\
    \ = len;\n\n    for (int j = 0; j < nc; ++j) {\n        if (!done.at(j)) continue;\n\
    \n        g.at(j) -= len - dist.at(j);\n        if (mate_inv.at(j) >= 0) {\n \
    \           f.at(mate_inv.at(j)) += len - dist.at(j);\n        } else {\n    \
    \        ret -= len - dist.at(j);\n        }\n    }\n\n    for (int cur = t; cur\
    \ >= 0;) {\n        const int i = prv.at(cur);\n        mate_inv.at(cur) = i;\n\
    \        if (i == -1) break;\n        std::swap(cur, mate.at(i));\n    }\n\n \
    \   return ret;\n}\n\n// Complexity: O(nr^2 nc)\ntemplate <class T>\nstd::tuple<T,\
    \ std::vector<int>, std::vector<T>, std::vector<T>>\n_solve(int nr, int nc, const\
    \ std::vector<std::vector<T>> &C) {\n\n    assert(nr <= nc);\n\n    std::vector<int>\
    \ mate(nr, -1);\n    std::vector<int> mate_inv(nc, -1);\n    std::vector<T> f(nr),\
    \ g(nc); // dual variables, f[i] + g[j] <= C[i][j] holds\n\n    if (nr == 0 or\
    \ nc == 0) return {T(), mate, f, g};\n\n    if (nr == nc) {\n        // Column\
    \ reduction\n        for (int j = nc - 1; j >= 0; --j) {\n            g.at(j)\
    \ = C.at(0).at(j) - f.at(0);\n            int imin = 0;\n            for (int\
    \ i = 1; i < nr; ++i) {\n                if (g.at(j) > C.at(i).at(j) - f.at(i))\
    \ {\n                    imin = i;\n                    g.at(j) = C.at(i).at(j)\
    \ - f.at(i);\n                }\n            }\n\n            if (mate.at(imin)\
    \ < 0) {\n                mate.at(imin) = j;\n                mate_inv.at(j) =\
    \ imin;\n            } else if (g.at(j) < g.at(mate.at(imin))) {\n           \
    \     mate_inv.at(mate.at(imin)) = -1;\n                mate.at(imin) = j;\n \
    \               mate_inv.at(j) = imin;\n            }\n        }\n\n        //\
    \ Reduction transfer (can be omitted)\n        if (nc > 1) {\n            for\
    \ (int i = 0; i < nr; ++i) {\n                if (mate.at(i) < 0) continue;\n\
    \                T best = C.at(i).at(0) - g.at(0), second_best = C.at(i).at(1)\
    \ - g.at(1);\n                int argbest = 0;\n                if (best > second_best)\
    \ std::swap(best, second_best), argbest = 1;\n\n                for (int j = 2;\
    \ j < nc; ++j) {\n                    if (T val = C.at(i).at(j) - g.at(j); val\
    \ < best) {\n                        second_best = best;\n                   \
    \     best = val;\n                        argbest = j;\n                    }\
    \ else if (val < second_best) {\n                        second_best = val;\n\
    \                    }\n                }\n\n                g.at(argbest) -=\
    \ second_best - best;\n                f.at(i) = second_best;\n            }\n\
    \        }\n\n        // Augmenting row reduction: not implemented\n    }\n\n\
    \    // Augmentation\n    for (int i = 0; i < nr; ++i) {\n        if (mate.at(i)\
    \ < 0) augment(nr, nc, C, f, g, i, mate, mate_inv);\n    }\n\n    T ret = 0;\n\
    \    for (int i = 0; i < nr; ++i) ret += C.at(i).at(mate.at(i));\n\n    return\
    \ {ret, mate, std::move(f), std::move(g)};\n}\n\n// Jonker\u2013Volgenant algorithm:\
    \ find minimum weight assignment\n// Dual problem (nr == nc): maximize sum(f)\
    \ + sum(g) s.t. f_i + g_j <= C_ij\n// Complexity: O(nr nc min(nr, nc))\ntemplate\
    \ <class T>\nstd::tuple<T, std::vector<int>, std::vector<T>, std::vector<T>>\n\
    solve(int nr, int nc, const std::vector<std::vector<T>> &C) {\n\n    const bool\
    \ transpose = (nr > nc);\n\n    if (!transpose) return _solve(nr, nc, C);\n\n\
    \    std::vector trans(nc, std::vector<T>(nr));\n\n    for (int i = 0; i < nr;\
    \ ++i) {\n        for (int j = 0; j < nc; ++j) trans.at(j).at(i) = C.at(i).at(j);\n\
    \    }\n\n    auto [v, mate, f, g] = _solve(nc, nr, trans);\n\n    std::vector<int>\
    \ mate2(nr, -1);\n    for (int j = 0; j < nc; ++j) {\n        if (mate.at(j) >=\
    \ 0) mate2.at(mate.at(j)) = j;\n    }\n\n    return {v, mate2, g, f};\n}\n\n}\
    \ // namespace linear_sum_assignment\n"
  dependsOn: []
  isVerificationFile: false
  path: combinatorial_opt/linear_sum_assignment.hpp
  requiredBy: []
  timestamp: '2023-08-22 20:35:28+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: combinatorial_opt/linear_sum_assignment.hpp
layout: document
title: "Linear sum assignment problem, Hungarian algorithm \uFF08\u5272\u5F53\u554F\
  \u984C\u306B\u5BFE\u3059\u308B\u30CF\u30F3\u30AC\u30EA\u30A2\u30F3\u6CD5\uFF09"
---

$r$ 行 $c$ 列の行列を入力とした割当問題（二部グラフの最小重み最大マッチング問題）を解く．計算量は `augment()` 一回あたり $O(rc)$ で，全体で $O(rc \min(r, c))$．

オーソドックスな Hungarian algorithm の実装ではなく， Jonker–Volgenant algorithm の工夫を一部取り入れることで定数倍高速化を試みている．

## 解いてくれる問題

主問題として，オーソドックスな線形重み割当問題を解く．

LP 緩和の双対問題を考えると，特に $r = c$ の場合，以下の問題のソルバとしても利用できる．

$\displaystyle
\begin{array}{rl}
\text{maximize} & \sum\_{i} f\_i + \sum\_j g\_j \\
\text{s.t.} & f\_{i} + g\_{j} \le C\_{ij}
\end{array}
$

## 使用方法

```cpp
vector C(r, vector<long long>(c));

long long min_weight;
vector<int> mate;
vector<long long> f, g;

std::tie(min_weight, mate, f, g) = linear_sum_assignment::solve(r, c, C);
```

`mate[i]` は第 $i$ 行が何列目の要素と対応するかを示す（ $r > c$ で，第 $i$ 行に対応する要素が存在しない場合は $-1$）．

また， `f[i]` および `g[j]` は最適解における双対変数の一例を示す．すなわち，任意の $i, j$ について $f\_i + g\_j \le C\_{ij}$ が成立し，特に第 $i$ 行と第 $j$ 列が対応する場合は等号が成立する．この双対変数は，行列の一部要素に更新を加えた場合の最適解の変化を効率的に追うために利用できる．

## 問題例

- [Library Checker: Assignment Problem](https://judge.yosupo.jp/problem/assignment)

## 文献・リンク集

- [Lecture 8: Assignment Algorithms](https://cyberlab.engr.uconn.edu/wp-content/uploads/sites/2576/2018/09/Lecture_8.pdf)
