---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: utilities/test/quotients.test.cpp
    title: utilities/test/quotients.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"utilities/quotients.hpp\"\n#include <algorithm>\n#include\
    \ <vector>\n\n// Generate all quotients of n\n// return: n/1, n/2, ..., n\n//\
    \ Complexity: O(sqrt(n))\ntemplate <class T = long long> std::vector<T> get_quotients(T\
    \ n) {\n    std::vector<T> res;\n    for (T x = 1;; ++x) {\n        if (x * x\
    \ >= n) {\n            const int sz = res.size();\n            if (x * x == n)\
    \ res.push_back(x);\n            res.reserve(res.size() + sz);\n            for\
    \ (int i = sz - 1; i >= 0; --i) {\n                T tmp = n / res.at(i);\n  \
    \              if (tmp < x) continue;\n                if (tmp == x and tmp *\
    \ tmp == n) continue;\n                res.push_back(tmp);\n            }\n  \
    \          return res;\n        } else {\n            res.push_back(x);\n    \
    \    }\n    }\n}\n"
  code: "#pragma once\n#include <algorithm>\n#include <vector>\n\n// Generate all\
    \ quotients of n\n// return: n/1, n/2, ..., n\n// Complexity: O(sqrt(n))\ntemplate\
    \ <class T = long long> std::vector<T> get_quotients(T n) {\n    std::vector<T>\
    \ res;\n    for (T x = 1;; ++x) {\n        if (x * x >= n) {\n            const\
    \ int sz = res.size();\n            if (x * x == n) res.push_back(x);\n      \
    \      res.reserve(res.size() + sz);\n            for (int i = sz - 1; i >= 0;\
    \ --i) {\n                T tmp = n / res.at(i);\n                if (tmp < x)\
    \ continue;\n                if (tmp == x and tmp * tmp == n) continue;\n    \
    \            res.push_back(tmp);\n            }\n            return res;\n   \
    \     } else {\n            res.push_back(x);\n        }\n    }\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/quotients.hpp
  requiredBy: []
  timestamp: '2023-12-26 22:24:23+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - utilities/test/quotients.test.cpp
documentation_of: utilities/quotients.hpp
layout: document
title: "Quotients of integer \uFF08\u5546\u5217\u6319\uFF09"
---

正の整数 $n$ に対して $\lfloor n / k \rfloor$ （ $k$ は整数）の形で表される整数を昇順に列挙する．計算量は $O(\sqrt{n})$.

## 使用方法

```cpp
long long n = 10;
vector<long long> v = get_quotients(n);  // 1, 2, 3, 5, 10
```

## 問題例

- [Library Checker: Enumerate Quotients](https://judge.yosupo.jp/problem/enumerate_quotients)
