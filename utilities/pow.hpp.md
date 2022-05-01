---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: utilities/test/pow.test.cpp
    title: utilities/test/pow.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 2 \"utilities/pow.hpp\"\n\ntemplate <typename T, typename Int>\
    \ T pow(T x, Int n) {\n    T ans = 1;\n    while (n) {\n        if (n & 1) ans\
    \ *= x;\n        x *= x;\n        n >>= 1;\n    }\n    return ans;\n}\n"
  code: "#pragma once\n\ntemplate <typename T, typename Int> T pow(T x, Int n) {\n\
    \    T ans = 1;\n    while (n) {\n        if (n & 1) ans *= x;\n        x *= x;\n\
    \        n >>= 1;\n    }\n    return ans;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/pow.hpp
  requiredBy: []
  timestamp: '2021-08-01 20:22:45+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - utilities/test/pow.test.cpp
documentation_of: utilities/pow.hpp
layout: document
title: "Power \uFF08\u7D2F\u4E57\uFF09"
---

繰り返し二乗法で $x^n$ を計算．計算量は $O(\log n)$．
