---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: formal_power_series/linear_recurrence.hpp
    title: formal_power_series/linear_recurrence.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/kitamasa.test.cpp
    title: formal_power_series/test/kitamasa.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - http://misawa.github.io/others/fast_kitamasa_method.html
    - http://sugarknri.hatenablog.com/entry/2017/11/18/233936
    - https://atcoder.jp/contests/abc198/submissions/21837815
  bundledCode: "#line 2 \"formal_power_series/linear_recurrence.hpp\"\n#include <algorithm>\n\
    #include <cassert>\n#include <utility>\n#include <vector>\n\n// CUT begin\n//\
    \ Berlekamp\u2013Massey algorithm\n// https://en.wikipedia.org/wiki/Berlekamp%E2%80%93Massey_algorithm\n\
    // Complexity: O(N^2)\n// input: S = sequence from field K\n// return: L     \
    \     = degree of minimal polynomial,\n//         C_reversed = monic min. polynomial\
    \ (size = L + 1, reversed order, C_reversed[0] = 1))\n// Formula: convolve(S,\
    \ C_reversed)[i] = 0 for i >= L\n// Example:\n// - [1, 2, 4, 8, 16]   -> (1, [1,\
    \ -2])\n// - [1, 1, 2, 3, 5, 8] -> (2, [1, -1, -1])\n// - [0, 0, 0, 0, 1]    ->\
    \ (5, [1, 0, 0, 0, 0, 998244352]) (mod 998244353)\n// - []                 ->\
    \ (0, [1])\n// - [0, 0, 0]          -> (0, [1])\n// - [-2]               -> (1,\
    \ [1, 2])\ntemplate <typename Tfield> std::pair<int, std::vector<Tfield>> linear_recurrence(const\
    \ std::vector<Tfield> &S) {\n    int N = S.size();\n    using poly = std::vector<Tfield>;\n\
    \    poly C_reversed{1}, B{1};\n    int L = 0, m = 1;\n    Tfield b = 1;\n\n \
    \   // adjust: C(x) <- C(x) - (d / b) x^m B(x)\n    auto adjust = [](poly C, const\
    \ poly &B, Tfield d, Tfield b, int m) -> poly {\n        C.resize(std::max(C.size(),\
    \ B.size() + m));\n        Tfield a = d / b;\n        for (unsigned i = 0; i <\
    \ B.size(); i++) C[i + m] -= a * B[i];\n        return C;\n    };\n\n    for (int\
    \ n = 0; n < N; n++) {\n        Tfield d = S[n];\n        for (int i = 1; i <=\
    \ L; i++) d += C_reversed[i] * S[n - i];\n\n        if (d == 0)\n            m++;\n\
    \        else if (2 * L <= n) {\n            poly T = C_reversed;\n          \
    \  C_reversed = adjust(C_reversed, B, d, b, m);\n            L = n + 1 - L;\n\
    \            B = T;\n            b = d;\n            m = 1;\n        } else\n\
    \            C_reversed = adjust(C_reversed, B, d, b, m++);\n    }\n    return\
    \ std::make_pair(L, C_reversed);\n}\n#line 5 \"formal_power_series/monomial_mod_polynomial.hpp\"\
    \n\n// CUT begin\n// Calculate $x^N \\bmod f(x)$\n// Known as `Kitamasa method`\n\
    // Input: f_reversed: monic, reversed (f_reversed[0] = 1)\n// Complexity: $O(K^2\
    \ \\log N)$ ($K$: deg. of $f$)\n// Example: (4, [1, -1, -1]) -> [2, 3]\n//   \
    \       ( x^4 = (x^2 + x + 2)(x^2 - x - 1) + 3x + 2 )\n// Reference: http://misawa.github.io/others/fast_kitamasa_method.html\n\
    //            http://sugarknri.hatenablog.com/entry/2017/11/18/233936\ntemplate\
    \ <typename Tfield>\nstd::vector<Tfield> monomial_mod_polynomial(long long N,\
    \ const std::vector<Tfield> &f_reversed) {\n    assert(!f_reversed.empty() and\
    \ f_reversed[0] == 1);\n    int K = f_reversed.size() - 1;\n    if (!K) return\
    \ {};\n    int D = 64 - __builtin_clzll(N);\n    std::vector<Tfield> ret(K, 0);\n\
    \    ret[0] = 1;\n    auto self_conv = [](std::vector<Tfield> x) -> std::vector<Tfield>\
    \ {\n        int d = x.size();\n        std::vector<Tfield> ret(d * 2 - 1);\n\
    \        for (int i = 0; i < d; i++) {\n            ret[i * 2] += x[i] * x[i];\n\
    \            for (int j = 0; j < i; j++) ret[i + j] += x[i] * x[j] * 2;\n    \
    \    }\n        return ret;\n    };\n    for (int d = D; d--;) {\n        ret\
    \ = self_conv(ret);\n        for (int i = 2 * K - 2; i >= K; i--) {\n        \
    \    for (int j = 1; j <= K; j++) ret[i - j] -= ret[i] * f_reversed[j];\n    \
    \    }\n        ret.resize(K);\n        if ((N >> d) & 1) {\n            std::vector<Tfield>\
    \ c(K);\n            c[0] = -ret[K - 1] * f_reversed[K];\n            for (int\
    \ i = 1; i < K; i++) { c[i] = ret[i - 1] - ret[K - 1] * f_reversed[K - i]; }\n\
    \            ret = c;\n        }\n    }\n    return ret;\n}\n\n// Find k-th element\
    \ of the sequence, assuming linear recurrence\n// initial_elements: 0-ORIGIN\n\
    // Verify: abc198f https://atcoder.jp/contests/abc198/submissions/21837815\ntemplate\
    \ <typename Tfield> Tfield find_kth_element(const std::vector<Tfield> &initial_elements,\
    \ long long k) {\n    assert(k >= 0);\n    if (k < static_cast<long long>(initial_elements.size()))\
    \ return initial_elements[k];\n    const auto f = linear_recurrence<Tfield>(initial_elements).second;\n\
    \    const auto g = monomial_mod_polynomial<Tfield>(k, f);\n    Tfield ret = 0;\n\
    \    for (unsigned i = 0; i < g.size(); i++) ret += g[i] * initial_elements[i];\n\
    \    return ret;\n}\n"
  code: "#pragma once\n#include \"linear_recurrence.hpp\"\n#include <cassert>\n#include\
    \ <vector>\n\n// CUT begin\n// Calculate $x^N \\bmod f(x)$\n// Known as `Kitamasa\
    \ method`\n// Input: f_reversed: monic, reversed (f_reversed[0] = 1)\n// Complexity:\
    \ $O(K^2 \\log N)$ ($K$: deg. of $f$)\n// Example: (4, [1, -1, -1]) -> [2, 3]\n\
    //          ( x^4 = (x^2 + x + 2)(x^2 - x - 1) + 3x + 2 )\n// Reference: http://misawa.github.io/others/fast_kitamasa_method.html\n\
    //            http://sugarknri.hatenablog.com/entry/2017/11/18/233936\ntemplate\
    \ <typename Tfield>\nstd::vector<Tfield> monomial_mod_polynomial(long long N,\
    \ const std::vector<Tfield> &f_reversed) {\n    assert(!f_reversed.empty() and\
    \ f_reversed[0] == 1);\n    int K = f_reversed.size() - 1;\n    if (!K) return\
    \ {};\n    int D = 64 - __builtin_clzll(N);\n    std::vector<Tfield> ret(K, 0);\n\
    \    ret[0] = 1;\n    auto self_conv = [](std::vector<Tfield> x) -> std::vector<Tfield>\
    \ {\n        int d = x.size();\n        std::vector<Tfield> ret(d * 2 - 1);\n\
    \        for (int i = 0; i < d; i++) {\n            ret[i * 2] += x[i] * x[i];\n\
    \            for (int j = 0; j < i; j++) ret[i + j] += x[i] * x[j] * 2;\n    \
    \    }\n        return ret;\n    };\n    for (int d = D; d--;) {\n        ret\
    \ = self_conv(ret);\n        for (int i = 2 * K - 2; i >= K; i--) {\n        \
    \    for (int j = 1; j <= K; j++) ret[i - j] -= ret[i] * f_reversed[j];\n    \
    \    }\n        ret.resize(K);\n        if ((N >> d) & 1) {\n            std::vector<Tfield>\
    \ c(K);\n            c[0] = -ret[K - 1] * f_reversed[K];\n            for (int\
    \ i = 1; i < K; i++) { c[i] = ret[i - 1] - ret[K - 1] * f_reversed[K - i]; }\n\
    \            ret = c;\n        }\n    }\n    return ret;\n}\n\n// Find k-th element\
    \ of the sequence, assuming linear recurrence\n// initial_elements: 0-ORIGIN\n\
    // Verify: abc198f https://atcoder.jp/contests/abc198/submissions/21837815\ntemplate\
    \ <typename Tfield> Tfield find_kth_element(const std::vector<Tfield> &initial_elements,\
    \ long long k) {\n    assert(k >= 0);\n    if (k < static_cast<long long>(initial_elements.size()))\
    \ return initial_elements[k];\n    const auto f = linear_recurrence<Tfield>(initial_elements).second;\n\
    \    const auto g = monomial_mod_polynomial<Tfield>(k, f);\n    Tfield ret = 0;\n\
    \    for (unsigned i = 0; i < g.size(); i++) ret += g[i] * initial_elements[i];\n\
    \    return ret;\n}\n"
  dependsOn:
  - formal_power_series/linear_recurrence.hpp
  isVerificationFile: false
  path: formal_power_series/monomial_mod_polynomial.hpp
  requiredBy: []
  timestamp: '2021-04-17 22:52:06+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - formal_power_series/test/kitamasa.test.cpp
documentation_of: formal_power_series/monomial_mod_polynomial.hpp
layout: document
redirect_from:
- /library/formal_power_series/monomial_mod_polynomial.hpp
- /library/formal_power_series/monomial_mod_polynomial.hpp.html
title: formal_power_series/monomial_mod_polynomial.hpp
---
