---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other_algorithms/slope_trick.hpp
    title: "Slope trick \uFF08\u533A\u5206\u7DDA\u5F62\u51F8\u95A2\u6570\u306B\u95A2\
      \u3059\u308B\u7279\u5B9A\u306E\u66F4\u65B0\u3092\u9AD8\u901F\u306B\u6271\u3046\
      \u624B\u6CD5\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: other_algorithms/test/dual_slope_trick.yuki2114.test.cpp
    title: other_algorithms/test/dual_slope_trick.yuki2114.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://maspypy.com/slope-trick-3-slope-trick-%E3%81%AE%E5%87%B8%E5%85%B1%E5%BD%B9
    - https://yukicoder.me/problems/no/2114
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
    \ Complexity: O(1)\n    using Q = struct { T min, lo, hi; };\n    Q get_min()\
    \ const { return {min_f, topL(), topR()}; }\n\n    // f(x) += b\n    // Complexity:\
    \ O(1)\n    slope_trick &add_const(const T &b) { return min_f += b, *this; }\n\
    \n    // f(x) += max(x - a, 0)  _/\n    // Complexity: O(log n)\n    slope_trick\
    \ &add_relu(const T &a) {\n        return min_f += std::max(T(0), topL() - a),\
    \ pushL(a), pushR(popL()), *this;\n    }\n\n    // f(x) += max(a - x, 0)  \\_\n\
    \    // Complexity: O(log n)\n    slope_trick &add_irelu(const T &a) {\n     \
    \   return min_f += std::max(T(0), a - topR()), pushR(a), pushL(popR()), *this;\n\
    \    }\n\n    // f(x) += |x - a|  \\/\n    // Complexity: O(log n)\n    slope_trick\
    \ &add_abs(const T &a) { return add_relu(a).add_irelu(a); }\n\n    // f(x) <-\
    \ min_{0 <= y <= w} f(x + y)  .\\ -> \\_\n    // Complexity: O(1)\n    slope_trick\
    \ &move_left_curve(const T &w) { return assert(w >= 0), displacement_l += w, *this;\
    \ }\n\n    // f(x) <- min_{0 <= y <= w} f(x - y)  /. -> _/\n    // Complexity:\
    \ O(1)\n    slope_trick &move_right_curve(const T &w) {\n        return assert(w\
    \ >= 0), displacement_r += w, *this;\n    }\n\n    // f(x) <- f(x - dx) \\/. ->\
    \ .\\/\n    // Complexity: O(1)\n    slope_trick &translate(const T &dx) {\n \
    \       return displacement_l -= dx, displacement_r += dx, *this;\n    }\n\n \
    \   // return f(x), f destructive\n    T get_destructive(const T &x) {\n     \
    \   T ret = get_min().min;\n        while (L.size()) ret += std::max(T(0), popL()\
    \ - x);\n        while (R.size()) ret += std::max(T(0), x - popR());\n       \
    \ return ret;\n    }\n\n    // f(x) += g(x), g destructive\n    slope_trick &merge_destructive(slope_trick<T,\
    \ INF> &g) {\n        if (sizeL() + sizeR() > g.sizeL() + g.sizeR()) {\n     \
    \       std::swap(min_f, g.min_f);\n            std::swap(displacement_l, g.displacement_l);\n\
    \            std::swap(displacement_r, g.displacement_r);\n            std::swap(L,\
    \ g.L);\n            std::swap(R, g.R);\n        }\n        min_f += g.get_min().min;\n\
    \        while (g.L.size()) add_irelu(g.popL());\n        while (g.R.size()) add_relu(g.popR());\n\
    \        return *this;\n    }\n};\n#line 3 \"other_algorithms/dual_slope_trick.hpp\"\
    \n\n// https://maspypy.com/slope-trick-3-slope-trick-%E3%81%AE%E5%87%B8%E5%85%B1%E5%BD%B9\n\
    // Verified: https://yukicoder.me/problems/no/2114\ntemplate <class T, T INF =\
    \ std::numeric_limits<T>::max() / 2>\nclass dual_slope_trick : private slope_trick<T,\
    \ INF> {\npublic:\n    using Base = slope_trick<T, INF>;\n\n    // Initialize:\
    \ f(x) = 0 (x == 0), inf (otherwise)\n    // Complexity: O(1)\n    dual_slope_trick()\
    \ : Base() {}\n\n    // Get f(0)\n    // Complexity: O(1)\n    T get_at_zero()\
    \ const { return -Base::get_min().min; }\n\n    // f(x) <- f(x - d) (Move graph\
    \ to right by d)\n    // Complexity: O(log n)\n    dual_slope_trick &shift(int\
    \ d) {\n        while (d > 0) --d, Base::add_relu(-INF).add_const(-INF);\n   \
    \     while (d < 0) ++d, Base::add_irelu(INF).add_const(-INF);\n        return\
    \ *this;\n    }\n\n    // f(x) += ax + b\n    // Complexity: O(log n)\n    dual_slope_trick\
    \ &add_linear(T a, T b) { return Base::translate(a).add_const(b), *this; }\n\n\
    \    // f(x) += max(c(x - a), 0)\n    // Complexity: O(|a| log n)\n    dual_slope_trick\
    \ &add_linear_or_zero(T c, int a) {\n        shift(-a);\n        if (c > T())\
    \ Base::move_right_curve(c);\n        if (c < T()) Base::move_left_curve(-c);\n\
    \        return shift(a);\n    }\n\n    // f(x) <- min f(x - d), a <= d <= b\n\
    \    // Complexity: O((|a| + |b|) log n)\n    dual_slope_trick &slide_min(int\
    \ a, int b) {\n        assert(a <= b);\n        shift(a);\n        for (int t\
    \ = 0; t < b - a; ++t) Base::add_relu(T());\n        return *this;\n    }\n};\n"
  code: "#pragma once\n#include \"slope_trick.hpp\"\n\n// https://maspypy.com/slope-trick-3-slope-trick-%E3%81%AE%E5%87%B8%E5%85%B1%E5%BD%B9\n\
    // Verified: https://yukicoder.me/problems/no/2114\ntemplate <class T, T INF =\
    \ std::numeric_limits<T>::max() / 2>\nclass dual_slope_trick : private slope_trick<T,\
    \ INF> {\npublic:\n    using Base = slope_trick<T, INF>;\n\n    // Initialize:\
    \ f(x) = 0 (x == 0), inf (otherwise)\n    // Complexity: O(1)\n    dual_slope_trick()\
    \ : Base() {}\n\n    // Get f(0)\n    // Complexity: O(1)\n    T get_at_zero()\
    \ const { return -Base::get_min().min; }\n\n    // f(x) <- f(x - d) (Move graph\
    \ to right by d)\n    // Complexity: O(log n)\n    dual_slope_trick &shift(int\
    \ d) {\n        while (d > 0) --d, Base::add_relu(-INF).add_const(-INF);\n   \
    \     while (d < 0) ++d, Base::add_irelu(INF).add_const(-INF);\n        return\
    \ *this;\n    }\n\n    // f(x) += ax + b\n    // Complexity: O(log n)\n    dual_slope_trick\
    \ &add_linear(T a, T b) { return Base::translate(a).add_const(b), *this; }\n\n\
    \    // f(x) += max(c(x - a), 0)\n    // Complexity: O(|a| log n)\n    dual_slope_trick\
    \ &add_linear_or_zero(T c, int a) {\n        shift(-a);\n        if (c > T())\
    \ Base::move_right_curve(c);\n        if (c < T()) Base::move_left_curve(-c);\n\
    \        return shift(a);\n    }\n\n    // f(x) <- min f(x - d), a <= d <= b\n\
    \    // Complexity: O((|a| + |b|) log n)\n    dual_slope_trick &slide_min(int\
    \ a, int b) {\n        assert(a <= b);\n        shift(a);\n        for (int t\
    \ = 0; t < b - a; ++t) Base::add_relu(T());\n        return *this;\n    }\n};\n"
  dependsOn:
  - other_algorithms/slope_trick.hpp
  isVerificationFile: false
  path: other_algorithms/dual_slope_trick.hpp
  requiredBy: []
  timestamp: '2022-12-04 20:53:42+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - other_algorithms/test/dual_slope_trick.yuki2114.test.cpp
documentation_of: other_algorithms/dual_slope_trick.hpp
layout: document
title: Dual slope trick
---

凸関数 $f(x)$ に関して $f(0)$ の値や $f(i + 1) - f(i)$ の値の集合を保持し，各種クエリを高速に処理する．Slope trick が保持する関数の凸共役にあたる．

## 問題例

- [No.2114 01 Matching - yukicoder](https://yukicoder.me/problems/no/2114)

## Links

- [slope trick (3) slope trick の凸共役 \| maspyのHP](https://maspypy.com/slope-trick-3-slope-trick-%E3%81%AE%E5%87%B8%E5%85%B1%E5%BD%B9)
