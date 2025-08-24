---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/no/950
    links:
    - https://yukicoder.me/problems/no/950
  bundledCode: "#line 1 \"number/test/discrete_logarithm_matrix.yuki950.test.cpp\"\
    \n#define PROBLEM \"https://yukicoder.me/problems/no/950\"\n#line 2 \"number/discrete_logarithm.hpp\"\
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
    \ y, f, md);\n}\n#line 3 \"utilities/pow_op.hpp\"\n\n// Calculate x^n\ntemplate\
    \ <class S, class F> S pow_op(S x, long long n, F op) {\n    assert(n > 0);\n\
    \    S ans = x;\n    --n;\n    while (n) {\n        if (n & 1) ans = op(ans, x);\n\
    \        x = op(x, x);\n        n >>= 1;\n    }\n    return ans;\n}\n#line 4 \"\
    number/test/discrete_logarithm_matrix.yuki950.test.cpp\"\n\n#include <array>\n\
    #include <iostream>\n#include <set>\nusing namespace std;\n\nusing S = array<long\
    \ long, 4>;\n\nlong long P;\nS op(S l, S r) {\n    return S{(((long long)l[0b00]\
    \ * r[0b00] % P + (long long)l[0b01] * r[0b10] % P) % P),\n             (((long\
    \ long)l[0b00] * r[0b01] % P + (long long)l[0b01] * r[0b11] % P) % P),\n     \
    \        (((long long)l[0b10] * r[0b00] % P + (long long)l[0b11] * r[0b10] % P)\
    \ % P),\n             (((long long)l[0b10] * r[0b01] % P + (long long)l[0b11]\
    \ * r[0b11] % P) % P)};\n};\n\nlong long det(S x) { return ((long long)x[0] *\
    \ x[3] % P - (long long)x[1] * x[2] % P + P) % P; };\n\nint main() {\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n    cin >> P;\n\n    S A, B;\n    for (auto &x\
    \ : A) cin >> x;\n    for (auto &x : B) cin >> x;\n\n    const long long det_A\
    \ = det(A), det_B = det(B);\n\n    if (!det_A and det_B) {\n        puts(\"-1\"\
    );\n        return 0;\n    }\n\n    const long long first_det_match = DiscreteLogarithmModNonzero<long\
    \ long>(det_A, det_B, P);\n\n    if (first_det_match < 0) {\n        puts(\"-1\"\
    );\n        return 0;\n    }\n\n    if (pow_op<S>(A, first_det_match, op) == B)\
    \ {\n        cout << first_det_match << '\\n';\n        return 0;\n    }\n\n \
    \   const long long det_period = det_A ? DiscreteLogarithmModNonzero<long long>(det_A,\
    \ 1, P) : 1;\n    if (det_period < 0) {\n        puts(\"-1\");\n        return\
    \ 0;\n    }\n\n    const S init = pow_op<S>(A, first_det_match, op);\n    const\
    \ S x = pow_op<S>(A, det_period, op);\n\n    const long long res = DiscreteLogarithm<S,\
    \ S, set<S>>(x, init, B, op, op, P * 2);\n\n    if (res < 0) {\n        puts(\"\
    -1\");\n    } else {\n        cout << first_det_match + res * det_period << '\\\
    n';\n    }\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/950\"\n#include \"number/discrete_logarithm.hpp\"\
    \n#include \"utilities/pow_op.hpp\"\n\n#include <array>\n#include <iostream>\n\
    #include <set>\nusing namespace std;\n\nusing S = array<long long, 4>;\n\nlong\
    \ long P;\nS op(S l, S r) {\n    return S{(((long long)l[0b00] * r[0b00] % P +\
    \ (long long)l[0b01] * r[0b10] % P) % P),\n             (((long long)l[0b00] *\
    \ r[0b01] % P + (long long)l[0b01] * r[0b11] % P) % P),\n             (((long\
    \ long)l[0b10] * r[0b00] % P + (long long)l[0b11] * r[0b10] % P) % P),\n     \
    \        (((long long)l[0b10] * r[0b01] % P + (long long)l[0b11] * r[0b11] % P)\
    \ % P)};\n};\n\nlong long det(S x) { return ((long long)x[0] * x[3] % P - (long\
    \ long)x[1] * x[2] % P + P) % P; };\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \    cin >> P;\n\n    S A, B;\n    for (auto &x : A) cin >> x;\n    for (auto\
    \ &x : B) cin >> x;\n\n    const long long det_A = det(A), det_B = det(B);\n\n\
    \    if (!det_A and det_B) {\n        puts(\"-1\");\n        return 0;\n    }\n\
    \n    const long long first_det_match = DiscreteLogarithmModNonzero<long long>(det_A,\
    \ det_B, P);\n\n    if (first_det_match < 0) {\n        puts(\"-1\");\n      \
    \  return 0;\n    }\n\n    if (pow_op<S>(A, first_det_match, op) == B) {\n   \
    \     cout << first_det_match << '\\n';\n        return 0;\n    }\n\n    const\
    \ long long det_period = det_A ? DiscreteLogarithmModNonzero<long long>(det_A,\
    \ 1, P) : 1;\n    if (det_period < 0) {\n        puts(\"-1\");\n        return\
    \ 0;\n    }\n\n    const S init = pow_op<S>(A, first_det_match, op);\n    const\
    \ S x = pow_op<S>(A, det_period, op);\n\n    const long long res = DiscreteLogarithm<S,\
    \ S, set<S>>(x, init, B, op, op, P * 2);\n\n    if (res < 0) {\n        puts(\"\
    -1\");\n    } else {\n        cout << first_det_match + res * det_period << '\\\
    n';\n    }\n}\n"
  dependsOn: []
  isVerificationFile: true
  path: number/test/discrete_logarithm_matrix.yuki950.test.cpp
  requiredBy: []
  timestamp: '2025-08-24 22:54:44+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: number/test/discrete_logarithm_matrix.yuki950.test.cpp
layout: document
redirect_from:
- /verify/number/test/discrete_logarithm_matrix.yuki950.test.cpp
- /verify/number/test/discrete_logarithm_matrix.yuki950.test.cpp.html
title: number/test/discrete_logarithm_matrix.yuki950.test.cpp
---
