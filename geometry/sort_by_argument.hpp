#pragma once
#include <cmath>

// CUT begin
// Point on grid, sortable by its argument
struct Point {
    constexpr static double eps = 1e-2;
    long long X, Y;
    double theta;
    Point() = default;
    Point(long long x, long long y) : X(x), Y(y), theta(std::atan2(y, x)) {}
    bool operator<(const Point &r) const {
        double b = theta - r.theta;
        return std::abs(b) > eps ? (b < 0) : (X * r.Y > r.X * Y);
    }
    bool operator==(const Point &r) const { return std::abs(theta - r.theta) < eps and X * r.Y == r.X * Y; }
    void rotate_pi() {
        theta += M_PI;
        X *= -1;
        Y *= -1;
    }
};
