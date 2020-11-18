#pragma once
#include <cmath>
#include <utility>
#include <vector>

// CUT begin
// Solve ax^2 + bx + c = 0.
// retval: (# of solutions (-1 == inf.), solutions(ascending order))
// Verify: <https://yukicoder.me/problems/no/955> <https://atcoder.jp/contests/tricky/tasks/tricky_2>
template <typename Float> std::pair<int, std::vector<Float>> quadratic_solver(Float A, Float B, Float C) {
    if (B < 0) A = -A, B = -B, C = -C;
    if (A == 0) {
        if (B == 0) {
            if (C == 0)
                return std::make_pair(-1, std::vector<Float>{}); // all real numbers
            else
                return std::make_pair(0, std::vector<Float>{}); // no solution
        } else
            return std::make_pair(1, std::vector<Float>{-C / B});
    }
    Float D = B * B - 4 * A * C;
    if (D < 0) return std::make_pair(0, std::vector<Float>{});
    if (D == 0) return std::make_pair(1, std::vector<Float>{-B / (2 * A)});
    Float ret1 = (-B - sqrt(D)) / (2 * A), ret2 = C / A / ret1;
    if (ret1 > ret2) std::swap(ret1, ret2);
    return std::make_pair(2, std::vector<Float>{ret1, ret2});
}
