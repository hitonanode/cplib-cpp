---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/det_of_sparse_matrix.hpp
    title: linear_algebra_matrix/det_of_sparse_matrix.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/test/det_of_sparse_matrix.test.cpp
    title: linear_algebra_matrix/test/det_of_sparse_matrix.test.cpp
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/test/linear_recurrence.test.cpp
    title: linear_algebra_matrix/test/linear_recurrence.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://en.wikipedia.org/wiki/Berlekamp%E2%80%93Massey_algorithm>
  bundledCode: "#line 2 \"linear_algebra_matrix/linear_recurrence.hpp\"\n#include\
    \ <algorithm>\n#include <cassert>\n#include <utility>\n#include <vector>\n\n//\
    \ CUT begin\n// Berlekamp\u2013Massey algorithm\n// <https://en.wikipedia.org/wiki/Berlekamp%E2%80%93Massey_algorithm>\n\
    // Complexity: O(N^2)\n// input: S = sequence from field K\n// return: L     \
    \     = degree of minimal polynomial,\n//         C_reversed = monic min. polynomial\
    \ (size = L + 1, reversed order, C_reversed[0] = 1))\n// Formula: convolve(S,\
    \ C_reversed)[i] = 0 for i >= L\n// Example:\n// - [1, 2, 4, 8, 16]   -> (1, [1,\
    \ -2])\n// - [1, 1, 2, 3, 5, 8] -> (2, [1, -1, -1])\n// - [0, 0, 0, 0, 1]    ->\
    \ (5, [1, 0, 0, 0, 0, 998244352]) (mod 998244353)\n// - []                 ->\
    \ (0, [1])\n// - [0, 0, 0]          -> (0, [1])\n// - [-2]               -> (1,\
    \ [1, 2])\ntemplate <typename Tfield>\nstd::pair<int, std::vector<Tfield>> linear_recurrence(const\
    \ std::vector<Tfield> &S)\n{\n    int N = S.size();\n    using poly = std::vector<Tfield>;\n\
    \    poly C_reversed{1}, B{1};\n    int L = 0, m = 1;\n    Tfield b = 1;\n\n \
    \   // adjust: C(x) <- C(x) - (d / b) x^m B(x)\n    auto adjust = [](poly C, const\
    \ poly &B, Tfield d, Tfield b, int m) -> poly {\n        C.resize(std::max(C.size(),\
    \ B.size() + m));\n        Tfield a = d / b;\n        for (unsigned i = 0; i <\
    \ B.size(); i++) C[i + m] -= a * B[i];\n        return C;\n    };\n\n    for (int\
    \ n = 0; n < N; n++) {\n        Tfield d = S[n];\n        for (int i = 1; i <=\
    \ L; i++) d += C_reversed[i] * S[n - i];\n\n        if (d == 0) m++;\n       \
    \ else if (2 * L <= n) {\n            poly T = C_reversed;\n            C_reversed\
    \ = adjust(C_reversed, B, d, b, m);\n            L = n + 1 - L;\n            B\
    \ = T;\n            b = d;\n            m = 1;\n        }\n        else C_reversed\
    \ = adjust(C_reversed, B, d, b, m++);\n    }\n    return std::make_pair(L, C_reversed);\n\
    }\n"
  code: "#pragma once\n#include <algorithm>\n#include <cassert>\n#include <utility>\n\
    #include <vector>\n\n// CUT begin\n// Berlekamp\u2013Massey algorithm\n// <https://en.wikipedia.org/wiki/Berlekamp%E2%80%93Massey_algorithm>\n\
    // Complexity: O(N^2)\n// input: S = sequence from field K\n// return: L     \
    \     = degree of minimal polynomial,\n//         C_reversed = monic min. polynomial\
    \ (size = L + 1, reversed order, C_reversed[0] = 1))\n// Formula: convolve(S,\
    \ C_reversed)[i] = 0 for i >= L\n// Example:\n// - [1, 2, 4, 8, 16]   -> (1, [1,\
    \ -2])\n// - [1, 1, 2, 3, 5, 8] -> (2, [1, -1, -1])\n// - [0, 0, 0, 0, 1]    ->\
    \ (5, [1, 0, 0, 0, 0, 998244352]) (mod 998244353)\n// - []                 ->\
    \ (0, [1])\n// - [0, 0, 0]          -> (0, [1])\n// - [-2]               -> (1,\
    \ [1, 2])\ntemplate <typename Tfield>\nstd::pair<int, std::vector<Tfield>> linear_recurrence(const\
    \ std::vector<Tfield> &S)\n{\n    int N = S.size();\n    using poly = std::vector<Tfield>;\n\
    \    poly C_reversed{1}, B{1};\n    int L = 0, m = 1;\n    Tfield b = 1;\n\n \
    \   // adjust: C(x) <- C(x) - (d / b) x^m B(x)\n    auto adjust = [](poly C, const\
    \ poly &B, Tfield d, Tfield b, int m) -> poly {\n        C.resize(std::max(C.size(),\
    \ B.size() + m));\n        Tfield a = d / b;\n        for (unsigned i = 0; i <\
    \ B.size(); i++) C[i + m] -= a * B[i];\n        return C;\n    };\n\n    for (int\
    \ n = 0; n < N; n++) {\n        Tfield d = S[n];\n        for (int i = 1; i <=\
    \ L; i++) d += C_reversed[i] * S[n - i];\n\n        if (d == 0) m++;\n       \
    \ else if (2 * L <= n) {\n            poly T = C_reversed;\n            C_reversed\
    \ = adjust(C_reversed, B, d, b, m);\n            L = n + 1 - L;\n            B\
    \ = T;\n            b = d;\n            m = 1;\n        }\n        else C_reversed\
    \ = adjust(C_reversed, B, d, b, m++);\n    }\n    return std::make_pair(L, C_reversed);\n\
    }\n"
  dependsOn: []
  isVerificationFile: false
  path: linear_algebra_matrix/linear_recurrence.hpp
  requiredBy:
  - linear_algebra_matrix/det_of_sparse_matrix.hpp
  timestamp: '2020-06-06 01:37:38+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - linear_algebra_matrix/test/linear_recurrence.test.cpp
  - linear_algebra_matrix/test/det_of_sparse_matrix.test.cpp
documentation_of: linear_algebra_matrix/linear_recurrence.hpp
layout: document
redirect_from:
- /library/linear_algebra_matrix/linear_recurrence.hpp
- /library/linear_algebra_matrix/linear_recurrence.hpp.html
title: linear_algebra_matrix/linear_recurrence.hpp
---
