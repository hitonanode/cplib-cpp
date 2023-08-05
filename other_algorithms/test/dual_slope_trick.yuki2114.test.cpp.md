---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other_algorithms/dual_slope_trick.hpp
    title: Dual slope trick
  - icon: ':heavy_check_mark:'
    path: other_algorithms/slope_trick.hpp
    title: "Slope trick \uFF08\u533A\u5206\u7DDA\u5F62\u51F8\u95A2\u6570\u306B\u95A2\
      \u3059\u308B\u7279\u5B9A\u306E\u66F4\u65B0\u3092\u9AD8\u901F\u306B\u6271\u3046\
      \u624B\u6CD5\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/no/2114
    links:
    - https://yukicoder.me/problems/no/2114
  bundledCode: "#line 1 \"other_algorithms/test/dual_slope_trick.yuki2114.test.cpp\"\
    \n#define PROBLEM \"https://yukicoder.me/problems/no/2114\"\n#line 2 \"other_algorithms/slope_trick.hpp\"\
    \n#include <algorithm>\n#include <cassert>\n#include <limits>\n#include <queue>\n\
    #include <utility>\n\n// Slope trick: fast operations for convex piecewise-linear\
    \ functions\n// Implementation idea:\n// - https://maspypy.com/slope-trick-1-%E8%A7%A3%E8%AA%AC%E7%B7%A8\n\
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
    \ = 0; t < b - a; ++t) Base::add_relu(T());\n        return *this;\n    }\n};\n\
    #line 4 \"other_algorithms/test/dual_slope_trick.yuki2114.test.cpp\"\n#include\
    \ <iostream>\n#include <map>\n#line 7 \"other_algorithms/test/dual_slope_trick.yuki2114.test.cpp\"\
    \n#include <vector>\nusing namespace std;\n\nint main() {\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n    int N, M, K;\n    cin >> N >> M >> K;\n  \
    \  map<int, vector<pair<int, int>>> mp;\n    for (int i = 0; i < N; ++i) {\n \
    \       int a;\n        cin >> a;\n        mp[a % K].emplace_back(a / K, 0);\n\
    \    }\n    for (int i = 0; i < M; ++i) {\n        int b;\n        cin >> b;\n\
    \        mp[b % K].emplace_back(b / K, 1);\n    }\n\n    long long ret = 0;\n\
    \    int nmatch = 0;\n    for (auto [key, vs] : mp) {\n        int n0 = 0, n1\
    \ = 0;\n        for (auto [x, t] : vs) (t ? n1 : n0)++;\n\n        nmatch += min(n0,\
    \ n1);\n\n        if (n0 > n1) {\n            swap(n0, n1);\n            for (auto\
    \ &[x, t] : vs) t ^= 1;\n        }\n        sort(vs.begin(), vs.end());\n\n  \
    \      dual_slope_trick<long long, 1LL << 40> dst;\n        int last_x = vs.front().first;\n\
    \        for (auto [x, tp] : vs) {\n            int dx = x - last_x;\n       \
    \     dst.add_linear_or_zero(dx, 0).add_linear_or_zero(-dx, 0);\n            if\
    \ (tp == 0) {\n                dst.shift(1);\n            } else {\n         \
    \       dst.slide_min(-1, 0);\n            }\n            last_x = x;\n      \
    \  }\n        ret += dst.get_at_zero();\n    }\n\n    if (nmatch < min(N, M))\
    \ ret = -1;\n\n    cout << ret << endl;\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/2114\"\n#include \"../dual_slope_trick.hpp\"\
    \n#include <algorithm>\n#include <iostream>\n#include <map>\n#include <utility>\n\
    #include <vector>\nusing namespace std;\n\nint main() {\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n    int N, M, K;\n    cin >> N >> M >> K;\n  \
    \  map<int, vector<pair<int, int>>> mp;\n    for (int i = 0; i < N; ++i) {\n \
    \       int a;\n        cin >> a;\n        mp[a % K].emplace_back(a / K, 0);\n\
    \    }\n    for (int i = 0; i < M; ++i) {\n        int b;\n        cin >> b;\n\
    \        mp[b % K].emplace_back(b / K, 1);\n    }\n\n    long long ret = 0;\n\
    \    int nmatch = 0;\n    for (auto [key, vs] : mp) {\n        int n0 = 0, n1\
    \ = 0;\n        for (auto [x, t] : vs) (t ? n1 : n0)++;\n\n        nmatch += min(n0,\
    \ n1);\n\n        if (n0 > n1) {\n            swap(n0, n1);\n            for (auto\
    \ &[x, t] : vs) t ^= 1;\n        }\n        sort(vs.begin(), vs.end());\n\n  \
    \      dual_slope_trick<long long, 1LL << 40> dst;\n        int last_x = vs.front().first;\n\
    \        for (auto [x, tp] : vs) {\n            int dx = x - last_x;\n       \
    \     dst.add_linear_or_zero(dx, 0).add_linear_or_zero(-dx, 0);\n            if\
    \ (tp == 0) {\n                dst.shift(1);\n            } else {\n         \
    \       dst.slide_min(-1, 0);\n            }\n            last_x = x;\n      \
    \  }\n        ret += dst.get_at_zero();\n    }\n\n    if (nmatch < min(N, M))\
    \ ret = -1;\n\n    cout << ret << endl;\n}\n"
  dependsOn:
  - other_algorithms/dual_slope_trick.hpp
  - other_algorithms/slope_trick.hpp
  isVerificationFile: true
  path: other_algorithms/test/dual_slope_trick.yuki2114.test.cpp
  requiredBy: []
  timestamp: '2023-08-05 14:49:43+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: other_algorithms/test/dual_slope_trick.yuki2114.test.cpp
layout: document
redirect_from:
- /verify/other_algorithms/test/dual_slope_trick.yuki2114.test.cpp
- /verify/other_algorithms/test/dual_slope_trick.yuki2114.test.cpp.html
title: other_algorithms/test/dual_slope_trick.yuki2114.test.cpp
---
