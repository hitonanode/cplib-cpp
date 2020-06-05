#pragma once
#include "linear_algebra_matrix/linalg_modint.hpp"
#include <utility>
#include <vector>

// CUT begin
// Solve Ax = b for T = ModInt<PRIME>
// - retval: {one of the solution, {freedoms}} (if solution exists)
//           {{}, {}} (otherwise)
// Complexity:
// - Yield one of the possible solutions: O(H^2 W) (H: # of eqs., W: # of variables)
// - Enumerate all of the bases: O(HW(H + W))
template <typename T>
std::pair<std::vector<T>, std::vector<std::vector<T>>>
system_of_linear_equations(matrix<T> A, std::vector<T> b)
{
    int H = A.H, W = A.W;
    matrix<T> M(H, W + 1);
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) M[i][j] = A[i][j];
        M[i][W] = b[i];
    }
    M = M.gauss_jordan();
    std::vector<int> ss(W, -1);
    for (int i = 0; i < H; i++) {
        int j = 0;
        while (j <= W and M[i][j] == 0) j++;
        if (j == W) { // No solution
            return {{}, {}};
        }
        if (j < W) ss[j] = i;
    }
    std::vector<T> x(W);
    std::vector<std::vector<T>> D;
    for (int j = 0; j < W; j++) {
        if (ss[j] == -1) {
            std::vector<T> d(W);
            d[j] = 1;
            for (int jj = 0; jj < j; jj++) if (ss[jj] != -1) d[jj] = -M[ss[jj]][j] / M[ss[jj]][jj];
            D.emplace_back(d);
        }
        else x[j] = M[ss[j]][W] / M[ss[j]][j];
    }
    return std::make_pair(x, D);
}
