---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: number/sqrt_mod.hpp
    title: "Square root modulo prime \uFF08\u5E73\u65B9\u5270\u4F59\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"number/square_sums.hpp\"\n#include <cmath>\n\n#line 2 \"\
    number/sqrt_mod.hpp\"\n#include <algorithm>\n#include <type_traits>\n\n// Solve\
    \ x^2 == a (MOD p) for prime p\n// If no solution exists, return -1\ntemplate\
    \ <class Int> Int sqrt_mod(Int a, Int p) {\n    using Long =\n        std::conditional_t<std::is_same_v<Int,\
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
    \ std::min(x, p - x);\n}\n#line 5 \"number/square_sums.hpp\"\n\n// Fermat's theorem\
    \ on sums of two squares\n// Solve x^2 + y^2 = p for prime p, where p != 3 (mod\
    \ 4)\ntemplate <class Int> std::pair<Int, Int> SumOfTwoSquaresPrime(Int p) {\n\
    \    if (p == 2) return {1, 1};\n    if (p % 4 != 1) return {-1, -1};\n\n    Int\
    \ r0 = p, r1 = sqrt_mod<Int>(p - 1, p);\n    for (const Int limit = std::sqrtl(p);\
    \ r1 > limit;) {\n        Int next_r = r0 % r1;\n        r0 = r1, r1 = next_r;\n\
    \    }\n\n    return std::minmax(r1, (Int)std::sqrtl(p - r1 * r1));\n}\n"
  code: "#pragma once\n#include <cmath>\n\n#include \"sqrt_mod.hpp\"\n\n// Fermat's\
    \ theorem on sums of two squares\n// Solve x^2 + y^2 = p for prime p, where p\
    \ != 3 (mod 4)\ntemplate <class Int> std::pair<Int, Int> SumOfTwoSquaresPrime(Int\
    \ p) {\n    if (p == 2) return {1, 1};\n    if (p % 4 != 1) return {-1, -1};\n\
    \n    Int r0 = p, r1 = sqrt_mod<Int>(p - 1, p);\n    for (const Int limit = std::sqrtl(p);\
    \ r1 > limit;) {\n        Int next_r = r0 % r1;\n        r0 = r1, r1 = next_r;\n\
    \    }\n\n    return std::minmax(r1, (Int)std::sqrtl(p - r1 * r1));\n}\n"
  dependsOn:
  - number/sqrt_mod.hpp
  isVerificationFile: false
  path: number/square_sums.hpp
  requiredBy: []
  timestamp: '2026-03-01 20:50:35+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: number/square_sums.hpp
layout: document
title: "Sum of two squares \uFF08\u4E8C\u3064\u306E\u5E73\u65B9\u6570\u306E\u548C\uFF09"
---

素数 $p$ に対して，$x^2 + y^2 = p$ を満たす非負整数の組 $(x, y)$ （$x \le y$）を求める．Fermat の二平方和定理に基づく．

$p = 2$ のとき $(1, 1)$ を，$p \equiv 1 \pmod{4}$ のとき解を返す．$p \equiv 3 \pmod{4}$ のときは解が存在せず $(-1, -1)$ を返す．

## 使用方法

```cpp
int p;  // prime
auto [x, y] = SumOfTwoSquaresPrime<int>(p);  // x <= y, x^2 + y^2 = p
```

内部で `sqrt_mod` を呼び出し，$-1$ の平方根 $r$ を求めた後，$p$ と $r$ に対するユークリッドの互除法を $r_i \le \sqrt{p}$ となるまで適用する．

## リンク

- [Fermat's theorem on sums of two squares - Wikipedia](https://en.wikipedia.org/wiki/Fermat%27s_theorem_on_sums_of_two_squares)
