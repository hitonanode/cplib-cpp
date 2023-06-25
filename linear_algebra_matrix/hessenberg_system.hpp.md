---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: number/dual_number.hpp
    title: "Dual number \uFF08\u4E8C\u91CD\u6570\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/test/hessenberg_system.stress.test.cpp
    title: linear_algebra_matrix/test/hessenberg_system.stress.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://atcoder.jp/contests/abc249/tasks/abc249_h
  bundledCode: "#line 1 \"number/dual_number.hpp\"\n#include <type_traits>\n\nnamespace\
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
    \ bx = 0 (b \\neq 0 is assumed)\n};\n#line 3 \"linear_algebra_matrix/hessenberg_system.hpp\"\
    \n#include <algorithm>\n#include <cassert>\n#include <vector>\n\n// Solve Ax =\
    \ b, where A is n x n (square), lower Hessenberg, and non-singular.\n// Complexity:\
    \ O(n^2)\n// Verified: https://atcoder.jp/contests/abc249/tasks/abc249_h\ntemplate\
    \ <class T>\nstd::vector<T>\nsolve_lower_hessenberg(const std::vector<std::vector<T>>\
    \ &A, const std::vector<T> &b) {\n    const int N = A.size();\n    if (!N) return\
    \ {};\n    assert(int(A[0].size()) == N and int(b.size()) == N);\n\n    using\
    \ dual = DualNumber<T>;\n    std::vector<dual> sol(N);\n    for (int h = 0; h\
    \ < N;) {\n        sol[h] = dual(0, 1);\n        for (int i = h;; ++i) {\n   \
    \         dual y = b[i];\n            for (int j = 0; j <= i; ++j) y -= sol[j]\
    \ * A[i][j];\n            T a = i + 1 < N ? A[i][i + 1] : T();\n            if\
    \ (a == T()) {\n                T x0 = y.root();\n                while (h <=\
    \ i) sol[h] = sol[h].eval(x0), ++h;\n                break;\n            } else\
    \ {\n                sol[i + 1] = y / a;\n            }\n        }\n    }\n  \
    \  std::vector<T> ret(N);\n    for (int i = 0; i < N; ++i) ret[i] = sol[i].a;\n\
    \    return ret;\n}\n\n// Solve Ax = b, where A is n x n (square), upper Hessenberg,\
    \ and non-singular\n// Complexity: O(n^2)\ntemplate <class T>\nstd::vector<T>\
    \ solve_upper_hessenberg(std::vector<std::vector<T>> A, std::vector<T> b) {\n\
    \    std::reverse(A.begin(), A.end());\n    for (auto &v : A) std::reverse(v.begin(),\
    \ v.end());\n    std::reverse(b.begin(), b.end());\n    auto ret = solve_lower_hessenberg(A,\
    \ b);\n    std::reverse(ret.begin(), ret.end());\n    return ret;\n}\n"
  code: "#pragma once\n#include \"../number/dual_number.hpp\"\n#include <algorithm>\n\
    #include <cassert>\n#include <vector>\n\n// Solve Ax = b, where A is n x n (square),\
    \ lower Hessenberg, and non-singular.\n// Complexity: O(n^2)\n// Verified: https://atcoder.jp/contests/abc249/tasks/abc249_h\n\
    template <class T>\nstd::vector<T>\nsolve_lower_hessenberg(const std::vector<std::vector<T>>\
    \ &A, const std::vector<T> &b) {\n    const int N = A.size();\n    if (!N) return\
    \ {};\n    assert(int(A[0].size()) == N and int(b.size()) == N);\n\n    using\
    \ dual = DualNumber<T>;\n    std::vector<dual> sol(N);\n    for (int h = 0; h\
    \ < N;) {\n        sol[h] = dual(0, 1);\n        for (int i = h;; ++i) {\n   \
    \         dual y = b[i];\n            for (int j = 0; j <= i; ++j) y -= sol[j]\
    \ * A[i][j];\n            T a = i + 1 < N ? A[i][i + 1] : T();\n            if\
    \ (a == T()) {\n                T x0 = y.root();\n                while (h <=\
    \ i) sol[h] = sol[h].eval(x0), ++h;\n                break;\n            } else\
    \ {\n                sol[i + 1] = y / a;\n            }\n        }\n    }\n  \
    \  std::vector<T> ret(N);\n    for (int i = 0; i < N; ++i) ret[i] = sol[i].a;\n\
    \    return ret;\n}\n\n// Solve Ax = b, where A is n x n (square), upper Hessenberg,\
    \ and non-singular\n// Complexity: O(n^2)\ntemplate <class T>\nstd::vector<T>\
    \ solve_upper_hessenberg(std::vector<std::vector<T>> A, std::vector<T> b) {\n\
    \    std::reverse(A.begin(), A.end());\n    for (auto &v : A) std::reverse(v.begin(),\
    \ v.end());\n    std::reverse(b.begin(), b.end());\n    auto ret = solve_lower_hessenberg(A,\
    \ b);\n    std::reverse(ret.begin(), ret.end());\n    return ret;\n}\n"
  dependsOn:
  - number/dual_number.hpp
  isVerificationFile: false
  path: linear_algebra_matrix/hessenberg_system.hpp
  requiredBy: []
  timestamp: '2022-04-30 23:36:43+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - linear_algebra_matrix/test/hessenberg_system.stress.test.cpp
documentation_of: linear_algebra_matrix/hessenberg_system.hpp
layout: document
title: Hessenberg linear system
---

体上の $n \times n$ 正則 Hessenberg 行列 $\mathbf{A}$ と $n$ 次元ベクトル $b$ に対して，線形方程式系 $\mathbf{A} \mathbf{x} = \mathbf{b}$ を解く．計算量は $O(n^2)$．

## 使用方法

```cpp
vector<vector<mint>> A(N, vector<mint>(N));
vector<mint> b(N);

// A: lower Hessenberg, regular
vector<mint> x = solve_lower_hessenberg(A, b);

// A: upper Hessenberg, regular
vector<mint> x = solve_upper_hessenberg(A, b);
```

## 問題例

- [AtCoder Beginner Contest 249 Ex - Dye Color](https://atcoder.jp/contests/abc249/tasks/abc249_h)
