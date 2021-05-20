---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: geometry/triangle.hpp
    title: geometry/triangle.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: geometry/test/circumcenter.test.cpp
    title: geometry/test/circumcenter.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"geometry/point3d.hpp\"\n#include <cmath>\n#include <iostream>\n\
    #include <tuple>\n\n// CUT begin\ntemplate <typename T> struct Point3d {\n   \
    \ T x, y, z;\n    Point3d() : x(0), y(0), z(0) {}\n    Point3d(T x_, T y_, T z_)\
    \ : x(x_), y(y_), z(z_) {}\n    Point3d(const std::tuple<T, T, T> &init) { std::tie(x,\
    \ y, z) = init; }\n    Point3d operator+(const Point3d &p) const noexcept { return\
    \ {x + p.x, y + p.y, z + p.z}; }\n    Point3d operator-(const Point3d &p) const\
    \ noexcept { return {x - p.x, y - p.y, z - p.z}; }\n    Point3d operator*(T d)\
    \ const noexcept { return {x * d, y * d, z * d}; }\n    Point3d operator/(T d)\
    \ const { return {x / d, y / d, z / d}; }\n    bool operator<(const Point3d &r)\
    \ const noexcept { return x != r.x ? x < r.x : (y != r.y ? y < r.y : z < r.z);\
    \ }\n    bool operator==(const Point3d &r) const noexcept { return x == r.x and\
    \ y == r.y and z == r.z; }\n    bool operator!=(const Point3d &r) const noexcept\
    \ { return !((*this) == r); }\n    T dot(const Point3d &p) const noexcept { return\
    \ x * p.x + y * p.y + z * p.z; }\n    T absdet(const Point3d &p) const noexcept\
    \ {\n        return Point3d(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y\
    \ * p.x).norm();\n    }\n    T norm() const noexcept { return std::sqrt(x * x\
    \ + y * y + z * z); }\n    T norm2() const noexcept { return x * x + y * y + z\
    \ * z; }\n    Point3d normalized() const { return (*this) / this->norm(); }\n\
    \    friend std::istream &operator>>(std::istream &is, Point3d &p) { return is\
    \ >> p.x >> p.y >> p.z; }\n    friend std::ostream &operator<<(std::ostream &os,\
    \ const Point3d &p) {\n        return os << '(' << p.x << ',' << p.y << ',' <<\
    \ p.z << ')';\n    }\n};\n"
  code: "#pragma once\n#include <cmath>\n#include <iostream>\n#include <tuple>\n\n\
    // CUT begin\ntemplate <typename T> struct Point3d {\n    T x, y, z;\n    Point3d()\
    \ : x(0), y(0), z(0) {}\n    Point3d(T x_, T y_, T z_) : x(x_), y(y_), z(z_) {}\n\
    \    Point3d(const std::tuple<T, T, T> &init) { std::tie(x, y, z) = init; }\n\
    \    Point3d operator+(const Point3d &p) const noexcept { return {x + p.x, y +\
    \ p.y, z + p.z}; }\n    Point3d operator-(const Point3d &p) const noexcept { return\
    \ {x - p.x, y - p.y, z - p.z}; }\n    Point3d operator*(T d) const noexcept {\
    \ return {x * d, y * d, z * d}; }\n    Point3d operator/(T d) const { return {x\
    \ / d, y / d, z / d}; }\n    bool operator<(const Point3d &r) const noexcept {\
    \ return x != r.x ? x < r.x : (y != r.y ? y < r.y : z < r.z); }\n    bool operator==(const\
    \ Point3d &r) const noexcept { return x == r.x and y == r.y and z == r.z; }\n\
    \    bool operator!=(const Point3d &r) const noexcept { return !((*this) == r);\
    \ }\n    T dot(const Point3d &p) const noexcept { return x * p.x + y * p.y + z\
    \ * p.z; }\n    T absdet(const Point3d &p) const noexcept {\n        return Point3d(y\
    \ * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x).norm();\n    }\n    T\
    \ norm() const noexcept { return std::sqrt(x * x + y * y + z * z); }\n    T norm2()\
    \ const noexcept { return x * x + y * y + z * z; }\n    Point3d normalized() const\
    \ { return (*this) / this->norm(); }\n    friend std::istream &operator>>(std::istream\
    \ &is, Point3d &p) { return is >> p.x >> p.y >> p.z; }\n    friend std::ostream\
    \ &operator<<(std::ostream &os, const Point3d &p) {\n        return os << '('\
    \ << p.x << ',' << p.y << ',' << p.z << ')';\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: geometry/point3d.hpp
  requiredBy:
  - geometry/triangle.hpp
  timestamp: '2021-05-20 18:58:10+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - geometry/test/circumcenter.test.cpp
documentation_of: geometry/point3d.hpp
layout: document
redirect_from:
- /library/geometry/point3d.hpp
- /library/geometry/point3d.hpp.html
title: geometry/point3d.hpp
---
