---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: geometry/problem_of_apollonius.hpp
    title: geometry/problem_of_apollonius.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: geometry/test/convex_cut.test.cpp
    title: geometry/test/convex_cut.test.cpp
  - icon: ':heavy_check_mark:'
    path: geometry/test/convex_hull.test.cpp
    title: geometry/test/convex_hull.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"geometry/geometry2d.hpp\"\n#include <algorithm>\n#include\
    \ <cassert>\n#include <cmath>\n#include <iostream>\n#include <utility>\n#include\
    \ <vector>\n\n\n// CUT begin\ntemplate <typename T_P>\nstruct P\n{\n    static\
    \ T_P EPS;\n    static void set_eps(T_P e)\n    {\n        EPS = e;\n    }\n \
    \   T_P x, y;\n    P() : x(0), y(0) {}\n    P(T_P x, T_P y) : x(x), y(y) {}\n\
    \    P(std::pair<T_P, T_P> p) : x(p.first), y(p.second) {}\n    P operator+(const\
    \ P &p) const noexcept { return P(x + p.x, y + p.y); }\n    P operator-(const\
    \ P &p) const noexcept { return P(x - p.x, y - p.y); }\n    P operator*(const\
    \ P &p) const noexcept { return P(x * p.x - y * p.y, x * p.y + y * p.x); }\n \
    \   P operator*(T_P d) const noexcept { return P(x * d, y * d); }\n    P operator/(T_P\
    \ d) const noexcept { return P(x / d, y / d); }\n    P inv() const { return conj()\
    \ / norm2(); }\n    P operator/(const P &p) const { return (*this) * p.inv();\
    \ }\n    bool operator<(const P &r) const noexcept { return x != r.x ? x < r.x\
    \ : y < r.y; }\n    bool operator==(const P &r) const noexcept { return x == r.x\
    \ and y  == r.y; }\n    bool operator!=(const P &r) const noexcept { return !((*this)\
    \ == r); }\n    T_P dot(P p) const noexcept { return x * p.x + y * p.y; }\n  \
    \  T_P det(P p) const noexcept { return x * p.y - y * p.x; }\n    T_P norm() const\
    \ noexcept { return std::sqrt(x * x + y * y); }\n    T_P norm2() const noexcept\
    \ { return x * x + y * y; }\n    T_P arg() const noexcept { return std::atan2(y,\
    \ x); }\n    // rotate point/vector by rad\n    P rotate(T_P rad) noexcept { return\
    \ P(x * std::cos(rad) - y * std::sin(rad), x * std::sin(rad) + y * std::cos(rad));\
    \ }\n    P normalized() const { return (*this) / this->norm(); }\n    P conj()\
    \ const noexcept { return P(x, -y); }\n    friend std::istream &operator>>(std::istream\
    \ &is, P &p) { T_P x, y; is >> x >> y; p = P(x, y); return is; }\n    friend std::ostream\
    \ &operator<<(std::ostream &os, const P &p) { os << '(' << p.x << ',' << p.y <<\
    \ ')'; return os; }\n};\ntemplate <>\ndouble P<double>::EPS = 1e-9;\ntemplate\
    \ <>\nlong double P<long double>::EPS = 1e-12;\n\n\ntemplate <typename T_P>\n\
    int ccw(const P<T_P> &a, const P<T_P> &b, const P<T_P> &c) // a->b->c\u306E\u66F2\
    \u304C\u308A\u65B9\n{\n    P<T_P> v1 = b - a;\n    P<T_P> v2 = c - a;\n    if\
    \ (v1.det(v2) > P<T_P>::EPS) return 1; // \u5DE6\u6298\n    if (v1.det(v2) < -P<T_P>::EPS)\
    \ return -1; // \u53F3\u6298\n    if (v1.dot(v2) < -P<T_P>::EPS) return 2; //\
    \ c-a-b\n    if (v1.norm() < v2.norm()) return -2; // a-b-c\n    return 0; //\
    \ a-c-b\n}\n\n\n// Convex hull \uFF08\u51F8\u5305\uFF09\n// return: IDs of vertices\
    \ used for convex hull, counterclockwise\n// include_boundary: If true, interior\
    \ angle pi is allowed\ntemplate <typename T_P>\nstd::vector<int> convex_hull(const\
    \ std::vector<P<T_P>> &ps, bool include_boundary = false)\n{\n    int n = ps.size();\n\
    \    if (n <= 1) return std::vector<int>(n, 0);\n    std::vector<std::pair<P<T_P>,\
    \ int>> points(n);\n    for (size_t i = 0; i < ps.size(); i++) points[i] = std::make_pair(ps[i],\
    \ i);\n    std::sort(points.begin(), points.end());\n    int k = 0;\n    std::vector<std::pair<P<T_P>,\
    \ int>> qs(2 * n);\n    auto ccw_check = [&](int c) {\n        if (include_boundary)\
    \ return c == -1;\n        else return c <= 0;\n    };\n    for (int i = 0; i\
    \ < n; i++)\n    {\n        while (k > 1 and ccw_check(ccw(qs[k - 2].first, qs[k\
    \ - 1].first, points[i].first))) k--;\n        qs[k++] = points[i]; \n    }\n\
    \    for (int i = n - 2, t = k; i >= 0; i--) {\n        while (k > t and ccw_check(ccw(qs[k\
    \ - 2].first, qs[k - 1].first, points[i].first))) k--;\n        qs[k++] = points[i];\n\
    \    }\n    std::vector<int> ret(k - 1);\n    for (int i = 0; i < k - 1; i++)\
    \ ret[i] = qs[i].second;\n    return ret;\n}\n\n// Solve r1 + t1 * v1 == r2 +\
    \ t2 * v2\ntemplate <typename T_P>\nP<T_P> lines_crosspoint(P<T_P> r1, P<T_P>\
    \ v1, P<T_P> r2, P<T_P> v2) {\n    assert(v2.det(v1) != 0);\n    return r1 + v1\
    \ * (v2.det(r2 - r1) / v2.det(v1));\n}\n\n// Convex cut\n// Cut the convex polygon\
    \ g by line p1->p2 and return the leftward one\ntemplate <typename T_P>\nstd::vector<P<T_P>>\
    \ convex_cut(const std::vector<P<T_P>>& g, P<T_P> p1, P<T_P> p2) {\n    assert(p1\
    \ != p2);\n    std::vector<P<T_P>> ret;\n    for (int i = 0; i < (int)g.size();\
    \ i++) {\n        const P<T_P> &now = g[i], &nxt = g[(i + 1) % g.size()];\n  \
    \      if (ccw(p1, p2, now) != -1) ret.push_back(now);\n        if ((ccw(p1, p2,\
    \ now) == -1) xor (ccw(p1, p2, nxt) == -1)) {\n            ret.push_back(lines_crosspoint(now,\
    \ nxt - now, p1, p2 - p1));\n        }\n    }\n    return ret;\n}\n\n// Circumcenter\
    \ \uFF08\u4E09\u89D2\u5F62\u306E\u5916\u5FC3\uFF09\n// - raise exception for collinear\
    \ points\ntemplate <typename T_P>\nP<T_P> circumcenter(const P<T_P> &z1, const\
    \ P<T_P> &z2, const P<T_P> &z3)\n{\n    assert(abs(ccw(z1, z2, z3)) % 2 == 1);\n\
    \    P<T_P> a = z2 - z1, b = z3 - z1;\n    return z1 + a * b * (a - b).conj()\
    \ / (b * a.conj() - a * b.conj());\n}\n\n// 2\u5186\u306E\u4EA4\u70B9 (ABC157F)\n\
    template <typename T_P>\nstd::vector<P<T_P>> IntersectTwoCircles(const P<T_P>\
    \ &Ca, double Ra, const P<T_P> &Cb, double Rb)\n{\n    double d = (Ca - Cb).norm();\n\
    \    if (Ra + Rb < d) return {};\n    double rc = (d * d + Ra * Ra - Rb * Rb)\
    \ / (2 * d);\n    double rs = sqrt(Ra * Ra - rc * rc);\n    P<T_P> diff = (Cb\
    \ - Ca) / d;\n    return {Ca + diff * P<T_P>(rc, rs), Ca + diff * P<T_P>(rc, -rs)};\n\
    }\n\n// Solve |x0 + vt| = R (SRM 543 Div.1 1000)\ntemplate <typename T_P>\nstd::vector<T_P>\
    \ IntersectCircleLine(const P<T_P> &x0, const P<T_P> &v, T_P R)\n{\n    T_P b\
    \ = x0.dot(v) / v.norm2();\n    T_P c = (x0.norm2() - R * R) / v.norm2();\n  \
    \  if (b * b - c < 0) return {};\n    T_P ret1;\n    if (b > 0) ret1 = -b - sqrt(b\
    \ * b - c);\n    else ret1 = -b + sqrt(b * b - c);\n    T_P ret2 = c / ret1;\n\
    \    std::vector<T_P> ret{ret1, ret2};\n    std::sort(ret.begin(), ret.end());\n\
    \    return ret;\n}\n\n// Distance between point p <-> line ab\ntemplate <typename\
    \ T_P>\nT_P DistancePointLine(const P<T_P> &p, const P<T_P> &a, const P<T_P> &b)\n\
    {\n    assert(a != b);\n    return std::abs((b - a).det(p - a)) / (b - a).norm();\n\
    }\n\n// Distance between point p <-> line segment ab\ntemplate <typename T_P>\n\
    T_P DistancePointSegment(const P<T_P> &p, const P<T_P> &a, const P<T_P> &b)\n\
    {\n    if (a == b) return (p - a).norm();\n    else if ((p - a).dot(b - a) <=\
    \ 0) return (p - a).norm();\n    else if ((p - b).dot(a - b) <= 0) return (p -\
    \ b).norm();\n    else return DistancePointLine(p, a, b);\n}\n\n// Area of polygon\
    \ (might be negative)\ntemplate <typename T_P>\nT_P signed_area_of_polygon(const\
    \ std::vector<P<T_P>>& poly)\n{\n    T_P area = 0;\n    for (size_t i = 0; i <\
    \ poly.size(); i++) {\n        area += poly[i].det(poly[(i + 1) % poly.size()]);\n\
    \    }\n    return area * 0.5;\n}\n"
  code: "#pragma once\n#include <algorithm>\n#include <cassert>\n#include <cmath>\n\
    #include <iostream>\n#include <utility>\n#include <vector>\n\n\n// CUT begin\n\
    template <typename T_P>\nstruct P\n{\n    static T_P EPS;\n    static void set_eps(T_P\
    \ e)\n    {\n        EPS = e;\n    }\n    T_P x, y;\n    P() : x(0), y(0) {}\n\
    \    P(T_P x, T_P y) : x(x), y(y) {}\n    P(std::pair<T_P, T_P> p) : x(p.first),\
    \ y(p.second) {}\n    P operator+(const P &p) const noexcept { return P(x + p.x,\
    \ y + p.y); }\n    P operator-(const P &p) const noexcept { return P(x - p.x,\
    \ y - p.y); }\n    P operator*(const P &p) const noexcept { return P(x * p.x -\
    \ y * p.y, x * p.y + y * p.x); }\n    P operator*(T_P d) const noexcept { return\
    \ P(x * d, y * d); }\n    P operator/(T_P d) const noexcept { return P(x / d,\
    \ y / d); }\n    P inv() const { return conj() / norm2(); }\n    P operator/(const\
    \ P &p) const { return (*this) * p.inv(); }\n    bool operator<(const P &r) const\
    \ noexcept { return x != r.x ? x < r.x : y < r.y; }\n    bool operator==(const\
    \ P &r) const noexcept { return x == r.x and y  == r.y; }\n    bool operator!=(const\
    \ P &r) const noexcept { return !((*this) == r); }\n    T_P dot(P p) const noexcept\
    \ { return x * p.x + y * p.y; }\n    T_P det(P p) const noexcept { return x *\
    \ p.y - y * p.x; }\n    T_P norm() const noexcept { return std::sqrt(x * x + y\
    \ * y); }\n    T_P norm2() const noexcept { return x * x + y * y; }\n    T_P arg()\
    \ const noexcept { return std::atan2(y, x); }\n    // rotate point/vector by rad\n\
    \    P rotate(T_P rad) noexcept { return P(x * std::cos(rad) - y * std::sin(rad),\
    \ x * std::sin(rad) + y * std::cos(rad)); }\n    P normalized() const { return\
    \ (*this) / this->norm(); }\n    P conj() const noexcept { return P(x, -y); }\n\
    \    friend std::istream &operator>>(std::istream &is, P &p) { T_P x, y; is >>\
    \ x >> y; p = P(x, y); return is; }\n    friend std::ostream &operator<<(std::ostream\
    \ &os, const P &p) { os << '(' << p.x << ',' << p.y << ')'; return os; }\n};\n\
    template <>\ndouble P<double>::EPS = 1e-9;\ntemplate <>\nlong double P<long double>::EPS\
    \ = 1e-12;\n\n\ntemplate <typename T_P>\nint ccw(const P<T_P> &a, const P<T_P>\
    \ &b, const P<T_P> &c) // a->b->c\u306E\u66F2\u304C\u308A\u65B9\n{\n    P<T_P>\
    \ v1 = b - a;\n    P<T_P> v2 = c - a;\n    if (v1.det(v2) > P<T_P>::EPS) return\
    \ 1; // \u5DE6\u6298\n    if (v1.det(v2) < -P<T_P>::EPS) return -1; // \u53F3\u6298\
    \n    if (v1.dot(v2) < -P<T_P>::EPS) return 2; // c-a-b\n    if (v1.norm() < v2.norm())\
    \ return -2; // a-b-c\n    return 0; // a-c-b\n}\n\n\n// Convex hull \uFF08\u51F8\
    \u5305\uFF09\n// return: IDs of vertices used for convex hull, counterclockwise\n\
    // include_boundary: If true, interior angle pi is allowed\ntemplate <typename\
    \ T_P>\nstd::vector<int> convex_hull(const std::vector<P<T_P>> &ps, bool include_boundary\
    \ = false)\n{\n    int n = ps.size();\n    if (n <= 1) return std::vector<int>(n,\
    \ 0);\n    std::vector<std::pair<P<T_P>, int>> points(n);\n    for (size_t i =\
    \ 0; i < ps.size(); i++) points[i] = std::make_pair(ps[i], i);\n    std::sort(points.begin(),\
    \ points.end());\n    int k = 0;\n    std::vector<std::pair<P<T_P>, int>> qs(2\
    \ * n);\n    auto ccw_check = [&](int c) {\n        if (include_boundary) return\
    \ c == -1;\n        else return c <= 0;\n    };\n    for (int i = 0; i < n; i++)\n\
    \    {\n        while (k > 1 and ccw_check(ccw(qs[k - 2].first, qs[k - 1].first,\
    \ points[i].first))) k--;\n        qs[k++] = points[i]; \n    }\n    for (int\
    \ i = n - 2, t = k; i >= 0; i--) {\n        while (k > t and ccw_check(ccw(qs[k\
    \ - 2].first, qs[k - 1].first, points[i].first))) k--;\n        qs[k++] = points[i];\n\
    \    }\n    std::vector<int> ret(k - 1);\n    for (int i = 0; i < k - 1; i++)\
    \ ret[i] = qs[i].second;\n    return ret;\n}\n\n// Solve r1 + t1 * v1 == r2 +\
    \ t2 * v2\ntemplate <typename T_P>\nP<T_P> lines_crosspoint(P<T_P> r1, P<T_P>\
    \ v1, P<T_P> r2, P<T_P> v2) {\n    assert(v2.det(v1) != 0);\n    return r1 + v1\
    \ * (v2.det(r2 - r1) / v2.det(v1));\n}\n\n// Convex cut\n// Cut the convex polygon\
    \ g by line p1->p2 and return the leftward one\ntemplate <typename T_P>\nstd::vector<P<T_P>>\
    \ convex_cut(const std::vector<P<T_P>>& g, P<T_P> p1, P<T_P> p2) {\n    assert(p1\
    \ != p2);\n    std::vector<P<T_P>> ret;\n    for (int i = 0; i < (int)g.size();\
    \ i++) {\n        const P<T_P> &now = g[i], &nxt = g[(i + 1) % g.size()];\n  \
    \      if (ccw(p1, p2, now) != -1) ret.push_back(now);\n        if ((ccw(p1, p2,\
    \ now) == -1) xor (ccw(p1, p2, nxt) == -1)) {\n            ret.push_back(lines_crosspoint(now,\
    \ nxt - now, p1, p2 - p1));\n        }\n    }\n    return ret;\n}\n\n// Circumcenter\
    \ \uFF08\u4E09\u89D2\u5F62\u306E\u5916\u5FC3\uFF09\n// - raise exception for collinear\
    \ points\ntemplate <typename T_P>\nP<T_P> circumcenter(const P<T_P> &z1, const\
    \ P<T_P> &z2, const P<T_P> &z3)\n{\n    assert(abs(ccw(z1, z2, z3)) % 2 == 1);\n\
    \    P<T_P> a = z2 - z1, b = z3 - z1;\n    return z1 + a * b * (a - b).conj()\
    \ / (b * a.conj() - a * b.conj());\n}\n\n// 2\u5186\u306E\u4EA4\u70B9 (ABC157F)\n\
    template <typename T_P>\nstd::vector<P<T_P>> IntersectTwoCircles(const P<T_P>\
    \ &Ca, double Ra, const P<T_P> &Cb, double Rb)\n{\n    double d = (Ca - Cb).norm();\n\
    \    if (Ra + Rb < d) return {};\n    double rc = (d * d + Ra * Ra - Rb * Rb)\
    \ / (2 * d);\n    double rs = sqrt(Ra * Ra - rc * rc);\n    P<T_P> diff = (Cb\
    \ - Ca) / d;\n    return {Ca + diff * P<T_P>(rc, rs), Ca + diff * P<T_P>(rc, -rs)};\n\
    }\n\n// Solve |x0 + vt| = R (SRM 543 Div.1 1000)\ntemplate <typename T_P>\nstd::vector<T_P>\
    \ IntersectCircleLine(const P<T_P> &x0, const P<T_P> &v, T_P R)\n{\n    T_P b\
    \ = x0.dot(v) / v.norm2();\n    T_P c = (x0.norm2() - R * R) / v.norm2();\n  \
    \  if (b * b - c < 0) return {};\n    T_P ret1;\n    if (b > 0) ret1 = -b - sqrt(b\
    \ * b - c);\n    else ret1 = -b + sqrt(b * b - c);\n    T_P ret2 = c / ret1;\n\
    \    std::vector<T_P> ret{ret1, ret2};\n    std::sort(ret.begin(), ret.end());\n\
    \    return ret;\n}\n\n// Distance between point p <-> line ab\ntemplate <typename\
    \ T_P>\nT_P DistancePointLine(const P<T_P> &p, const P<T_P> &a, const P<T_P> &b)\n\
    {\n    assert(a != b);\n    return std::abs((b - a).det(p - a)) / (b - a).norm();\n\
    }\n\n// Distance between point p <-> line segment ab\ntemplate <typename T_P>\n\
    T_P DistancePointSegment(const P<T_P> &p, const P<T_P> &a, const P<T_P> &b)\n\
    {\n    if (a == b) return (p - a).norm();\n    else if ((p - a).dot(b - a) <=\
    \ 0) return (p - a).norm();\n    else if ((p - b).dot(a - b) <= 0) return (p -\
    \ b).norm();\n    else return DistancePointLine(p, a, b);\n}\n\n// Area of polygon\
    \ (might be negative)\ntemplate <typename T_P>\nT_P signed_area_of_polygon(const\
    \ std::vector<P<T_P>>& poly)\n{\n    T_P area = 0;\n    for (size_t i = 0; i <\
    \ poly.size(); i++) {\n        area += poly[i].det(poly[(i + 1) % poly.size()]);\n\
    \    }\n    return area * 0.5;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: geometry/geometry2d.hpp
  requiredBy:
  - geometry/problem_of_apollonius.hpp
  timestamp: '2020-11-16 12:44:28+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - geometry/test/convex_hull.test.cpp
  - geometry/test/convex_cut.test.cpp
documentation_of: geometry/geometry2d.hpp
layout: document
redirect_from:
- /library/geometry/geometry2d.hpp
- /library/geometry/geometry2d.hpp.html
title: geometry/geometry2d.hpp
---
