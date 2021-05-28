#pragma once
#include <algorithm>
#include <cassert>
#include <cmath>
#include <complex>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>

// CUT begin
template <typename T_P> struct Point2d {
    static T_P EPS;
    static void set_eps(T_P e) { EPS = e; }
    T_P x, y;
    Point2d() : x(0), y(0) {}
    Point2d(T_P x, T_P y) : x(x), y(y) {}
    Point2d(const std::pair<T_P, T_P> &p) : x(p.first), y(p.second) {}
    Point2d(const std::complex<T_P> &p) : x(p.real()), y(p.imag()) {}
    std::complex<T_P> to_complex() const noexcept { return {x, y}; }
    Point2d operator+(const Point2d &p) const noexcept { return Point2d(x + p.x, y + p.y); }
    Point2d operator-(const Point2d &p) const noexcept { return Point2d(x - p.x, y - p.y); }
    Point2d operator*(const Point2d &p) const noexcept { return Point2d(x * p.x - y * p.y, x * p.y + y * p.x); }
    Point2d operator*(T_P d) const noexcept { return Point2d(x * d, y * d); }
    Point2d operator/(T_P d) const noexcept { return Point2d(x / d, y / d); }
    Point2d inv() const { return conj() / norm2(); }
    Point2d operator/(const Point2d &p) const { return (*this) * p.inv(); }
    bool operator<(const Point2d &r) const noexcept { return x != r.x ? x < r.x : y < r.y; }
    bool operator==(const Point2d &r) const noexcept { return x == r.x and y == r.y; }
    bool operator!=(const Point2d &r) const noexcept { return !((*this) == r); }
    T_P dot(Point2d p) const noexcept { return x * p.x + y * p.y; }
    T_P det(Point2d p) const noexcept { return x * p.y - y * p.x; }
    T_P absdet(Point2d p) const noexcept { return std::abs(det(p)); }
    T_P norm() const noexcept { return std::sqrt(x * x + y * y); }
    T_P norm2() const noexcept { return x * x + y * y; }
    T_P arg() const noexcept { return std::atan2(y, x); }
    // rotate point/vector by rad
    Point2d rotate(T_P rad) const noexcept {
        return Point2d(x * std::cos(rad) - y * std::sin(rad), x * std::sin(rad) + y * std::cos(rad));
    }
    Point2d normalized() const { return (*this) / this->norm(); }
    Point2d conj() const noexcept { return Point2d(x, -y); }
    friend std::istream &operator>>(std::istream &is, Point2d &p) {
        T_P x, y;
        is >> x >> y;
        p = Point2d(x, y);
        return is;
    }
    friend std::ostream &operator<<(std::ostream &os, const Point2d &p) {
        os << '(' << p.x << ',' << p.y << ')';
        return os;
    }
};
template <> double Point2d<double>::EPS = 1e-9;
template <> long double Point2d<long double>::EPS = 1e-12;

template <typename T_P>
int ccw(const Point2d<T_P> &a, const Point2d<T_P> &b, const Point2d<T_P> &c) { // a->b->cの曲がり方
    Point2d<T_P> v1 = b - a;
    Point2d<T_P> v2 = c - a;
    if (v1.det(v2) > Point2d<T_P>::EPS) return 1;   // 左折
    if (v1.det(v2) < -Point2d<T_P>::EPS) return -1; // 右折
    if (v1.dot(v2) < -Point2d<T_P>::EPS) return 2;  // c-a-b
    if (v1.norm() < v2.norm()) return -2;           // a-b-c
    return 0;                                       // a-c-b
}

// Convex hull （凸包）
// return: IDs of vertices used for convex hull, counterclockwise
// include_boundary: If true, interior angle pi is allowed
template <typename T_P>
std::vector<int> convex_hull(const std::vector<Point2d<T_P>> &ps, bool include_boundary = false) {
    int n = ps.size();
    if (n <= 1) return std::vector<int>(n, 0);
    std::vector<std::pair<Point2d<T_P>, int>> points(n);
    for (size_t i = 0; i < ps.size(); i++) points[i] = std::make_pair(ps[i], i);
    std::sort(points.begin(), points.end());
    int k = 0;
    std::vector<std::pair<Point2d<T_P>, int>> qs(2 * n);
    auto ccw_check = [&](int c) { return include_boundary ? (c == -1) : (c <= 0); };
    for (int i = 0; i < n; i++) {
        while (k > 1 and ccw_check(ccw(qs[k - 2].first, qs[k - 1].first, points[i].first))) k--;
        qs[k++] = points[i];
    }
    for (int i = n - 2, t = k; i >= 0; i--) {
        while (k > t and ccw_check(ccw(qs[k - 2].first, qs[k - 1].first, points[i].first))) k--;
        qs[k++] = points[i];
    }
    std::vector<int> ret(k - 1);
    for (int i = 0; i < k - 1; i++) ret[i] = qs[i].second;
    return ret;
}

