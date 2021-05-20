#pragma once
#include "geometry.hpp"
#include <complex>

// CUT begin
// Circumcenter （三角形の外心）
template <typename Float>
Point2d<Float> circumcenter(const Point2d<Float> &A, const Point2d<Float> &B, const Point2d<Float> &C) {
    std::complex<Float> a = (C - A).to_complex(), b = (B - A).to_complex();
    return A + Point2d<Float>(a * b * std::conj(a - b) / (std::conj(a) * b - a * std::conj(b)));
}
template <typename Float>
Point3d<Float> circumcenter(const Point3d<Float> &A, const Point3d<Float> &B, const Point3d<Float> &C) {
    auto a = (B - C).norm(), b = (C - A).norm(), c = (A - B).norm();
    auto acosA = a * a * (C - A).dot(B - A);
    auto bcosB = b * b * (A - B).dot(C - B);
    auto ccosC = c * c * (B - C).dot(A - C);
    return (A * acosA + B * bcosB + C * ccosC) / (acosA + bcosB + ccosC);
}
