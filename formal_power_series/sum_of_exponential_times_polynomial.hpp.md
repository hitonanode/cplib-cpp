---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: formal_power_series/lagrange_interpolation.hpp
    title: "Lagrange interpolation\uFF08\u591A\u9805\u5F0F\u306E Lagrange \u88DC\u9593\
      \uFF09"
  - icon: ':heavy_check_mark:'
    path: formal_power_series/sum_of_exponential_times_polynomial_limit.hpp
    title: Sum of exponential times polynomial limit ($\sum_{i=0}^\infty r^i f(i)$)
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: number/arithmetic_cumsum.hpp
    title: "Cumulative sum of arithmetic functions \uFF08\u6570\u8AD6\u7684\u95A2\u6570\
      \u306E\u7D2F\u7A4D\u548C\uFF09"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: formal_power_series/test/sum_of_exponential_times_polynomial.test.cpp
    title: formal_power_series/test/sum_of_exponential_times_polynomial.test.cpp
  - icon: ':heavy_check_mark:'
    path: number/test/arithmetic_function_totient.test.cpp
    title: number/test/arithmetic_function_totient.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial
    - https://min-25.hatenablog.com/entry/2015/04/24/031413
  bundledCode: "#line 2 \"formal_power_series/lagrange_interpolation.hpp\"\n#include\
    \ <vector>\n\n// CUT begin\n// Lagrange interpolation\n// Input: [f(0), ..., f(N-1)]\
    \ (length = N), deg(f) < N\n// Output: f(x_eval)\n// Complexity: O(N)\n// Verified:\
    \ https://atcoder.jp/contests/arc033/tasks/arc033_4\ntemplate <typename MODINT>\
    \ MODINT interpolate_iota(const std::vector<MODINT> ys, MODINT x_eval) {\n   \
    \ const int N = ys.size();\n    if (x_eval.val() < N) return ys[x_eval.val()];\n\
    \    std::vector<MODINT> facinv(N);\n    facinv[N - 1] = MODINT::facinv(N - 1);\n\
    \    for (int i = N - 1; i > 0; i--) facinv[i - 1] = facinv[i] * i;\n    std::vector<MODINT>\
    \ numleft(N);\n    MODINT numtmp = 1;\n    for (int i = 0; i < N; i++) {\n   \
    \     numleft[i] = numtmp;\n        numtmp *= x_eval - i;\n    }\n    numtmp =\
    \ 1;\n    MODINT ret = 0;\n    for (int i = N - 1; i >= 0; i--) {\n        MODINT\
    \ tmp = ys[i] * numleft[i] * numtmp * facinv[i] * facinv[N - 1 - i];\n       \
    \ ret += ((N - 1 - i) & 1) ? (-tmp) : tmp;\n        numtmp *= x_eval - i;\n  \
    \  }\n    return ret;\n}\n#line 2 \"formal_power_series/sum_of_exponential_times_polynomial_limit.hpp\"\
    \n#include <cassert>\n#line 4 \"formal_power_series/sum_of_exponential_times_polynomial_limit.hpp\"\
    \n\n// CUT begin\n// $d$ \u6B21\u4EE5\u4E0B\u306E\u591A\u9805\u5F0F $f(x)$ \u3068\
    \u5B9A\u6570 $r$ \u306B\u3064\u3044\u3066\uFF0C\n// $\\sum_{i=0}^\\infty r^i f(i)$\
    \ \u306E\u5024\u3092 $[f(0), ..., f(d - 1), f(d)]$ \u306E\u5024\u304B\u3089 $O(d)$\
    \ \u3067\u8A08\u7B97\uFF0E\n// Requirement: r != 1\n// https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial_limit\n\
    // Document: https://hitonanode.github.io/cplib-cpp/formal_power_series/sum_of_exponential_times_polynomial_limit.hpp\n\
    template <typename MODINT>\nMODINT sum_of_exponential_times_polynomial_limit(MODINT\
    \ r, std::vector<MODINT> init) {\n    assert(r != 1);\n    if (init.empty()) return\
    \ 0;\n    if (init.size() == 1) return init[0] / (1 - r);\n    auto &bs = init;\n\
    \    const int d = int(bs.size()) - 1;\n    MODINT rp = 1;\n    for (int i = 1;\
    \ i <= d; i++) rp *= r, bs[i] = bs[i] * rp + bs[i - 1];\n    MODINT ret = 0;\n\
    \    rp = 1;\n    for (int i = 0; i <= d; i++) {\n        ret += bs[d - i] * MODINT::binom(d\
    \ + 1, i) * rp;\n        rp *= -r;\n    }\n    return ret / MODINT(1 - r).pow(d\
    \ + 1);\n};\n#line 6 \"formal_power_series/sum_of_exponential_times_polynomial.hpp\"\
    \n\n// CUT begin\n// $d$ \u6B21\u4EE5\u4E0B\u306E\u591A\u9805\u5F0F $f(x)$ \u3068\
    \u5B9A\u6570 $r$ \u306B\u3064\u3044\u3066\uFF0C\n// $\\sum_{i=0}^{N-1} r^i f(i)$\
    \ \u306E\u5024\u3092 $[f(0), ..., f(d - 1), f(d)]$ \u306E\u5024\u304B\u3089 $O(d)$\
    \ \u3067\u8A08\u7B97\uFF0E\n// Reference:\n// - https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial\n\
    // - https://min-25.hatenablog.com/entry/2015/04/24/031413\ntemplate <typename\
    \ MODINT>\nMODINT sum_of_exponential_times_polynomial(MODINT r, const std::vector<MODINT>\
    \ &init, long long N) {\n    if (N <= 0) return 0;\n    if (init.size() == 1)\
    \ return init[0] * (r == 1 ? MODINT(N) : (1 - r.pow(N)) / (1 - r));\n\n    std::vector<MODINT>\
    \ S(init.size() + 1);\n    MODINT rp = 1;\n    for (int i = 0; i < int(init.size());\
    \ i++) {\n        S[i + 1] = S[i] + init[i] * rp;\n        rp *= r;\n    }\n \
    \   if (N < (long long)S.size()) return S[N];\n\n    if (r == 1) return interpolate_iota<MODINT>(S,\
    \ N);\n\n    const MODINT Sinf = sum_of_exponential_times_polynomial_limit<MODINT>(r,\
    \ init);\n    MODINT rinv = r.inv(), rinvp = 1;\n    for (int i = 0; i < int(S.size());\
    \ i++) {\n        S[i] = (S[i] - Sinf) * rinvp;\n        rinvp *= rinv;\n    }\n\
    \    return interpolate_iota<MODINT>(S, N) * r.pow(N) + Sinf;\n};\n"
  code: "#pragma once\n#include \"lagrange_interpolation.hpp\"\n#include \"sum_of_exponential_times_polynomial_limit.hpp\"\
    \n#include <cassert>\n#include <vector>\n\n// CUT begin\n// $d$ \u6B21\u4EE5\u4E0B\
    \u306E\u591A\u9805\u5F0F $f(x)$ \u3068\u5B9A\u6570 $r$ \u306B\u3064\u3044\u3066\
    \uFF0C\n// $\\sum_{i=0}^{N-1} r^i f(i)$ \u306E\u5024\u3092 $[f(0), ..., f(d -\
    \ 1), f(d)]$ \u306E\u5024\u304B\u3089 $O(d)$ \u3067\u8A08\u7B97\uFF0E\n// Reference:\n\
    // - https://judge.yosupo.jp/problem/sum_of_exponential_times_polynomial\n// -\
    \ https://min-25.hatenablog.com/entry/2015/04/24/031413\ntemplate <typename MODINT>\n\
    MODINT sum_of_exponential_times_polynomial(MODINT r, const std::vector<MODINT>\
    \ &init, long long N) {\n    if (N <= 0) return 0;\n    if (init.size() == 1)\
    \ return init[0] * (r == 1 ? MODINT(N) : (1 - r.pow(N)) / (1 - r));\n\n    std::vector<MODINT>\
    \ S(init.size() + 1);\n    MODINT rp = 1;\n    for (int i = 0; i < int(init.size());\
    \ i++) {\n        S[i + 1] = S[i] + init[i] * rp;\n        rp *= r;\n    }\n \
    \   if (N < (long long)S.size()) return S[N];\n\n    if (r == 1) return interpolate_iota<MODINT>(S,\
    \ N);\n\n    const MODINT Sinf = sum_of_exponential_times_polynomial_limit<MODINT>(r,\
    \ init);\n    MODINT rinv = r.inv(), rinvp = 1;\n    for (int i = 0; i < int(S.size());\
    \ i++) {\n        S[i] = (S[i] - Sinf) * rinvp;\n        rinvp *= rinv;\n    }\n\
    \    return interpolate_iota<MODINT>(S, N) * r.pow(N) + Sinf;\n};\n"
  dependsOn:
  - formal_power_series/lagrange_interpolation.hpp
  - formal_power_series/sum_of_exponential_times_polynomial_limit.hpp
  isVerificationFile: false
  path: formal_power_series/sum_of_exponential_times_polynomial.hpp
  requiredBy:
  - number/arithmetic_cumsum.hpp
  timestamp: '2025-08-25 00:44:05+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - number/test/arithmetic_function_totient.test.cpp
  - formal_power_series/test/sum_of_exponential_times_polynomial.test.cpp
documentation_of: formal_power_series/sum_of_exponential_times_polynomial.hpp
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
