---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: number/square_sums.hpp
    title: "Sum of two squares \uFF08\u4E8C\u3064\u306E\u5E73\u65B9\u6570\u306E\u548C\
      \uFF09"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: number/test/sqrt_mod.test.cpp
    title: number/test/sqrt_mod.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"number/sqrt_mod.hpp\"\n#include <algorithm>\n#include <type_traits>\n\
    \n// Solve x^2 == a (MOD p) for prime p\n// If no solution exists, return -1\n\
    template <class Int> Int sqrt_mod(Int a, Int p) {\n    using Long =\n        std::conditional_t<std::is_same_v<Int,\
    \ int>, long long,\n                           std::conditional_t<std::is_same_v<Int,\
    \ long long>, __int128, void>>;\n\n    auto pow = [&](Int x, long long n) {\n\
    \        Int ans = 1, tmp = x;\n        while (n) {\n            if (n & 1) ans\
    \ = (Long)ans * tmp % p;\n            tmp = (Long)tmp * tmp % p, n /= 2;\n   \
    \     }\n        return ans;\n    };\n    if (a == 0) return 0;\n\n    a = (a\
    \ % p + p) % p;\n    if (p == 2) return a;\n    if (pow(a, (p - 1) / 2) != 1)\
    \ return -1;\n\n    int b = 1;\n    while (pow(b, (p - 1) / 2) == 1) ++b;\n\n\
    \    int e = 0;\n    Int m = p - 1;\n    while (m % 2 == 0) m /= 2, ++e;\n\n \
    \   Int x = pow(a, (m - 1) / 2), y = (Long)x * x % p * a % p;\n    x = (Long)x\
    \ * a % p;\n    Int z = pow(b, m);\n    while (y != 1) {\n        int j = 0;\n\
    \        Int t = y;\n        while (t != 1) t = (Long)t * t % p, ++j;\n      \
    \  z = pow(z, 1LL << (e - j - 1));\n        x = (Long)x * z % p;\n        z =\
    \ (Long)z * z % p;\n        y = (Long)y * z % p;\n        e = j;\n    }\n    return\
    \ std::min(x, p - x);\n}\n"
  code: "#pragma once\n#include <algorithm>\n#include <type_traits>\n\n// Solve x^2\
    \ == a (MOD p) for prime p\n// If no solution exists, return -1\ntemplate <class\
    \ Int> Int sqrt_mod(Int a, Int p) {\n    using Long =\n        std::conditional_t<std::is_same_v<Int,\
    \ int>, long long,\n                           std::conditional_t<std::is_same_v<Int,\
    \ long long>, __int128, void>>;\n\n    auto pow = [&](Int x, long long n) {\n\
    \        Int ans = 1, tmp = x;\n        while (n) {\n            if (n & 1) ans\
    \ = (Long)ans * tmp % p;\n            tmp = (Long)tmp * tmp % p, n /= 2;\n   \
    \     }\n        return ans;\n    };\n    if (a == 0) return 0;\n\n    a = (a\
    \ % p + p) % p;\n    if (p == 2) return a;\n    if (pow(a, (p - 1) / 2) != 1)\
    \ return -1;\n\n    int b = 1;\n    while (pow(b, (p - 1) / 2) == 1) ++b;\n\n\
    \    int e = 0;\n    Int m = p - 1;\n    while (m % 2 == 0) m /= 2, ++e;\n\n \
    \   Int x = pow(a, (m - 1) / 2), y = (Long)x * x % p * a % p;\n    x = (Long)x\
    \ * a % p;\n    Int z = pow(b, m);\n    while (y != 1) {\n        int j = 0;\n\
    \        Int t = y;\n        while (t != 1) t = (Long)t * t % p, ++j;\n      \
    \  z = pow(z, 1LL << (e - j - 1));\n        x = (Long)x * z % p;\n        z =\
    \ (Long)z * z % p;\n        y = (Long)y * z % p;\n        e = j;\n    }\n    return\
    \ std::min(x, p - x);\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: number/sqrt_mod.hpp
  requiredBy:
  - number/square_sums.hpp
  timestamp: '2026-03-01 20:50:35+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - number/test/sqrt_mod.test.cpp
documentation_of: number/sqrt_mod.hpp
layout: document
title: "Square root modulo prime \uFF08\u5E73\u65B9\u5270\u4F59\uFF09"
---

素数 $p$ と整数 $a$ に対して，$x^2 \equiv a \pmod{p}$ を満たす $x$ を求める．解が存在しない場合は $-1$ を返す．Tonelli-Shanks algorithm に基づく．

## 使用方法

```cpp
int a, p;
int x = sqrt_mod<int>(a, p);  // x^2 ≡ a (mod p), or -1

long long al, pl;
long long xl = sqrt_mod<long long>(al, pl);  // __int128 を内部で使用
```

`Int` が `int` のとき内部で `long long`，`long long` のとき `__int128` を乗算のオーバーフロー回避に使用する．

## 問題例

- [Library Checker: Sqrt Mod](https://judge.yosupo.jp/problem/sqrt_mod)

## リンク

- [Tonelli–Shanks algorithm - Wikipedia](https://en.wikipedia.org/wiki/Tonelli%E2%80%93Shanks_algorithm)
