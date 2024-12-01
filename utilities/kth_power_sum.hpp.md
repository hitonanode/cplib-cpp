---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: utilities/test/kth_power_sum.yuki665.test.cpp
    title: utilities/test/kth_power_sum.yuki665.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"utilities/kth_power_sum.hpp\"\n#include <vector>\n\n// Computes\
    \ the sum of the k-th powers\n// Complexity:\n// - O(k) per query,\n// - O(k^2)\
    \ precomputation (can be reduced to O(k log k) with FFT)\ntemplate <class MODINT>\
    \ struct kth_power_sum {\n\n    // generating function:  x / (e^x - 1) + x\n \
    \   // NOTE: use B(1) = 1/2 definition\n    std::vector<MODINT> bernoulli;\n\n\
    \    kth_power_sum() = default;\n\n    void expand() {\n        if (bernoulli.empty())\
    \ {\n            bernoulli = {1};\n        } else {\n            const int k =\
    \ bernoulli.size();\n            MODINT x(0);\n            for (int i = 0; i <\
    \ k; ++i) { x = -x + bernoulli[i] * MODINT::binom(k + 1, i); }\n            bernoulli.push_back(x\
    \ / (k + 1));\n        }\n    }\n\n    // Calculate 1^k + 2^k + ... + n^k\n  \
    \  // Based on Faulhaber's formula:\n    // S_k(n) = 1 / (k + 1) * sum_{j=0}^{k}\
    \ B_j * C(k + 1, j) * n^(k + 1 - j)\n\n    template <class T> MODINT prefix_sum(int\
    \ k, const T &n) {\n        while ((int)bernoulli.size() <= k) expand();\n\n \
    \       MODINT ret(0), np(1);\n        for (int j = k; j >= 0; --j) {\n      \
    \      np *= n;\n            ret += MODINT::binom(k + 1, j) * bernoulli[j] * np;\n\
    \        }\n        return ret / (k + 1);\n    }\n};\n"
  code: "#pragma once\n#include <vector>\n\n// Computes the sum of the k-th powers\n\
    // Complexity:\n// - O(k) per query,\n// - O(k^2) precomputation (can be reduced\
    \ to O(k log k) with FFT)\ntemplate <class MODINT> struct kth_power_sum {\n\n\
    \    // generating function:  x / (e^x - 1) + x\n    // NOTE: use B(1) = 1/2 definition\n\
    \    std::vector<MODINT> bernoulli;\n\n    kth_power_sum() = default;\n\n    void\
    \ expand() {\n        if (bernoulli.empty()) {\n            bernoulli = {1};\n\
    \        } else {\n            const int k = bernoulli.size();\n            MODINT\
    \ x(0);\n            for (int i = 0; i < k; ++i) { x = -x + bernoulli[i] * MODINT::binom(k\
    \ + 1, i); }\n            bernoulli.push_back(x / (k + 1));\n        }\n    }\n\
    \n    // Calculate 1^k + 2^k + ... + n^k\n    // Based on Faulhaber's formula:\n\
    \    // S_k(n) = 1 / (k + 1) * sum_{j=0}^{k} B_j * C(k + 1, j) * n^(k + 1 - j)\n\
    \n    template <class T> MODINT prefix_sum(int k, const T &n) {\n        while\
    \ ((int)bernoulli.size() <= k) expand();\n\n        MODINT ret(0), np(1);\n  \
    \      for (int j = k; j >= 0; --j) {\n            np *= n;\n            ret +=\
    \ MODINT::binom(k + 1, j) * bernoulli[j] * np;\n        }\n        return ret\
    \ / (k + 1);\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/kth_power_sum.hpp
  requiredBy: []
  timestamp: '2024-12-02 06:13:59+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - utilities/test/kth_power_sum.yuki665.test.cpp
documentation_of: utilities/kth_power_sum.hpp
layout: document
title: "Sum of $k$-th powers of first $n$ positive integers \uFF08\u81EA\u7136\u6570\
  \u306E $k$ \u4E57\u548C\uFF09"
---

「 $1$ 以上 $n$ 以下の自然数の $k$ 乗の総和」を Faulhaber の公式を用いて計算する．

内部で Bernoulli 数の先頭 $k + 1$ 項を計算する必要がある．このコードでは `prefix_sum()` メンバ関数が呼ばれた時点で動的に不足している部分を計算し， $\Theta(k^2)$ で動く．より高速にする必要があれば，母関数 $x / (\exp(x) - 1) + x$ （第 1 項の定義に $+1/2$ を採用している点に注意）の冪級数展開を FFT 等で計算してメンバ変数 `bernoulli` に事前に設定しておけばよい．

## 使用方法

```cpp
using mint = ModInt<998244353>;
kth_power_sum<mint> kp;

int k = 1;
long long n = 10;

auto sum = kp.prefix_sum(k, n);  // 1^k + ... + n^k

assert(sum == mint(55));
```

## 問題例

- [No.665 Bernoulli Bernoulli - yukicoder](https://yukicoder.me/problems/no/665)
- [Educational Codeforces Round 7 F. The Sum of the k-th Powers - Codeforces](https://codeforces.com/contest/622/problem/F)
