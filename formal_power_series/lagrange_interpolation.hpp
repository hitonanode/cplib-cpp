#pragma once
#include <vector>

// CUT begin
// Lagrange interpolation
// Input: [f(0), ..., f(N-1)] (length = N), deg(f) < N
// Output: f(x_eval)
// Complexity: O(N)
// Verified: https://atcoder.jp/contests/arc033/tasks/arc033_4
template <typename MODINT> MODINT interpolate_iota(const std::vector<MODINT> ys, MODINT x_eval) {
    const int N = ys.size();
    if (x_eval.val() < N) return ys[x_eval.val()];
    std::vector<MODINT> facinv(N);
    facinv[N - 1] = MODINT(N - 1).fac().inv();
    for (int i = N - 1; i > 0; i--) facinv[i - 1] = facinv[i] * i;
    std::vector<MODINT> numleft(N);
    MODINT numtmp = 1;
    for (int i = 0; i < N; i++) {
        numleft[i] = numtmp;
        numtmp *= x_eval - i;
    }
    numtmp = 1;
    MODINT ret = 0;
    for (int i = N - 1; i >= 0; i--) {
        MODINT tmp = ys[i] * numleft[i] * numtmp * facinv[i] * facinv[N - 1 - i];
        ret += ((N - 1 - i) & 1) ? (-tmp) : tmp;
        numtmp *= x_eval - i;
    }
    return ret;
}
