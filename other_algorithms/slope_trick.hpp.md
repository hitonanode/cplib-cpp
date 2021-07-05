---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: other_algorithms/test/slope_trick_stress.test.cpp
    title: other_algorithms/test/slope_trick_stress.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://ei1333.github.io/library/structure/others/slope-trick.cpp
    - https://maspypy.com/slope-trick-1-%E8%A7%A3%E8%AA%AC%E7%B7%A8
  bundledCode: "#line 2 \"other_algorithms/slope_trick.hpp\"\n#include <algorithm>\n\
    #include <cassert>\n#include <limits>\n#include <queue>\n#include <utility>\n\n\
    // CUT begin\n// Slope trick: fast operations for convex piecewise-linear functions\n\
    //\n// Implementation idea:\n// - https://maspypy.com/slope-trick-1-%E8%A7%A3%E8%AA%AC%E7%B7%A8\n\
    // - https://ei1333.github.io/library/structure/others/slope-trick.cpp\ntemplate\
    \ <class T, T INF = std::numeric_limits<T>::max() / 2> class slope_trick {\n \
    \   T min_f;\n    T displacement_l, displacement_r;\n    std::priority_queue<T,\
    \ std::vector<T>, std::less<T>> L;\n    std::priority_queue<T, std::vector<T>,\
    \ std::greater<T>> R;\n    void pushR(const T &a) { R.push(a - displacement_r);\
    \ }\n    T topR() const { return R.empty() ? INF : R.top() + displacement_r; }\n\
    \    T popR() {\n        auto ret = topR();\n        if (R.size()) R.pop();\n\
    \        return ret;\n    }\n    void pushL(const T &a) { L.push(a + displacement_l);\
    \ }\n    T topL() const { return L.empty() ? -INF : L.top() - displacement_l;\
    \ }\n    T popL() {\n        auto ret = topL();\n        if (L.size()) L.pop();\n\
    \        return ret;\n    }\n    int size() const { return L.size() + R.size8();\
    \ }\n\npublic:\n    // Initialize: f(x) = 0\n    slope_trick() : min_f(0), displacement_l(0),\
    \ displacement_r(0) {\n        static_assert(INF > 0, \"INF must be greater than\
    \ 0\");\n    }\n    int sizeL() const { return L.size(); }\n    int sizeR() const\
    \ { return R.size(); }\n    // argmin f(x), min f(x)\n    using Q = struct { T\
    \ min, lo, hi; };\n    Q get_min() const { return {min_f, topL(), topR()}; }\n\
    \    // f(x) += b\n    void add_const(const T &b) { min_f += b; }\n    // f(x)\
    \ += max(x - a, 0)  _/\n    void add_relu(const T &a) { min_f += std::max(T(0),\
    \ topL() - a), pushL(a), pushR(popL()); }\n    // f(x) += max(a - x, 0)  \\_\n\
    \    void add_irelu(const T &a) { min_f += std::max(T(0), a - topR()), pushR(a),\
    \ pushL(popR()); }\n    // f(x) += |x - a|  \\/\n    void add_abs(const T &a)\
    \ { add_relu(a), add_irelu(a); }\n    // f(x) <- min_{0 <= y <= w} f(x + y)  .\\\
    \ -> \\_\n    void move_left_curve(const T &w) { assert(w >= 0), displacement_l\
    \ += w; }\n    // f(x) <- min_{0 <= y <= w} f(x - y)  /. -> _/\n    void move_right_curve(const\
    \ T &w) { assert(w >= 0), displacement_r += w; }\n    // f(x) <- f(x - dx) \\\
    /. -> .\\/\n    void translate(const T &dx) { displacement_l -= dx, displacement_r\
    \ += dx; }\n    // return f(x), f destructive\n    T get_destructive(const T &x)\
    \ {\n        T ret = get_min().min;\n        while (L.size()) ret += std::max(T(0),\
    \ popL() - x);\n        while (R.size()) ret += std::max(T(0), x - popR());\n\
    \        return ret;\n    }\n    // f(x) += g(x), g destructive\n    void merge_destructive(slope_trick<T,\
    \ INF> &g) {\n        if (sizeL() + sizeR() > g.sizeL() + g.sizeR()) {\n     \
    \       std::swap(min_f, g.min_f);\n            std::swap(displacement_l, g.displacement_l);\n\
    \            std::swap(displacement_r, g.displacement_r);\n            std::swap(L,\
    \ g.L);\n            std::swap(R, g.R);\n        }\n        min_f += g.get_min().min;\n\
    \        while (g.L.size()) add_irelu(g.popL());\n        while (g.R.size()) add_relu(g.popR());\n\
    \    }\n};\n"
  code: "#pragma once\n#include <algorithm>\n#include <cassert>\n#include <limits>\n\
    #include <queue>\n#include <utility>\n\n// CUT begin\n// Slope trick: fast operations\
    \ for convex piecewise-linear functions\n//\n// Implementation idea:\n// - https://maspypy.com/slope-trick-1-%E8%A7%A3%E8%AA%AC%E7%B7%A8\n\
    // - https://ei1333.github.io/library/structure/others/slope-trick.cpp\ntemplate\
    \ <class T, T INF = std::numeric_limits<T>::max() / 2> class slope_trick {\n \
    \   T min_f;\n    T displacement_l, displacement_r;\n    std::priority_queue<T,\
    \ std::vector<T>, std::less<T>> L;\n    std::priority_queue<T, std::vector<T>,\
    \ std::greater<T>> R;\n    void pushR(const T &a) { R.push(a - displacement_r);\
    \ }\n    T topR() const { return R.empty() ? INF : R.top() + displacement_r; }\n\
    \    T popR() {\n        auto ret = topR();\n        if (R.size()) R.pop();\n\
    \        return ret;\n    }\n    void pushL(const T &a) { L.push(a + displacement_l);\
    \ }\n    T topL() const { return L.empty() ? -INF : L.top() - displacement_l;\
    \ }\n    T popL() {\n        auto ret = topL();\n        if (L.size()) L.pop();\n\
    \        return ret;\n    }\n    int size() const { return L.size() + R.size8();\
    \ }\n\npublic:\n    // Initialize: f(x) = 0\n    slope_trick() : min_f(0), displacement_l(0),\
    \ displacement_r(0) {\n        static_assert(INF > 0, \"INF must be greater than\
    \ 0\");\n    }\n    int sizeL() const { return L.size(); }\n    int sizeR() const\
    \ { return R.size(); }\n    // argmin f(x), min f(x)\n    using Q = struct { T\
    \ min, lo, hi; };\n    Q get_min() const { return {min_f, topL(), topR()}; }\n\
    \    // f(x) += b\n    void add_const(const T &b) { min_f += b; }\n    // f(x)\
    \ += max(x - a, 0)  _/\n    void add_relu(const T &a) { min_f += std::max(T(0),\
    \ topL() - a), pushL(a), pushR(popL()); }\n    // f(x) += max(a - x, 0)  \\_\n\
    \    void add_irelu(const T &a) { min_f += std::max(T(0), a - topR()), pushR(a),\
    \ pushL(popR()); }\n    // f(x) += |x - a|  \\/\n    void add_abs(const T &a)\
    \ { add_relu(a), add_irelu(a); }\n    // f(x) <- min_{0 <= y <= w} f(x + y)  .\\\
    \ -> \\_\n    void move_left_curve(const T &w) { assert(w >= 0), displacement_l\
    \ += w; }\n    // f(x) <- min_{0 <= y <= w} f(x - y)  /. -> _/\n    void move_right_curve(const\
    \ T &w) { assert(w >= 0), displacement_r += w; }\n    // f(x) <- f(x - dx) \\\
    /. -> .\\/\n    void translate(const T &dx) { displacement_l -= dx, displacement_r\
    \ += dx; }\n    // return f(x), f destructive\n    T get_destructive(const T &x)\
    \ {\n        T ret = get_min().min;\n        while (L.size()) ret += std::max(T(0),\
    \ popL() - x);\n        while (R.size()) ret += std::max(T(0), x - popR());\n\
    \        return ret;\n    }\n    // f(x) += g(x), g destructive\n    void merge_destructive(slope_trick<T,\
    \ INF> &g) {\n        if (sizeL() + sizeR() > g.sizeL() + g.sizeR()) {\n     \
    \       std::swap(min_f, g.min_f);\n            std::swap(displacement_l, g.displacement_l);\n\
    \            std::swap(displacement_r, g.displacement_r);\n            std::swap(L,\
    \ g.L);\n            std::swap(R, g.R);\n        }\n        min_f += g.get_min().min;\n\
    \        while (g.L.size()) add_irelu(g.popL());\n        while (g.R.size()) add_relu(g.popR());\n\
    \    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: other_algorithms/slope_trick.hpp
  requiredBy: []
  timestamp: '2021-07-06 00:01:07+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - other_algorithms/test/slope_trick_stress.test.cpp
