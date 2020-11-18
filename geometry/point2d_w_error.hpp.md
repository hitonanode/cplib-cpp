---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"geometry/point2d_w_error.hpp\"\n#include <cmath>\n#include\
    \ <iostream>\n#include <utility>\n\ntemplate <typename T_P> struct P {\n    static\
    \ T_P EPS;\n    static void set_eps(T_P e) { EPS = e; }\n    T_P x, y;\n    P()\
    \ : x(0), y(0) {}\n    P(T_P x, T_P y) : x(x), y(y) {}\n    P(std::pair<T_P, T_P>\
    \ p) : x(p.first), y(p.second) {}\n    static T_P add_w_error(T_P a, T_P b) noexcept\
    \ { return (std::abs(a + b) < P::EPS * (std::abs(a) + std::abs(b))) ? 0 : a +\
    \ b; }\n    P operator+(const P &p) const noexcept { return P(add_w_error(x, p.x),\
    \ add_w_error(y, p.y)); }\n    P operator-(const P &p) const noexcept { return\
    \ P(add_w_error(x, -p.x), add_w_error(y, -p.y)); }\n    P operator*(const P &p)\
    \ const noexcept { return P(add_w_error(x * p.x, -y * p.y), add_w_error(x * p.y,\
    \ y * p.x)); }\n    P operator*(T_P d) const noexcept { return P(x * d, y * d);\
    \ }\n    P operator/(T_P d) const noexcept { return P(x / d, y / d); }\n    P\
    \ inv() const { return conj() / norm2(); }\n    P operator/(const P &p) const\
    \ { return (*this) * p.inv(); }\n    bool operator<(const P &r) const noexcept\
    \ { return x != r.x ? x < r.x : y < r.y; }\n    bool operator==(const P &r) const\
    \ noexcept { return add_w_error(x, -r.x) == 0 and add_w_error(y, -r.y) == 0; }\n\
    \    bool operator!=(const P &r) const noexcept { return !((*this) == r); }\n\
    \    T_P dot(P p) const noexcept { return add_w_error(x * p.x, y * p.y); }\n \
    \   T_P det(P p) const noexcept { return add_w_error(x * p.y, -y * p.x); }\n \
    \   T_P norm() const noexcept { return std::sqrt(x * x + y * y); }\n    T_P norm2()\
    \ const noexcept { return x * x + y * y; }\n    T_P arg() const noexcept { return\
    \ std::atan2(y, x); }\n    // rotate point/vector by rad\n    P rotate(T_P rad)\
    \ noexcept { return P(add_w_error(x * std::cos(rad), -y * std::sin(rad)), add_w_error(x\
    \ * std::sin(rad), y * std::cos(rad))); }\n    P normalized() const { return (*this)\
    \ / this->norm(); }\n    P conj() const noexcept { return P(x, -y); }\n    friend\
    \ std::istream &operator>>(std::istream &is, P &p) {\n        T_P x, y;\n    \
    \    is >> x >> y;\n        p = P(x, y);\n        return is;\n    }\n    friend\
    \ std::ostream &operator<<(std::ostream &os, const P &p) {\n        os << '('\
    \ << p.x << ',' << p.y << ')';\n        return os;\n    }\n};\ntemplate <> double\
    \ P<double>::EPS = 1e-9;\ntemplate <> long double P<long double>::EPS = 1e-12;\n"
  code: "#pragma once\n#include <cmath>\n#include <iostream>\n#include <utility>\n\
    \ntemplate <typename T_P> struct P {\n    static T_P EPS;\n    static void set_eps(T_P\
    \ e) { EPS = e; }\n    T_P x, y;\n    P() : x(0), y(0) {}\n    P(T_P x, T_P y)\
    \ : x(x), y(y) {}\n    P(std::pair<T_P, T_P> p) : x(p.first), y(p.second) {}\n\
    \    static T_P add_w_error(T_P a, T_P b) noexcept { return (std::abs(a + b) <\
    \ P::EPS * (std::abs(a) + std::abs(b))) ? 0 : a + b; }\n    P operator+(const\
    \ P &p) const noexcept { return P(add_w_error(x, p.x), add_w_error(y, p.y)); }\n\
    \    P operator-(const P &p) const noexcept { return P(add_w_error(x, -p.x), add_w_error(y,\
    \ -p.y)); }\n    P operator*(const P &p) const noexcept { return P(add_w_error(x\
    \ * p.x, -y * p.y), add_w_error(x * p.y, y * p.x)); }\n    P operator*(T_P d)\
    \ const noexcept { return P(x * d, y * d); }\n    P operator/(T_P d) const noexcept\
    \ { return P(x / d, y / d); }\n    P inv() const { return conj() / norm2(); }\n\
    \    P operator/(const P &p) const { return (*this) * p.inv(); }\n    bool operator<(const\
    \ P &r) const noexcept { return x != r.x ? x < r.x : y < r.y; }\n    bool operator==(const\
    \ P &r) const noexcept { return add_w_error(x, -r.x) == 0 and add_w_error(y, -r.y)\
    \ == 0; }\n    bool operator!=(const P &r) const noexcept { return !((*this) ==\
    \ r); }\n    T_P dot(P p) const noexcept { return add_w_error(x * p.x, y * p.y);\
    \ }\n    T_P det(P p) const noexcept { return add_w_error(x * p.y, -y * p.x);\
    \ }\n    T_P norm() const noexcept { return std::sqrt(x * x + y * y); }\n    T_P\
    \ norm2() const noexcept { return x * x + y * y; }\n    T_P arg() const noexcept\
    \ { return std::atan2(y, x); }\n    // rotate point/vector by rad\n    P rotate(T_P\
    \ rad) noexcept { return P(add_w_error(x * std::cos(rad), -y * std::sin(rad)),\
    \ add_w_error(x * std::sin(rad), y * std::cos(rad))); }\n    P normalized() const\
    \ { return (*this) / this->norm(); }\n    P conj() const noexcept { return P(x,\
    \ -y); }\n    friend std::istream &operator>>(std::istream &is, P &p) {\n    \
    \    T_P x, y;\n        is >> x >> y;\n        p = P(x, y);\n        return is;\n\
    \    }\n    friend std::ostream &operator<<(std::ostream &os, const P &p) {\n\
    \        os << '(' << p.x << ',' << p.y << ')';\n        return os;\n    }\n};\n\
    template <> double P<double>::EPS = 1e-9;\ntemplate <> long double P<long double>::EPS\
    \ = 1e-12;\n"
  dependsOn: []
  isVerificationFile: false
  path: geometry/point2d_w_error.hpp
  requiredBy: []
  timestamp: '2020-11-18 20:25:12+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: geometry/point2d_w_error.hpp
layout: document
redirect_from:
- /library/geometry/point2d_w_error.hpp
- /library/geometry/point2d_w_error.hpp.html
title: geometry/point2d_w_error.hpp
---
