---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':x:'
    path: formal_power_series/sum_of_exponential_times_polynomial.hpp
    title: Sum of exponential times polynomial ($\sum_{i=0}^{N - 1} r^i f(i)$)
  _extendedVerifiedWith:
  - icon: ':x:'
    path: formal_power_series/test/sum_of_exponential_times_polynomial.test.cpp
    title: formal_power_series/test/sum_of_exponential_times_polynomial.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links:
    - https://atcoder.jp/contests/arc033/tasks/arc033_4
  bundledCode: "#line 2 \"formal_power_series/lagrange_interpolation.hpp\"\n#include\
    \ <vector>\n\n// CUT begin\n// Lagrange interpolation\n// Input: [f(0), ..., f(N-1)]\
    \ (length = N), deg(f) < N\n// Output: f(x_eval)\n// Complexity: O(N)\n// Verified:\
    \ https://atcoder.jp/contests/arc033/tasks/arc033_4\ntemplate <typename MODINT>\
    \ MODINT interpolate_iota(const std::vector<MODINT> ys, MODINT x_eval) {\n   \
    \ const int N = ys.size();\n    if (x_eval.val < N) return ys[x_eval.val];\n \
    \   std::vector<MODINT> facinv(N);\n    facinv[N - 1] = MODINT(N - 1).fac().inv();\n\
    \    for (int i = N - 1; i > 0; i--) facinv[i - 1] = facinv[i] * i;\n    std::vector<MODINT>\
    \ numleft(N);\n    MODINT numtmp = 1;\n    for (int i = 0; i < N; i++) {\n   \
    \     numleft[i] = numtmp;\n        numtmp *= x_eval - i;\n    }\n    numtmp =\
    \ 1;\n    MODINT ret = 0;\n    for (int i = N - 1; i >= 0; i--) {\n        MODINT\
    \ tmp = ys[i] * numleft[i] * numtmp * facinv[i] * facinv[N - 1 - i];\n       \
    \ ret += ((N - 1 - i) & 1) ? (-tmp) : tmp;\n        numtmp *= x_eval - i;\n  \
    \  }\n    return ret;\n}\n"
  code: "#pragma once\n#include <vector>\n\n// CUT begin\n// Lagrange interpolation\n\
    // Input: [f(0), ..., f(N-1)] (length = N), deg(f) < N\n// Output: f(x_eval)\n\
    // Complexity: O(N)\n// Verified: https://atcoder.jp/contests/arc033/tasks/arc033_4\n\
    template <typename MODINT> MODINT interpolate_iota(const std::vector<MODINT> ys,\
    \ MODINT x_eval) {\n    const int N = ys.size();\n    if (x_eval.val < N) return\
    \ ys[x_eval.val];\n    std::vector<MODINT> facinv(N);\n    facinv[N - 1] = MODINT(N\
    \ - 1).fac().inv();\n    for (int i = N - 1; i > 0; i--) facinv[i - 1] = facinv[i]\
    \ * i;\n    std::vector<MODINT> numleft(N);\n    MODINT numtmp = 1;\n    for (int\
    \ i = 0; i < N; i++) {\n        numleft[i] = numtmp;\n        numtmp *= x_eval\
    \ - i;\n    }\n    numtmp = 1;\n    MODINT ret = 0;\n    for (int i = N - 1; i\
    \ >= 0; i--) {\n        MODINT tmp = ys[i] * numleft[i] * numtmp * facinv[i] *\
    \ facinv[N - 1 - i];\n        ret += ((N - 1 - i) & 1) ? (-tmp) : tmp;\n     \
    \   numtmp *= x_eval - i;\n    }\n    return ret;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: formal_power_series/lagrange_interpolation.hpp
  requiredBy:
  - formal_power_series/sum_of_exponential_times_polynomial.hpp
  timestamp: '2021-05-03 18:16:21+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - formal_power_series/test/sum_of_exponential_times_polynomial.test.cpp
documentation_of: formal_power_series/lagrange_interpolation.hpp
layout: document
title: "Lagrange interpolation\uFF08\u591A\u9805\u5F0F\u306E Lagrange \u88DC\u9593\
  \uFF09"
---

$N - 1$ 次多項式 $f(x)$ の $x = 0, \dots, N - 1$ における値から，所望の $x = x_\mathrm{eval}$ での $f(x)$ の値を復元する．計算量は $O(N + \log \mathrm{MOD})$．

## 原理

$N$ 点 $x_0, \dots, x_{N - 1}$ のうち $x_i$ で値 $y_i$ をとり他の $N - 1$ 点でゼロとなるような $N - 1$ 次多項式は

$\displaystyle
y_i \cdot \frac{(x - x_0)(x - x_1) \dots (x - x_{i - 1})(x - x_{i + 1}) \dots (x - x_{N - 1})}{(x_i - x_0)(x_i - x_1) \dots (x_i - x_{i - 1})(x_i - x_{i + 1}) \dots (x_i - x_{N - 1})}
$

と一意に定まる．よってこれを $i = 0, \dots, N - 1$ で重ね合わせればもとの $f(x)$ も復元できる．

$x = x_\mathrm{eval}$ での $f(x)$ の値を知るにはもとの関数を直接復元する必要はなく，各 $i$ について上の式に $x = x_\mathrm{eval}$ を代入して評価した結果を足し合わせればよい．$x_i$ たちが一般の配置の場合は分母の計算のため $O \left(N \left( \log N \right)^2 \right)$ の分割統治を行う必要があるが，$x_i$ が等間隔に並ぶ場合は分母の値が規則的になり，$O(N)$ で計算できる．具体的には， $x_{i + 1} = x_i + 1 \, (i = 0, \ldots, N - 2)$ のとき，

$\displaystyle
f(x_\mathrm{eval}) = \sum_{i = 0}^{N - 1} y_i \cdot \frac{\prod_{j=0}^{i-1} (x_\mathrm{eval} - x_j)\cdot \prod_{j=i+1}^{N-1} (x_\mathrm{eval} - x_j)}{i! (N - 1 - i)! \cdot(-1)^{N - 1 - i}}
$

と書ける．

## 使用方法

先頭の $d + 1$ 項を計算して `interpolate_iota()` 関数に与える．
```cpp
vector<mint> A(N + 1);
for (auto &a : A) cin >> a;

cout << interpolate_iota<mint>(A, 12345678910111213LL) << '\n';
```

## リンク

- [AtCoder Regular Contest 033 D - 見たことのない多項式](https://atcoder.jp/contests/arc033/submissions/22279922)
