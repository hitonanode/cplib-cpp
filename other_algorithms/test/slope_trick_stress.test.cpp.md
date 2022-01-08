---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: other_algorithms/slope_trick.hpp
    title: "Slope trick \uFF08\u533A\u5206\u7DDA\u5F62\u51F8\u95A2\u6570\u306B\u95A2\
      \u3059\u308B\u7279\u5B9A\u306E\u66F4\u65B0\u3092\u9AD8\u901F\u306B\u6271\u3046\
      \u624B\u6CD5\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
  bundledCode: "#line 1 \"other_algorithms/test/slope_trick_stress.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \ // DUMMY\n#line 2 \"other_algorithms/slope_trick.hpp\"\n#include <algorithm>\n\
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
    \        return ret;\n    }\n\npublic:\n    // Initialize: f(x) = 0\n    slope_trick()\
    \ : min_f(0), displacement_l(0), displacement_r(0) {\n        static_assert(INF\
    \ > 0, \"INF must be greater than 0\");\n    }\n    int sizeL() const { return\
    \ L.size(); }\n    int sizeR() const { return R.size(); }\n\n    // argmin f(x),\
    \ min f(x)\n    using Q = struct { T min, lo, hi; };\n    Q get_min() const {\
    \ return {min_f, topL(), topR()}; }\n\n    // f(x) += b\n    void add_const(const\
    \ T &b) { min_f += b; }\n\n    // f(x) += max(x - a, 0)  _/\n    void add_relu(const\
    \ T &a) { min_f += std::max(T(0), topL() - a), pushL(a), pushR(popL()); }\n\n\
    \    // f(x) += max(a - x, 0)  \\_\n    void add_irelu(const T &a) { min_f +=\
    \ std::max(T(0), a - topR()), pushR(a), pushL(popR()); }\n\n    // f(x) += |x\
    \ - a|  \\/\n    void add_abs(const T &a) { add_relu(a), add_irelu(a); }\n\n \
    \   // f(x) <- min_{0 <= y <= w} f(x + y)  .\\ -> \\_\n    void move_left_curve(const\
    \ T &w) { assert(w >= 0), displacement_l += w; }\n\n    // f(x) <- min_{0 <= y\
    \ <= w} f(x - y)  /. -> _/\n    void move_right_curve(const T &w) { assert(w >=\
    \ 0), displacement_r += w; }\n\n    // f(x) <- f(x - dx) \\/. -> .\\/\n    void\
    \ translate(const T &dx) { displacement_l -= dx, displacement_r += dx; }\n\n \
    \   // return f(x), f destructive\n    T get_destructive(const T &x) {\n     \
    \   T ret = get_min().min;\n        while (L.size()) ret += std::max(T(0), popL()\
    \ - x);\n        while (R.size()) ret += std::max(T(0), x - popR());\n       \
    \ return ret;\n    }\n\n    // f(x) += g(x), g destructive\n    void merge_destructive(slope_trick<T,\
    \ INF> &g) {\n        if (sizeL() + sizeR() > g.sizeL() + g.sizeR()) {\n     \
    \       std::swap(min_f, g.min_f);\n            std::swap(displacement_l, g.displacement_l);\n\
    \            std::swap(displacement_r, g.displacement_r);\n            std::swap(L,\
    \ g.L);\n            std::swap(R, g.R);\n        }\n        min_f += g.get_min().min;\n\
    \        while (g.L.size()) add_irelu(g.popL());\n        while (g.R.size()) add_relu(g.popR());\n\
    \    }\n};\n#line 3 \"other_algorithms/test/slope_trick_stress.test.cpp\"\n#include\
    \ <cstdio>\n#include <random>\n#include <tuple>\n#line 7 \"other_algorithms/test/slope_trick_stress.test.cpp\"\
    \nusing namespace std;\n\nmt19937 mt(1010101);\n\ntemplate <typename Int> pair<slope_trick<Int>,\
    \ vector<Int>> gen_random_function(Int lo, Int hi) {\n    slope_trick<Int> f;\n\
    \    const Int dxmax = 10;\n\n    int nquery = 100;\n\n    const Int stupid_lo\
    \ = lo - nquery * dxmax, stupid_hi = hi + nquery * dxmax;\n    std::vector<Int>\
    \ stupid_f(stupid_hi - stupid_lo + 1);\n\n    for (int t = 0; t < nquery; t++)\
    \ {\n        int qtype = uniform_int_distribution<int>(0, 6)(mt);\n        Int\
    \ a = uniform_int_distribution<Int>(lo, hi)(mt);\n        Int w = uniform_int_distribution<Int>(0,\
    \ dxmax)(mt);\n        if (qtype == 0) {\n            Int b = uniform_int_distribution<Int>(-10000,\
    \ 10000)(mt);\n            f.add_const(b);\n            for (Int x = stupid_lo;\
    \ x <= stupid_hi; x++) stupid_f[x - stupid_lo] += b;\n        }\n        if (qtype\
    \ == 1) {\n            f.add_relu(a);\n            for (Int x = stupid_lo; x <=\
    \ stupid_hi; x++)\n                stupid_f[x - stupid_lo] += max<Int>(x - a,\
    \ 0);\n        }\n        if (qtype == 2) {\n            f.add_irelu(a);\n   \
    \         for (Int x = stupid_lo; x <= stupid_hi; x++)\n                stupid_f[x\
    \ - stupid_lo] += max<Int>(a - x, 0);\n        }\n        if (qtype == 3) {\n\
    \            f.add_abs(a);\n            for (Int x = stupid_lo; x <= stupid_hi;\
    \ x++) stupid_f[x - stupid_lo] += abs(x - a);\n        }\n        if (qtype ==\
    \ 4) {\n            f.move_left_curve(w);\n            for (Int x = stupid_lo;\
    \ x <= stupid_hi; x++) {\n                for (Int y = x + 1; y <= min(stupid_hi,\
    \ x + w); y++) {\n                    stupid_f[x - stupid_lo] = min(stupid_f[x\
    \ - stupid_lo], stupid_f[y - stupid_lo]);\n                }\n            }\n\
    \        }\n        if (qtype == 5) {\n            f.move_right_curve(w);\n  \
    \          for (Int x = stupid_hi; x >= stupid_lo; x--) {\n                for\
    \ (Int y = x - 1; y >= max(stupid_lo, x - w); y--) {\n                    stupid_f[x\
    \ - stupid_lo] = min(stupid_f[x - stupid_lo], stupid_f[y - stupid_lo]);\n    \
    \            }\n            }\n        }\n        if (qtype == 6) {\n        \
    \    Int dx = uniform_int_distribution<Int>(-dxmax, dxmax)(mt);\n            f.translate(dx);\n\
    \            auto g = stupid_f;\n            for (Int x = stupid_lo; x <= stupid_hi;\
    \ x++) {\n                Int y = x - dx;\n                if (y >= stupid_lo\
    \ and y <= stupid_hi) g[x - stupid_lo] = stupid_f[y - stupid_lo];\n          \
    \  }\n            stupid_f = g;\n        }\n    }\n    vector<Int> fvals;\n  \
    \  for (Int x = lo; x <= hi; x++) {\n        Int ret1 = stupid_f[x - stupid_lo];\n\
    \        auto g = f;\n        Int ret2 = g.get_destructive(x);\n        fvals.push_back(ret2);\n\
    \        assert(ret1 == ret2);\n    }\n    return {f, fvals};\n}\n\ntemplate <typename\
    \ Int> void merge_verify() {\n    const Int lo = uniform_int_distribution<Int>(-10000,\
    \ 10000)(mt);\n    const Int hi = lo + 1000;\n    slope_trick<Int> f, g;\n   \
    \ vector<Int> fval, gval;\n    tie(f, fval) = gen_random_function(lo, hi);\n \
    \   tie(g, gval) = gen_random_function(lo, hi);\n    f.merge_destructive(g);\n\
    \    for (Int x = lo; x <= hi; x++) {\n        auto tmp = f;\n        assert(tmp.get_destructive(x)\
    \ == fval.at(x - lo) + gval.at(x - lo));\n    }\n}\n\nint main() {\n    for (int\
    \ t = 0; t < 1000; t++) {\n        merge_verify<int>();\n        merge_verify<long\
    \ long>();\n    }\n    puts(\"Hello World\");\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \ // DUMMY\n#include \"../slope_trick.hpp\"\n#include <cstdio>\n#include <random>\n\
    #include <tuple>\n#include <utility>\nusing namespace std;\n\nmt19937 mt(1010101);\n\
    \ntemplate <typename Int> pair<slope_trick<Int>, vector<Int>> gen_random_function(Int\
    \ lo, Int hi) {\n    slope_trick<Int> f;\n    const Int dxmax = 10;\n\n    int\
    \ nquery = 100;\n\n    const Int stupid_lo = lo - nquery * dxmax, stupid_hi =\
    \ hi + nquery * dxmax;\n    std::vector<Int> stupid_f(stupid_hi - stupid_lo +\
    \ 1);\n\n    for (int t = 0; t < nquery; t++) {\n        int qtype = uniform_int_distribution<int>(0,\
    \ 6)(mt);\n        Int a = uniform_int_distribution<Int>(lo, hi)(mt);\n      \
    \  Int w = uniform_int_distribution<Int>(0, dxmax)(mt);\n        if (qtype ==\
    \ 0) {\n            Int b = uniform_int_distribution<Int>(-10000, 10000)(mt);\n\
    \            f.add_const(b);\n            for (Int x = stupid_lo; x <= stupid_hi;\
    \ x++) stupid_f[x - stupid_lo] += b;\n        }\n        if (qtype == 1) {\n \
    \           f.add_relu(a);\n            for (Int x = stupid_lo; x <= stupid_hi;\
    \ x++)\n                stupid_f[x - stupid_lo] += max<Int>(x - a, 0);\n     \
    \   }\n        if (qtype == 2) {\n            f.add_irelu(a);\n            for\
    \ (Int x = stupid_lo; x <= stupid_hi; x++)\n                stupid_f[x - stupid_lo]\
    \ += max<Int>(a - x, 0);\n        }\n        if (qtype == 3) {\n            f.add_abs(a);\n\
    \            for (Int x = stupid_lo; x <= stupid_hi; x++) stupid_f[x - stupid_lo]\
    \ += abs(x - a);\n        }\n        if (qtype == 4) {\n            f.move_left_curve(w);\n\
    \            for (Int x = stupid_lo; x <= stupid_hi; x++) {\n                for\
    \ (Int y = x + 1; y <= min(stupid_hi, x + w); y++) {\n                    stupid_f[x\
    \ - stupid_lo] = min(stupid_f[x - stupid_lo], stupid_f[y - stupid_lo]);\n    \
    \            }\n            }\n        }\n        if (qtype == 5) {\n        \
    \    f.move_right_curve(w);\n            for (Int x = stupid_hi; x >= stupid_lo;\
    \ x--) {\n                for (Int y = x - 1; y >= max(stupid_lo, x - w); y--)\
    \ {\n                    stupid_f[x - stupid_lo] = min(stupid_f[x - stupid_lo],\
    \ stupid_f[y - stupid_lo]);\n                }\n            }\n        }\n   \
    \     if (qtype == 6) {\n            Int dx = uniform_int_distribution<Int>(-dxmax,\
    \ dxmax)(mt);\n            f.translate(dx);\n            auto g = stupid_f;\n\
    \            for (Int x = stupid_lo; x <= stupid_hi; x++) {\n                Int\
    \ y = x - dx;\n                if (y >= stupid_lo and y <= stupid_hi) g[x - stupid_lo]\
    \ = stupid_f[y - stupid_lo];\n            }\n            stupid_f = g;\n     \
    \   }\n    }\n    vector<Int> fvals;\n    for (Int x = lo; x <= hi; x++) {\n \
    \       Int ret1 = stupid_f[x - stupid_lo];\n        auto g = f;\n        Int\
    \ ret2 = g.get_destructive(x);\n        fvals.push_back(ret2);\n        assert(ret1\
    \ == ret2);\n    }\n    return {f, fvals};\n}\n\ntemplate <typename Int> void\
    \ merge_verify() {\n    const Int lo = uniform_int_distribution<Int>(-10000, 10000)(mt);\n\
    \    const Int hi = lo + 1000;\n    slope_trick<Int> f, g;\n    vector<Int> fval,\
    \ gval;\n    tie(f, fval) = gen_random_function(lo, hi);\n    tie(g, gval) = gen_random_function(lo,\
    \ hi);\n    f.merge_destructive(g);\n    for (Int x = lo; x <= hi; x++) {\n  \
    \      auto tmp = f;\n        assert(tmp.get_destructive(x) == fval.at(x - lo)\
    \ + gval.at(x - lo));\n    }\n}\n\nint main() {\n    for (int t = 0; t < 1000;\
    \ t++) {\n        merge_verify<int>();\n        merge_verify<long long>();\n \
    \   }\n    puts(\"Hello World\");\n}\n"
  dependsOn:
  - other_algorithms/slope_trick.hpp
  isVerificationFile: true
  path: other_algorithms/test/slope_trick_stress.test.cpp
  requiredBy: []
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: other_algorithms/test/slope_trick_stress.test.cpp
layout: document
redirect_from:
- /verify/other_algorithms/test/slope_trick_stress.test.cpp
- /verify/other_algorithms/test/slope_trick_stress.test.cpp.html
title: other_algorithms/test/slope_trick_stress.test.cpp
---
