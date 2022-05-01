#pragma once
#include "matrix.hpp"
#include <vector>

// Characteristic polynomial of upper Hessenberg matrix M (|xI - M|)
// Complexity: O(n^3)
// R. Rehman, I. C. Ipsen, "La Budde's Method for Computing Characteristic Polynomials," 2011.
template <class Tp> std::vector<Tp> characteristic_poly_of_hessenberg(matrix<Tp> &M) {
    const int N = M.height();
    // p[i + 1] = (Characteristic polynomial of i-th leading principal minor)
    std::vector<std::vector<Tp>> p(N + 1);
    p[0] = {1};
    for (int i = 0; i < N; i++) {
        p[i + 1].assign(i + 2, Tp());
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
