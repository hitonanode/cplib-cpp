#pragma once
#include "../utilities/quadratic_solver.hpp"
#include "geometry.hpp"
#include <utility>
#include <vector>

// CUT begin
// アポロニウスの問題：3円に接する円の中心と半径
// Verify: TCO 2020 North America Qualifier 1000
// input:
// - Center* : 各円の中心座標
// - Radius* : 各円の半径
// - sgn*    : 外接(-1) / 内接(1)
// retval:
// - [(Center, Radius), ...] （条件をみたす円は複数存在しうる）
template <typename Float>
std::vector<std::pair<Point2d<Float>, Float>> Problem_of_Apollonius(Point2d<Float> Center1, Float Radius1, Point2d<Float> Center2, Float Radius2, Point2d<Float> Center3, Float Radius3, int sgn1, int sgn2, int sgn3) {
    Center2 = Center2 - Center1, Center3 = Center3 - Center1;
    Float a2 = -Center2.x * 2, b2 = -Center2.y * 2, c2 = (-Radius1 * sgn1 + Radius2 * sgn2) * 2,
          d2 = -Radius1 * Radius1 - Center2.norm2() + Radius2 * Radius2;
    Float a3 = -Center3.x * 2, b3 = -Center3.y * 2, c3 = (-Radius1 * sgn1 + Radius3 * sgn3) * 2,
          d3 = -Radius1 * Radius1 - Center3.norm2() + Radius3 * Radius3;
    Float denom = a2 * b3 - b2 * a3;
    std::vector<std::pair<Point2d<Float>, Float>> ret_circles;
    if (denom == 0) return ret_circles;
    Point2d<Float> v0((b3 * d2 - b2 * d3) / denom, (-a3 * d2 + a2 * d3) / denom), v1((-b3 * c2 + b2 * c3) / denom, (a3 * c2 - a2 * c3) / denom);
    Float A = v1.norm2() - 1, B = 2 * (v1.dot(v0) + Radius1 * sgn1), C = v0.norm2() - Radius1 * Radius1;
    auto quad_ret = quadratic_solver(A, B, C);
    for (const auto r : quad_ret.second) {
        if (r >= 0.0) {
            Point2d<Float> Center = v0 + v1 * r + Center1;
            ret_circles.emplace_back(Center, r);
        }
    }
    return ret_circles;
};
