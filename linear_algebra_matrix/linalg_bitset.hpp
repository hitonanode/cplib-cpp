#pragma once
#include <bitset>
#include <cassert>
#include <tuple>
#include <utility>
#include <vector>

// Gauss-Jordan elimination of n * m matrix M
// Complexity: O(nm + nm rank(M) / 64)
// Verified: abc276_h (2000 x 8000)
template <int Wmax>
std::vector<std::bitset<Wmax>> f2_gauss_jordan(int W, std::vector<std::bitset<Wmax>> M) {
    assert(W <= Wmax);
    int H = M.size(), c = 0;
    for (int h = 0; h < H and c < W; ++h, ++c) {
        int piv = -1;
        for (int j = h; j < H; ++j) {
            if (M[j][c]) {
                piv = j;
                break;
            }
        }
        if (piv == -1) {
            --h;
            continue;
        }
        std::swap(M[piv], M[h]);
        for (int hh = 0; hh < H; ++hh) {
            if (hh != h and M[hh][c]) M[hh] ^= M[h];
        }
    }
    return M;
}

// Rank of Gauss-Jordan eliminated matrix
template <int Wmax> int f2_rank_gauss_jordan(int W, const std::vector<std::bitset<Wmax>> &M) {
    assert(W <= Wmax);
    for (int h = (int)M.size() - 1; h >= 0; h--) {
        int j = 0;
        while (j < W and !M[h][j]) ++j;
        if (j < W) return h + 1;
    }
    return 0;
}

// determinant of F2 matrix.
// Return 0 if the matrix is singular, otherwise return 1.
// Complexity: O(W^3 / 64)
template <int Wmax> int f2_determinant(const std::vector<std::bitset<Wmax>> &M) {
    const int H = M.size();
    if (H > Wmax) return 0;

    auto tmp = M;
    for (int h = 0; h < H; ++h) {
        int piv = -1;
        for (int j = h; j < H; ++j) {
            if (tmp.at(j).test(h)) {
                piv = j;
                break;
            }
        }
        if (piv == -1) return 0; // singular

        if (piv != h) std::swap(tmp.at(piv), tmp.at(h));
        for (int hh = h + 1; hh < H; ++hh) {
            if (tmp.at(hh).test(h)) tmp.at(hh) ^= tmp.at(h);
        }
    }

    return 1; // nonsingular
}

template <int W1, int W2>
std::vector<std::bitset<W2>>
f2_matmul(const std::vector<std::bitset<W1>> &A, const std::vector<std::bitset<W2>> &B) {
    int H = A.size(), K = B.size();
    std::vector<std::bitset<W2>> C(H);
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < K; j++) {
            if (A.at(i).test(j)) C.at(i) ^= B.at(j);
        }
    }
    return C;
}

template <int Wmax>
std::vector<std::bitset<Wmax>> f2_matpower(std::vector<std::bitset<Wmax>> X, long long n) {
    int D = X.size();
    std::vector<std::bitset<Wmax>> ret(D);
    for (int i = 0; i < D; i++) ret[i][i] = 1;
    while (n) {
        if (n & 1) ret = f2_matmul<Wmax, Wmax>(ret, X);
        X = f2_matmul<Wmax, Wmax>(X, X), n >>= 1;
    }
    return ret;
}

// Solve Ax = b on F_2
// - retval: {true, one of the solutions, {freedoms}} (if solution exists)
//           {false, {}, {}} (otherwise)
// Complexity: O(HW + HW rank(A) / 64 + W^2 len(freedoms))
template <int Wmax, class Vec>
std::tuple<bool, std::bitset<Wmax>, std::vector<std::bitset<Wmax>>>
f2_system_of_linear_equations(std::vector<std::bitset<Wmax>> A, Vec b, int W) {
    int H = A.size();
    assert(W <= Wmax);
    assert(A.size() == b.size());

    std::vector<std::bitset<Wmax + 1>> M(H);
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) M[i][j] = A[i][j];
        M[i][W] = b[i];
    }
    M = f2_gauss_jordan<Wmax + 1>(W + 1, M);
    std::vector<int> ss(W, -1);
    std::vector<int> ss_nonneg_js;
    for (int i = 0; i < H; i++) {
        int j = 0;
        while (j <= W and !M[i][j]) ++j;
        if (j == W) return {false, 0, {}};
        if (j < W) {
            ss_nonneg_js.push_back(j);
            ss[j] = i;
        }
    }
    std::bitset<Wmax> x;
    std::vector<std::bitset<Wmax>> D;
    for (int j = 0; j < W; ++j) {
        if (ss[j] == -1) {
            // This part may require W^2 space complexity in output
            std::bitset<Wmax> d;
            d[j] = 1;
            for (int jj : ss_nonneg_js) d[jj] = M[ss[jj]][j];
            D.emplace_back(d);
        } else {
            x[j] = M[ss[j]][W];
        }
    }
    return std::make_tuple(true, x, D);
}
