#pragma once
#include "../number/bare_mod_algebra.hpp"
#include <cassert>
#include <cstdlib>
#include <vector>

// CUT begin
template <typename lint, typename mdint>
std::vector<std::vector<lint>> gauss_jordan(std::vector<std::vector<lint>> mtr, mdint mod) {
    // Gauss-Jordan elimination 行基本変形のみを用いるガウス消去法
    int H = mtr.size(), W = mtr[0].size(), c = 0;
    for (int h = 0; h < H; h++) {
        if (c == W) break;
        int piv = -1;
        for (int j = h; j < H; j++)
            if (mtr[j][c]) {
                if (piv == -1 or abs(mtr[j][c]) > abs(mtr[piv][c])) piv = j;
            }
        if (piv == -1) {
            c++;
            h--;
            continue;
        }
        std::swap(mtr[piv], mtr[h]);
        if (h != piv) {
            for (int w = 0; w < W; w++) {
                mtr[piv][w] =
                    mtr[piv][w] ? mod - mtr[piv][w] : 0; // To preserve sign of determinant
            }
        }
        lint pivinv = mod_inverse<lint>(mtr[h][c], mod);
        for (int hh = 0; hh < H; hh++) {
            if (hh == h) continue;
            lint coeff = mtr[hh][c] * pivinv % mod;
            for (int w = W - 1; w >= c; w--) {
                mtr[hh][w] = mtr[hh][w] - mtr[h][w] * coeff % mod;
                if (mtr[hh][w] < 0) mtr[hh][w] += mod;
            }
        }
        c++;
    }
    return mtr;
}

template <typename lint>
int rank_gauss_jordan(const std::vector<std::vector<lint>> &mtr) // Rank of Gauss-Jordan eliminated matrix
{
    for (int h = (int)mtr.size() - 1; h >= 0; h--) {
        for (auto v : mtr[h])
            if (v) return h + 1;
    }
    return 0;
}

template <typename lint, typename mdint>
lint mod_determinant(std::vector<std::vector<lint>> mtr, mdint mod) {
    if (mtr.empty()) return 1 % mod;
    assert(mtr.size() == mtr[0].size());
    lint ans = 1;
    mtr = gauss_jordan(mtr, mod);
    for (int i = 0; i < (int)mtr.size(); i++) ans = ans * mtr[i][i] % mod;
    return ans;
}

template <typename lint, typename mdint>
std::vector<std::vector<lint>>
matmul(const std::vector<std::vector<lint>> &A, const std::vector<std::vector<lint>> &B, mdint mod) {
    int H = A.size(), W = B[0].size(), K = B.size();
    std::vector<std::vector<lint>> C(H, std::vector<lint>(W));
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            for (int k = 0; k < K; k++) (C[i][j] += A[i][k] * B[k][j]) %= mod;
        }
    }
    return C;
}

template <typename lint, typename mdint>
std::vector<lint>
matmul(const std::vector<std::vector<lint>> &A, const std::vector<lint> &v, mdint mod) {
    std::vector<lint> res(A.size());
    for (int i = 0; i < (int)A.size(); i++) {
        for (int j = 0; j < (int)v.size(); j++) (res[i] += A[i][j] * v[j]) %= mod;
    }
    return res;
}

template <typename lint, typename powint, typename mdint>
std::vector<std::vector<lint>> matpower(std::vector<std::vector<lint>> X, powint n, mdint mod) {
    std::vector<std::vector<lint>> res(X.size(), std::vector<lint>(X.size()));
    for (int i = 0; i < (int)res.size(); i++) res[i][i] = 1;
    while (n) {
        if (n & 1) res = matmul(res, X, mod);
        X = matmul(X, X, mod);
        n >>= 1;
    }
    return res;
}
