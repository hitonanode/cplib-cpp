#pragma once
#include <cmath>
#include <iostream>
#include <utility>

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
