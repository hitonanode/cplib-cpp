---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: number/primitive_root.hpp
    title: "Primitive root modulo $n$ \uFF08\u539F\u59CB\u6839\u306E\u767A\u898B\uFF09"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: number/test/primitive_root.test.cpp
    title: number/test/primitive_root.test.cpp
  - icon: ':heavy_check_mark:'
    path: number/test/primitive_root_1e18.test.cpp
    title: number/test/primitive_root_1e18.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"number/pow_mod.hpp\"\n#include <cassert>\n#include <type_traits>\n\
    \ntemplate <class Int> Int pow_mod(Int x, long long n, Int md) {\n    using Long\
    \ =\n        std::conditional_t<std::is_same_v<Int, int>, long long,\n       \
    \                    std::conditional_t<std::is_same_v<Int, long long>, __int128,\
    \ void>>;\n    assert(n >= 0 and md > 0);\n    if (md == 1) return 0;\n    if\
    \ (n == 0) return 1;\n\n    x = (x % md + md) % md;\n    Int ans = 1;\n    while\
    \ (n > 0) {\n        if (n & 1) ans = (Long)ans * x % md;\n        x = (Long)x\
    \ * x % md;\n        n >>= 1;\n    }\n    return ans;\n}\n"
  code: "#pragma once\n#include <cassert>\n#include <type_traits>\n\ntemplate <class\
    \ Int> Int pow_mod(Int x, long long n, Int md) {\n    using Long =\n        std::conditional_t<std::is_same_v<Int,\
    \ int>, long long,\n                           std::conditional_t<std::is_same_v<Int,\
    \ long long>, __int128, void>>;\n    assert(n >= 0 and md > 0);\n    if (md ==\
    \ 1) return 0;\n    if (n == 0) return 1;\n\n    x = (x % md + md) % md;\n   \
    \ Int ans = 1;\n    while (n > 0) {\n        if (n & 1) ans = (Long)ans * x %\
    \ md;\n        x = (Long)x * x % md;\n        n >>= 1;\n    }\n    return ans;\n\
    }\n"
  dependsOn: []
  isVerificationFile: false
  path: number/pow_mod.hpp
  requiredBy:
  - number/primitive_root.hpp
  timestamp: '2026-04-11 14:52:31+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - number/test/primitive_root.test.cpp
  - number/test/primitive_root_1e18.test.cpp
documentation_of: number/pow_mod.hpp
layout: document
title: "Modular exponentiation \uFF08\u3079\u304D\u4E57 mod\uFF09"
---

整数 $x$, 非負整数 $n$, 正整数 $m$ に対し，$x^n \bmod m$ を $O(\log n)$ で計算する．繰り返し二乗法による実装．`Int` が `int` のとき内部で `long long`，`long long` のとき `__int128` を用いてオーバーフローを回避する．

## 使用方法

```cpp
int a = pow_mod(3, 100, 1000000007);       // Int = int
long long b = pow_mod(3LL, 100LL, (long long)1e18 + 9); // Int = long long
```

- `x`: 底．
- `n`: 指数（$n \ge 0$）．
- `md`: 法（$m \ge 1$）．$m = 1$ のとき常に $0$ を返す．
