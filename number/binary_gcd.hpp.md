---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: number/test/binary_gcd.stress.test.cpp
    title: number/test/binary_gcd.stress.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 2 \"number/binary_gcd.hpp\"\n#include <type_traits>\n\n// CUT\
    \ begin\ntemplate <typename Int> Int binary_gcd(Int x_, Int y_) {\n    using Uint\
    \ = std::make_unsigned_t<Int>;\n    auto magnitude = [](Int v) -> Uint {\n   \
    \     Uint u = static_cast<Uint>(v);\n        return v < 0 ? Uint(0) - u : u;\n\
    \    };\n    unsigned long long x = magnitude(x_), y = magnitude(y_);\n    if\
    \ (!x or !y) return x + y;\n    int n = __builtin_ctzll(x), m = __builtin_ctzll(y);\n\
    \    x >>= n, y >>= m;\n    while (x != y) {\n        if (x > y) {\n         \
    \   x = (x - y) >> __builtin_ctzll(x - y);\n        } else {\n            y =\
    \ (y - x) >> __builtin_ctzll(y - x);\n        }\n    }\n    return x << (n > m\
    \ ? m : n);\n}\n"
  code: "#pragma once\n#include <type_traits>\n\n// CUT begin\ntemplate <typename\
    \ Int> Int binary_gcd(Int x_, Int y_) {\n    using Uint = std::make_unsigned_t<Int>;\n\
    \    auto magnitude = [](Int v) -> Uint {\n        Uint u = static_cast<Uint>(v);\n\
    \        return v < 0 ? Uint(0) - u : u;\n    };\n    unsigned long long x = magnitude(x_),\
    \ y = magnitude(y_);\n    if (!x or !y) return x + y;\n    int n = __builtin_ctzll(x),\
    \ m = __builtin_ctzll(y);\n    x >>= n, y >>= m;\n    while (x != y) {\n     \
    \   if (x > y) {\n            x = (x - y) >> __builtin_ctzll(x - y);\n       \
    \ } else {\n            y = (y - x) >> __builtin_ctzll(y - x);\n        }\n  \
    \  }\n    return x << (n > m ? m : n);\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: number/binary_gcd.hpp
  requiredBy: []
  timestamp: '2026-09-05 21:26:13+09:00'
  verificationStatus: LIBRARY_ALL_WA
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
