---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: number/test/gcd_of_gaussian_integers.test.cpp
    title: number/test/gcd_of_gaussian_integers.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"number/gaussian_integer.hpp\"\n#include <cassert>\n#include\
    \ <utility>\n\nstruct GaussianInteger {\n    using Int = long long;\n    using\
    \ G = GaussianInteger;\n    Int x, y; // x + yi\n\n    Int re() const noexcept\
    \ { return x; }\n    Int im() const noexcept { return y; }\n\n    explicit GaussianInteger(Int\
    \ x_ = 0, Int y_ = 0) : x(x_), y(y_) {}\n\n    G &operator+=(const G &n) {\n \
    \       x += n.x, y += n.y;\n        return *this;\n    }\n    G &operator-=(const\
    \ G &n) {\n        x -= n.x, y -= n.y;\n        return *this;\n    }\n    G &operator*=(const\
    \ G &n) {\n        const Int nx = x * n.x - y * n.y, ny = x * n.y + y * n.x;\n\
    \        x = nx, y = ny;\n        return *this;\n    }\n\n    // Euclidean division\n\
    \    G &operator/=(const G &n) {\n        const Int d = n.norm();\n        assert(d\
    \ != 0);\n        const Int nx = x * n.x + y * n.y, ny = y * n.x - x * n.y;\n\
    \        auto div_round = [](Int num, Int den) {\n            return (num >= 0)\
    \ ? (num + den / 2) / den : (num - den / 2) / den;\n        };\n        x = div_round(nx,\
    \ d), y = div_round(ny, d);\n        return *this;\n    }\n\n    G &operator%=(const\
    \ G &n) {\n        *this -= (*this / n) * n;\n        return *this;\n    }\n\n\
    \    G operator+(const G &n) const { return G(*this) += n; }\n    G operator-(const\
    \ G &n) const { return G(*this) -= n; }\n    G operator*(const G &n) const { return\
    \ G(*this) *= n; }\n    G operator/(const G &n) const { return G(*this) /= n;\
    \ }\n    G operator%(const G &n) const { return G(*this) %= n; }\n\n    Int norm()\
    \ const { return x * x + y * y; }\n\n    G conj() const { return G{x, -y}; }\n\
    \n    static G gcd(G a, G b) {\n        while (b.x != 0 or b.y != 0) {\n     \
    \       a %= b;\n            std::swap(a, b);\n        }\n        return a.canonical();\n\
    \    }\n    friend G gcd(G a, G b) { return G::gcd(a, b); }\n\n    bool operator==(const\
    \ G &n) const { return x == n.x and y == n.y; }\n    bool operator!=(const G &n)\
    \ const { return !(*this == n); }\n\n    template <class OStream> friend OStream\
    \ &operator<<(OStream &os, const G &g) {\n        return os << g.x << (g.y >=\
    \ 0 ? \"+\" : \"\") << g.y << \"i\";\n    }\n\n    // move to first quadrant (x\
    \ > 0, y >= 0)\n    G canonical() const {\n        if (x > 0 and y >= 0) return\
    \ *this;\n        if (x <= 0 and y > 0) return G{y, -x};\n        if (x < 0 and\
    \ y <= 0) return G{-x, -y};\n        return G{-y, x};\n    }\n\n    std::pair<Int,\
    \ Int> to_pair() const { return {x, y}; }\n};\n"
  code: "#pragma once\n#include <cassert>\n#include <utility>\n\nstruct GaussianInteger\
    \ {\n    using Int = long long;\n    using G = GaussianInteger;\n    Int x, y;\
    \ // x + yi\n\n    Int re() const noexcept { return x; }\n    Int im() const noexcept\
    \ { return y; }\n\n    explicit GaussianInteger(Int x_ = 0, Int y_ = 0) : x(x_),\
    \ y(y_) {}\n\n    G &operator+=(const G &n) {\n        x += n.x, y += n.y;\n \
    \       return *this;\n    }\n    G &operator-=(const G &n) {\n        x -= n.x,\
    \ y -= n.y;\n        return *this;\n    }\n    G &operator*=(const G &n) {\n \
    \       const Int nx = x * n.x - y * n.y, ny = x * n.y + y * n.x;\n        x =\
    \ nx, y = ny;\n        return *this;\n    }\n\n    // Euclidean division\n   \
    \ G &operator/=(const G &n) {\n        const Int d = n.norm();\n        assert(d\
    \ != 0);\n        const Int nx = x * n.x + y * n.y, ny = y * n.x - x * n.y;\n\
    \        auto div_round = [](Int num, Int den) {\n            return (num >= 0)\
    \ ? (num + den / 2) / den : (num - den / 2) / den;\n        };\n        x = div_round(nx,\
    \ d), y = div_round(ny, d);\n        return *this;\n    }\n\n    G &operator%=(const\
    \ G &n) {\n        *this -= (*this / n) * n;\n        return *this;\n    }\n\n\
    \    G operator+(const G &n) const { return G(*this) += n; }\n    G operator-(const\
    \ G &n) const { return G(*this) -= n; }\n    G operator*(const G &n) const { return\
    \ G(*this) *= n; }\n    G operator/(const G &n) const { return G(*this) /= n;\
    \ }\n    G operator%(const G &n) const { return G(*this) %= n; }\n\n    Int norm()\
    \ const { return x * x + y * y; }\n\n    G conj() const { return G{x, -y}; }\n\
    \n    static G gcd(G a, G b) {\n        while (b.x != 0 or b.y != 0) {\n     \
    \       a %= b;\n            std::swap(a, b);\n        }\n        return a.canonical();\n\
    \    }\n    friend G gcd(G a, G b) { return G::gcd(a, b); }\n\n    bool operator==(const\
    \ G &n) const { return x == n.x and y == n.y; }\n    bool operator!=(const G &n)\
    \ const { return !(*this == n); }\n\n    template <class OStream> friend OStream\
    \ &operator<<(OStream &os, const G &g) {\n        return os << g.x << (g.y >=\
    \ 0 ? \"+\" : \"\") << g.y << \"i\";\n    }\n\n    // move to first quadrant (x\
    \ > 0, y >= 0)\n    G canonical() const {\n        if (x > 0 and y >= 0) return\
    \ *this;\n        if (x <= 0 and y > 0) return G{y, -x};\n        if (x < 0 and\
    \ y <= 0) return G{-x, -y};\n        return G{-y, x};\n    }\n\n    std::pair<Int,\
    \ Int> to_pair() const { return {x, y}; }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: number/gaussian_integer.hpp
  requiredBy: []
  timestamp: '2026-03-01 20:50:35+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - number/test/gcd_of_gaussian_integers.test.cpp
documentation_of: number/gaussian_integer.hpp
layout: document
title: "Gaussian Integer \uFF08\u30AC\u30A6\u30B9\u6574\u6570\uFF09"
---

ガウス整数を扱う．

## 問題例

- [Library Checker: Gcd of Gaussian Integers](https://judge.yosupo.jp/problem/gcd_of_gaussian_integers)
