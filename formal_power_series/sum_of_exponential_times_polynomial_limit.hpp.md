---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
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
    \n#include <vector>\n\n// CUT begin\n// $d$ \u6B21\u4EE5\u4E0B\u306E\u591A\u9805\
    \u5F0F $f(x)$ \u3068\u5B9A\u6570 $r$ \u306B\u3064\u3044\u3066\uFF0C\n// $\\sum_{i=0}^\\\
    infty r^i f(i)$ \u306E\u5024\u3092 $[f(0), ..., f(d - 1), f(d)]$ \u306E\u5024\u304B\
    \u3089 $O(d)$ \u3067\u8A08\u7B97\uFF0E\n// https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial_limit\n\
    // Document: https://hitonanode.github.io/cplib-cpp/formal_power_series/sum_of_exponential_times_polynomial_limit.hpp\n\
    template <typename MODINT> MODINT sum_of_exponential_times_polynomial_limit(MODINT\
    \ r, std::vector<MODINT> init) {\n    auto &bs = init;\n    if (bs.empty()) return\
    \ 0;\n    const int d = int(bs.size()) - 1;\n    if (d == 0) { return 1 / (1 -\
    \ r); }\n    MODINT rp = 1;\n    for (int i = 1; i <= d; i++) rp *= r, bs[i] =\
    \ bs[i] * rp + bs[i - 1];\n    MODINT ret = 0;\n    rp = 1;\n    for (int i =\
    \ 0; i <= d; i++) {\n        ret += bs[d - i] * MODINT(d + 1).nCr(i) * rp;\n \
    \       rp *= -r;\n    }\n    return ret / MODINT(1 - r).pow(d + 1);\n};\n"
  code: "#pragma once\n#include <vector>\n\n// CUT begin\n// $d$ \u6B21\u4EE5\u4E0B\
    \u306E\u591A\u9805\u5F0F $f(x)$ \u3068\u5B9A\u6570 $r$ \u306B\u3064\u3044\u3066\
    \uFF0C\n// $\\sum_{i=0}^\\infty r^i f(i)$ \u306E\u5024\u3092 $[f(0), ..., f(d\
    \ - 1), f(d)]$ \u306E\u5024\u304B\u3089 $O(d)$ \u3067\u8A08\u7B97\uFF0E\n// https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial_limit\n\
    // Document: https://hitonanode.github.io/cplib-cpp/formal_power_series/sum_of_exponential_times_polynomial_limit.hpp\n\
    template <typename MODINT> MODINT sum_of_exponential_times_polynomial_limit(MODINT\
    \ r, std::vector<MODINT> init) {\n    auto &bs = init;\n    if (bs.empty()) return\
    \ 0;\n    const int d = int(bs.size()) - 1;\n    if (d == 0) { return 1 / (1 -\
    \ r); }\n    MODINT rp = 1;\n    for (int i = 1; i <= d; i++) rp *= r, bs[i] =\
    \ bs[i] * rp + bs[i - 1];\n    MODINT ret = 0;\n    rp = 1;\n    for (int i =\
    \ 0; i <= d; i++) {\n        ret += bs[d - i] * MODINT(d + 1).nCr(i) * rp;\n \
    \       rp *= -r;\n    }\n    return ret / MODINT(1 - r).pow(d + 1);\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: formal_power_series/sum_of_exponential_times_polynomial_limit.hpp
  requiredBy: []
  timestamp: '2021-05-03 13:23:02+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - formal_power_series/test/sum_of_exponential_times_polynomial_limit.test.cpp
documentation_of: formal_power_series/sum_of_exponential_times_polynomial_limit.hpp
layout: document
title: Sum of exponential times polynomial limit ($\sum_{i=0}^\infty r^i f(i)$)
---

一般に $f(x)$ を高々 $d$ 次の多項式として，$\displaystyle \sum_{i=0}^\infty r^i f(i) \, (r \neq 1)$ を求める方法を議論する．先頭 $d + 1$ 項の値が既知であれば計算量は $O(d)$．未知の場合は $O\left(d \left(\log d\right)^2\right)$ で先頭 $d + 1$ 項の値の multipoint evaluation を行う必要があると思われる．

## 導出の説明

一般に $d$ 次以下の多項式 $f(x)$ に $x = 0, 1, 2, \dots$ を代入して得られる数列の母関数は，初期条件を意味する高々 $d$ 次の多項式 $g(x)$ を用いて

$\displaystyle
\frac{g(x)}{(1 - x)^{d + 1}}
$

と書けるらしい（$(1 - x)$ で一回割ることが累積和に対応する．累積和 1 回で定数関数，2 回で一次関数， ...，累積和 $(d + 1)$ 回で $d$ 次関数が作れる）．これを鑑みて数列 $a = [a_i]_{i = 0, \dots}, \, a_i = r^i f(i)$ の母関数を検討する．これは，数列が一個進む毎に値が $r$ 倍に減衰する影響を考慮すると，$d$ 次以下の $g(x)$ を用いて

$\displaystyle
\frac{g(x)}{(1-rx)^{d + 1}}
$

と書けるはずである．ここで $g(x)$ の形は，$\sum_i a_i x^i \cdot (1 - rx)^{d + 1}  \bmod{x^{d+1}}$ によって決定される（さもなくば最初の $d + 1$ 項の辻褄が合わなくなる）．

求めたい値は，この母関数に $x=1$ を代入することで得られる．これは，$[a_i]_i$ の累積和を $b = [b_i]_i, \, b_i = b_{i - 1} + a_i$ とすると，

$\displaystyle
\frac{1}{(1 - r)^{d + 1}} \sum_{i=0}^d b_{d - i} \binom{d + 1}{i}(-r)^{i}
$

と整理される．この式は $a$ の先頭 $d + 1$ 項の値が既知であれば $O(d)$ で計算可能である．

## 使用方法

先頭の $d + 1$ 項を計算して `sum_of_exponential_times_polynomial_limit()` 関数に与える．
```cpp
using mint = ModInt<998244353>;
vector<mint> xs(d + 1);
for (int i = 0; i <= d; i++) xs[i] = i;
vector<mint> f = some_function();
vector<mint> initial_terms = MultipointEvaluation<mint>(xs).evaluate_polynomial(f);

mint sum = sum_of_exponential_times_polynomial_limit<mint>(r, initial_terms);
```

## 特に $f(x)$ が単項式の場合

単項式の場合，先頭 $d + 1$ 項の列挙が線形篩により $O(d)$ で可能である．使用方法は以下の通り．
```cpp
mint r;
int d;
vector<mint> initial_terms = Sieve(d).enumerate_kth_pows<mint>(d, d);
cout << sum_of_exponential_times_polynomial_limit<mint>(r, initial_terms) << '\n';
```

## リンク

- https://github.com/yosupo06/library-checker-problems/issues/99
