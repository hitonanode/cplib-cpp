---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://csacademy.com/contest/fii-code-2021-round-2/task/clown-fiesta/
    - https://kopricky.github.io/code/Computation_Advanced/tetration.html
  bundledCode: "#line 2 \"number/euler_totient_phi.hpp\"\n#include <numeric>\n#include\
    \ <vector>\n\n// CUT begin\n// Euler's totient function\n// Complexity: O(NlgN)\n\
    std::vector<int> euler_phi_table(int N) {\n    std::vector<int> ret(N + 1);\n\
    \    std::iota(ret.begin(), ret.end(), 0);\n    for (int p = 2; p <= N; p++) {\n\
    \        if (ret[p] == p) {\n            ret[p] = p - 1;\n            for (int\
    \ i = p * 2; i <= N; i += p) ret[i] = ret[i] / p * (p - 1);\n        }\n    }\n\
    \    return ret;\n}\n\n// Euler's totient function\n// Complexity: O(sqrtN)\n\
    // https://csacademy.com/contest/fii-code-2021-round-2/task/clown-fiesta/\n//\
    \ https://kopricky.github.io/code/Computation_Advanced/tetration.html\ntemplate\
    \ <typename Int> Int euler_phi(Int n) {\n    Int ret = n;\n    if (n % 2 == 0)\
    \ {\n        ret /= 2;\n        do { n /= 2; } while (n % 2 == 0);\n    }\n  \
    \  if (n % 3 == 0) {\n        ret = ret / 3 * 2;\n        do { n /= 3; } while\
    \ (n % 3 == 0);\n    }\n    for (Int i = 5; i * i <= n; i += 4) {\n        if\
    \ (n % i == 0) {\n            ret = ret / i * (i - 1);\n            do { n /=\
    \ i; } while (n % i == 0);\n        }\n        i += 2;\n        if (n % i == 0)\
    \ {\n            ret = ret / i * (i - 1);\n            do { n /= i; } while (n\
    \ % i == 0);\n        }\n    }\n    if (n != 1) ret = ret / n * (n - 1);\n   \
    \ return ret;\n}\n"
  code: "#pragma once\n#include <numeric>\n#include <vector>\n\n// CUT begin\n// Euler's\
    \ totient function\n// Complexity: O(NlgN)\nstd::vector<int> euler_phi_table(int\
    \ N) {\n    std::vector<int> ret(N + 1);\n    std::iota(ret.begin(), ret.end(),\
    \ 0);\n    for (int p = 2; p <= N; p++) {\n        if (ret[p] == p) {\n      \
    \      ret[p] = p - 1;\n            for (int i = p * 2; i <= N; i += p) ret[i]\
    \ = ret[i] / p * (p - 1);\n        }\n    }\n    return ret;\n}\n\n// Euler's\
    \ totient function\n// Complexity: O(sqrtN)\n// https://csacademy.com/contest/fii-code-2021-round-2/task/clown-fiesta/\n\
    // https://kopricky.github.io/code/Computation_Advanced/tetration.html\ntemplate\
    \ <typename Int> Int euler_phi(Int n) {\n    Int ret = n;\n    if (n % 2 == 0)\
    \ {\n        ret /= 2;\n        do { n /= 2; } while (n % 2 == 0);\n    }\n  \
    \  if (n % 3 == 0) {\n        ret = ret / 3 * 2;\n        do { n /= 3; } while\
    \ (n % 3 == 0);\n    }\n    for (Int i = 5; i * i <= n; i += 4) {\n        if\
    \ (n % i == 0) {\n            ret = ret / i * (i - 1);\n            do { n /=\
    \ i; } while (n % i == 0);\n        }\n        i += 2;\n        if (n % i == 0)\
    \ {\n            ret = ret / i * (i - 1);\n            do { n /= i; } while (n\
    \ % i == 0);\n        }\n    }\n    if (n != 1) ret = ret / n * (n - 1);\n   \
    \ return ret;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: number/euler_totient_phi.hpp
  requiredBy: []
  timestamp: '2021-05-05 10:47:28+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: number/euler_totient_phi.hpp
layout: document
title: "Euler's totient function\uFF08\u30AA\u30A4\u30E9\u30FC\u306E\u30C8\u30FC\u30B7\
  \u30A7\u30F3\u30C8\u95A2\u6570\uFF09"
---

Euler's totient function $\varphi(n)$ は正の整数 $n$ に対して $n$ と互いに素な $n$ 以下の正の整数の個数．

## 使用例

``` cpp
std::vector<int> phi_table = euler_phi_table(N);  // N 以下の正の整数に対するテーブル作成 O(N log N)

auto phi = euler_phi<long long>(12345678910LL);  // 特定の整数に対する計算 O(sqrt N)
```

## 性質

- （オイラーの定理）$a$ と $n$ が互いに素なとき，$\displaystyle a^{\varphi(n)} \equiv 1 \pmod{n}$

## 問題例

- [CS Academy FIICode 2021 Round #2 - Clown Fiesta](https://csacademy.com/contest/fii-code-2021-round-2/task/clown-fiesta/)

## リンク

- [Euler's totient function - Wikipedia](https://en.wikipedia.org/wiki/Euler%27s_totient_function)
