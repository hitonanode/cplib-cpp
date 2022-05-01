---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"utilities/pow_op.hpp\"\n#include <cassert>\n\n// Calculate\
    \ x^n\ntemplate <class S, S (*op)(S, S)> S pow_op(S x, long long n) {\n    assert(n\
    \ > 0);\n    S ans = x;\n    --n;\n    while (n) {\n        if (n & 1) ans = op(ans,\
    \ x);\n        x = op(x, x);\n        n >>= 1;\n    }\n    return ans;\n}\n"
  code: "#pragma once\n#include <cassert>\n\n// Calculate x^n\ntemplate <class S,\
    \ S (*op)(S, S)> S pow_op(S x, long long n) {\n    assert(n > 0);\n    S ans =\
    \ x;\n    --n;\n    while (n) {\n        if (n & 1) ans = op(ans, x);\n      \
    \  x = op(x, x);\n        n >>= 1;\n    }\n    return ans;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/pow_op.hpp
  requiredBy: []
  timestamp: '2022-05-01 23:43:19+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utilities/pow_op.hpp
layout: document
title: Power (general monoid)
---

一般のモノイドの元 $x$ について繰り返し二乗法で $x^k$ を計算．単位元を必要としない構成にしたため，$k = 0$ はエラーとなることに注意．計算量は $O(\log n)$．

## 使用方法

数論関数の $k$ 乗（の先頭の数項）を計算したい場合：

```cpp
vector<mint> op(vector<mint> l, vector<mint> r) {
    S ret(l.size());
    for (int i = 1; i < int(l.size()); ++i) {
        for (int j = 1; i * j < int(l.size()); ++j) ret[i * j] += l[i] * r[j];
    }
    return ret;
}

vector<mint> f;
long long k;
f = pow_op<decltype(f), op>(f, k);
```
