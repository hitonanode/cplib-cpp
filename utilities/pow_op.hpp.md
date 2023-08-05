---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: utilities/test/pow_op.test.cpp
    title: utilities/test/pow_op.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"utilities/pow_op.hpp\"\n#include <cassert>\n\n// Calculate\
    \ x^n\ntemplate <class S, class F> S pow_op(S x, long long n, F op) {\n    assert(n\
    \ > 0);\n    S ans = x;\n    --n;\n    while (n) {\n        if (n & 1) ans = op(ans,\
    \ x);\n        x = op(x, x);\n        n >>= 1;\n    }\n    return ans;\n}\n"
  code: "#pragma once\n#include <cassert>\n\n// Calculate x^n\ntemplate <class S,\
    \ class F> S pow_op(S x, long long n, F op) {\n    assert(n > 0);\n    S ans =\
    \ x;\n    --n;\n    while (n) {\n        if (n & 1) ans = op(ans, x);\n      \
    \  x = op(x, x);\n        n >>= 1;\n    }\n    return ans;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/pow_op.hpp
  requiredBy: []
  timestamp: '2023-08-05 12:13:51+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - utilities/test/pow_op.test.cpp
documentation_of: utilities/pow_op.hpp
layout: document
title: Power (general monoid)
---

一般のモノイドの元 $x$ について繰り返し二乗法で $x^n$ を計算．単位元が不要な設計としたため，$n = 0$ はエラーとなることに注意．計算量は $O(\log n)$．

## 使用方法

### 例 1: $\bmod{x^k - m}$ で多項式 $f(x)$ の $n$ 乗を計算したい場合

```cpp
auto trun = [&](vector<mint> &vec) {
    while (vec.size() > k) {
        vec.at(vec.size() - 1 - k) += vec.back() * m;
        vec.pop_back();
    }
};

auto op = [&](vector<mint> l, const vector<mint> &r) {
    l = nttconv(l, r);
    trun(l);
    return l;
};

vector<mint> f;

f = pow_op(f, n, op);
```

### 例 2: 数論関数の $n$ 乗（の先頭の数項）を計算したい場合

```cpp
vector<mint> op(vector<mint> l, vector<mint> r) {
    S ret(l.size());
    for (int i = 1; i < int(l.size()); ++i) {
        for (int j = 1; i * j < int(l.size()); ++j) ret[i * j] += l[i] * r[j];
    }
    return ret;
}

vector<mint> f;
long long n;
f = pow_op(f, n, op);
```

## 問題例

- [No.2396 等差二項展開 - yukicoder](https://yukicoder.me/problems/no/2396)
