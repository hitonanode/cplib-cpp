#pragma once
#include <cmath>
#include <numeric>
#include <vector>

// CUT begin
// Maximize cx s.t. Ax <= b, x >= 0
// Implementation idea: https://kopricky.github.io/code/Computation_Advanced/simplex.html
// Refer to https://hitonanode.github.io/cplib-cpp/combinatorial_opt/simplex.hpp
template <typename Float = double, int DEPS = 30> struct Simplex {
    const Float EPS = Float(1.0) / (1LL << DEPS);
    int N, M;
    std::vector<int> idx;
    std::vector<std::vector<Float>> mat;
    int i_ch, j_ch;

private:
    void _initialize(const std::vector<std::vector<Float>> &A, const std::vector<Float> &b, const std::vector<Float> &c) {
        N = c.size(), M = A.size();

        mat.assign(M + 2, std::vector<Float>(N + 2));
        i_ch = M;
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) mat[i][j] = -A[i][j];
            mat[i][N] = 1, mat[i][N + 1] = b[i];
            if (mat[i_ch][N + 1] > mat[i][N + 1]) i_ch = i;
        }
        for (int j = 0; j < N; j++) mat[M][j] = c[j];
        mat[M + 1][N] = -1;

        idx.resize(N + M + 1);
        std::iota(idx.begin(), idx.end(), 0);
    }

    inline Float abs_(Float x) noexcept { return x > -x ? x : -x; }
    void _solve() {
        std::vector<int> jupd;
        for (j_ch = N;;) {
            if (i_ch < M) {
                std::swap(idx[j_ch], idx[i_ch + N + 1]);
                mat[i_ch][j_ch] = Float(1) / mat[i_ch][j_ch];
                jupd.clear();
                for (int j = 0; j < N + 2; j++) {
                    if (j != j_ch) {
                        mat[i_ch][j] *= -mat[i_ch][j_ch];
                        if (abs_(mat[i_ch][j]) > EPS) jupd.push_back(j);
                    }
                }
                for (int i = 0; i < M + 2; i++) {
                    if (abs_(mat[i][j_ch]) < EPS or i == i_ch) continue;
                    for (auto j : jupd) mat[i][j] += mat[i][j_ch] * mat[i_ch][j];
                    mat[i][j_ch] *= mat[i_ch][j_ch];
                }
            }

            j_ch = -1;
            for (int j = 0; j < N + 1; j++) {
                if (j_ch < 0 or idx[j_ch] > idx[j]) {
                    if (mat[M + 1][j] > EPS or (abs_(mat[M + 1][j]) < EPS and mat[M][j] > EPS)) j_ch = j;
                }
            }
            if (j_ch < 0) break;

            i_ch = -1;
            for (int i = 0; i < M; i++) {
                if (mat[i][j_ch] < -EPS) {
                    if (i_ch < 0) {
                        i_ch = i;
                    } else if (mat[i_ch][N + 1] / mat[i_ch][j_ch] - mat[i][N + 1] / mat[i][j_ch] < -EPS) {
                        i_ch = i;
                    } else if (mat[i_ch][N + 1] / mat[i_ch][j_ch] - mat[i][N + 1] / mat[i][j_ch] < EPS and idx[i_ch] > idx[i]) {
                        i_ch = i;
                    }
                }
            }
            if (i_ch < 0) {
                is_infty = true;
                break;
            }
        }
        if (mat[M + 1][N + 1] < -EPS) {
            infeasible = true;
            return;
        }
        x.assign(N, 0);
        for (int i = 0; i < M; i++) {
            if (idx[N + 1 + i] < N) x[idx[N + 1 + i]] = mat[i][N + 1];
        }
        ans = mat[M][N + 1];
    }

public:
    Simplex(const std::vector<std::vector<Float>> &A, const std::vector<Float> &b, const std::vector<Float> &c) {
        is_infty = infeasible = false;
        _initialize(A, b, c);
        _solve();
    }
    bool is_infty;
    bool infeasible;
    std::vector<Float> x;
    Float ans;
};
