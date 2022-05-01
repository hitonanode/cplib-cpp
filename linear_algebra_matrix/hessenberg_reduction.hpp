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

template <class Ring> void ring_hessenberg_reduction(matrix<Ring> &M) {
    assert(M.height() == M.width());
    const int N = M.height();
    for (int r = 0; r < N - 2; r++) {
        int piv = matrix<Ring>::choose_pivot(M, r + 1, r);
        if (piv < 0) continue;
        for (int i = 0; i < N; i++) std::swap(M[r + 1][i], M[piv][i]);
        for (int i = 0; i < N; i++) std::swap(M[i][r + 1], M[i][piv]);

        for (int i = r + 2; i < N; i++) {
            if (M[i][r] == Ring()) continue;
            Ring a = M[r + 1][r], b = M[i][r], m00 = 1, m01 = 0, m10 = 0, m11 = 1;
            while (a != Ring() and b != Ring()) {
                if (a.val() > b.val()) {
                    auto d = a.val() / b.val();
                    a -= b * d, m00 -= m10 * d, m01 -= m11 * d;
                } else {
                    auto d = b.val() / a.val();
                    b -= a * d, m10 -= m00 * d, m11 -= m01 * d;
                }
            }
            if (a == Ring()) std::swap(a, b), std::swap(m00, m10), std::swap(m01, m11);

            for (int j = 0; j < N; j++) {
                Ring anew = M[r + 1][j] * m00 + M[i][j] * m01;
                Ring bnew = M[r + 1][j] * m10 + M[i][j] * m11;
                M[r + 1][j] = anew;
                M[i][j] = bnew;
            }
            assert(M[i][r] == 0);

            for (int j = 0; j < N; j++) {
                Ring anew = M[j][r + 1] * m11 - M[j][i] * m10;
                Ring bnew = -M[j][r + 1] * m01 + M[j][i] * m00;
                M[j][r + 1] = anew;
                M[j][i] = bnew;
            }
        }
    }
}
