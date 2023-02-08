---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/blackbox_algorithm.hpp
    title: "Black box linear algebra \u3092\u5229\u7528\u3057\u305F\u5404\u7A2E\u9AD8\
      \u901F\u8A08\u7B97"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/kitamasa.test.cpp
    title: formal_power_series/test/kitamasa.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/linear_recurrence.test.cpp
    title: formal_power_series/test/linear_recurrence.test.cpp
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/test/blackbox_matrix_stress.test.cpp
    title: linear_algebra_matrix/test/blackbox_matrix_stress.test.cpp
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/test/det_of_blackbox_matrix.test.cpp
    title: linear_algebra_matrix/test/det_of_blackbox_matrix.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - http://misawa.github.io/others/fast_kitamasa_method.html
    - http://sugarknri.hatenablog.com/entry/2017/11/18/233936
    - https://atcoder.jp/contests/abc198/submissions/21837815
    - https://en.wikipedia.org/wiki/Berlekamp%E2%80%93Massey_algorithm
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
    \ [1, 2])\ntemplate <typename Tfield>\nstd::pair<int, std::vector<Tfield>> find_linear_recurrence(const\
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
    \ std::make_pair(L, C_reversed);\n}\n\n// Calculate $x^N \\bmod f(x)$\n// Known\
    \ as `Kitamasa method`\n// Input: f_reversed: monic, reversed (f_reversed[0] =\
    \ 1)\n// Complexity: $O(K^2 \\log N)$ ($K$: deg. of $f$)\n// Example: (4, [1,\
    \ -1, -1]) -> [2, 3]\n//          ( x^4 = (x^2 + x + 2)(x^2 - x - 1) + 3x + 2\
    \ )\n// Reference: http://misawa.github.io/others/fast_kitamasa_method.html\n\
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
    \            ret = c;\n        }\n    }\n    return ret;\n}\n\n// Guess k-th element\
    \ of the sequence, assuming linear recurrence\n// initial_elements: 0-ORIGIN\n\
    // Verify: abc198f https://atcoder.jp/contests/abc198/submissions/21837815\ntemplate\
    \ <typename Tfield>\nTfield guess_kth_term(const std::vector<Tfield> &initial_elements,\
    \ long long k) {\n    assert(k >= 0);\n    if (k < static_cast<long long>(initial_elements.size()))\
    \ return initial_elements[k];\n    const auto f = find_linear_recurrence<Tfield>(initial_elements).second;\n\
    \    const auto g = monomial_mod_polynomial<Tfield>(k, f);\n    Tfield ret = 0;\n\
    \    for (unsigned i = 0; i < g.size(); i++) ret += g[i] * initial_elements[i];\n\
    \    return ret;\n}\n"
  code: "#pragma once\n#include <algorithm>\n#include <cassert>\n#include <utility>\n\
    #include <vector>\n\n// CUT begin\n// Berlekamp\u2013Massey algorithm\n// https://en.wikipedia.org/wiki/Berlekamp%E2%80%93Massey_algorithm\n\
    // Complexity: O(N^2)\n// input: S = sequence from field K\n// return: L     \
    \     = degree of minimal polynomial,\n//         C_reversed = monic min. polynomial\
    \ (size = L + 1, reversed order, C_reversed[0] = 1))\n// Formula: convolve(S,\
    \ C_reversed)[i] = 0 for i >= L\n// Example:\n// - [1, 2, 4, 8, 16]   -> (1, [1,\
    \ -2])\n// - [1, 1, 2, 3, 5, 8] -> (2, [1, -1, -1])\n// - [0, 0, 0, 0, 1]    ->\
    \ (5, [1, 0, 0, 0, 0, 998244352]) (mod 998244353)\n// - []                 ->\
    \ (0, [1])\n// - [0, 0, 0]          -> (0, [1])\n// - [-2]               -> (1,\
    \ [1, 2])\ntemplate <typename Tfield>\nstd::pair<int, std::vector<Tfield>> find_linear_recurrence(const\
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
    \ std::make_pair(L, C_reversed);\n}\n\n// Calculate $x^N \\bmod f(x)$\n// Known\
    \ as `Kitamasa method`\n// Input: f_reversed: monic, reversed (f_reversed[0] =\
    \ 1)\n// Complexity: $O(K^2 \\log N)$ ($K$: deg. of $f$)\n// Example: (4, [1,\
    \ -1, -1]) -> [2, 3]\n//          ( x^4 = (x^2 + x + 2)(x^2 - x - 1) + 3x + 2\
    \ )\n// Reference: http://misawa.github.io/others/fast_kitamasa_method.html\n\
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
    \            ret = c;\n        }\n    }\n    return ret;\n}\n\n// Guess k-th element\
    \ of the sequence, assuming linear recurrence\n// initial_elements: 0-ORIGIN\n\
    // Verify: abc198f https://atcoder.jp/contests/abc198/submissions/21837815\ntemplate\
    \ <typename Tfield>\nTfield guess_kth_term(const std::vector<Tfield> &initial_elements,\
    \ long long k) {\n    assert(k >= 0);\n    if (k < static_cast<long long>(initial_elements.size()))\
    \ return initial_elements[k];\n    const auto f = find_linear_recurrence<Tfield>(initial_elements).second;\n\
    \    const auto g = monomial_mod_polynomial<Tfield>(k, f);\n    Tfield ret = 0;\n\
    \    for (unsigned i = 0; i < g.size(); i++) ret += g[i] * initial_elements[i];\n\
    \    return ret;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: formal_power_series/linear_recurrence.hpp
  requiredBy:
  - linear_algebra_matrix/blackbox_algorithm.hpp
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - formal_power_series/test/kitamasa.test.cpp
  - formal_power_series/test/linear_recurrence.test.cpp
  - linear_algebra_matrix/test/blackbox_matrix_stress.test.cpp
  - linear_algebra_matrix/test/det_of_blackbox_matrix.test.cpp
documentation_of: formal_power_series/linear_recurrence.hpp
layout: document
title: "\u7DDA\u5F62\u6F38\u5316\u5F0F\u306E\u767A\u898B\u30FB\u7B2C $N$ \u9805\u63A8\
  \u5B9A"
---

線形漸化式

## 漸化式（最小多項式）の推定

Berlekamp-Massey algorithm を用いて，最初の数項から漸化式を推定する．時間計算量は入力数列長 $L$ に対して $O(L^2)$．

```cpp
vector<mint> a = {1, 1, 2, 3, 5, 8, 11};
auto [d, Crev] = find_linear_recurrence(a);  // (2, [1, -1, -1])
```

推測して得られた $C^\mathrm{rev}$ は，

$\displaystyle
    \sum_{j=0}^d C_{i - j}^\mathrm{rev} a_{j} = 0
$

が成立．

## $K$ 次線形漸化式に従う数列の第 $N$ 項の，先頭 $K$ 項の寄与への分解

時間計算量は現在の実装だと $O(K^2 \log N)$ （正しくアルゴリズムを設計すれば $O(K \log K \log N)$）．

```cpp
long long n = 12345678910111213LL;
vector<mint> b = monomial_mod_polynomial(n, Crev);
```

母関数の言葉で述べると，単項式 $x^n$ を $K$ 次多項式 $C^\mathrm{rev} (x)$ で割った剰余を求めている．先頭 $K$ 項を $[a_0, \dots, a_{K-1}]$ とすると，第$N$ 項の値は $\displaystyle \sum_{i=0}^{K-1} a_i b_i$ で与えられる．

## 線形漸化式に従う数列の先頭の $L$ 項からの，第 $N$ 項の値の推定

上記を一括で行う．時間計算量は入力数列長 $L$ に対して $O(L^2 \log N)$．

```cpp
mint kth_term = guess_kth_term(vector<mint>{1, 1, 2, 3, 5, 8}, 12345678910111213);
```
