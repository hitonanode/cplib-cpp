---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: formal_power_series/sum_of_exponential_times_polynomial.hpp
    title: formal_power_series/sum_of_exponential_times_polynomial.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/sum_of_exponential_times_polynomial.test.cpp
    title: formal_power_series/test/sum_of_exponential_times_polynomial.test.cpp
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/sum_of_exponential_times_polynomial_limit.test.cpp
    title: formal_power_series/test/sum_of_exponential_times_polynomial_limit.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://hitonanode.github.io/cplib-cpp/formal_power_series/sum_of_exponential_times_polynomial_limit.hpp
    - https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial_limit
  bundledCode: "#line 2 \"formal_power_series/sum_of_exponential_times_polynomial_limit.hpp\"\
    \n#include <cassert>\n#include <vector>\n\n// CUT begin\n// $d$ \u6B21\u4EE5\u4E0B\
    \u306E\u591A\u9805\u5F0F $f(x)$ \u3068\u5B9A\u6570 $r$ \u306B\u3064\u3044\u3066\
    \uFF0C\n// $\\sum_{i=0}^\\infty r^i f(i)$ \u306E\u5024\u3092 $[f(0), ..., f(d\
    \ - 1), f(d)]$ \u306E\u5024\u304B\u3089 $O(d)$ \u3067\u8A08\u7B97\uFF0E\n// Requirement:\
    \ r != 1\n// https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial_limit\n\
    // Document: https://hitonanode.github.io/cplib-cpp/formal_power_series/sum_of_exponential_times_polynomial_limit.hpp\n\
    template <typename MODINT> MODINT sum_of_exponential_times_polynomial_limit(MODINT\
    \ r, std::vector<MODINT> init) {\n    assert(r != 1);\n    if (init.empty()) return\
    \ 0;\n    if (init.size() == 1) return init[0] / (1 - r);\n    auto &bs = init;\n\
    \    const int d = int(bs.size()) - 1;\n    MODINT rp = 1;\n    for (int i = 1;\
    \ i <= d; i++) rp *= r, bs[i] = bs[i] * rp + bs[i - 1];\n    MODINT ret = 0;\n\
    \    rp = 1;\n    for (int i = 0; i <= d; i++) {\n        ret += bs[d - i] * MODINT(d\
    \ + 1).nCr(i) * rp;\n        rp *= -r;\n    }\n    return ret / MODINT(1 - r).pow(d\
    \ + 1);\n};\n"
  code: "#pragma once\n#include <cassert>\n#include <vector>\n\n// CUT begin\n// $d$\
    \ \u6B21\u4EE5\u4E0B\u306E\u591A\u9805\u5F0F $f(x)$ \u3068\u5B9A\u6570 $r$ \u306B\
    \u3064\u3044\u3066\uFF0C\n// $\\sum_{i=0}^\\infty r^i f(i)$ \u306E\u5024\u3092\
    \ $[f(0), ..., f(d - 1), f(d)]$ \u306E\u5024\u304B\u3089 $O(d)$ \u3067\u8A08\u7B97\
    \uFF0E\n// Requirement: r != 1\n// https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial_limit\n\
    // Document: https://hitonanode.github.io/cplib-cpp/formal_power_series/sum_of_exponential_times_polynomial_limit.hpp\n\
    template <typename MODINT> MODINT sum_of_exponential_times_polynomial_limit(MODINT\
    \ r, std::vector<MODINT> init) {\n    assert(r != 1);\n    if (init.empty()) return\
    \ 0;\n    if (init.size() == 1) return init[0] / (1 - r);\n    auto &bs = init;\n\
    \    const int d = int(bs.size()) - 1;\n    MODINT rp = 1;\n    for (int i = 1;\
    \ i <= d; i++) rp *= r, bs[i] = bs[i] * rp + bs[i - 1];\n    MODINT ret = 0;\n\
    \    rp = 1;\n    for (int i = 0; i <= d; i++) {\n        ret += bs[d - i] * MODINT(d\
    \ + 1).nCr(i) * rp;\n        rp *= -r;\n    }\n    return ret / MODINT(1 - r).pow(d\
    \ + 1);\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: formal_power_series/sum_of_exponential_times_polynomial_limit.hpp
  requiredBy:
  - formal_power_series/sum_of_exponential_times_polynomial.hpp
  timestamp: '2021-05-03 18:16:21+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - formal_power_series/test/sum_of_exponential_times_polynomial.test.cpp
  - formal_power_series/test/sum_of_exponential_times_polynomial_limit.test.cpp
documentation_of: formal_power_series/sum_of_exponential_times_polynomial_limit.hpp
layout: document
title: Sum of exponential times polynomial ($\sum_{i=0}^{N - 1} r^i f(i)$)
---

一般に $f(x)$ を高々 $d$ 次の多項式として，$\displaystyle \sum_{i=0}^{N - 1} r^i f(i)$ を求める．先頭 $d + 1$ 項の値が既知であれば計算量は $O(d)$．関数は分かるが具体的な値が未知の場合は $O\left(d \left(\log d\right)^2\right)$ で先頭 $d + 1$ 項の値の multipoint evaluation を行う必要があると思われる．

## 導出の説明

[min\_25 さん](https://min-25.hatenablog.com/entry/2015/04/24/031413) によると，求めたい値は $C + g(x) r^x$, $g(x)$ はなんらかの多項式，という形になる．したがって，$r = 1$ の場合はそのまま Lagrange 補間を行えばよく，$r \neq 1$ の場合は $C$ や $r^x$ の分を打ち消した $g(x)$ に対して Lagrange 補間を行えばよい．$C$ の値は `sum_of_sum_of_exponential_times_polynomial_limit()` 関数によって $O(d)$ で求められる．

## 使用方法

先頭の $d + 1$ 項を計算して `sum_of_exponential_times_polynomial()` 関数に与える．
```cpp
using mint = ModInt<998244353>;
vector<mint> xs(d + 1);
for (int i = 0; i <= d; i++) xs[i] = i;
vector<mint> f = some_function();
vector<mint> initial_terms = MultipointEvaluation<mint>(xs).evaluate_polynomial(f);

mint sum = sum_of_exponential_times_polynomial<mint>(r, initial_terms, 12345678910111213LL);
```

単項式の場合，先頭 $d + 1$ 項の列挙が線形篩により $O(d)$ で可能である．使用方法は以下の通り．

```cpp
mint r;
int d;
vector<mint> initial_terms = Sieve(d).enumerate_kth_pows<mint>(d, d);
cout << sum_of_exponential_times_polynomial<mint>(r, initial_terms, 12345678910111213LL) << '\n';
```

## リンク

- https://min-25.hatenablog.com/entry/2015/04/24/031413
- https://github.com/yosupo06/library-checker-problems/issues/98
