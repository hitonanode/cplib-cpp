---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: geometry/problem_of_apollonius.hpp
    title: geometry/problem_of_apollonius.hpp
  - icon: ':heavy_check_mark:'
    path: geometry/triangle.hpp
    title: geometry/triangle.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: geometry/test/circumcenter.test.cpp
    title: geometry/test/circumcenter.test.cpp
  - icon: ':heavy_check_mark:'
    path: geometry/test/convex_cut.test.cpp
    title: geometry/test/convex_cut.test.cpp
  - icon: ':heavy_check_mark:'
    path: geometry/test/convex_hull.test.cpp
    title: geometry/test/convex_hull.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"geometry/geometry.hpp\"\n#include <algorithm>\n#include\
    \ <cassert>\n#include <cmath>\n#include <complex>\n#include <iostream>\n#include\
    \ <tuple>\n#include <utility>\n#include <vector>\n\n// CUT begin\ntemplate <typename\
    \ T_P> struct Point2d {\n    static T_P EPS;\n    static void set_eps(T_P e) {\
    \ EPS = e; }\n    T_P x, y;\n    Point2d() : x(0), y(0) {}\n    Point2d(T_P x,\
    \ T_P y) : x(x), y(y) {}\n    Point2d(const std::pair<T_P, T_P> &p) : x(p.first),\
    \ y(p.second) {}\n    Point2d(const std::complex<T_P> &p) : x(p.real()), y(p.imag())\
    \ {}\n    std::complex<T_P> to_complex() const noexcept { return {x, y}; }\n \
    \   Point2d operator+(const Point2d &p) const noexcept { return Point2d(x + p.x,\
    \ y + p.y); }\n    Point2d operator-(const Point2d &p) const noexcept { return\
    \ Point2d(x - p.x, y - p.y); }\n    Point2d operator*(const Point2d &p) const\
    \ noexcept { return Point2d(x * p.x - y * p.y, x * p.y + y * p.x); }\n    Point2d\
    \ operator*(T_P d) const noexcept { return Point2d(x * d, y * d); }\n    Point2d\
    \ operator/(T_P d) const noexcept { return Point2d(x / d, y / d); }\n    Point2d\
    \ inv() const { return conj() / norm2(); }\n    Point2d operator/(const Point2d\
    \ &p) const { return (*this) * p.inv(); }\n    bool operator<(const Point2d &r)\
    \ const noexcept { return x != r.x ? x < r.x : y < r.y; }\n    bool operator==(const\
    \ Point2d &r) const noexcept { return x == r.x and y == r.y; }\n    bool operator!=(const\
    \ Point2d &r) const noexcept { return !((*this) == r); }\n    T_P dot(Point2d\
    \ p) const noexcept { return x * p.x + y * p.y; }\n    T_P det(Point2d p) const\
    \ noexcept { return x * p.y - y * p.x; }\n    T_P absdet(Point2d p) const noexcept\
    \ { return std::abs(det(p)); }\n    T_P norm() const noexcept { return std::sqrt(x\
    \ * x + y * y); }\n    T_P norm2() const noexcept { return x * x + y * y; }\n\
    \    T_P arg() const noexcept { return std::atan2(y, x); }\n    // rotate point/vector\
    \ by rad\n    Point2d rotate(T_P rad) const noexcept {\n        return Point2d(x\
    \ * std::cos(rad) - y * std::sin(rad), x * std::sin(rad) + y * std::cos(rad));\n\
    \    }\n    Point2d normalized() const { return (*this) / this->norm(); }\n  \
    \  Point2d conj() const noexcept { return Point2d(x, -y); }\n    friend std::istream\
    \ &operator>>(std::istream &is, Point2d &p) {\n        T_P x, y;\n        is >>\
    \ x >> y;\n        p = Point2d(x, y);\n        return is;\n    }\n    friend std::ostream\
    \ &operator<<(std::ostream &os, const Point2d &p) {\n        os << '(' << p.x\
    \ << ',' << p.y << ')';\n        return os;\n    }\n};\ntemplate <> double Point2d<double>::EPS\
    \ = 1e-9;\ntemplate <> long double Point2d<long double>::EPS = 1e-12;\ntemplate\
    \ <> long long Point2d<long long>::EPS = 0;\n\ntemplate <typename T_P>\nint ccw(const\
    \ Point2d<T_P> &a, const Point2d<T_P> &b, const Point2d<T_P> &c) { // a->b->c\u306E\
    \u66F2\u304C\u308A\u65B9\n    Point2d<T_P> v1 = b - a;\n    Point2d<T_P> v2 =\
    \ c - a;\n    if (v1.det(v2) > Point2d<T_P>::EPS) return 1;   // \u5DE6\u6298\n\
    \    if (v1.det(v2) < -Point2d<T_P>::EPS) return -1; // \u53F3\u6298\n    if (v1.dot(v2)\
    \ < -Point2d<T_P>::EPS) return 2;  // c-a-b\n    if (v1.norm() < v2.norm()) return\
    \ -2;           // a-b-c\n    return 0;                                      \
    \ // a-c-b\n}\n\n// Convex hull \uFF08\u51F8\u5305\uFF09\n// return: IDs of vertices\
    \ used for convex hull, counterclockwise\n// include_boundary: If true, interior\
    \ angle pi is allowed\ntemplate <typename T_P>\nstd::vector<int> convex_hull(const\
    \ std::vector<Point2d<T_P>> &ps, bool include_boundary = false) {\n    int n =\
    \ ps.size();\n    if (n <= 1) return std::vector<int>(n, 0);\n    std::vector<std::pair<Point2d<T_P>,\
    \ int>> points(n);\n    for (size_t i = 0; i < ps.size(); i++) points[i] = std::make_pair(ps[i],\
    \ i);\n    std::sort(points.begin(), points.end());\n    int k = 0;\n    std::vector<std::pair<Point2d<T_P>,\
    \ int>> qs(2 * n);\n    auto ccw_check = [&](int c) { return include_boundary\
    \ ? (c == -1) : (c <= 0); };\n    for (int i = 0; i < n; i++) {\n        while\
    \ (k > 1 and ccw_check(ccw(qs[k - 2].first, qs[k - 1].first, points[i].first)))\
    \ k--;\n        qs[k++] = points[i];\n    }\n    for (int i = n - 2, t = k; i\
    \ >= 0; i--) {\n        while (k > t and ccw_check(ccw(qs[k - 2].first, qs[k -\
    \ 1].first, points[i].first))) k--;\n        qs[k++] = points[i];\n    }\n   \
    \ std::vector<int> ret(k - 1);\n    for (int i = 0; i < k - 1; i++) ret[i] = qs[i].second;\n\
    \    return ret;\n}\n\n// Solve r1 + t1 * v1 == r2 + t2 * v2\ntemplate <typename\
    \ T_P>\nPoint2d<T_P> lines_crosspoint(Point2d<T_P> r1, Point2d<T_P> v1, Point2d<T_P>\
    \ r2, Point2d<T_P> v2) {\n    assert(v2.det(v1) != 0);\n    return r1 + v1 * (v2.det(r2\
    \ - r1) / v2.det(v1));\n}\n\n// Whether two segments s1t1 & s2t2 intersect or\
    \ not (endpoints not included)\n// Google Code Jam 2013 Round 3 - Rural Planning\n\
    // Google Code Jam 2021 Round 3 - Fence Design\ntemplate <typename T> bool intersect_open_segments(Point2d<T>\
    \ s1, Point2d<T> t1, Point2d<T> s2, Point2d<T> t2) {\n    if (s1 == t1 or s2 ==\
    \ t2) return false; // Not segment but point\n    int nbad = 0;\n    for (int\
    \ t = 0; t < 2; t++) {\n        Point2d<T> v1 = t1 - s1, v2 = t2 - s2;\n     \
    \   T den = v2.det(v1);\n        if (den == 0) {\n            if (s1.det(v1) ==\
    \ s2.det(v1)) {\n                auto L1 = s1.dot(v1), R1 = t1.dot(v1);\n    \
    \            auto L2 = s2.dot(v1), R2 = t2.dot(v1);\n                if (L1 >\
    \ R1) std::swap(L1, R1);\n                if (L2 > R2) std::swap(L2, R2);\n  \
    \              if (L1 > L2) std::swap(L1, L2), std::swap(R1, R2);\n          \
    \      return R1 > L2;\n            } else {\n                return false;\n\
    \            }\n        } else {\n            auto num = v2.det(s2 - s1);\n  \
    \          if ((0 < num and num < den) or (den < num and num < 0)) nbad++;\n \
    \       }\n        std::swap(s1, s2);\n        std::swap(t1, t2);\n    }\n   \
    \ return nbad == 2;\n}\n\n// Whether point p is on segment (s, t) (endpoints not\
    \ included)\n// Google Code Jam 2013 Round 3 - Rural Planning\ntemplate <typename\
    \ PointNd> bool is_point_on_open_segment(PointNd s, PointNd t, PointNd p) {\n\
    \    if (s == t) return false; // not segment but point\n    if (p == s or p ==\
    \ t) return false;\n    auto v = t - s, w = p - s;\n    if (v.absdet(w)) return\
    \ false;\n    auto vv = v.dot(v), vw = v.dot(w);\n    return vw > 0 and vw < vv;\n\
    }\n\n// Convex cut\n// Cut the convex polygon g by line p1->p2 and return the\
    \ leftward one\ntemplate <typename T_P>\nstd::vector<Point2d<T_P>> convex_cut(const\
    \ std::vector<Point2d<T_P>> &g, Point2d<T_P> p1, Point2d<T_P> p2) {\n    assert(p1\
    \ != p2);\n    std::vector<Point2d<T_P>> ret;\n    for (int i = 0; i < (int)g.size();\
    \ i++) {\n        const Point2d<T_P> &now = g[i], &nxt = g[(i + 1) % g.size()];\n\
    \        if (ccw(p1, p2, now) != -1) ret.push_back(now);\n        if ((ccw(p1,\
    \ p2, now) == -1) xor (ccw(p1, p2, nxt) == -1)) {\n            ret.push_back(lines_crosspoint(now,\
    \ nxt - now, p1, p2 - p1));\n        }\n    }\n    return ret;\n}\n\n// 2\u5186\
    \u306E\u4EA4\u70B9 (ABC157F)\ntemplate <typename T_P>\nstd::vector<Point2d<T_P>>\
    \ IntersectTwoCircles(const Point2d<T_P> &Ca, double Ra, const Point2d<T_P> &Cb,\
    \ double Rb) {\n    double d = (Ca - Cb).norm();\n    if (Ra + Rb < d) return\
    \ {};\n    double rc = (d * d + Ra * Ra - Rb * Rb) / (2 * d);\n    double rs =\
    \ sqrt(Ra * Ra - rc * rc);\n    Point2d<T_P> diff = (Cb - Ca) / d;\n    return\
    \ {Ca + diff * Point2d<T_P>(rc, rs), Ca + diff * Point2d<T_P>(rc, -rs)};\n}\n\n\
    // Solve |x0 + vt| = R (SRM 543 Div.1 1000, GCJ 2016 R3 C)\ntemplate <typename\
    \ PointNd, typename Float>\nstd::vector<Float> IntersectCircleLine(const PointNd\
    \ &x0, const PointNd &v, Float R) {\n    Float b = Float(x0.dot(v)) / v.norm2();\n\
    \    Float c = Float(x0.norm2() - Float(R) * R) / v.norm2();\n    if (b * b -\
    \ c < 0) return {};\n    Float ret1 = -b + sqrtl(b * b - c) * (b > 0 ? -1 : 1);\n\
    \    Float ret2 = c / ret1;\n    return ret1 < ret2 ? std::vector<Float>{ret1,\
    \ ret2} : std::vector<Float>{ret2, ret1};\n}\n\n// Distance between point p <->\
    \ line ab\ntemplate <typename PointFloat>\ndecltype(PointFloat::x) DistancePointLine(const\
    \ PointFloat &p, const PointFloat &a, const PointFloat &b) {\n    assert(a !=\
    \ b);\n    return (b - a).absdet(p - a) / (b - a).norm();\n}\n\n// Distance between\
    \ point p <-> line segment ab\ntemplate <typename PointFloat>\ndecltype(PointFloat::x)\
    \ DistancePointSegment(const PointFloat &p, const PointFloat &a, const PointFloat\
    \ &b) {\n    if (a == b) {\n        return (p - a).norm();\n    } else if ((p\
    \ - a).dot(b - a) <= 0) {\n        return (p - a).norm();\n    } else if ((p -\
    \ b).dot(a - b) <= 0) {\n        return (p - b).norm();\n    } else {\n      \
    \  return DistancePointLine<PointFloat>(p, a, b);\n    }\n}\n\n// Area of polygon\
    \ (might be negative)\ntemplate <typename T_P> T_P signed_area_of_polygon(const\
    \ std::vector<Point2d<T_P>> &poly) {\n    T_P area = 0;\n    for (size_t i = 0;\
    \ i < poly.size(); i++) area += poly[i].det(poly[(i + 1) % poly.size()]);\n  \
    \  return area * 0.5;\n}\n"
  code: "#pragma once\n#include <algorithm>\n#include <cassert>\n#include <cmath>\n\
    #include <complex>\n#include <iostream>\n#include <tuple>\n#include <utility>\n\
    #include <vector>\n\n// CUT begin\ntemplate <typename T_P> struct Point2d {\n\
    \    static T_P EPS;\n    static void set_eps(T_P e) { EPS = e; }\n    T_P x,\
    \ y;\n    Point2d() : x(0), y(0) {}\n    Point2d(T_P x, T_P y) : x(x), y(y) {}\n\
    \    Point2d(const std::pair<T_P, T_P> &p) : x(p.first), y(p.second) {}\n    Point2d(const\
    \ std::complex<T_P> &p) : x(p.real()), y(p.imag()) {}\n    std::complex<T_P> to_complex()\
    \ const noexcept { return {x, y}; }\n    Point2d operator+(const Point2d &p) const\
    \ noexcept { return Point2d(x + p.x, y + p.y); }\n    Point2d operator-(const\
    \ Point2d &p) const noexcept { return Point2d(x - p.x, y - p.y); }\n    Point2d\
    \ operator*(const Point2d &p) const noexcept { return Point2d(x * p.x - y * p.y,\
    \ x * p.y + y * p.x); }\n    Point2d operator*(T_P d) const noexcept { return\
    \ Point2d(x * d, y * d); }\n    Point2d operator/(T_P d) const noexcept { return\
    \ Point2d(x / d, y / d); }\n    Point2d inv() const { return conj() / norm2();\
    \ }\n    Point2d operator/(const Point2d &p) const { return (*this) * p.inv();\
    \ }\n    bool operator<(const Point2d &r) const noexcept { return x != r.x ? x\
    \ < r.x : y < r.y; }\n    bool operator==(const Point2d &r) const noexcept { return\
    \ x == r.x and y == r.y; }\n    bool operator!=(const Point2d &r) const noexcept\
    \ { return !((*this) == r); }\n    T_P dot(Point2d p) const noexcept { return\
    \ x * p.x + y * p.y; }\n    T_P det(Point2d p) const noexcept { return x * p.y\
    \ - y * p.x; }\n    T_P absdet(Point2d p) const noexcept { return std::abs(det(p));\
    \ }\n    T_P norm() const noexcept { return std::sqrt(x * x + y * y); }\n    T_P\
    \ norm2() const noexcept { return x * x + y * y; }\n    T_P arg() const noexcept\
    \ { return std::atan2(y, x); }\n    // rotate point/vector by rad\n    Point2d\
    \ rotate(T_P rad) const noexcept {\n        return Point2d(x * std::cos(rad) -\
    \ y * std::sin(rad), x * std::sin(rad) + y * std::cos(rad));\n    }\n    Point2d\
    \ normalized() const { return (*this) / this->norm(); }\n    Point2d conj() const\
    \ noexcept { return Point2d(x, -y); }\n    friend std::istream &operator>>(std::istream\
    \ &is, Point2d &p) {\n        T_P x, y;\n        is >> x >> y;\n        p = Point2d(x,\
    \ y);\n        return is;\n    }\n    friend std::ostream &operator<<(std::ostream\
    \ &os, const Point2d &p) {\n        os << '(' << p.x << ',' << p.y << ')';\n \
    \       return os;\n    }\n};\ntemplate <> double Point2d<double>::EPS = 1e-9;\n\
    template <> long double Point2d<long double>::EPS = 1e-12;\ntemplate <> long long\
    \ Point2d<long long>::EPS = 0;\n\ntemplate <typename T_P>\nint ccw(const Point2d<T_P>\
    \ &a, const Point2d<T_P> &b, const Point2d<T_P> &c) { // a->b->c\u306E\u66F2\u304C\
    \u308A\u65B9\n    Point2d<T_P> v1 = b - a;\n    Point2d<T_P> v2 = c - a;\n   \
    \ if (v1.det(v2) > Point2d<T_P>::EPS) return 1;   // \u5DE6\u6298\n    if (v1.det(v2)\
    \ < -Point2d<T_P>::EPS) return -1; // \u53F3\u6298\n    if (v1.dot(v2) < -Point2d<T_P>::EPS)\
    \ return 2;  // c-a-b\n    if (v1.norm() < v2.norm()) return -2;           //\
    \ a-b-c\n    return 0;                                       // a-c-b\n}\n\n//\
    \ Convex hull \uFF08\u51F8\u5305\uFF09\n// return: IDs of vertices used for convex\
    \ hull, counterclockwise\n// include_boundary: If true, interior angle pi is allowed\n\
    template <typename T_P>\nstd::vector<int> convex_hull(const std::vector<Point2d<T_P>>\
    \ &ps, bool include_boundary = false) {\n    int n = ps.size();\n    if (n <=\
    \ 1) return std::vector<int>(n, 0);\n    std::vector<std::pair<Point2d<T_P>, int>>\
    \ points(n);\n    for (size_t i = 0; i < ps.size(); i++) points[i] = std::make_pair(ps[i],\
    \ i);\n    std::sort(points.begin(), points.end());\n    int k = 0;\n    std::vector<std::pair<Point2d<T_P>,\
    \ int>> qs(2 * n);\n    auto ccw_check = [&](int c) { return include_boundary\
    \ ? (c == -1) : (c <= 0); };\n    for (int i = 0; i < n; i++) {\n        while\
    \ (k > 1 and ccw_check(ccw(qs[k - 2].first, qs[k - 1].first, points[i].first)))\
    \ k--;\n        qs[k++] = points[i];\n    }\n    for (int i = n - 2, t = k; i\
    \ >= 0; i--) {\n        while (k > t and ccw_check(ccw(qs[k - 2].first, qs[k -\
    \ 1].first, points[i].first))) k--;\n        qs[k++] = points[i];\n    }\n   \
    \ std::vector<int> ret(k - 1);\n    for (int i = 0; i < k - 1; i++) ret[i] = qs[i].second;\n\
    \    return ret;\n}\n\n// Solve r1 + t1 * v1 == r2 + t2 * v2\ntemplate <typename\
    \ T_P>\nPoint2d<T_P> lines_crosspoint(Point2d<T_P> r1, Point2d<T_P> v1, Point2d<T_P>\
    \ r2, Point2d<T_P> v2) {\n    assert(v2.det(v1) != 0);\n    return r1 + v1 * (v2.det(r2\
    \ - r1) / v2.det(v1));\n}\n\n// Whether two segments s1t1 & s2t2 intersect or\
    \ not (endpoints not included)\n// Google Code Jam 2013 Round 3 - Rural Planning\n\
    // Google Code Jam 2021 Round 3 - Fence Design\ntemplate <typename T> bool intersect_open_segments(Point2d<T>\
    \ s1, Point2d<T> t1, Point2d<T> s2, Point2d<T> t2) {\n    if (s1 == t1 or s2 ==\
    \ t2) return false; // Not segment but point\n    int nbad = 0;\n    for (int\
    \ t = 0; t < 2; t++) {\n        Point2d<T> v1 = t1 - s1, v2 = t2 - s2;\n     \
    \   T den = v2.det(v1);\n        if (den == 0) {\n            if (s1.det(v1) ==\
    \ s2.det(v1)) {\n                auto L1 = s1.dot(v1), R1 = t1.dot(v1);\n    \
    \            auto L2 = s2.dot(v1), R2 = t2.dot(v1);\n                if (L1 >\
    \ R1) std::swap(L1, R1);\n                if (L2 > R2) std::swap(L2, R2);\n  \
    \              if (L1 > L2) std::swap(L1, L2), std::swap(R1, R2);\n          \
    \      return R1 > L2;\n            } else {\n                return false;\n\
    \            }\n        } else {\n            auto num = v2.det(s2 - s1);\n  \
    \          if ((0 < num and num < den) or (den < num and num < 0)) nbad++;\n \
    \       }\n        std::swap(s1, s2);\n        std::swap(t1, t2);\n    }\n   \
    \ return nbad == 2;\n}\n\n// Whether point p is on segment (s, t) (endpoints not\
    \ included)\n// Google Code Jam 2013 Round 3 - Rural Planning\ntemplate <typename\
    \ PointNd> bool is_point_on_open_segment(PointNd s, PointNd t, PointNd p) {\n\
    \    if (s == t) return false; // not segment but point\n    if (p == s or p ==\
    \ t) return false;\n    auto v = t - s, w = p - s;\n    if (v.absdet(w)) return\
    \ false;\n    auto vv = v.dot(v), vw = v.dot(w);\n    return vw > 0 and vw < vv;\n\
    }\n\n// Convex cut\n// Cut the convex polygon g by line p1->p2 and return the\
    \ leftward one\ntemplate <typename T_P>\nstd::vector<Point2d<T_P>> convex_cut(const\
    \ std::vector<Point2d<T_P>> &g, Point2d<T_P> p1, Point2d<T_P> p2) {\n    assert(p1\
    \ != p2);\n    std::vector<Point2d<T_P>> ret;\n    for (int i = 0; i < (int)g.size();\
    \ i++) {\n        const Point2d<T_P> &now = g[i], &nxt = g[(i + 1) % g.size()];\n\
    \        if (ccw(p1, p2, now) != -1) ret.push_back(now);\n        if ((ccw(p1,\
    \ p2, now) == -1) xor (ccw(p1, p2, nxt) == -1)) {\n            ret.push_back(lines_crosspoint(now,\
    \ nxt - now, p1, p2 - p1));\n        }\n    }\n    return ret;\n}\n\n// 2\u5186\
    \u306E\u4EA4\u70B9 (ABC157F)\ntemplate <typename T_P>\nstd::vector<Point2d<T_P>>\
    \ IntersectTwoCircles(const Point2d<T_P> &Ca, double Ra, const Point2d<T_P> &Cb,\
    \ double Rb) {\n    double d = (Ca - Cb).norm();\n    if (Ra + Rb < d) return\
    \ {};\n    double rc = (d * d + Ra * Ra - Rb * Rb) / (2 * d);\n    double rs =\
    \ sqrt(Ra * Ra - rc * rc);\n    Point2d<T_P> diff = (Cb - Ca) / d;\n    return\
    \ {Ca + diff * Point2d<T_P>(rc, rs), Ca + diff * Point2d<T_P>(rc, -rs)};\n}\n\n\
    // Solve |x0 + vt| = R (SRM 543 Div.1 1000, GCJ 2016 R3 C)\ntemplate <typename\
    \ PointNd, typename Float>\nstd::vector<Float> IntersectCircleLine(const PointNd\
    \ &x0, const PointNd &v, Float R) {\n    Float b = Float(x0.dot(v)) / v.norm2();\n\
    \    Float c = Float(x0.norm2() - Float(R) * R) / v.norm2();\n    if (b * b -\
    \ c < 0) return {};\n    Float ret1 = -b + sqrtl(b * b - c) * (b > 0 ? -1 : 1);\n\
    \    Float ret2 = c / ret1;\n    return ret1 < ret2 ? std::vector<Float>{ret1,\
    \ ret2} : std::vector<Float>{ret2, ret1};\n}\n\n// Distance between point p <->\
    \ line ab\ntemplate <typename PointFloat>\ndecltype(PointFloat::x) DistancePointLine(const\
    \ PointFloat &p, const PointFloat &a, const PointFloat &b) {\n    assert(a !=\
    \ b);\n    return (b - a).absdet(p - a) / (b - a).norm();\n}\n\n// Distance between\
    \ point p <-> line segment ab\ntemplate <typename PointFloat>\ndecltype(PointFloat::x)\
    \ DistancePointSegment(const PointFloat &p, const PointFloat &a, const PointFloat\
    \ &b) {\n    if (a == b) {\n        return (p - a).norm();\n    } else if ((p\
    \ - a).dot(b - a) <= 0) {\n        return (p - a).norm();\n    } else if ((p -\
    \ b).dot(a - b) <= 0) {\n        return (p - b).norm();\n    } else {\n      \
    \  return DistancePointLine<PointFloat>(p, a, b);\n    }\n}\n\n// Area of polygon\
    \ (might be negative)\ntemplate <typename T_P> T_P signed_area_of_polygon(const\
    \ std::vector<Point2d<T_P>> &poly) {\n    T_P area = 0;\n    for (size_t i = 0;\
    \ i < poly.size(); i++) area += poly[i].det(poly[(i + 1) % poly.size()]);\n  \
    \  return area * 0.5;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: geometry/geometry.hpp
  requiredBy:
  - geometry/triangle.hpp
  - geometry/problem_of_apollonius.hpp
  timestamp: '2021-06-06 03:50:20+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - geometry/test/convex_cut.test.cpp
  - geometry/test/convex_hull.test.cpp
  - geometry/test/circumcenter.test.cpp
documentation_of: geometry/geometry.hpp
layout: document
redirect_from:
- /library/geometry/geometry.hpp
- /library/geometry/geometry.hpp.html
title: geometry/geometry.hpp
---
