#pragma once
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <utility>
#include <vector>


// CUT begin
template <typename T_P>
struct P
{
    static T_P EPS;
    static void set_eps(T_P e)
    {
        EPS = e;
    }
    T_P x, y;
    P() : x(0), y(0) {}
    P(T_P x, T_P y) : x(x), y(y) {}
    P(std::pair<T_P, T_P> p) : x(p.first), y(p.second) {}
    static T_P add_w_error(T_P a, T_P b) noexcept { return (std::abs(a + b) < P::EPS * (std::abs(a) + std::abs(b))) ? 0 : a + b; }
    P operator+(const P &p) const noexcept { return P(add_w_error(x, p.x), add_w_error(y, p.y)); }
    P operator-(const P &p) const noexcept { return P(add_w_error(x, -p.x), add_w_error(y, -p.y)); }
    P operator*(const P &p) const noexcept { return P(add_w_error(x * p.x,  -y * p.y), add_w_error(x * p.y, y * p.x)); }
    P operator*(T_P d) const noexcept { return P(x * d, y * d); }
    P operator/(T_P d) const noexcept { return P(x / d, y / d); }
    P inv() const { return conj() / norm2(); }
    P operator/(const P &p) const { return (*this) * p.inv(); }
    bool operator<(const P &r) const noexcept { return x != r.x ? x < r.x : y < r.y; }
    bool operator==(const P &r) const noexcept { return add_w_error(x, -r.x) == 0 and add_w_error(y, -r.y) == 0; }
    bool operator!=(const P &r) const noexcept { return !((*this) == r); }
    T_P dot(P p) const noexcept { return add_w_error(x * p.x, y * p.y); }
    T_P det(P p) const noexcept { return add_w_error(x * p.y, -y * p.x); }
    T_P norm() const noexcept { return std::sqrt(x * x + y * y); }
    T_P norm2() const noexcept { return x * x + y * y; }
    T_P arg() const noexcept { return std::atan2(y, x); }
    // rotate point/vector by rad
    P rotate(T_P rad) noexcept { return P(add_w_error(x * std::cos(rad), -y * std::sin(rad)), add_w_error(x * std::sin(rad), y * std::cos(rad))); }
    P normalized() const { return (*this) / this->norm(); }
    P conj() const noexcept { return P(x, -y); }
    friend std::istream &operator>>(std::istream &is, P &p) { T_P x, y; is >> x >> y; p = P(x, y); return is; }
    friend std::ostream &operator<<(std::ostream &os, const P &p) { os << '(' << p.x << ',' << p.y << ')'; return os; }
};
template <>
double P<double>::EPS = 1e-9;
template <>
long double P<long double>::EPS = 1e-12;


template <typename T_P>
int ccw(const P<T_P> &a, const P<T_P> &b, const P<T_P> &c) // a->b->cの曲がり方
{
    P<T_P> v1 = b - a;
    P<T_P> v2 = c - a;
    if (v1.det(v2) > P<T_P>::EPS) return 1; // 左折
    if (v1.det(v2) < -P<T_P>::EPS) return -1; // 右折
    if (v1.dot(v2) < -P<T_P>::EPS) return 2; // c-a-b
    if (v1.norm() < v2.norm()) return -2; // a-b-c
    return 0; // a-c-b
}


// Convex hull （凸包）
// return: IDs of vertices used for convex hull, counterclockwise
// include_boundary: If true, interior angle pi is allowed
template <typename T_P>
std::vector<int> convex_hull(const std::vector<P<T_P>> &ps, bool include_boundary = false)
{
    int n = ps.size();
    if (n <= 1) return std::vector<int>(n, 0);
    std::vector<std::pair<P<T_P>, int>> points(n);
    for (size_t i = 0; i < ps.size(); i++) points[i] = std::make_pair(ps[i], i);
    std::sort(points.begin(), points.end());
    int k = 0;
    std::vector<std::pair<P<T_P>, int>> qs(2 * n);
    auto ccw_check = [&](int c) {
        if (include_boundary) return c == -1;
        else return c <= 0;
    };
    for (int i = 0; i < n; i++)
    {
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

// Circumcenter （三角形の外心）
// - raise exception for collinear points
template <typename T_P>
P<T_P> circumcenter(const P<T_P> &z1, const P<T_P> &z2, const P<T_P> &z3)
{
    assert(abs(ccw(z1, z2, z3)) % 2 == 1);
    P<T_P> a = z2 - z1, b = z3 - z1;
    return z1 + a * b * (a - b).conj() / (b * a.conj() - a * b.conj());
}

// 2円の交点 (ABC157F)
template <typename T_P>
std::vector<P<T_P>> IntersectTwoCircles(const P<T_P> &Ca, double Ra, const P<T_P> &Cb, double Rb)
{
    double d = (Ca - Cb).norm();
    if (Ra + Rb < d) return {};
    double rc = (d * d + Ra * Ra - Rb * Rb) / (2 * d);
    double rs = sqrt(Ra * Ra - rc * rc);
    P<T_P> diff = (Cb - Ca) / d;
    return {Ca + diff * P<T_P>(rc, rs), Ca + diff * P<T_P>(rc, -rs)};
}

// Solve |x0 + vt| = R (SRM 543 Div.1 1000)
template <typename T_P>
std::vector<T_P> IntersectCircleLine(const P<T_P> &x0, const P<T_P> &v, T_P R)
{
    T_P b = x0.dot(v) / v.norm2();
    T_P c = (x0.norm2() - R * R) / v.norm2();
    if (b * b - c < 0) return {};
    T_P ret1;
    if (b > 0) ret1 = -b - sqrt(b * b - c);
    else ret1 = -b + sqrt(b * b - c);
    T_P ret2 = c / ret1;
    std::vector<T_P> ret{ret1, ret2};
    std::sort(ret.begin(), ret.end());
    return ret;
}

// Distance between point p <-> line ab
template <typename T_P>
T_P DistancePointLine(const P<T_P> &p, const P<T_P> &a, const P<T_P> &b)
{
    assert(a != b);
    return std::abs((b - a).det(p - a)) / (b - a).norm();
}

// Distance between point p <-> line segment ab
template <typename T_P>
T_P DistancePointSegment(const P<T_P> &p, const P<T_P> &a, const P<T_P> &b)
{
    if (a == b) return (p - a).norm();
    else if ((p - a).dot(b - a) <= 0) return (p - a).norm();
    else if ((p - b).dot(a - b) <= 0) return (p - b).norm();
    else return DistancePointLine(p, a, b);
}

// Area of polygon (might be negative)
template <typename T_P>
T_P signed_area_of_polygon(const std::vector<P<T_P>>& poly)
{
    T_P area = 0;
    for (size_t i = 0; i < poly.size(); i++) {
        area += poly[i].det(poly[(i + 1) % poly.size()]);
    }
    return area * 0.5;
}
