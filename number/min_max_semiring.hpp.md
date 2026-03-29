---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/test/linalg_semirings.yuki1340.test.cpp
    title: linear_algebra_matrix/test/linalg_semirings.yuki1340.test.cpp
  - icon: ':heavy_check_mark:'
    path: number/test/min_max_semiring.test.cpp
    title: number/test/min_max_semiring.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"number/min_max_semiring.hpp\"\n#include <limits>\n\n// min-max\
    \ \u534A\u74B0\uFF08\u52A0\u6CD5\u304C min, \u4E57\u6CD5\u304C max, \u96F6\u5143\
    \u304C INF, \u5358\u4F4D\u5143\u304C -INF\uFF09\n// Verified: abc236g, abc388f\n\
    template <class T> struct min_max_semiring {\n    T val;\n    min_max_semiring()\
    \ : val(std::numeric_limits<T>::max()) {\n        static_assert(std::numeric_limits<T>::max()\
    \ > 0,\n                      \"std::numeric_limits<>::max() must be properly\
    \ defined\");\n    }\n    min_max_semiring(T x) : val(x) {}\n    static min_max_semiring\
    \ id() { return T(std::numeric_limits<T>::min()); }\n    static min_max_semiring\
    \ max() { return T(); }\n    min_max_semiring operator+(const min_max_semiring\
    \ &r) const {\n        return (this->val > r.val ? r.val : this->val);\n    }\n\
    \    min_max_semiring &operator+=(const min_max_semiring &r) { return *this =\
    \ *this + r; }\n    min_max_semiring operator*(const min_max_semiring &r) const\
    \ {\n        return (this->val < r.val ? r.val : this->val);\n    }\n    min_max_semiring\
    \ &operator*=(const min_max_semiring &r) { return *this = *this * r; }\n    bool\
    \ operator==(const min_max_semiring &r) const { return this->val == r.val; }\n\
    \    bool operator!=(const min_max_semiring &r) const { return !(*this == r);\
    \ }\n    bool operator<(const min_max_semiring &r) const { return this->val <\
    \ r.val; }\n    bool operator>(const min_max_semiring &r) const { return this->val\
    \ > r.val; }\n    bool operator<=(const min_max_semiring &r) const { return this->val\
    \ <= r.val; }\n    bool operator>=(const min_max_semiring &r) const { return this->val\
    \ >= r.val; }\n    template <class OStream> friend OStream &operator<<(OStream\
    \ &os, const min_max_semiring &x) {\n        return os << x.val;\n    }\n};\n"
  code: "#pragma once\n#include <limits>\n\n// min-max \u534A\u74B0\uFF08\u52A0\u6CD5\
    \u304C min, \u4E57\u6CD5\u304C max, \u96F6\u5143\u304C INF, \u5358\u4F4D\u5143\
    \u304C -INF\uFF09\n// Verified: abc236g, abc388f\ntemplate <class T> struct min_max_semiring\
    \ {\n    T val;\n    min_max_semiring() : val(std::numeric_limits<T>::max()) {\n\
    \        static_assert(std::numeric_limits<T>::max() > 0,\n                  \
    \    \"std::numeric_limits<>::max() must be properly defined\");\n    }\n    min_max_semiring(T\
    \ x) : val(x) {}\n    static min_max_semiring id() { return T(std::numeric_limits<T>::min());\
    \ }\n    static min_max_semiring max() { return T(); }\n    min_max_semiring operator+(const\
    \ min_max_semiring &r) const {\n        return (this->val > r.val ? r.val : this->val);\n\
    \    }\n    min_max_semiring &operator+=(const min_max_semiring &r) { return *this\
    \ = *this + r; }\n    min_max_semiring operator*(const min_max_semiring &r) const\
    \ {\n        return (this->val < r.val ? r.val : this->val);\n    }\n    min_max_semiring\
    \ &operator*=(const min_max_semiring &r) { return *this = *this * r; }\n    bool\
    \ operator==(const min_max_semiring &r) const { return this->val == r.val; }\n\
    \    bool operator!=(const min_max_semiring &r) const { return !(*this == r);\
    \ }\n    bool operator<(const min_max_semiring &r) const { return this->val <\
    \ r.val; }\n    bool operator>(const min_max_semiring &r) const { return this->val\
    \ > r.val; }\n    bool operator<=(const min_max_semiring &r) const { return this->val\
    \ <= r.val; }\n    bool operator>=(const min_max_semiring &r) const { return this->val\
    \ >= r.val; }\n    template <class OStream> friend OStream &operator<<(OStream\
    \ &os, const min_max_semiring &x) {\n        return os << x.val;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: number/min_max_semiring.hpp
  requiredBy: []
  timestamp: '2025-05-06 21:03:53+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - linear_algebra_matrix/test/linalg_semirings.yuki1340.test.cpp
  - number/test/min_max_semiring.test.cpp
documentation_of: number/min_max_semiring.hpp
layout: document
title: "Min-max semiring\uFF08(min, max) \u534A\u74B0\uFF09"
---

加法を `min`，乗法を `max` で定義した半環．零元は `std::numeric_limits<T>::max()`、単位元は `std::numeric_limits<T>::min()` となっていることに注意．例えば距離行列に載せて行列積をとることで，パス上の最大重みの最小化等に使用できる．

## 問題例

- [AtCoder Beginner Contest 236 G - Good Vertices](https://atcoder.jp/contests/abc236/tasks/abc236_g)
- - [No.1340 おーじ君をさがせ - yukicoder](https://yukicoder.me/problems/no/1340)
