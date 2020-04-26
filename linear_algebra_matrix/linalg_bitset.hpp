#pragma once
#include <bitset>
#include <utility>
#include <vector>

// CUT begin
constexpr int Wmax = 320;
std::vector<std::bitset<Wmax>> gauss_jordan(int W, std::vector<std::bitset<Wmax>> mtr)
{
    int H = mtr.size(), c = 0;
    for (int h = 0; h < H; h++, c++)
    {
        if (c == W) break;
        int piv = -1;
        for (int j = h; j < H; j++) if (mtr[j][c]) {
                piv = j; break;
        }
        if (piv == -1) { h--; continue; }
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

std::vector<std::bitset<Wmax>> matmul(const std::vector<std::bitset<Wmax>> &A, const std::vector<std::bitset<Wmax>> &B)
{
    int H = A.size(), K = B.size();
    std::vector<std::bitset<Wmax>> C(H);
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < K; j++) {
            if (A[i][j]) C[i] ^= B[j];
        }
    }
    return C;
}

std::vector<std::bitset<Wmax>> matpower(std::vector<std::bitset<Wmax>> X, long long n)
{
    int D = X.size();
    std::vector<std::bitset<Wmax>> ret(D);
    for (int i = 0; i < D; i++) ret[i][i] = 1;
    while (n)
    {
        if (n & 1) ret = matmul(ret, X);
        X = matmul(X, X), n >>= 1;
    }
    return ret;
}
