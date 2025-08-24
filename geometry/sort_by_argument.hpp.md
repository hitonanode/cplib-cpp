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
  bundledCode: "#line 2 \"geometry/sort_by_argument.hpp\"\n\n// Point on grid, sortable\
    \ by its argument\nstruct Point {\n    long long X, Y;\n    Point() = default;\n\
    \    Point(long long x, long long y) : X(x), Y(y) {}\n\n    bool operator<(const\
    \ Point &r) const {\n        const int ll = lower_or_upper(), lr = r.lower_or_upper();\n\
    \        if (ll != lr) return ll < lr;\n        return X * r.Y > r.X * Y;\n  \
    \  }\n\n    bool operator==(const Point &r) const {\n        return lower_or_upper()\
    \ == r.lower_or_upper() and X * r.Y == r.X * Y;\n    }\n\n    int lower_or_upper()\
    \ const {\n        if (Y) return Y > 0 ? 1 : -1;\n        if (X) return X > 0\
    \ ? -1 : 1;\n        return 0; // origin\n    }\n\n    void rotate_pi() { X =\
    \ -X, Y = -Y; }\n};\n"
  code: "#pragma once\n\n// Point on grid, sortable by its argument\nstruct Point\
    \ {\n    long long X, Y;\n    Point() = default;\n    Point(long long x, long\
    \ long y) : X(x), Y(y) {}\n\n    bool operator<(const Point &r) const {\n    \
    \    const int ll = lower_or_upper(), lr = r.lower_or_upper();\n        if (ll\
    \ != lr) return ll < lr;\n        return X * r.Y > r.X * Y;\n    }\n\n    bool\
    \ operator==(const Point &r) const {\n        return lower_or_upper() == r.lower_or_upper()\
    \ and X * r.Y == r.X * Y;\n    }\n\n    int lower_or_upper() const {\n       \
    \ if (Y) return Y > 0 ? 1 : -1;\n        if (X) return X > 0 ? -1 : 1;\n     \
    \   return 0; // origin\n    }\n\n    void rotate_pi() { X = -X, Y = -Y; }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: geometry/sort_by_argument.hpp
  requiredBy: []
  timestamp: '2025-08-05 22:50:49+09:00'
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
