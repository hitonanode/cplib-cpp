#pragma once
#include "matrix.hpp"
#include <cassert>
#include <utility>

// Upper Hessenberg reduction of square matrices
// Complexity: O(n^3)
// Reference:
// http://www.phys.uri.edu/nigh/NumRec/bookfpdf/f11-5.pdf
template <class Tp> void hessenberg_reduction(matrix<Tp> &M) {
    assert(M.height() == M.width());
    const int N = M.height();
    for (int r = 0; r < N - 2; r++) {
        int piv = matrix<Tp>::choose_pivot(M, r + 1, r);
        if (piv < 0) continue;
        for (int i = 0; i < N; i++) std::swap(M[r + 1][i], M[piv][i]);
        for (int i = 0; i < N; i++) std::swap(M[i][r + 1], M[i][piv]);

        const auto rinv = Tp(1) / M[r + 1][r];
        for (int i = r + 2; i < N; i++) {
            const auto n = M[i][r] * rinv;
            for (int j = 0; j < N; j++) M[i][j] -= M[r + 1][j] * n;
            for (int j = 0; j < N; j++) M[j][r + 1] += M[j][i] * n;
        }
    }
}
