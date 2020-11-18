#pragma once
#include <bitset>
#include <cassert>
#include <tuple>
#include <utility>
#include <vector>

// CUT begin
constexpr int Wmax = 320;
std::vector<std::bitset<Wmax>> gauss_jordan(int W, std::vector<std::bitset<Wmax>> mtr) {
    int H = mtr.size(), c = 0;
    for (int h = 0; h < H; h++, c++) {
        if (c == W) break;
        int piv = -1;
        for (int j = h; j < H; j++)
            if (mtr[j][c]) {
                piv = j;
                break;
            }
        if (piv == -1) {
            h--;
            continue;
        }
        std::swap(mtr[piv], mtr[h]);
        for (int hh = 0; hh < H; hh++) {
            if (hh != h and mtr[hh][c]) mtr[hh] ^= mtr[h];
        }
    }
    return mtr;
}

int rank_gauss_jordan(int W, const std::vector<std::bitset<Wmax>> &mtr) // Rank of Gauss-Jordan eliminated matrix
{
    for (int h = (int)mtr.size() - 1; h >= 0; h--) {
        if (mtr[h]._Find_first() < W) return h + 1;
    }
    return 0;
}

std::vector<std::bitset<Wmax>> matmul(const std::vector<std::bitset<Wmax>> &A, const std::vector<std::bitset<Wmax>> &B) {
    int H = A.size(), K = B.size();
    std::vector<std::bitset<Wmax>> C(H);
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < K; j++) {
            if (A[i][j]) C[i] ^= B[j];
        }
    }
    return C;
}

std::vector<std::bitset<Wmax>> matpower(std::vector<std::bitset<Wmax>> X, long long n) {
    int D = X.size();
    std::vector<std::bitset<Wmax>> ret(D);
    for (int i = 0; i < D; i++) ret[i][i] = 1;
    while (n) {
        if (n & 1) ret = matmul(ret, X);
        X = matmul(X, X), n >>= 1;
    }
    return ret;
}

// Solve Ax = b on F_2
// - retval: {true, one of the solutions, {freedoms}} (if solution exists)
//           {false, {}, {}} (otherwise)
std::tuple<bool, std::bitset<Wmax>, std::vector<std::bitset<Wmax>>> system_of_linear_equations(std::vector<std::bitset<Wmax>> A, std::bitset<Wmax> b, int W) {
    int H = A.size();
    assert(W + 1 <= Wmax);
    assert(H <= Wmax);

    std::vector<std::bitset<Wmax>> M = A;
    for (int i = 0; i < H; i++) M[i][W] = b[i];
    M = gauss_jordan(W + 1, M);
    std::vector<int> ss(W, -1);
    for (int i = 0; i < H; i++) {
        int j = M[i]._Find_first();
        if (j == W) { return std::make_tuple(false, std::bitset<Wmax>(), std::vector<std::bitset<Wmax>>()); }
        if (j < W) ss[j] = i;
    }
    std::bitset<Wmax> x;
    std::vector<std::bitset<Wmax>> D;
    for (int j = 0; j < W; j++) {
        if (ss[j] == -1) {
            std::bitset<Wmax> d;
            d[j] = 1;
            for (int jj = 0; jj < W; jj++)
                if (ss[jj] != -1) d[jj] = M[ss[jj]][j];
            D.emplace_back(d);
        } else
            x[j] = M[ss[j]][W];
    }
    return std::make_tuple(true, x, D);
}
