---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: other_algorithms/dual_slope_trick.hpp
    title: Dual slope trick
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: other_algorithms/test/dual_slope_trick.yuki2114.test.cpp
    title: other_algorithms/test/dual_slope_trick.yuki2114.test.cpp
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
    // Slope trick: fast operations for convex piecewise-linear functions\n// Implementation\
    \ idea:\n// - https://maspypy.com/slope-trick-1-%E8%A7%A3%E8%AA%AC%E7%B7%A8\n\
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
    \        return ret;\n    }\n\npublic:\n    // Initialize, f(x) = 0 everywhere\n\
    \    // Complexity: O(1)\n    slope_trick() : min_f(0), displacement_l(0), displacement_r(0)\
    \ {\n        static_assert(INF > 0, \"INF must be greater than 0\");\n    }\n\
    \    inline int sizeL() const noexcept { return L.size(); }\n    inline int sizeR()\
    \ const noexcept { return R.size(); }\n\n    // argmin f(x), min f(x)\n    //\
    \ Complexity: O(1)\n    using Q = struct {\n        T min, lo, hi;\n    };\n \
    \   Q get_min() const { return {min_f, topL(), topR()}; }\n\n    // f(x) += b\n\
    \    // Complexity: O(1)\n    slope_trick &add_const(const T &b) { return min_f\
    \ += b, *this; }\n\n    // f(x) += max(x - a, 0)  _/\n    // Complexity: O(log\
    \ n)\n    slope_trick &add_relu(const T &a) {\n        return min_f += std::max(T(0),\
    \ topL() - a), pushL(a), pushR(popL()), *this;\n    }\n\n    // f(x) += max(a\
    \ - x, 0)  \\_\n    // Complexity: O(log n)\n    slope_trick &add_irelu(const\
    \ T &a) {\n        return min_f += std::max(T(0), a - topR()), pushR(a), pushL(popR()),\
    \ *this;\n    }\n\n    // f(x) += |x - a|  \\/\n    // Complexity: O(log n)\n\
    \    slope_trick &add_abs(const T &a) { return add_relu(a).add_irelu(a); }\n\n\
    \    // f(x) <- min_{0 <= y <= w} f(x + y)  .\\ -> \\_\n    // Complexity: O(1)\n\
    \    slope_trick &move_left_curve(const T &w) { return assert(w >= 0), displacement_l\
    \ += w, *this; }\n\n    // f(x) <- min_{0 <= y <= w} f(x - y)  /. -> _/\n    //\
    \ Complexity: O(1)\n    slope_trick &move_right_curve(const T &w) {\n        return\
    \ assert(w >= 0), displacement_r += w, *this;\n    }\n\n    // f(x) <- f(x - dx)\
    \ \\/. -> .\\/\n    // Complexity: O(1)\n    slope_trick &translate(const T &dx)\
    \ {\n        return displacement_l -= dx, displacement_r += dx, *this;\n    }\n\
    \n    // return f(x), f destructive\n    T get_destructive(const T &x) {\n   \
    \     T ret = get_min().min;\n        while (L.size()) ret += std::max(T(0), popL()\
    \ - x);\n        while (R.size()) ret += std::max(T(0), x - popR());\n       \
    \ return ret;\n    }\n\n    // f(x) += g(x), g destructive\n    slope_trick &merge_destructive(slope_trick<T,\
    \ INF> &g) {\n        if (sizeL() + sizeR() > g.sizeL() + g.sizeR()) {\n     \
    \       std::swap(min_f, g.min_f);\n            std::swap(displacement_l, g.displacement_l);\n\
    \            std::swap(displacement_r, g.displacement_r);\n            std::swap(L,\
    \ g.L);\n            std::swap(R, g.R);\n        }\n        min_f += g.get_min().min;\n\
    \        while (g.L.size()) add_irelu(g.popL());\n        while (g.R.size()) add_relu(g.popR());\n\
    \        return *this;\n    }\n};\n"
  code: "#pragma once\n#include <algorithm>\n#include <cassert>\n#include <limits>\n\
    #include <queue>\n#include <utility>\n\n// Slope trick: fast operations for convex\
    \ piecewise-linear functions\n// Implementation idea:\n// - https://maspypy.com/slope-trick-1-%E8%A7%A3%E8%AA%AC%E7%B7%A8\n\
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
    \        return ret;\n    }\n\npublic:\n    // Initialize, f(x) = 0 everywhere\n\
    \    // Complexity: O(1)\n    slope_trick() : min_f(0), displacement_l(0), displacement_r(0)\
    \ {\n        static_assert(INF > 0, \"INF must be greater than 0\");\n    }\n\
    \    inline int sizeL() const noexcept { return L.size(); }\n    inline int sizeR()\
    \ const noexcept { return R.size(); }\n\n    // argmin f(x), min f(x)\n    //\
    \ Complexity: O(1)\n    using Q = struct {\n        T min, lo, hi;\n    };\n \
    \   Q get_min() const { return {min_f, topL(), topR()}; }\n\n    // f(x) += b\n\
    \    // Complexity: O(1)\n    slope_trick &add_const(const T &b) { return min_f\
    \ += b, *this; }\n\n    // f(x) += max(x - a, 0)  _/\n    // Complexity: O(log\
    \ n)\n    slope_trick &add_relu(const T &a) {\n        return min_f += std::max(T(0),\
    \ topL() - a), pushL(a), pushR(popL()), *this;\n    }\n\n    // f(x) += max(a\
    \ - x, 0)  \\_\n    // Complexity: O(log n)\n    slope_trick &add_irelu(const\
    \ T &a) {\n        return min_f += std::max(T(0), a - topR()), pushR(a), pushL(popR()),\
    \ *this;\n    }\n\n    // f(x) += |x - a|  \\/\n    // Complexity: O(log n)\n\
    \    slope_trick &add_abs(const T &a) { return add_relu(a).add_irelu(a); }\n\n\
    \    // f(x) <- min_{0 <= y <= w} f(x + y)  .\\ -> \\_\n    // Complexity: O(1)\n\
    \    slope_trick &move_left_curve(const T &w) { return assert(w >= 0), displacement_l\
    \ += w, *this; }\n\n    // f(x) <- min_{0 <= y <= w} f(x - y)  /. -> _/\n    //\
    \ Complexity: O(1)\n    slope_trick &move_right_curve(const T &w) {\n        return\
    \ assert(w >= 0), displacement_r += w, *this;\n    }\n\n    // f(x) <- f(x - dx)\
    \ \\/. -> .\\/\n    // Complexity: O(1)\n    slope_trick &translate(const T &dx)\
    \ {\n        return displacement_l -= dx, displacement_r += dx, *this;\n    }\n\
    \n    // return f(x), f destructive\n    T get_destructive(const T &x) {\n   \
    \     T ret = get_min().min;\n        while (L.size()) ret += std::max(T(0), popL()\
    \ - x);\n        while (R.size()) ret += std::max(T(0), x - popR());\n       \
    \ return ret;\n    }\n\n    // f(x) += g(x), g destructive\n    slope_trick &merge_destructive(slope_trick<T,\
    \ INF> &g) {\n        if (sizeL() + sizeR() > g.sizeL() + g.sizeR()) {\n     \
    \       std::swap(min_f, g.min_f);\n            std::swap(displacement_l, g.displacement_l);\n\
    \            std::swap(displacement_r, g.displacement_r);\n            std::swap(L,\
    \ g.L);\n            std::swap(R, g.R);\n        }\n        min_f += g.get_min().min;\n\
    \        while (g.L.size()) add_irelu(g.popL());\n        while (g.R.size()) add_relu(g.popR());\n\
    \        return *this;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: other_algorithms/slope_trick.hpp
  requiredBy:
  - other_algorithms/dual_slope_trick.hpp
  timestamp: '2023-08-05 14:49:43+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - other_algorithms/test/slope_trick_stress.test.cpp
  - other_algorithms/test/dual_slope_trick.yuki2114.test.cpp
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
- [AtCoder Beginner Contest 217 H - Snuketoon](https://atcoder.jp/contests/abc217/tasks/abc217_h)

## Links

- [slope trick (1) 解説編 \| maspyのHP](https://maspypy.com/slope-trick-1-%E8%A7%A3%E8%AA%AC%E7%B7%A8)
- [Slope-Trick \| Luzhiled’s Library](https://ei1333.github.io/library/structure/others/slope-trick.cpp)
