---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: formal_power_series/test/pow_of_sparse_fps.stress.test.cpp
    title: formal_power_series/test/pow_of_sparse_fps.stress.test.cpp
  - icon: ':x:'
    path: formal_power_series/test/pow_of_sparse_fps.yuki1939.test.cpp
    title: formal_power_series/test/pow_of_sparse_fps.yuki1939.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 2 \"formal_power_series/pow_of_sparse_fps.hpp\"\n#include <algorithm>\n\
    #include <cassert>\n#include <tuple>\n#include <utility>\n#include <vector>\n\n\
    // Calculate f(x)^k up to x^N\n// Requirement: k > 0\n// Complexity: O(NM) (M\
    \ : num. of nonzero coefficients of f(x))\ntemplate <class T> std::vector<T> pow_of_sparse_fps(const\
    \ std::vector<T> &f, int N, long long k) {\n    assert(k > 0);\n    std::vector<std::pair<int,\
    \ T>> nonzero_terms;\n    int d0 = 0;\n    while (d0 < int(f.size()) and d0 <=\
    \ N and f[d0] == T()) ++d0;\n    if (d0 == int(f.size()) or d0 > N) return std::vector<T>(N\
    \ + 1);\n\n    if (d0 and N / d0 < k) return std::vector<T>(N + 1);\n\n    for\
    \ (int d = d0; d < std::min<int>(N + 1, f.size()); ++d) {\n        if (f[d] !=\
    \ T()) nonzero_terms.emplace_back(d - d0, f[d]);\n    }\n\n    int Ncalc = N -\
    \ d0 * k;\n\n    std::vector<T> ret(Ncalc + 1);\n    ret[0] = f[d0].pow(k);\n\
    \    for (int d = 0; d + 1 < int(ret.size()); ++d) {\n        // Compare [x^d](k\
    \ f'g - fg')\n        T tmp = T();\n        int i, j;\n        T fi;\n       \
    \ for (auto i_fi : nonzero_terms) {\n            std::tie(i, fi) = i_fi;\n   \
    \         if (!i) continue;\n            j = d - i;\n            if (0 <= j) tmp\
    \ -= fi * ret[j + 1] * (j + 1);\n            j = d - (i - 1);\n            if\
    \ (0 <= j) tmp += fi * i * ret[j] * T(k);\n        }\n        ret[d + 1] = tmp\
    \ / (f[d0] * (d + 1));\n    }\n\n    ret.resize(N + 1, T());\n    std::rotate(ret.begin(),\
    \ ret.end() - d0 * k, ret.end());\n    return ret;\n}\n"
  code: "#pragma once\n#include <algorithm>\n#include <cassert>\n#include <tuple>\n\
    #include <utility>\n#include <vector>\n\n// Calculate f(x)^k up to x^N\n// Requirement:\
    \ k > 0\n// Complexity: O(NM) (M : num. of nonzero coefficients of f(x))\ntemplate\
    \ <class T> std::vector<T> pow_of_sparse_fps(const std::vector<T> &f, int N, long\
    \ long k) {\n    assert(k > 0);\n    std::vector<std::pair<int, T>> nonzero_terms;\n\
    \    int d0 = 0;\n    while (d0 < int(f.size()) and d0 <= N and f[d0] == T())\
    \ ++d0;\n    if (d0 == int(f.size()) or d0 > N) return std::vector<T>(N + 1);\n\
    \n    if (d0 and N / d0 < k) return std::vector<T>(N + 1);\n\n    for (int d =\
    \ d0; d < std::min<int>(N + 1, f.size()); ++d) {\n        if (f[d] != T()) nonzero_terms.emplace_back(d\
    \ - d0, f[d]);\n    }\n\n    int Ncalc = N - d0 * k;\n\n    std::vector<T> ret(Ncalc\
    \ + 1);\n    ret[0] = f[d0].pow(k);\n    for (int d = 0; d + 1 < int(ret.size());\
    \ ++d) {\n        // Compare [x^d](k f'g - fg')\n        T tmp = T();\n      \
    \  int i, j;\n        T fi;\n        for (auto i_fi : nonzero_terms) {\n     \
    \       std::tie(i, fi) = i_fi;\n            if (!i) continue;\n            j\
    \ = d - i;\n            if (0 <= j) tmp -= fi * ret[j + 1] * (j + 1);\n      \
    \      j = d - (i - 1);\n            if (0 <= j) tmp += fi * i * ret[j] * T(k);\n\
    \        }\n        ret[d + 1] = tmp / (f[d0] * (d + 1));\n    }\n\n    ret.resize(N\
    \ + 1, T());\n    std::rotate(ret.begin(), ret.end() - d0 * k, ret.end());\n \
    \   return ret;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: formal_power_series/pow_of_sparse_fps.hpp
  requiredBy: []
  timestamp: '2022-05-29 00:37:50+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - formal_power_series/test/pow_of_sparse_fps.yuki1939.test.cpp
  - formal_power_series/test/pow_of_sparse_fps.stress.test.cpp
documentation_of: formal_power_series/pow_of_sparse_fps.hpp
layout: document
title: "Power of sparse formal power series \uFF08\u975E\u96F6\u306A\u9805\u304C\u758E\
  \u306A\u5F62\u5F0F\u7684\u51AA\u7D1A\u6570\u306E\u7D2F\u4E57\uFF09"
---

形式的冪級数 $f(x)$ について，$(f(x))^k$ の $x^N$ までの項を $O(NM)$ で計算する．ここで $M$ は $f(x)$ の $N$ 次以下で非零な項の個数．

## ナイーブな説明

$\displaystyle
g(x) = f(x)^k
$

について，両辺 $\log$ をとってから微分することで

$\displaystyle
\frac{g'(x)}{g(x)} = k \frac{f'(x)}{f(x)}
$

を得る．これより

$\displaystyle
f(x) g'(x) = k f'(x) g(x)
$

が成立する．両辺の各項の次数を低い順から順に合わせていけばよい．

## 使用方法

```cpp
vector<mint> f;  // mint は除算が可能でなければならない
long long k;

// f(x)^k を x^N の係数まで計算
vector<mint> g = pow_of_sparse_fps(f, N, k)  // g.size() == N + 1
```

## 問題例

- [No.1939 Numbered Colorful Balls - yukicoder](https://yukicoder.me/problems/no/1939)

## リンク
- [A problem collection of ODE and differential technique - Codeforces](https://codeforces.com/blog/entry/76447)
