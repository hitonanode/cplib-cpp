#pragma once
#include "matrix.hpp"
#include <cassert>
#include <utility>
#include <vector>

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

// Characteristic polynomial of matrix M (|xI - M|)
// Complexity: O(n^3)
// R. Rehman, I. C. Ipsen, "La Budde's Method for Computing Characteristic Polynomials," 2011.
template <class Tp> std::vector<Tp> characteristic_poly(matrix<Tp> M) {
    hessenberg_reduction(M);
    const int N = M.height();
    std::vector<std::vector<Tp>> p(N + 1); // p[i + 1] = (Characteristic polynomial of i-th leading principal minor)
    p[0] = {1};
    for (int i = 0; i < N; i++) {
        p[i + 1].assign(i + 2, 0);
        for (int j = 0; j < i + 1; j++) p[i + 1][j + 1] += p[i][j];
        for (int j = 0; j < i + 1; j++) p[i + 1][j] -= p[i][j] * M[i][i];
        Tp betas = 1;
        for (int j = i - 1; j >= 0; j--) {
            betas *= M[j + 1][j];
            Tp hb = -M[j][i] * betas;
            for (int k = 0; k < j + 1; k++) p[i + 1][k] += hb * p[j][k];
        }
    }
    return p[N];
}
