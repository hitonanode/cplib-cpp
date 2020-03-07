---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :warning: geometry/geometry2d.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#ed7daeb157cd9b31e53896ad3c771a26">geometry</a>
* <a href="{{ site.github.repository_url }}/blob/master/geometry/geometry2d.hpp">View this file on GitHub</a>
    - Last commit date: 2020-03-07 22:40:57+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <algorithm>
#include <cassert>
#include <cmath>
#include <complex>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

// CUT begin
/*
using T_P = double;
constexpr T_P EPS = 1E-9;
*/

struct P
{
    T_P x, y;
    P(T_P x = 0, T_P y = 0) : x(x), y(y) {}
    P(pair<T_P, T_P> p) : x(p.first), y(p.second) {}
    static T_P add_w_error(T_P a, T_P b) { return (abs(a + b) < EPS * (abs(a) + abs(b))) ? 0 : a + b; }
    P operator+(const P &p) const { return P(add_w_error(x, p.x), add_w_error(y, p.y)); }
    P operator-(const P &p) const { return P(add_w_error(x, -p.x), add_w_error(y, -p.y)); }
    P operator*(const P &p) const { return P(add_w_error(x * p.x,  -y * p.y), add_w_error(x * p.y, y * p.x)); }
    P operator*(T_P d) const { return P(x * d, y * d); }
    P operator/(T_P d) const { return P(x / d, y / d); }
    P inv() const { return conj() / norm2(); }
    P operator/(const P &p) const { return (*this) * p.inv(); }
    bool operator<(const P &r) const{ return x != r.x ? x < r.x : y < r.y; }
    bool operator==(const P &r) const{ return add_w_error(x, -r.x) == 0 and add_w_error(y, -r.y) == 0; }
    T_P dot(P p) const { return add_w_error(x * p.x, y * p.y); }
    T_P det(P p) const { return add_w_error(x * p.y, -y * p.x); }
    T_P norm() const { return sqrt(x * x + y * y); }
    T_P norm2() const { return x * x + y * y; }
    T_P arg() const { return atan2(y, x); }
    // rotate point/vector by rad
    P rotate(T_P rad) { return P(add_w_error(x * cos(rad), -y * sin(rad)), add_w_error(x * sin(rad), y * cos(rad))); }
    P conj() const { return P(x, -y); }
    friend istream &operator>>(istream &is, P &p) { T_P x, y; is >> x >> y; p = P(x, y); return is; }
    friend ostream &operator<<(ostream &os, const P &p) { os << '(' << p.x << ',' << p.y << ')'; return os; }
};

struct L
{
    P a, b;
    L() {}
    L(P a, P b) : a(a), b(b) {}
};

struct C
{
    P center;
    T_P radius;
    C() : center(), radius(0) {}
    C(P c, T_P r) : center(c), radius(r) {}
};

int ccw(P a, P b, P c) // a->b->cの曲がり方
{
    P v1 = b - a;
    P v2 = c - a;
    if (v1.det(v2) > EPS) return 1; // 左折
    if (v1.det(v2) < -EPS) return -1; // 右折
    if (v1.dot(v2) < -EPS) return 2; // c-a-b
    if (v1.norm() < v2.norm()) return -2; // a-b-c
    return 0; // a-c-b
}


// Convex hull （凸包）
// return: IDs of vertices used for convex hull, counterclockwise
// include_boundary: If true, interior angle pi is allowed
vector<int> convex_hull(const vector<P> &ps, bool include_boundary=false)
{
    int n = ps.size();
    if (n <= 1) return vector<int>(n, 0);
    vector<pair<P, int>> points(n);
    for (size_t i = 0; i < ps.size(); i++) points[i] = make_pair(ps[i], i);
    sort(points.begin(), points.end());
    int k = 0;
    vector<pair<P, int> > qs(2 * n);
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
    vector<int> ret(k - 1);
    for (int i = 0; i < k - 1; i++) ret[i] = qs[i].second;
    return ret;
}

// Circumcenter （三角形の外心）
// - raise exception for collinear points
P circumcenter(P z1, P z2, P z3) {
    assert(abs(ccw(z1, z2, z3)) % 2 == 1);
    P a = z2 - z1, b = z3 - z1;
    return z1 + a * b * (a - b).conj() / (b * a.conj() - a * b.conj());
}


