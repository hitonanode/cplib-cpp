---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: geometry/geometry2d.hpp
    title: geometry/geometry2d.hpp
  - icon: ':warning:'
    path: utilities/quadratic_solver.hpp
    title: utilities/quadratic_solver.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"utilities/quadratic_solver.hpp\"\n#include <cmath>\n#include\
    \ <utility>\n#include <vector>\n\n// CUT begin\n// Solve ax^2 + bx + c = 0.\n\
    // retval: (# of solutions (-1 == inf.), solutions(ascending order))\n// Verify:\
    \ <https://yukicoder.me/problems/no/955> <https://atcoder.jp/contests/tricky/tasks/tricky_2>\n\
    template <typename Float>\nstd::pair<int, std::vector<Float>> quadratic_solver(Float\
    \ A, Float B, Float C)\n{\n    if (B < 0) A = -A, B = -B, C = -C;\n    if (A ==\
    \ 0) {\n        if (B == 0) {\n            if (C == 0) return std::make_pair(-1,\
    \ std::vector<Float>{});  // all real numbers\n            else return std::make_pair(0,\
    \ std::vector<Float>{});  // no solution\n        }\n        else return std::make_pair(1,\
    \ std::vector<Float>{-C / B});\n    }\n    Float D = B * B - 4 * A * C;\n    if\
    \ (D < 0) return std::make_pair(0, std::vector<Float>{});\n    if (D == 0) return\
    \ std::make_pair(1, std::vector<Float>{-B / (2 * A)});\n    Float ret1 = (-B -\
    \ sqrt(D)) / (2 * A), ret2 = C / A / ret1;\n    if (ret1 > ret2) swap(ret1, ret2);\n\
    \    return std::make_pair(2, std::vector<Float>{ret1, ret2});\n}\n#line 2 \"\
    geometry/geometry2d.hpp\"\n#include <algorithm>\n#include <cassert>\n#line 5 \"\
    geometry/geometry2d.hpp\"\n#include <iostream>\n#line 8 \"geometry/geometry2d.hpp\"\
    \n\n\n// CUT begin\ntemplate <typename T_P>\nstruct P\n{\n    static T_P EPS;\n\
    \    static void set_eps(T_P e)\n    {\n        EPS = e;\n    }\n    T_P x, y;\n\
    \    P() : x(0), y(0) {}\n    P(T_P x, T_P y) : x(x), y(y) {}\n    P(std::pair<T_P,\
    \ T_P> p) : x(p.first), y(p.second) {}\n    static T_P add_w_error(T_P a, T_P\
    \ b) noexcept { return (std::abs(a + b) < P::EPS * (std::abs(a) + std::abs(b)))\
    \ ? 0 : a + b; }\n    P operator+(const P &p) const noexcept { return P(add_w_error(x,\
    \ p.x), add_w_error(y, p.y)); }\n    P operator-(const P &p) const noexcept {\
    \ return P(add_w_error(x, -p.x), add_w_error(y, -p.y)); }\n    P operator*(const\
    \ P &p) const noexcept { return P(add_w_error(x * p.x,  -y * p.y), add_w_error(x\
    \ * p.y, y * p.x)); }\n    P operator*(T_P d) const noexcept { return P(x * d,\
    \ y * d); }\n    P operator/(T_P d) const noexcept { return P(x / d, y / d); }\n\
    \    P inv() const { return conj() / norm2(); }\n    P operator/(const P &p) const\
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
    \ std::istream &operator>>(std::istream &is, P &p) { T_P x, y; is >> x >> y; p\
    \ = P(x, y); return is; }\n    friend std::ostream &operator<<(std::ostream &os,\
    \ const P &p) { os << '(' << p.x << ',' << p.y << ')'; return os; }\n};\ntemplate\
    \ <>\ndouble P<double>::EPS = 1e-9;\ntemplate <>\nlong double P<long double>::EPS\
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
    \    }\n    return area * 0.5;\n}\n#line 4 \"geometry/problem_of_apollonius.hpp\"\
    \n\n#line 7 \"geometry/problem_of_apollonius.hpp\"\n\n// CUT begin\n// \u30A2\u30DD\
    \u30ED\u30CB\u30A6\u30B9\u306E\u554F\u984C\uFF1A3\u5186\u306B\u63A5\u3059\u308B\
    \u5186\u306E\u4E2D\u5FC3\u3068\u534A\u5F84\n// Verify: TCO 2020 North America\
    \ Qualifier 1000\n// input:\n// - Center* : \u5404\u5186\u306E\u4E2D\u5FC3\u5EA7\
    \u6A19\n// - Radius* : \u5404\u5186\u306E\u534A\u5F84\n// - sgn*    : \u5916\u63A5\
    (-1) / \u5185\u63A5(1)\n// retval:\n// - [(Center, Radius), ...] \uFF08\u6761\u4EF6\
    \u3092\u307F\u305F\u3059\u5186\u306F\u8907\u6570\u5B58\u5728\u3057\u3046\u308B\
    \uFF09\ntemplate <typename T_P>\nstd::vector<std::pair<P<T_P>, T_P>> Problem_of_Apollonius(P<T_P>\
    \ Center1, T_P Radius1, P<T_P> Center2, T_P Radius2, P<T_P> Center3, T_P Radius3,\
    \ int sgn1, int sgn2, int sgn3) {\n    Center2 = Center2 - Center1, Center3 =\
    \ Center3 - Center1;\n    T_P a2 = -Center2.x * 2, b2 = -Center2.y * 2, c2 = (-Radius1\
    \ * sgn1 + Radius2 * sgn2) * 2, d2 = -Radius1 * Radius1 - Center2.norm2() + Radius2\
    \ * Radius2;\n    T_P a3 = -Center3.x * 2, b3 = -Center3.y * 2, c3 = (-Radius1\
    \ * sgn1 + Radius3 * sgn3) * 2, d3 = -Radius1 * Radius1 - Center3.norm2() + Radius3\
    \ * Radius3;\n    T_P denom = a2 * b3 - b2 * a3;\n    std::vector<std::pair<P<T_P>,\
    \ T_P>> ret_circles;\n    if (denom == 0) return ret_circles;\n    P<T_P> v0((b3\
    \ * d2 - b2 * d3) / denom, (-a3 * d2 + a2 * d3) / denom), v1((-b3 * c2 + b2 *\
    \ c3) / denom, (a3 * c2 - a2 * c3) / denom);\n    T_P A = v1.norm2() - 1, B =\
    \ 2 * (v1.dot(v0) + Radius1 * sgn1), C = v0.norm2() - Radius1 * Radius1;\n   \
    \ auto quad_ret = quadratic_solver(A, B, C);\n    for (const auto r : quad_ret.second)\
    \ if (r >= 0.0) {\n        P<T_P> Center = v0 + v1 * r + Center1;\n        ret_circles.emplace_back(Center,\
    \ r);\n    }\n    return ret_circles;\n};\n"
  code: "#pragma once\n#include \"utilities/quadratic_solver.hpp\"\n#include \"geometry/geometry2d.hpp\"\
    \n\n#include <utility>\n#include <vector>\n\n// CUT begin\n// \u30A2\u30DD\u30ED\
    \u30CB\u30A6\u30B9\u306E\u554F\u984C\uFF1A3\u5186\u306B\u63A5\u3059\u308B\u5186\
    \u306E\u4E2D\u5FC3\u3068\u534A\u5F84\n// Verify: TCO 2020 North America Qualifier\
    \ 1000\n// input:\n// - Center* : \u5404\u5186\u306E\u4E2D\u5FC3\u5EA7\u6A19\n\
    // - Radius* : \u5404\u5186\u306E\u534A\u5F84\n// - sgn*    : \u5916\u63A5(-1)\
    \ / \u5185\u63A5(1)\n// retval:\n// - [(Center, Radius), ...] \uFF08\u6761\u4EF6\
    \u3092\u307F\u305F\u3059\u5186\u306F\u8907\u6570\u5B58\u5728\u3057\u3046\u308B\
    \uFF09\ntemplate <typename T_P>\nstd::vector<std::pair<P<T_P>, T_P>> Problem_of_Apollonius(P<T_P>\
    \ Center1, T_P Radius1, P<T_P> Center2, T_P Radius2, P<T_P> Center3, T_P Radius3,\
    \ int sgn1, int sgn2, int sgn3) {\n    Center2 = Center2 - Center1, Center3 =\
    \ Center3 - Center1;\n    T_P a2 = -Center2.x * 2, b2 = -Center2.y * 2, c2 = (-Radius1\
    \ * sgn1 + Radius2 * sgn2) * 2, d2 = -Radius1 * Radius1 - Center2.norm2() + Radius2\
    \ * Radius2;\n    T_P a3 = -Center3.x * 2, b3 = -Center3.y * 2, c3 = (-Radius1\
    \ * sgn1 + Radius3 * sgn3) * 2, d3 = -Radius1 * Radius1 - Center3.norm2() + Radius3\
    \ * Radius3;\n    T_P denom = a2 * b3 - b2 * a3;\n    std::vector<std::pair<P<T_P>,\
    \ T_P>> ret_circles;\n    if (denom == 0) return ret_circles;\n    P<T_P> v0((b3\
    \ * d2 - b2 * d3) / denom, (-a3 * d2 + a2 * d3) / denom), v1((-b3 * c2 + b2 *\
    \ c3) / denom, (a3 * c2 - a2 * c3) / denom);\n    T_P A = v1.norm2() - 1, B =\
    \ 2 * (v1.dot(v0) + Radius1 * sgn1), C = v0.norm2() - Radius1 * Radius1;\n   \
    \ auto quad_ret = quadratic_solver(A, B, C);\n    for (const auto r : quad_ret.second)\
    \ if (r >= 0.0) {\n        P<T_P> Center = v0 + v1 * r + Center1;\n        ret_circles.emplace_back(Center,\
    \ r);\n    }\n    return ret_circles;\n};\n"
  dependsOn:
  - utilities/quadratic_solver.hpp
  - geometry/geometry2d.hpp
  isVerificationFile: false
  path: geometry/problem_of_apollonius.hpp
  requiredBy: []
  timestamp: '2020-10-29 23:07:35+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: geometry/problem_of_apollonius.hpp
layout: document
redirect_from:
- /library/geometry/problem_of_apollonius.hpp
- /library/geometry/problem_of_apollonius.hpp.html
title: geometry/problem_of_apollonius.hpp
---
