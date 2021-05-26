#pragma once
#include "linalg_modint.hpp"
#include <utility>

// CUT begin
// Expansion by the basis of binary (1 / -1) circular vectors such as [1, 1, 1, 1], [1, 1, -1, -1] & [1, -1, 1, -1]
// Note that transinv has only O(N) nonzero elements.
// Verified: GCJ 2015 Round 3 River Flow
template <typename MODINT> std::pair<matrix<MODINT>, matrix<MODINT>> circular_binary_expansion(int lgdim) {
    const int D = 1 << lgdim;
    const MODINT invD = MODINT(D).inv();
    matrix<MODINT> trans(D, D), transinv(D, D);
    for (int i = 0; i < D; i++) trans[i][0] = transinv[0][i] = 1;
    int h = 1;
    for (int d = 1; d * 2 <= D; d *= 2) {
        int z = d * 2;
        for (int xl = -d + 1; xl <= 0; xl++) {
            for (int i = 0; i < D; i++) trans[i][h] = (!(((i - xl) / d) & 1) ? 1 : -1);
            if (h == 1) {
                for (int i = 0; i < D; i++) transinv[h][i] = i % 2 ? -1 : 1;
            } else {
                for (int i = 0; i < D; i++) {
                    int md = (i + z) % (d * 2);
                    if (md == 0 or md == d + 1) transinv[h][i] = d / 2;
                    if (md == 1 or md == d) transinv[h][i] = -d / 2;
                }
            }
            h++;
            z--;
        }
    }
    for (int i = 0; i < D; i++) {
        for (int j = 0; j < D; j++) transinv[i][j] *= invD;
        return {trans, transinv};
    }
}
