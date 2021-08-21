---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: number/test/binary_gcd.stress.test.cpp
    title: number/test/binary_gcd.stress.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"number/binary_gcd.hpp\"\n\n// CUT begin\ntemplate <typename\
    \ Int> Int binary_gcd(Int x_, Int y_) {\n    unsigned long long x = x_ < 0 ? -x_\
    \ : x_, y = y_ < 0 ? -y_ : y_;\n    if (!x or !y) return x + y;\n    int n = __builtin_ctzll(x),\
    \ m = __builtin_ctzll(y);\n    x >>= n, y >>= m;\n    while (x != y) {\n     \
    \   if (x > y) {\n            x = (x - y) >> __builtin_ctzll(x - y);\n       \
    \ } else {\n            y = (y - x) >> __builtin_ctzll(y - x);\n        }\n  \
    \  }\n    return x << (n > m ? m : n);\n}\n"
  code: "#pragma once\n\n// CUT begin\ntemplate <typename Int> Int binary_gcd(Int\
    \ x_, Int y_) {\n    unsigned long long x = x_ < 0 ? -x_ : x_, y = y_ < 0 ? -y_\
    \ : y_;\n    if (!x or !y) return x + y;\n    int n = __builtin_ctzll(x), m =\
    \ __builtin_ctzll(y);\n    x >>= n, y >>= m;\n    while (x != y) {\n        if\
    \ (x > y) {\n            x = (x - y) >> __builtin_ctzll(x - y);\n        } else\
    \ {\n            y = (y - x) >> __builtin_ctzll(y - x);\n        }\n    }\n  \
    \  return x << (n > m ? m : n);\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: number/binary_gcd.hpp
  requiredBy: []
  timestamp: '2021-08-21 15:46:09+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - number/test/binary_gcd.stress.test.cpp
documentation_of: number/binary_gcd.hpp
layout: document
title: Binary GCD
---

二つの整数の最大公約数を求める高速なアルゴリズムとして知られる Binary GCD の実装．Euclid の互除法によるアルゴリズムと異なり，2 以外の除算が登場しない．

## 使用例

``` cpp
long long a, b;
long long g = binary_gcd(a, b);
```

## リンク

- [Binary GCD algorithm - Wikipedia](https://en.wikipedia.org/wiki/Binary_GCD_algorithm)
