---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/hessenberg_system.hpp
    title: Hessenberg linear system
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/test/hessenberg_system.stress.test.cpp
    title: linear_algebra_matrix/test/hessenberg_system.stress.test.cpp
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/test/matrix_det_dual_number.yuki1303.test.cpp
    title: linear_algebra_matrix/test/matrix_det_dual_number.yuki1303.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://atcoder.jp/contests/abc235/tasks/abc235_f
  bundledCode: "#line 2 \"number/dual_number.hpp\"\n#include <type_traits>\n\nnamespace\
    \ dual_number_ {\nstruct has_id_method_impl {\n    template <class T_> static\
    \ auto check(T_ *) -> decltype(T_::id(), std::true_type());\n    template <class\
    \ T_> static auto check(...) -> std::false_type;\n};\ntemplate <class T_> struct\
    \ has_id : decltype(has_id_method_impl::check<T_>(nullptr)) {};\n} // namespace\
    \ dual_number_\n\n// Dual number \uFF08\u4E8C\u91CD\u6570\uFF09\n// Verified:\
    \ https://atcoder.jp/contests/abc235/tasks/abc235_f\ntemplate <class T> struct\
    \ DualNumber {\n    T a, b; // a + bx\n\n    template <typename T2, typename std::enable_if<dual_number_::has_id<T2>::value>::type\
    \ * = nullptr>\n    static T2 _T_id() {\n        return T2::id();\n    }\n   \
    \ template <typename T2, typename std::enable_if<!dual_number_::has_id<T2>::value>::type\
    \ * = nullptr>\n    static T2 _T_id() {\n        return T2(1);\n    }\n\n    DualNumber(T\
    \ x = T(), T y = T()) : a(x), b(y) {}\n    static DualNumber id() { return DualNumber(_T_id<T>(),\
    \ T()); }\n    explicit operator bool() const { return a != T() or b != T(); }\n\
    \    DualNumber operator+(const DualNumber &x) const { return DualNumber(a + x.a,\
    \ b + x.b); }\n    DualNumber operator-(const DualNumber &x) const { return DualNumber(a\
    \ - x.a, b - x.b); }\n    DualNumber operator*(const DualNumber &x) const {\n\
    \        return DualNumber(a * x.a, b * x.a + a * x.b);\n    }\n    DualNumber\
    \ operator/(const DualNumber &x) const {\n        T cinv = _T_id<T>() / x.a;\n\
    \        return DualNumber(a * cinv, (b * x.a - a * x.b) * cinv * cinv);\n   \
    \ }\n    DualNumber operator-() const { return DualNumber(-a, -b); }\n    DualNumber\
    \ &operator+=(const DualNumber &x) { return *this = *this + x; }\n    DualNumber\
    \ &operator-=(const DualNumber &x) { return *this = *this - x; }\n    DualNumber\
    \ &operator*=(const DualNumber &x) { return *this = *this * x; }\n    DualNumber\
    \ &operator/=(const DualNumber &x) { return *this = *this / x; }\n    bool operator==(const\
    \ DualNumber &x) const { return a == x.a and b == x.b; }\n    bool operator!=(const\
    \ DualNumber &x) const { return !(*this == x); }\n    bool operator<(const DualNumber\
    \ &x) const { return (a != x.a ? a < x.a : b < x.b); }\n    template <class OStream>\
    \ friend OStream &operator<<(OStream &os, const DualNumber &x) {\n        return\
    \ os << '{' << x.a << ',' << x.b << '}';\n    }\n\n    T eval(const T &x) const\
    \ { return a + b * x; }\n    T root() const { return (-a) / b; } // Solve a +\
    \ bx = 0 (b \\neq 0 is assumed)\n};\n"
  code: "#pragma once\n#include <type_traits>\n\nnamespace dual_number_ {\nstruct\
    \ has_id_method_impl {\n    template <class T_> static auto check(T_ *) -> decltype(T_::id(),\
    \ std::true_type());\n    template <class T_> static auto check(...) -> std::false_type;\n\
    };\ntemplate <class T_> struct has_id : decltype(has_id_method_impl::check<T_>(nullptr))\
    \ {};\n} // namespace dual_number_\n\n// Dual number \uFF08\u4E8C\u91CD\u6570\uFF09\
    \n// Verified: https://atcoder.jp/contests/abc235/tasks/abc235_f\ntemplate <class\
    \ T> struct DualNumber {\n    T a, b; // a + bx\n\n    template <typename T2,\
    \ typename std::enable_if<dual_number_::has_id<T2>::value>::type * = nullptr>\n\
    \    static T2 _T_id() {\n        return T2::id();\n    }\n    template <typename\
    \ T2, typename std::enable_if<!dual_number_::has_id<T2>::value>::type * = nullptr>\n\
    \    static T2 _T_id() {\n        return T2(1);\n    }\n\n    DualNumber(T x =\
    \ T(), T y = T()) : a(x), b(y) {}\n    static DualNumber id() { return DualNumber(_T_id<T>(),\
    \ T()); }\n    explicit operator bool() const { return a != T() or b != T(); }\n\
    \    DualNumber operator+(const DualNumber &x) const { return DualNumber(a + x.a,\
    \ b + x.b); }\n    DualNumber operator-(const DualNumber &x) const { return DualNumber(a\
    \ - x.a, b - x.b); }\n    DualNumber operator*(const DualNumber &x) const {\n\
    \        return DualNumber(a * x.a, b * x.a + a * x.b);\n    }\n    DualNumber\
    \ operator/(const DualNumber &x) const {\n        T cinv = _T_id<T>() / x.a;\n\
    \        return DualNumber(a * cinv, (b * x.a - a * x.b) * cinv * cinv);\n   \
    \ }\n    DualNumber operator-() const { return DualNumber(-a, -b); }\n    DualNumber\
    \ &operator+=(const DualNumber &x) { return *this = *this + x; }\n    DualNumber\
    \ &operator-=(const DualNumber &x) { return *this = *this - x; }\n    DualNumber\
    \ &operator*=(const DualNumber &x) { return *this = *this * x; }\n    DualNumber\
    \ &operator/=(const DualNumber &x) { return *this = *this / x; }\n    bool operator==(const\
    \ DualNumber &x) const { return a == x.a and b == x.b; }\n    bool operator!=(const\
    \ DualNumber &x) const { return !(*this == x); }\n    bool operator<(const DualNumber\
    \ &x) const { return (a != x.a ? a < x.a : b < x.b); }\n    template <class OStream>\
    \ friend OStream &operator<<(OStream &os, const DualNumber &x) {\n        return\
    \ os << '{' << x.a << ',' << x.b << '}';\n    }\n\n    T eval(const T &x) const\
    \ { return a + b * x; }\n    T root() const { return (-a) / b; } // Solve a +\
    \ bx = 0 (b \\neq 0 is assumed)\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: number/dual_number.hpp
  requiredBy:
  - linear_algebra_matrix/hessenberg_system.hpp
  timestamp: '2025-05-06 21:03:53+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - linear_algebra_matrix/test/hessenberg_system.stress.test.cpp
  - linear_algebra_matrix/test/matrix_det_dual_number.yuki1303.test.cpp
documentation_of: number/dual_number.hpp
layout: document
title: "Dual number \uFF08\u4E8C\u91CD\u6570\uFF09"
---

二重数 `DualNumber<T>` の実装．直感的には $x$ の一次の係数まで常に保持する形式的冪級数と等価．

総和を DP で求めさせる問題で頻出する
```cpp
vector<T> dp0, dp1, dpnxt0, dpnxt1;
dpnxt1[inxt] += dp1[i] * a;
dpnxt1[inxt] += dp0[i] * b;
dpnxt0[inxt] += dp0[i] * a;
```
のような遷移について，`T` 上の二重数を導入すると
```cpp
using TT = DualNumber<T>;
vector<TT> dp, dpnxt;
dpnxt[inxt] += dp[i] * TT(a, b);
```
のように書けて楽．


## 問題例

- [AtCoder Beginner Contest 235 F - Variety of Digits](https://atcoder.jp/contests/abc235/tasks/abc235_f)
- [No.1303 Inconvenient Kingdom - yukicoder](https://yukicoder.me/problems/no/1303)