documentation_of: other_algorithms/slope_trick.hpp
layout: document
title: "Slope trick \uFF08\u533A\u5206\u7DDA\u5F62\u51F8\u95A2\u6570\u306B\u95A2\u3059\
  \u308B\u7279\u5B9A\u306E\u66F4\u65B0\u3092\u9AD8\u901F\u306B\u6271\u3046\u624B\u6CD5\
  \uFF09"
---

区分線形凸関数 $f(x)$ に関して傾きが 1 変化する $x$ 座標の多重集合と，$f(x)$ が最小値をとる区間を常に保持する．

```cpp
slope_trick<long long> f; // f(x) := 0                                    O(1)
f.add_const(b);           // f(x) += b                                    O(1)
f.add_relu(a);            // f(x) += max(x - a, 0)                        O(log N)
f.add_irelu(a);           // f(x) += max(a - x, 0)                        O(log N)
f.add_abs(a);             // f(x) += |x - a|                              O(log N)
f.move_left_curve(w);     // f(x) <- min_{0 <= y <= w} f(x + y),  w >= 0  O(1)
f.move_right_curve(w);    // f(x) <- min_{0 <= y <= w} f(x - y),  w >= 0  O(1)
f.translate(dx);          // f(x) <- f(x - dx)                            O(1)
f.merge_destructive(g);   // f(x) += g(x), g(x) broken                    O(min(N_f, N_g) log (N_f + N_g))
auto v = f.get_min().min; // v = min_x f(x)                               O(1)
y = f.get_destructive(x); // y = f(x), f(x) broken                        O(log N)
```

## 問題例

- [Codeforces LATOKEN Round 1 (Div. 1 + Div. 2) G. A New Beginning](https://codeforces.com/contest/1534/problem/G)

## Links

- [slope trick (1) 解説編 | maspyのHP](https://maspypy.com/slope-trick-1-%E8%A7%A3%E8%AA%AC%E7%B7%A8)
- [Slope-Trick | Luzhiled’s Library](https://ei1333.github.io/library/structure/others/slope-trick.cpp)
