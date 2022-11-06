#pragma once
#include "matrix.hpp"
#include <utility>
#include <vector>

// CUT begin
// Solve Ax = b for T = ModInt<PRIME>
// - retval: {one of the solution, {freedoms}} (if solution exists)
//           {{}, {}} (otherwise)
// Complexity:
// - Yield one of the possible solutions: O(HW rank(A)) (H: # of eqs., W: # of variables)
// - Enumerate all of the bases: O(W(H + W))
template <typename T>
std::pair<std::vector<T>, std::vector<std::vector<T>>>
system_of_linear_equations(matrix<T> A, std::vector<T> b) {
    int H = A.height(), W = A.width();
    matrix<T> M(H, W + 1);
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) M[i][j] = A[i][j];
        M[i][W] = b[i];
    }
    M = M.gauss_jordan();
    std::vector<int> ss(W, -1), ss_nonneg_js;
    for (int i = 0; i < H; i++) {
        int j = 0;
        while (j <= W and M[i][j] == 0) j++;
        if (j == W) { // No solution
            return {{}, {}};
        } else if (j < W) {
            ss_nonneg_js.push_back(j);
            ss[j] = i;
        } else {
            break;
        }
    }

    std::vector<T> x(W);
    std::vector<std::vector<T>> D;
    for (int j = 0; j < W; j++) {
        if (ss[j] == -1) {
            // This part may require W^2 space complexity in output
            std::vector<T> d(W);
            d[j] = 1;
            for (int jj : ss_nonneg_js) {
                if (jj >= j) break;
                d[jj] = -M[ss[jj]][j] / M[ss[jj]][jj];
            }
            D.emplace_back(d);
        } else {
            x[j] = M[ss[j]][W] / M[ss[j]][j];
        }
    }
    return std::make_pair(x, D);
}
