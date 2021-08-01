---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: utilities/test/pow.test.cpp
    title: utilities/test/pow.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"utilities/pow_sum.hpp\"\n#include <algorithm>\n#include\
    \ <utility>\n\n// CUT begin\n// {x^n, x^0 + ... + x^(n - 1)} for n >= 1\n// Verify:\
    \ ABC212H\ntemplate <typename T, typename Int> std::pair<T, T> pow_sum(T x, Int\
    \ n) {\n    T sum = 1, p = x; // ans = x^0 + ... + x^(len - 1), p = x^len\n  \
    \  for (int d = std::__lg(n) - 1; d >= 0; d--) {\n        sum = sum * (p + 1);\n\
    \        p *= p;\n        if ((n >> d) & 1) {\n            sum += p;\n       \
    \     p *= x;\n        }\n    }\n    return {p, sum};\n}\n"
  code: "#pragma once\n#include <algorithm>\n#include <utility>\n\n// CUT begin\n\
    // {x^n, x^0 + ... + x^(n - 1)} for n >= 1\n// Verify: ABC212H\ntemplate <typename\
    \ T, typename Int> std::pair<T, T> pow_sum(T x, Int n) {\n    T sum = 1, p = x;\
    \ // ans = x^0 + ... + x^(len - 1), p = x^len\n    for (int d = std::__lg(n) -\
    \ 1; d >= 0; d--) {\n        sum = sum * (p + 1);\n        p *= p;\n        if\
    \ ((n >> d) & 1) {\n            sum += p;\n            p *= x;\n        }\n  \
    \  }\n    return {p, sum};\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/pow_sum.hpp
  requiredBy: []
  timestamp: '2021-08-01 20:22:45+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - utilities/test/pow.test.cpp
documentation_of: utilities/pow_sum.hpp
layout: document
title: "power sum \uFF08\u7D2F\u4E57\u548C\uFF09"
---

繰り返し二乗法で $(x^n, \sum_{i=0}^{n-1} x^i)$ の組を計算．計算量は $O(\log n)$．

## 問題例

- [AtCoder Beginner Contest 212 H - Nim Counting](https://atcoder.jp/contests/abc212/tasks/abc212_h)
