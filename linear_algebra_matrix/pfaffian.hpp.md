---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/test/pfaffian.test.cpp
    title: linear_algebra_matrix/test/pfaffian.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://judge.yosupo.jp/submission/278787
  bundledCode: "#line 2 \"linear_algebra_matrix/pfaffian.hpp\"\n\n#include <utility>\n\
    #include <vector>\n\n// Calculate Pfaffian of Matrix\n// requirement: T is field,\
    \ M is skew-symmetric\n// Complexity: O(n^3)\n// Implementation is based on Nachia-san's\
    \ submission https://judge.yosupo.jp/submission/278787\ntemplate <class T> T Pfaffian(const\
    \ std::vector<std::vector<T>> &M) {\n    const int n = M.size();\n    if (n %\
    \ 2) return T{};\n\n    auto mat = M;\n    T res{1};\n\n    for (int s = 0; s\
    \ < n; s += 2) {\n        {\n            int t = s + 1;\n            while (t\
    \ < n and mat[s][t] == T{}) ++t;\n            if (t == n) return T{};\n\n    \
    \        if (t != s + 1) {\n                for (int i = s; i < n; ++i) std::swap(mat[s\
    \ + 1][i], mat[t][i]);\n                for (int i = s; i < n; ++i) std::swap(mat[i][s\
    \ + 1], mat[i][t]);\n                res = -res;\n            }\n        }\n\n\
    \        res *= mat[s][s + 1];\n\n        const T w = mat[s][s + 1].inv();\n\n\
    \        for (int i = s + 1; i < n; ++i) mat[s][i] *= w;\n        for (int i =\
    \ s + 1; i < n; ++i) mat[i][s] *= w;\n\n        // mat[s+2:, s+2:] += mat[:, s]\
    \ ^ mat[s + 1, :]\n        for (int i = s + 2; i < n; ++i) {\n            for\
    \ (int j = s + 2; j < n; ++j) {\n                // mat[i][j] += mat[i][s] * mat[s\
    \ + 1][j] - mat[i][s + 1] * mat[s][j];\n                mat[i][j] += mat[s + 1][i]\
    \ * mat[s][j] - mat[s][i] * mat[s + 1][j];\n            }\n        }\n    }\n\n\
    \    return res;\n}\n"
  code: "#pragma once\n\n#include <utility>\n#include <vector>\n\n// Calculate Pfaffian\
    \ of Matrix\n// requirement: T is field, M is skew-symmetric\n// Complexity: O(n^3)\n\
    // Implementation is based on Nachia-san's submission https://judge.yosupo.jp/submission/278787\n\
    template <class T> T Pfaffian(const std::vector<std::vector<T>> &M) {\n    const\
    \ int n = M.size();\n    if (n % 2) return T{};\n\n    auto mat = M;\n    T res{1};\n\
    \n    for (int s = 0; s < n; s += 2) {\n        {\n            int t = s + 1;\n\
    \            while (t < n and mat[s][t] == T{}) ++t;\n            if (t == n)\
    \ return T{};\n\n            if (t != s + 1) {\n                for (int i = s;\
    \ i < n; ++i) std::swap(mat[s + 1][i], mat[t][i]);\n                for (int i\
    \ = s; i < n; ++i) std::swap(mat[i][s + 1], mat[i][t]);\n                res =\
    \ -res;\n            }\n        }\n\n        res *= mat[s][s + 1];\n\n       \
    \ const T w = mat[s][s + 1].inv();\n\n        for (int i = s + 1; i < n; ++i)\
    \ mat[s][i] *= w;\n        for (int i = s + 1; i < n; ++i) mat[i][s] *= w;\n\n\
    \        // mat[s+2:, s+2:] += mat[:, s] ^ mat[s + 1, :]\n        for (int i =\
    \ s + 2; i < n; ++i) {\n            for (int j = s + 2; j < n; ++j) {\n      \
    \          // mat[i][j] += mat[i][s] * mat[s + 1][j] - mat[i][s + 1] * mat[s][j];\n\
    \                mat[i][j] += mat[s + 1][i] * mat[s][j] - mat[s][i] * mat[s +\
    \ 1][j];\n            }\n        }\n    }\n\n    return res;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: linear_algebra_matrix/pfaffian.hpp
  requiredBy: []
  timestamp: '2025-08-10 23:51:27+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - linear_algebra_matrix/test/pfaffian.test.cpp
documentation_of: linear_algebra_matrix/pfaffian.hpp
layout: document
title: "Pfaffian of skew-symmetric matrix \uFF08\u6B6A\u5BFE\u79F0\u884C\u5217\u306E\
  \u30D1\u30D5\u30A3\u30A2\u30F3\uFF09"
---

`T` を加減乗除が可能な型（体）として， `std::vector<std::vector<T>>` の形で与えられる $n \times n$ 歪対称正方行列の Pfaffian を $O(n^3)$ で計算する．

## 使用方法

```cpp
int N;
using mint = atcoder::modint998244353;
vector A(N, vector<mint>(N));

const mint res = Pfaffian(A);
```

## 問題例

- [Library Checker: Pfaffian of Matrix](https://judge.yosupo.jp/problem/pfaffian_of_matrix)

## 参考文献・リンク

- [Submission #278787](https://judge.yosupo.jp/submission/278787)
  - Nachia さんの実装．歪対称性を保ったまま