// 2円の交点 (ABC157F)
vector<P> IntersectTwoCircles(P Ca, double Ra, P Cb, double Rb) {
    double d = (Ca - Cb).norm();
    if (Ra + Rb < d) return {};
    double rc = (d * d + Ra * Ra - Rb * Rb) / (2 * d);
    double rs = sqrt(Ra * Ra - rc * rc);
    P diff = (Cb - Ca) / d;
    return {Ca + diff * P(rc, rs), Ca + diff * P(rc, -rs)};
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "geometry/geometry2d.hpp"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <complex>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

// CUT begin
/*
using T_P = double;
constexpr T_P EPS = 1E-9;
*/

struct P
{
    T_P x, y;
    P(T_P x = 0, T_P y = 0) : x(x), y(y) {}
    P(pair<T_P, T_P> p) : x(p.first), y(p.second) {}
    static T_P add_w_error(T_P a, T_P b) { return (abs(a + b) < EPS * (abs(a) + abs(b))) ? 0 : a + b; }
    P operator+(const P &p) const { return P(add_w_error(x, p.x), add_w_error(y, p.y)); }
    P operator-(const P &p) const { return P(add_w_error(x, -p.x), add_w_error(y, -p.y)); }
    P operator*(const P &p) const { return P(add_w_error(x * p.x,  -y * p.y), add_w_error(x * p.y, y * p.x)); }
    P operator*(T_P d) const { return P(x * d, y * d); }
    P operator/(T_P d) const { return P(x / d, y / d); }
    P inv() const { return conj() / norm2(); }
    P operator/(const P &p) const { return (*this) * p.inv(); }
    bool operator<(const P &r) const{ return x != r.x ? x < r.x : y < r.y; }
    bool operator==(const P &r) const{ return add_w_error(x, -r.x) == 0 and add_w_error(y, -r.y) == 0; }
    T_P dot(P p) const { return add_w_error(x * p.x, y * p.y); }
    T_P det(P p) const { return add_w_error(x * p.y, -y * p.x); }
    T_P norm() const { return sqrt(x * x + y * y); }
    T_P norm2() const { return x * x + y * y; }
    T_P arg() const { return atan2(y, x); }
    // rotate point/vector by rad
    P rotate(T_P rad) { return P(add_w_error(x * cos(rad), -y * sin(rad)), add_w_error(x * sin(rad), y * cos(rad))); }
    P conj() const { return P(x, -y); }
    friend istream &operator>>(istream &is, P &p) { T_P x, y; is >> x >> y; p = P(x, y); return is; }
    friend ostream &operator<<(ostream &os, const P &p) { os << '(' << p.x << ',' << p.y << ')'; return os; }
};

struct L
{
    P a, b;
    L() {}
    L(P a, P b) : a(a), b(b) {}
};

struct C
{
    P center;
    T_P radius;
    C() : center(), radius(0) {}
    C(P c, T_P r) : center(c), radius(r) {}
};

int ccw(P a, P b, P c) // a->b->cの曲がり方
{
    P v1 = b - a;
    P v2 = c - a;
    if (v1.det(v2) > EPS) return 1; // 左折
    if (v1.det(v2) < -EPS) return -1; // 右折
    if (v1.dot(v2) < -EPS) return 2; // c-a-b
    if (v1.norm() < v2.norm()) return -2; // a-b-c
    return 0; // a-c-b
}


// Convex hull （凸包）
// return: IDs of vertices used for convex hull, counterclockwise
// include_boundary: If true, interior angle pi is allowed
vector<int> convex_hull(const vector<P> &ps, bool include_boundary=false)
{
    int n = ps.size();
    if (n <= 1) return vector<int>(n, 0);
    vector<pair<P, int>> points(n);
    for (size_t i = 0; i < ps.size(); i++) points[i] = make_pair(ps[i], i);
    sort(points.begin(), points.end());
    int k = 0;
    vector<pair<P, int> > qs(2 * n);
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
    vector<int> ret(k - 1);
    for (int i = 0; i < k - 1; i++) ret[i] = qs[i].second;
    return ret;
}

// Circumcenter （三角形の外心）
// - raise exception for collinear points
P circumcenter(P z1, P z2, P z3) {
    assert(abs(ccw(z1, z2, z3)) % 2 == 1);
    P a = z2 - z1, b = z3 - z1;
    return z1 + a * b * (a - b).conj() / (b * a.conj() - a * b.conj());
}


// 2円の交点 (ABC157F)
vector<P> IntersectTwoCircles(P Ca, double Ra, P Cb, double Rb) {
    double d = (Ca - Cb).norm();
    if (Ra + Rb < d) return {};
    double rc = (d * d + Ra * Ra - Rb * Rb) / (2 * d);
    double rs = sqrt(Ra * Ra - rc * rc);
    P diff = (Cb - Ca) / d;
    return {Ca + diff * P(rc, rs), Ca + diff * P(rc, -rs)};
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

