---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: number/test/rational_approximation.test.cpp
    title: number/test/rational_approximation.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"number/rational_approximation.hpp\"\n\n#include <cassert>\n\
    #include <utility>\n#include <vector>\n\n// Rational approximation based on Stern\u2013\
    Brocot tree\n// Input: N > 0, num >= 0, den >= 0 (num > 0 or den > 0)\n// return\
    \ {{p, q}, {r, s}} where p/q <= num/den <= r/s. Strictly,\n// - p/q = max(n /\
    \ d | n / d <= num / den, 0 <= n <= N, 1 <= d <= N)\n// - r/s = min(n / d | num\
    \ / den <= n / d, 0 <= n <= N, 1 <= d <= N)\ntemplate <class Int>\nstd::pair<std::pair<Int,\
    \ Int>, std::pair<Int, Int>> rational_approximation(Int N, Int num, Int den) {\n\
    \    assert(N >= 1);\n    assert(num >= 0);\n    assert(den >= 0);\n    assert(num\
    \ > 0 or den > 0);\n\n    if (num == Int(0)) return {{Int(0), Int(1)}, {Int(0),\
    \ Int(1)}}; // 0\n    if (den == Int(0)) return {{Int(1), Int(0)}, {Int(1), Int(0)}};\
    \ // inf\n\n    // p/q <= num/den <= r/s\n    Int p = 0, q = 1, r = 1, s = 0;\n\
    \n    bool is_left = false;\n    while (true) {\n        Int max_steps = num /\
    \ den;\n\n        if (is_left) {\n            // r + steps * p <= N\n        \
    \    // s + steps * q <= N\n\n            if (p > Int(0)) max_steps = std::min(max_steps,\
    \ (N - r) / p);\n            max_steps = std::min(max_steps, (N - s) / q);\n\n\
    \            r += max_steps * p;\n            s += max_steps * q;\n        } else\
    \ {\n            // p + steps * r <= N\n            // q + steps * s <= N\n\n\
    \            max_steps = std::min(max_steps, (N - p) / r);\n            if (s\
    \ > Int(0)) max_steps = std::min(max_steps, (N - q) / s);\n\n            p +=\
    \ max_steps * r;\n            q += max_steps * s;\n        }\n\n        if (is_left\
    \ and !max_steps) break;\n\n        num -= max_steps * den;\n\n        if (num\
    \ == Int(0)) {\n            if (is_left) {\n                return {{r, s}, {r,\
    \ s}};\n            } else {\n                return {{p, q}, {p, q}};\n     \
    \       }\n        }\n\n        std::swap(num, den);\n        is_left = !is_left;\n\
    \    }\n\n    return {{p, q}, {r, s}};\n}\n"
  code: "#pragma once\n\n#include <cassert>\n#include <utility>\n#include <vector>\n\
    \n// Rational approximation based on Stern\u2013Brocot tree\n// Input: N > 0,\
    \ num >= 0, den >= 0 (num > 0 or den > 0)\n// return {{p, q}, {r, s}} where p/q\
    \ <= num/den <= r/s. Strictly,\n// - p/q = max(n / d | n / d <= num / den, 0 <=\
    \ n <= N, 1 <= d <= N)\n// - r/s = min(n / d | num / den <= n / d, 0 <= n <= N,\
    \ 1 <= d <= N)\ntemplate <class Int>\nstd::pair<std::pair<Int, Int>, std::pair<Int,\
    \ Int>> rational_approximation(Int N, Int num, Int den) {\n    assert(N >= 1);\n\
    \    assert(num >= 0);\n    assert(den >= 0);\n    assert(num > 0 or den > 0);\n\
    \n    if (num == Int(0)) return {{Int(0), Int(1)}, {Int(0), Int(1)}}; // 0\n \
    \   if (den == Int(0)) return {{Int(1), Int(0)}, {Int(1), Int(0)}}; // inf\n\n\
    \    // p/q <= num/den <= r/s\n    Int p = 0, q = 1, r = 1, s = 0;\n\n    bool\
    \ is_left = false;\n    while (true) {\n        Int max_steps = num / den;\n\n\
    \        if (is_left) {\n            // r + steps * p <= N\n            // s +\
    \ steps * q <= N\n\n            if (p > Int(0)) max_steps = std::min(max_steps,\
    \ (N - r) / p);\n            max_steps = std::min(max_steps, (N - s) / q);\n\n\
    \            r += max_steps * p;\n            s += max_steps * q;\n        } else\
    \ {\n            // p + steps * r <= N\n            // q + steps * s <= N\n\n\
    \            max_steps = std::min(max_steps, (N - p) / r);\n            if (s\
    \ > Int(0)) max_steps = std::min(max_steps, (N - q) / s);\n\n            p +=\
    \ max_steps * r;\n            q += max_steps * s;\n        }\n\n        if (is_left\
    \ and !max_steps) break;\n\n        num -= max_steps * den;\n\n        if (num\
    \ == Int(0)) {\n            if (is_left) {\n                return {{r, s}, {r,\
    \ s}};\n            } else {\n                return {{p, q}, {p, q}};\n     \
    \       }\n        }\n\n        std::swap(num, den);\n        is_left = !is_left;\n\
    \    }\n\n    return {{p, q}, {r, s}};\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: number/rational_approximation.hpp
  requiredBy: []
  timestamp: '2024-07-14 00:23:24+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - number/test/rational_approximation.test.cpp
documentation_of: number/rational_approximation.hpp
layout: document
title: "Rational approximation \uFF08\u6709\u7406\u6570\u8FD1\u4F3C\uFF09"
---

与えられた非負の有理数 `num / den` に対して，分子・分母がともに $N$ 以下の分数で両側から近似する．

## 使用方法

```cpp
int N, num, den;
const auto [l, r] = rational_approximation<int>(N, num, den);

// lnum / lden <= num / den <= rnum / rden
// max(lnum, lden, rnum, rden) <= N
const auto [lnum, lden] = l;
const auto [rnum, rden] = r;
```

## 問題例

- [Library Checker: Rational Approximation](https://judge.yosupo.jp/problem/rational_approximation)
