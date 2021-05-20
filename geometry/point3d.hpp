#pragma once
#include <cmath>
#include <iostream>
#include <tuple>

// CUT begin
template <typename T> struct Point3d {
    T x, y, z;
    Point3d() : x(0), y(0), z(0) {}
    Point3d(T x_, T y_, T z_) : x(x_), y(y_), z(z_) {}
    Point3d(const std::tuple<T, T, T> &init) { std::tie(x, y, z) = init; }
    Point3d operator+(const Point3d &p) const noexcept { return {x + p.x, y + p.y, z + p.z}; }
    Point3d operator-(const Point3d &p) const noexcept { return {x - p.x, y - p.y, z - p.z}; }
    Point3d operator*(T d) const noexcept { return {x * d, y * d, z * d}; }
    Point3d operator/(T d) const { return {x / d, y / d, z / d}; }
    bool operator<(const Point3d &r) const noexcept { return x != r.x ? x < r.x : (y != r.y ? y < r.y : z < r.z); }
    bool operator==(const Point3d &r) const noexcept { return x == r.x and y == r.y and z == r.z; }
    bool operator!=(const Point3d &r) const noexcept { return !((*this) == r); }
    T dot(const Point3d &p) const noexcept { return x * p.x + y * p.y + z * p.z; }
    T absdet(const Point3d &p) const noexcept {
        return Point3d(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x).norm();
    }
    T norm() const noexcept { return std::sqrt(x * x + y * y + z * z); }
    T norm2() const noexcept { return x * x + y * y + z * z; }
    Point3d normalized() const { return (*this) / this->norm(); }
    friend std::istream &operator>>(std::istream &is, Point3d &p) { return is >> p.x >> p.y >> p.z; }
    friend std::ostream &operator<<(std::ostream &os, const Point3d &p) {
        return os << '(' << p.x << ',' << p.y << ',' << p.z << ')';
    }
};
