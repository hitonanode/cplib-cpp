---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: number/discrete_logarithm.hpp
    title: "Discrete logarithm / Baby-step giant-step \uFF08\u96E2\u6563\u5BFE\u6570\
      \u554F\u984C\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/no/261
    links:
    - https://yukicoder.me/problems/no/261
  bundledCode: "#line 1 \"number/test/discrete_logarithm_symmetric_group.yuki261.test.cpp\"\
    \n#define PROBLEM \"https://yukicoder.me/problems/no/261\"\n#line 2 \"number/discrete_logarithm.hpp\"\
    \n#include <cassert>\n#include <cmath>\n#include <functional>\n#include <unordered_set>\n\
    \n// Solve min_n f^n s = t (0 <= n <= max_search)\n// baby = f, giant = f^giant_stride\n\
    // If solution is not found, return -1.\n// https://maspypy.com/%e3%83%a2%e3%83%8e%e3%82%a4%e3%83%89%e4%bd%9c%e7%94%a8%e3%81%ab%e9%96%a2%e3%81%99%e3%82%8b%e9%9b%a2%e6%95%a3%e5%af%be%e6%95%b0%e5%95%8f%e9%a1%8c\n\
    template <class S, class F, class Container>\nlong long\nDiscreteLogarithm(const\
    \ F &baby, const F &giant, const S &s, const S &t,\n                  const std::function<S(F,\
    \ S)> &mapping, long long max_search, int giant_stride) {\n    if (s == t) return\
    \ 0;\n    if (max_search <= 0) return -1;\n\n    Container ys;\n    // ys.reserve(giant_stride);\
    \ // if unordered_set\n    {\n        auto yt = t;\n        for (int i = 0; i\
    \ < giant_stride; ++i) {\n            ys.emplace(yt);\n            yt = mapping(baby,\
    \ yt);\n        }\n    }\n\n    int num_fails = 0;\n    S cur = s;\n\n    for\
    \ (long long k = 1;; ++k) {\n        if (const S nxt = mapping(giant, cur); ys.count(nxt))\
    \ {\n            for (int i = 1; i <= giant_stride; ++i) {\n                cur\
    \ = mapping(baby, cur);\n                if (cur == t) {\n                   \
    \ long long ret = (k - 1) * giant_stride + i;\n                    return (ret\
    \ <= max_search) ? ret : -1;\n                }\n            }\n            ++num_fails;\n\
    \        } else {\n            cur = nxt;\n        }\n\n        if (num_fails\
    \ >= 2 or k * giant_stride > max_search) return -1;\n    }\n}\n\n// Solve min_n\
    \ f^n s = t (0 <= n <= max_search) f \\in F, s \\in S, t \\in S\n// mapping: (F,\
    \ S) -> S\n// composition: (F, F) -> F\ntemplate <class S, class F, class Container>\n\
    long long\nDiscreteLogarithm(const F &f, const S &s, const S &t, const std::function<S(F,\
    \ S)> &mapping,\n                  const std::function<F(F, F)> &composition,\
    \ long long max_search) {\n    const int giant_stride = ceil(sqrtl(max_search));\n\
    \    F giant = f, tmp = f;\n    for (int n = giant_stride - 1; n; n >>= 1) {\n\
    \        if (n & 1) giant = composition(giant, tmp);\n        tmp = composition(tmp,\
    \ tmp);\n    }\n    return DiscreteLogarithm<S, F, Container>(f, giant, s, t,\
    \ mapping, max_search, giant_stride);\n}\n\n// Solve min_n x^n = y (1 <= n <=\
    \ max_search)\ntemplate <class S, class Container>\nlong long DiscreteLogarithmNonzero(const\
    \ S &x, const S &y, const std::function<S(S, S)> &op,\n                      \
    \             long long max_search) {\n    long long res = DiscreteLogarithm<S,\
    \ S, Container>(x, x, y, op, op, max_search);\n    if (res < 0 or res >= max_search)\
    \ return -1;\n    return res + 1;\n}\n\n// Solve min_n x^n = y mod md (n >= 0)\
    \ or return -1 if infeasible\ntemplate <class Int> Int DiscreteLogarithmMod(Int\
    \ x, Int y, Int md) {\n    x %= md, y %= md;\n    if (x < 0) x += md;\n    if\
    \ (y < 0) y += md;\n    // You may change __int128 to long long, but be careful\
    \ about overflow.\n    auto f = [&](Int a, Int b) -> Int { return __int128(a)\
    \ * b % md; };\n    return DiscreteLogarithm<Int, Int, std::unordered_set<Int>>(x,\
    \ Int{1} % md, y, f, f, md);\n}\n\n// Solve min_n x^n = y mod md (n >= 1) or return\
    \ -1 if infeasible\ntemplate <class Int> Int DiscreteLogarithmModNonzero(Int x,\
    \ Int y, Int md) {\n    x %= md, y %= md;\n    if (x < 0) x += md;\n    if (y\
    \ < 0) y += md;\n    // You may change __int128 to long long, but be careful about\
    \ overflow.\n    auto f = [&](Int a, Int b) -> Int { return __int128(a) * b %\
    \ md; };\n    return DiscreteLogarithmNonzero<Int, std::unordered_set<Int>>(x,\
    \ y, f, md);\n}\n#line 3 \"number/test/discrete_logarithm_symmetric_group.yuki261.test.cpp\"\
    \n\n#include <iostream>\n#include <numeric>\n#include <set>\n#include <utility>\n\
    using namespace std;\n\nconstexpr int D = 100;\nusing S = std::array<int, D>;\n\
    \nS e() {\n    S res;\n    iota(res.begin(), res.end(), 0);\n    return res;\n\
    }\n\nS op(S l, S r) {\n    S res = e();\n    for (int i = 0; i < D; ++i) res[i]\
    \ = l[r[i]];\n    return res;\n}\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \n    int N, K;\n    cin >> N >> K;\n\n    S f = e();\n    while (K--) {\n   \
    \     int x, y;\n        cin >> x >> y;\n        --x, --y;\n        swap(f[x],\
    \ f[y]);\n    }\n\n    int Q;\n    cin >> Q;\n    while (Q--) {\n        S g =\
    \ e();\n        for (int i = 0; i < N; ++i) cin >> g.at(i), g.at(i)--;\n     \
    \   cout << DiscreteLogarithmNonzero<S, set<S>>(f, g, op, 1LL << 30) << '\\n';\n\
    \    }\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/261\"\n#include \"../discrete_logarithm.hpp\"\
    \n\n#include <iostream>\n#include <numeric>\n#include <set>\n#include <utility>\n\
    using namespace std;\n\nconstexpr int D = 100;\nusing S = std::array<int, D>;\n\
    \nS e() {\n    S res;\n    iota(res.begin(), res.end(), 0);\n    return res;\n\
    }\n\nS op(S l, S r) {\n    S res = e();\n    for (int i = 0; i < D; ++i) res[i]\
    \ = l[r[i]];\n    return res;\n}\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \n    int N, K;\n    cin >> N >> K;\n\n    S f = e();\n    while (K--) {\n   \
    \     int x, y;\n        cin >> x >> y;\n        --x, --y;\n        swap(f[x],\
    \ f[y]);\n    }\n\n    int Q;\n    cin >> Q;\n    while (Q--) {\n        S g =\
    \ e();\n        for (int i = 0; i < N; ++i) cin >> g.at(i), g.at(i)--;\n     \
    \   cout << DiscreteLogarithmNonzero<S, set<S>>(f, g, op, 1LL << 30) << '\\n';\n\
    \    }\n}\n"
  dependsOn:
  - number/discrete_logarithm.hpp
  isVerificationFile: true
  path: number/test/discrete_logarithm_symmetric_group.yuki261.test.cpp
  requiredBy: []
  timestamp: '2025-08-24 23:11:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: number/test/discrete_logarithm_symmetric_group.yuki261.test.cpp
layout: document
redirect_from:
- /verify/number/test/discrete_logarithm_symmetric_group.yuki261.test.cpp
- /verify/number/test/discrete_logarithm_symmetric_group.yuki261.test.cpp.html
title: number/test/discrete_logarithm_symmetric_group.yuki261.test.cpp
---
