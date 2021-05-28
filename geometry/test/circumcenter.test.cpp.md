---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: geometry/geometry.hpp
    title: geometry/geometry.hpp
  - icon: ':heavy_check_mark:'
    path: geometry/point3d.hpp
    title: geometry/point3d.hpp
  - icon: ':heavy_check_mark:'
    path: geometry/triangle.hpp
    title: geometry/triangle.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    ERROR: '0.000001'
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_C
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_C
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
    \ = 1e-9;\ntemplate <> long double Point2d<long double>::EPS = 1e-12;\n\ntemplate\
    \ <typename T_P>\nint ccw(const Point2d<T_P> &a, const Point2d<T_P> &b, const\
    \ Point2d<T_P> &c) { // a->b->c\u306E\u66F2\u304C\u308A\u65B9\n    Point2d<T_P>\
    \ v1 = b - a;\n    Point2d<T_P> v2 = c - a;\n    if (v1.det(v2) > Point2d<T_P>::EPS)\
    \ return 1;   // \u5DE6\u6298\n    if (v1.det(v2) < -Point2d<T_P>::EPS) return\
    \ -1; // \u53F3\u6298\n    if (v1.dot(v2) < -Point2d<T_P>::EPS) return 2;  //\
    \ c-a-b\n    if (v1.norm() < v2.norm()) return -2;           // a-b-c\n    return\
    \ 0;                                       // a-c-b\n}\n\n// Convex hull \uFF08\
    \u51F8\u5305\uFF09\n// return: IDs of vertices used for convex hull, counterclockwise\n\
    // include_boundary: If true, interior angle pi is allowed\ntemplate <typename\
    \ T_P>\nstd::vector<int> convex_hull(const std::vector<Point2d<T_P>> &ps, bool\
    \ include_boundary = false) {\n    int n = ps.size();\n    if (n <= 1) return\
    \ std::vector<int>(n, 0);\n    std::vector<std::pair<Point2d<T_P>, int>> points(n);\n\
    \    for (size_t i = 0; i < ps.size(); i++) points[i] = std::make_pair(ps[i],\
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
    \ not (not include endpoints)\n// Google Code Jam 2013 Round 3 - Rural Planning\n\
    template <typename T> int intersect_open_segments(Point2d<T> s1, Point2d<T> t1,\
    \ Point2d<T> s2, Point2d<T> t2) {\n    if (s1 == t1 or s2 == t2) return false;\n\
    \    Point2d<T> v1 = t1 - s1, v2 = t2 - s2;\n    int nbad = 0;\n    for (int t\
    \ = 0; t < 2; t++) {\n        T den = v2.det(v1);\n        if (den == 0) {\n \
    \           if (s1.det(v1) == s2.det(v1)) {\n                auto L1 = s1.dot(v1),\
    \ R1 = (s1 + v1).dot(v1);\n                auto L2 = s2.dot(v1), R2 = (s2 + v2).dot(v1);\n\
    \                if (L1 > R1) std::swap(L1, R1);\n                if (L2 > R2)\
    \ std::swap(L2, R2);\n                if (L1 > L2) std::swap(L1, L2), std::swap(R1,\
    \ R2);\n                return R1 > L2;\n            } else {\n              \
    \  return false;\n            }\n        }\n        auto num = v2.det(s2 - s1);\n\
    \        if (den * num < 0 or (num >= den and den > 0) or (num <= den and den\
    \ < 0)) {\n            //\n        } else {\n            nbad++;\n        }\n\
    \        std::swap(s1, s2);\n        std::swap(v1, v2);\n    }\n    return nbad\
    \ >= 2;\n}\n\n// Convex cut\n// Cut the convex polygon g by line p1->p2 and return\
    \ the leftward one\ntemplate <typename T_P>\nstd::vector<Point2d<T_P>> convex_cut(const\
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
    \  return area * 0.5;\n}\n#line 5 \"geometry/point3d.hpp\"\n\n// CUT begin\ntemplate\
    \ <typename T> struct Point3d {\n    T x, y, z;\n    Point3d() : x(0), y(0), z(0)\
    \ {}\n    Point3d(T x_, T y_, T z_) : x(x_), y(y_), z(z_) {}\n    Point3d(const\
    \ std::tuple<T, T, T> &init) { std::tie(x, y, z) = init; }\n    Point3d operator+(const\
    \ Point3d &p) const noexcept { return {x + p.x, y + p.y, z + p.z}; }\n    Point3d\
    \ operator-(const Point3d &p) const noexcept { return {x - p.x, y - p.y, z - p.z};\
    \ }\n    Point3d operator*(T d) const noexcept { return {x * d, y * d, z * d};\
    \ }\n    Point3d operator/(T d) const { return {x / d, y / d, z / d}; }\n    bool\
    \ operator<(const Point3d &r) const noexcept { return x != r.x ? x < r.x : (y\
    \ != r.y ? y < r.y : z < r.z); }\n    bool operator==(const Point3d &r) const\
    \ noexcept { return x == r.x and y == r.y and z == r.z; }\n    bool operator!=(const\
    \ Point3d &r) const noexcept { return !((*this) == r); }\n    T dot(const Point3d\
    \ &p) const noexcept { return x * p.x + y * p.y + z * p.z; }\n    T absdet(const\
    \ Point3d &p) const noexcept {\n        return Point3d(y * p.z - z * p.y, z *\
    \ p.x - x * p.z, x * p.y - y * p.x).norm();\n    }\n    T norm() const noexcept\
    \ { return std::sqrt(x * x + y * y + z * z); }\n    T norm2() const noexcept {\
    \ return x * x + y * y + z * z; }\n    Point3d normalized() const { return (*this)\
    \ / this->norm(); }\n    friend std::istream &operator>>(std::istream &is, Point3d\
    \ &p) { return is >> p.x >> p.y >> p.z; }\n    friend std::ostream &operator<<(std::ostream\
    \ &os, const Point3d &p) {\n        return os << '(' << p.x << ',' << p.y << ','\
    \ << p.z << ')';\n    }\n};\n#line 5 \"geometry/triangle.hpp\"\n\n// CUT begin\n\
    // Circumcenter \uFF08\u4E09\u89D2\u5F62\u306E\u5916\u5FC3\uFF09\ntemplate <typename\
    \ Float>\nPoint2d<Float> circumcenter(const Point2d<Float> &A, const Point2d<Float>\
    \ &B, const Point2d<Float> &C) {\n    std::complex<Float> a = (C - A).to_complex(),\
    \ b = (B - A).to_complex();\n    return A + Point2d<Float>(a * b * std::conj(a\
    \ - b) / (std::conj(a) * b - a * std::conj(b)));\n}\ntemplate <typename Float>\n\
    Point3d<Float> circumcenter(const Point3d<Float> &A, const Point3d<Float> &B,\
    \ const Point3d<Float> &C) {\n    auto a = (B - C).norm(), b = (C - A).norm(),\
    \ c = (A - B).norm();\n    auto acosA = a * a * (C - A).dot(B - A);\n    auto\
    \ bcosB = b * b * (A - B).dot(C - B);\n    auto ccosC = c * c * (B - C).dot(A\
    \ - C);\n    return (A * acosA + B * bcosB + C * ccosC) / (acosA + bcosB + ccosC);\n\
    }\n#line 3 \"geometry/test/circumcenter.test.cpp\"\n#include <iomanip>\n#line\
    \ 5 \"geometry/test/circumcenter.test.cpp\"\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_C\"\
    \n#define ERROR 0.000001\nusing namespace std;\n\nint main() {\n    Point2d<long\
    \ double> X, Y, Z;\n    cin >> X >> Y >> Z;\n    auto c = circumcenter(X, Y, Z);\n\
    \    cout << fixed << setprecision(10) << c.x << ' ' << c.y << ' ' << (X - c).norm()\
    \ << '\\n';\n}\n"
  code: "#include \"../geometry.hpp\"\n#include \"../triangle.hpp\"\n#include <iomanip>\n\
    #include <iostream>\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_C\"\
    \n#define ERROR 0.000001\nusing namespace std;\n\nint main() {\n    Point2d<long\
    \ double> X, Y, Z;\n    cin >> X >> Y >> Z;\n    auto c = circumcenter(X, Y, Z);\n\
    \    cout << fixed << setprecision(10) << c.x << ' ' << c.y << ' ' << (X - c).norm()\
    \ << '\\n';\n}\n"
  dependsOn:
  - geometry/geometry.hpp
  - geometry/triangle.hpp
  - geometry/point3d.hpp
  isVerificationFile: true
  path: geometry/test/circumcenter.test.cpp
  requiredBy: []
  timestamp: '2021-05-28 14:56:25+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: geometry/test/circumcenter.test.cpp
layout: document
redirect_from:
- /verify/geometry/test/circumcenter.test.cpp
- /verify/geometry/test/circumcenter.test.cpp.html
title: geometry/test/circumcenter.test.cpp
---
