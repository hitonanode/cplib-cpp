---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: geometry/test/sort_by_argument.test.cpp
    title: geometry/test/sort_by_argument.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"geometry/sort_by_argument.hpp\"\n#include <cmath>\n\n//\
    \ CUT begin\n// Point on grid, sortable by its argument\nstruct Point {\n    constexpr\
    \ static double eps = 1e-2;\n    long long X, Y;\n    double theta;\n    Point()\
    \ = default;\n    Point(long long x, long long y) : X(x), Y(y), theta(std::atan2(y,\
    \ x)) {}\n    bool operator<(const Point &r) const {\n        double b = theta\
    \ - r.theta;\n        return std::abs(b) > eps ? (b < 0) : (X * r.Y > r.X * Y);\n\
    \    }\n    bool operator==(const Point &r) const { return std::abs(theta - r.theta)\
    \ < eps and X * r.Y == r.X * Y; }\n    void rotate_pi() {\n        theta += M_PI;\n\
    \        X *= -1;\n        Y *= -1;\n    }\n};\n"
  code: "#pragma once\n#include <cmath>\n\n// CUT begin\n// Point on grid, sortable\
    \ by its argument\nstruct Point {\n    constexpr static double eps = 1e-2;\n \
    \   long long X, Y;\n    double theta;\n    Point() = default;\n    Point(long\
    \ long x, long long y) : X(x), Y(y), theta(std::atan2(y, x)) {}\n    bool operator<(const\
    \ Point &r) const {\n        double b = theta - r.theta;\n        return std::abs(b)\
    \ > eps ? (b < 0) : (X * r.Y > r.X * Y);\n    }\n    bool operator==(const Point\
    \ &r) const { return std::abs(theta - r.theta) < eps and X * r.Y == r.X * Y; }\n\
    \    void rotate_pi() {\n        theta += M_PI;\n        X *= -1;\n        Y *=\
    \ -1;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: geometry/sort_by_argument.hpp
  requiredBy: []
  timestamp: '2021-05-20 18:58:10+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - geometry/test/sort_by_argument.test.cpp
documentation_of: geometry/sort_by_argument.hpp
layout: document
redirect_from:
- /library/geometry/sort_by_argument.hpp
- /library/geometry/sort_by_argument.hpp.html
title: geometry/sort_by_argument.hpp
---