// Solve r1 + t1 * v1 == r2 + t2 * v2
template <typename T_P>
Point2d<T_P> lines_crosspoint(Point2d<T_P> r1, Point2d<T_P> v1, Point2d<T_P> r2, Point2d<T_P> v2) {
    assert(v2.det(v1) != 0);
    return r1 + v1 * (v2.det(r2 - r1) / v2.det(v1));
}

// Whether two segments s1t1 & s2t2 intersect or not (not include endpoints)
// Google Code Jam 2013 Round 3 - Rural Planning
template <typename T> int intersect_open_segments(Point2d<T> s1, Point2d<T> t1, Point2d<T> s2, Point2d<T> t2) {
    if (s1 == t1 or s2 == t2) return false;
    Point2d<T> v1 = t1 - s1, v2 = t2 - s2;
    int nbad = 0;
    for (int t = 0; t < 2; t++) {
        T den = v2.det(v1);
        if (den == 0) {
            if (s1.det(v1) == s2.det(v1)) {
                auto L1 = s1.dot(v1), R1 = (s1 + v1).dot(v1);
                auto L2 = s2.dot(v1), R2 = (s2 + v2).dot(v1);
                if (L1 > R1) std::swap(L1, R1);
                if (L2 > R2) std::swap(L2, R2);
                if (L1 > L2) std::swap(L1, L2), std::swap(R1, R2);
                return R1 > L2;
            } else {
                return false;
            }
        }
        auto num = v2.det(s2 - s1);
        if (den * num < 0 or (num >= den and den > 0) or (num <= den and den < 0)) {
            //
        } else {
            nbad++;
        }
        std::swap(s1, s2);
        std::swap(v1, v2);
    }
    return nbad >= 2;
}

// Convex cut
// Cut the convex polygon g by line p1->p2 and return the leftward one
template <typename T_P>
std::vector<Point2d<T_P>> convex_cut(const std::vector<Point2d<T_P>> &g, Point2d<T_P> p1, Point2d<T_P> p2) {
    assert(p1 != p2);
    std::vector<Point2d<T_P>> ret;
    for (int i = 0; i < (int)g.size(); i++) {
        const Point2d<T_P> &now = g[i], &nxt = g[(i + 1) % g.size()];
        if (ccw(p1, p2, now) != -1) ret.push_back(now);
        if ((ccw(p1, p2, now) == -1) xor (ccw(p1, p2, nxt) == -1)) {
            ret.push_back(lines_crosspoint(now, nxt - now, p1, p2 - p1));
        }
    }
    return ret;
}

// 2円の交点 (ABC157F)
template <typename T_P>
std::vector<Point2d<T_P>> IntersectTwoCircles(const Point2d<T_P> &Ca, double Ra, const Point2d<T_P> &Cb, double Rb) {
    double d = (Ca - Cb).norm();
    if (Ra + Rb < d) return {};
    double rc = (d * d + Ra * Ra - Rb * Rb) / (2 * d);
    double rs = sqrt(Ra * Ra - rc * rc);
    Point2d<T_P> diff = (Cb - Ca) / d;
    return {Ca + diff * Point2d<T_P>(rc, rs), Ca + diff * Point2d<T_P>(rc, -rs)};
}

// Solve |x0 + vt| = R (SRM 543 Div.1 1000, GCJ 2016 R3 C)
template <typename PointNd, typename Float>
std::vector<Float> IntersectCircleLine(const PointNd &x0, const PointNd &v, Float R) {
    Float b = Float(x0.dot(v)) / v.norm2();
    Float c = Float(x0.norm2() - Float(R) * R) / v.norm2();
    if (b * b - c < 0) return {};
    Float ret1 = -b + sqrtl(b * b - c) * (b > 0 ? -1 : 1);
    Float ret2 = c / ret1;
    return ret1 < ret2 ? std::vector<Float>{ret1, ret2} : std::vector<Float>{ret2, ret1};
}

// Distance between point p <-> line ab
template <typename PointFloat>
decltype(PointFloat::x) DistancePointLine(const PointFloat &p, const PointFloat &a, const PointFloat &b) {
    assert(a != b);
    return (b - a).absdet(p - a) / (b - a).norm();
}

// Distance between point p <-> line segment ab
template <typename PointFloat>
decltype(PointFloat::x) DistancePointSegment(const PointFloat &p, const PointFloat &a, const PointFloat &b) {
    if (a == b) {
        return (p - a).norm();
    } else if ((p - a).dot(b - a) <= 0) {
        return (p - a).norm();
    } else if ((p - b).dot(a - b) <= 0) {
        return (p - b).norm();
    } else {
        return DistancePointLine<PointFloat>(p, a, b);
    }
}

// Area of polygon (might be negative)
template <typename T_P> T_P signed_area_of_polygon(const std::vector<Point2d<T_P>> &poly) {
    T_P area = 0;
    for (size_t i = 0; i < poly.size(); i++) area += poly[i].det(poly[(i + 1) % poly.size()]);
    return area * 0.5;
}
