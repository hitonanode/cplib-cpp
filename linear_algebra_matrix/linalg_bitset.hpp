#pragma once
#include <bitset>
#include <utility>
#include <vector>
using namespace std;

// CUT begin
constexpr int Wmax = 320;
vector<bitset<Wmax>> gauss_jordan(int W, vector<bitset<Wmax>> mtr)
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
        swap(mtr[piv], mtr[h]);
        for (int hh = 0; hh < H; hh++) {
            if (hh != h and mtr[hh][c]) mtr[hh] ^= mtr[h];
        }
    }
    return mtr;
}

int rank_gauss_jordan(int W, const vector<bitset<Wmax>> &mtr) // Rank of Gauss-Jordan eliminated matrix
{
    for (int h = (int)mtr.size() - 1; h >= 0; h--) {
        if (mtr[h]._Find_first() < W) return h + 1;
    }
    return 0;
}

vector<bitset<Wmax>> matmul(const vector<bitset<Wmax>> &A, const vector<bitset<Wmax>> &B, int W_B)
{
    int H = A.size(), K = B.size();
    vector<bitset<Wmax>> BT(W_B);
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < W_B; j++) {
            BT[j][i] = B[i][j];
        }
    }
    vector<bitset<Wmax>> C(H);
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W_B; j++) {
            C[i][j] = (A[i] & BT[j]).count() % 2;
        }
    }
    return C;
}

vector<bitset<Wmax>> matpower(vector<bitset<Wmax>> X, long long int n) // Calc X**n
{
    int D = X.size();
    vector<bitset<Wmax>> ret(D);
    for (int i = 0; i < D; i++) ret[i][i] = 1;
    while (n)
    {
        if (n & 1) ret = matmul(ret, X, D);
        X = matmul(X, X, D); n >>= 1;
    }
    return ret;
}
