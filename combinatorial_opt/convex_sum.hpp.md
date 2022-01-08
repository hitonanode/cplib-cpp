---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/test/convex_sum.test.cpp
    title: combinatorial_opt/test/convex_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://codeforces.com/contest/1344/problem/D
    - https://yukicoder.me/problems/no/1495
  bundledCode: "#line 2 \"combinatorial_opt/convex_sum.hpp\"\n#include <cassert>\n\
    #include <utility>\n#include <vector>\n\n// ax^2 + bx + c (convex), lb <= x <=\
    \ ub\nstruct Quadratic {\n    using Int = long long;\n    Int a, b, c, lb, ub;\n\
    \    Quadratic(Int a, Int b, Int c, Int lb, Int ub) : a(a), b(b), c(c), lb(lb),\
    \ ub(ub) {}\n    Int slope(Int s) const noexcept {\n        if (a == 0) return\
    \ b <= s ? ub : lb;\n        auto ret = (s + a - b) / (a * 2);\n        return\
    \ ret > ub ? ub : ret < lb ? lb : ret;\n    }\n    Int eval(Int x) const noexcept\
    \ { return (a * x + b) * x + c; }\n    // f(x) - f(x - 1)\n    Int next_cost(Int\
    \ x) const noexcept { return 2 * a * x - a + b; }\n};\n\n// x^3 - ax, x \\geq\
    \ 0 (convex)\nstruct Cubic {\n    int a, lb, ub;\n    Cubic(int a, int ub) : a(a),\
    \ lb(0), ub(ub) {}\n    int slope(long long s) const noexcept {\n        int lo\
    \ = lb, hi = ub + 1;\n        while (hi - lo > 1) {\n            int x = (lo +\
    \ hi) / 2;\n            (next_cost(x) <= s ? lo : hi) = x;\n        }\n      \
    \  return lo;\n    }\n    long long eval(long long x) const noexcept { return\
    \ (x * x - a) * x; }\n    // f(x) - f(x - 1)\n    long long next_cost(long long\
    \ x) const noexcept { return 3 * x * x - 3 * x + 1 - a; }\n};\n\n// \\minimize\
    \ $\\sum_i \\sum_j^{k_i} f_i(x_{ij})$\n// https://codeforces.com/contest/1344/problem/D\n\
    // https://yukicoder.me/problems/no/1495\n// return: (y, [[(x_i, # of such x_i),\
    \ ... ], ...])\ntemplate <typename F, typename Int, Int INF>\nstd::pair<Int, std::vector<std::vector<std::pair<Int,\
    \ Int>>>>\nMinConvexSumUnderLinearConstraint(const std::vector<Int> &k, const\
    \ std::vector<F> &f, Int C) {\n    assert(k.size() == f.size());\n    assert(k.size()\
    \ > 0);\n    Int lbsum = 0, ubsum = 0;\n    for (auto func : f) lbsum += func.lb,\
    \ ubsum += func.ub;\n    if (lbsum > C or ubsum < C) return {};\n\n    const int\
    \ N = k.size();\n    Int few = -INF, enough = INF;\n    while (enough - few >\
    \ 1) {\n        auto slope = few + (enough - few) / 2;\n        Int cnt = 0;\n\
    \        for (int i = 0; i < N; i++) {\n            auto tmp = f[i].slope(slope);\n\
    \            cnt += tmp * k[i];\n            if (cnt >= C) break;\n        }\n\
    \        (cnt >= C ? enough : few) = slope;\n    }\n\n    std::vector<std::vector<std::pair<Int,\
    \ Int>>> ret(N);\n    std::vector<int> additional;\n    Int ctmp = 0;\n    Int\
    \ sol = 0;\n    for (int i = 0; i < N; i++) {\n        auto xlo = f[i].slope(few);\n\
    \        auto xhi = f[i].slope(few + 1);\n        ctmp += k[i] * xlo;\n      \
    \  ret[i].emplace_back(xlo, k[i]);\n        if (xlo < xhi) additional.push_back(i);\n\
    \        sol += k[i] * f[i].eval(xlo);\n    }\n    sol += (C - ctmp) * (few +\
    \ 1);\n    while (additional.size()) {\n        int i = additional.back();\n \
    \       additional.pop_back();\n        Int add = C - ctmp > k[i] ? k[i] : C -\
    \ ctmp;\n        auto x = ret[i][0].first;\n        if (add) {\n            ret[i][0].second\
    \ -= add;\n            if (ret[i][0].second == 0) ret[i].pop_back();\n       \
    \     ret[i].emplace_back(x + 1, add);\n            ctmp += add;\n        }\n\
    \    }\n    return {sol, ret};\n}\n"
  code: "#pragma once\n#include <cassert>\n#include <utility>\n#include <vector>\n\
    \n// ax^2 + bx + c (convex), lb <= x <= ub\nstruct Quadratic {\n    using Int\
    \ = long long;\n    Int a, b, c, lb, ub;\n    Quadratic(Int a, Int b, Int c, Int\
    \ lb, Int ub) : a(a), b(b), c(c), lb(lb), ub(ub) {}\n    Int slope(Int s) const\
    \ noexcept {\n        if (a == 0) return b <= s ? ub : lb;\n        auto ret =\
    \ (s + a - b) / (a * 2);\n        return ret > ub ? ub : ret < lb ? lb : ret;\n\
    \    }\n    Int eval(Int x) const noexcept { return (a * x + b) * x + c; }\n \
    \   // f(x) - f(x - 1)\n    Int next_cost(Int x) const noexcept { return 2 * a\
    \ * x - a + b; }\n};\n\n// x^3 - ax, x \\geq 0 (convex)\nstruct Cubic {\n    int\
    \ a, lb, ub;\n    Cubic(int a, int ub) : a(a), lb(0), ub(ub) {}\n    int slope(long\
    \ long s) const noexcept {\n        int lo = lb, hi = ub + 1;\n        while (hi\
    \ - lo > 1) {\n            int x = (lo + hi) / 2;\n            (next_cost(x) <=\
    \ s ? lo : hi) = x;\n        }\n        return lo;\n    }\n    long long eval(long\
    \ long x) const noexcept { return (x * x - a) * x; }\n    // f(x) - f(x - 1)\n\
    \    long long next_cost(long long x) const noexcept { return 3 * x * x - 3 *\
    \ x + 1 - a; }\n};\n\n// \\minimize $\\sum_i \\sum_j^{k_i} f_i(x_{ij})$\n// https://codeforces.com/contest/1344/problem/D\n\
    // https://yukicoder.me/problems/no/1495\n// return: (y, [[(x_i, # of such x_i),\
    \ ... ], ...])\ntemplate <typename F, typename Int, Int INF>\nstd::pair<Int, std::vector<std::vector<std::pair<Int,\
    \ Int>>>>\nMinConvexSumUnderLinearConstraint(const std::vector<Int> &k, const\
    \ std::vector<F> &f, Int C) {\n    assert(k.size() == f.size());\n    assert(k.size()\
    \ > 0);\n    Int lbsum = 0, ubsum = 0;\n    for (auto func : f) lbsum += func.lb,\
    \ ubsum += func.ub;\n    if (lbsum > C or ubsum < C) return {};\n\n    const int\
    \ N = k.size();\n    Int few = -INF, enough = INF;\n    while (enough - few >\
    \ 1) {\n        auto slope = few + (enough - few) / 2;\n        Int cnt = 0;\n\
    \        for (int i = 0; i < N; i++) {\n            auto tmp = f[i].slope(slope);\n\
    \            cnt += tmp * k[i];\n            if (cnt >= C) break;\n        }\n\
    \        (cnt >= C ? enough : few) = slope;\n    }\n\n    std::vector<std::vector<std::pair<Int,\
    \ Int>>> ret(N);\n    std::vector<int> additional;\n    Int ctmp = 0;\n    Int\
    \ sol = 0;\n    for (int i = 0; i < N; i++) {\n        auto xlo = f[i].slope(few);\n\
    \        auto xhi = f[i].slope(few + 1);\n        ctmp += k[i] * xlo;\n      \
    \  ret[i].emplace_back(xlo, k[i]);\n        if (xlo < xhi) additional.push_back(i);\n\
    \        sol += k[i] * f[i].eval(xlo);\n    }\n    sol += (C - ctmp) * (few +\
    \ 1);\n    while (additional.size()) {\n        int i = additional.back();\n \
    \       additional.pop_back();\n        Int add = C - ctmp > k[i] ? k[i] : C -\
    \ ctmp;\n        auto x = ret[i][0].first;\n        if (add) {\n            ret[i][0].second\
    \ -= add;\n            if (ret[i][0].second == 0) ret[i].pop_back();\n       \
    \     ret[i].emplace_back(x + 1, add);\n            ctmp += add;\n        }\n\
    \    }\n    return {sol, ret};\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: combinatorial_opt/convex_sum.hpp
  requiredBy: []
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - combinatorial_opt/test/convex_sum.test.cpp
documentation_of: combinatorial_opt/convex_sum.hpp
layout: document
title: "\u5F15\u6570\u7DCF\u548C\u306B\u95A2\u3059\u308B\u7B49\u5F0F\u5236\u7D04\u4E0B\
  \u306E\u4E92\u3044\u306B\u72EC\u7ACB\u306A\u4E00\u5F15\u6570\u96E2\u6563\u51F8\u95A2\
  \u6570\u548C\u306E\u6700\u5C0F\u5316"
---

コスト関数

$\displaystyle
y = \sum_{i=1}^N \sum_{j=1}^{k_i} f_i (x_{ij})
$

を，等式制約 $\displaystyle \sum_{i=1}^N \sum_{j=1}^{k_i} x_{ij} = C$ のもと最小化する．

## 問題例

- [Codeforces Round #639 (Div. 1) D. Résumé Review](https://codeforces.com/contest/1344/problem/D)
- [yukicoder No.1495 パンの仕入れ](https://yukicoder.me/problems/no/1495)
