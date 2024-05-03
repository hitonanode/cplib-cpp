---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/test/f2_intersection.test.cpp
    title: linear_algebra_matrix/test/f2_intersection.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"linear_algebra_matrix/f2_linear_space.hpp\"\n#include <algorithm>\n\
    #include <utility>\n#include <vector>\n\ntemplate <class Int> struct f2_vector_space\
    \ {\n    std::vector<Int> basis;\n\n    f2_vector_space() = default;\n\n    Int\
    \ add(Int x) {\n        for (const Int &b : basis) x = std::min(x, x ^ b);\n\n\
    \        if (x) {\n            basis.push_back(x);\n            return x;\n  \
    \      } else {\n            return Int(0);\n        }\n    }\n};\n\nstd::vector<int>\
    \ f2_intersection(const std::vector<int> &A, const std::vector<int> &B) {\n  \
    \  f2_vector_space<long long> tmp;\n    for (int a : A) tmp.add(((long long)a\
    \ << 32) + a);\n\n    std::vector<int> ret;\n\n    for (int b : B) {\n       \
    \ long long v = (long long)b << 32;\n\n        auto u = tmp.add(v);\n        if\
    \ (u < (1LL << 32)) ret.push_back(u);\n    }\n\n    return ret;\n}\n"
  code: "#pragma once\n#include <algorithm>\n#include <utility>\n#include <vector>\n\
    \ntemplate <class Int> struct f2_vector_space {\n    std::vector<Int> basis;\n\
    \n    f2_vector_space() = default;\n\n    Int add(Int x) {\n        for (const\
    \ Int &b : basis) x = std::min(x, x ^ b);\n\n        if (x) {\n            basis.push_back(x);\n\
    \            return x;\n        } else {\n            return Int(0);\n       \
    \ }\n    }\n};\n\nstd::vector<int> f2_intersection(const std::vector<int> &A,\
    \ const std::vector<int> &B) {\n    f2_vector_space<long long> tmp;\n    for (int\
    \ a : A) tmp.add(((long long)a << 32) + a);\n\n    std::vector<int> ret;\n\n \
    \   for (int b : B) {\n        long long v = (long long)b << 32;\n\n        auto\
    \ u = tmp.add(v);\n        if (u < (1LL << 32)) ret.push_back(u);\n    }\n\n \
    \   return ret;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: linear_algebra_matrix/f2_linear_space.hpp
  requiredBy: []
  timestamp: '2024-05-03 13:54:12+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - linear_algebra_matrix/test/f2_intersection.test.cpp
documentation_of: linear_algebra_matrix/f2_linear_space.hpp
layout: document
title: "$\\mathbb{F}_{2}$ linear space ($\\mathbb{F}_{2}$ \u7DDA\u5F62\u7A7A\u9593\
  )"
---

$\mathbb{F}_{2}$ 線形空間に関する各種演算．

## 使用方法

`A` の元で張られる線形空間と `B` の元で張られる線形空間の共通部分の基底を一つ求める関数方法．

```cpp
int n, m;
vector<int> A(n), B(m);

vector<int> C = f2_intersection(A, B);
```

## 問題例

- [Library Checker: Intersection of F_2 vector spaces](https://judge.yosupo.jp/problem/intersection_of_f2_vector_spaces)
