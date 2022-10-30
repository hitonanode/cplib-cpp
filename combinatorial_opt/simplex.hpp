#pragma once
#include <algorithm>
#include <chrono>
#include <cmath>
#include <numeric>
#include <random>
#include <vector>

// Maximize cx s.t. Ax <= b, x >= 0
// Implementation idea: https://kopricky.github.io/code/Computation_Advanced/simplex.html
// Refer to https://hitonanode.github.io/cplib-cpp/combinatorial_opt/simplex.hpp
template <typename Float = double, int DEPS = 30, bool Randomize = true> struct Simplex {
    const Float EPS = Float(1.0) / (1LL << DEPS);
    int N, M;
    std::vector<int> shuffle_idx;
    std::vector<int> idx;
    std::vector<std::vector<Float>> mat;
    int i_ch, j_ch;

private:
    void _initialize(const std::vector<std::vector<Float>> &A, const std::vector<Float> &b,
                     const std::vector<Float> &c) {
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
        for (nb_iter = 0, j_ch = N;; nb_iter++) {
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
                    if (mat[M + 1][j] > EPS or (abs_(mat[M + 1][j]) < EPS and mat[M][j] > EPS))
                        j_ch = j;
                }
            }
            if (j_ch < 0) break;

            i_ch = -1;
            for (int i = 0; i < M; i++) {
                if (mat[i][j_ch] < -EPS) {
                    if (i_ch < 0) {
                        i_ch = i;
                    } else if (mat[i_ch][N + 1] / mat[i_ch][j_ch] - mat[i][N + 1] / mat[i][j_ch] <
                               -EPS) {
                        i_ch = i;
                    } else if (mat[i_ch][N + 1] / mat[i_ch][j_ch] - mat[i][N + 1] / mat[i][j_ch] <
                                   EPS and
                               idx[i_ch] > idx[i]) {
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
    Simplex(std::vector<std::vector<Float>> A, std::vector<Float> b, std::vector<Float> c) {
        is_infty = infeasible = false;

        if (Randomize) {
            std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

            std::vector<std::pair<std::vector<Float>, Float>> Abs;
            for (unsigned i = 0; i < A.size(); i++) Abs.emplace_back(A[i], b[i]);
            std::shuffle(Abs.begin(), Abs.end(), rng);
            A.clear(), b.clear();
            for (auto &&Ab : Abs) A.emplace_back(Ab.first), b.emplace_back(Ab.second);

            shuffle_idx.resize(c.size());
            std::iota(shuffle_idx.begin(), shuffle_idx.end(), 0);
            std::shuffle(shuffle_idx.begin(), shuffle_idx.end(), rng);
            auto Atmp = A;
            auto ctmp = c;
            for (unsigned i = 0; i < A.size(); i++) {
                for (unsigned j = 0; j < A[i].size(); j++) A[i][j] = Atmp[i][shuffle_idx[j]];
            }
            for (unsigned j = 0; j < c.size(); j++) c[j] = ctmp[shuffle_idx[j]];
        }

        _initialize(A, b, c);
        _solve();

        if (Randomize and x.size() == c.size()) {
            auto xtmp = x;
            for (unsigned j = 0; j < c.size(); j++) x[shuffle_idx[j]] = xtmp[j];
        }
    }
    unsigned nb_iter;
    bool is_infty;
    bool infeasible;
    std::vector<Float> x;
    Float ans;

    static void
    dual(std::vector<std::vector<Float>> &A, std::vector<Float> &b, std::vector<Float> &c) {
        const int n = b.size(), m = c.size();
        std::vector<std::vector<Float>> At(m, std::vector<Float>(n));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) At[j][i] = -A[i][j];
        }
        A = At;
        for (int i = 0; i < n; ++i) b[i] = -b[i];
        for (int j = 0; j < m; ++j) c[j] = -c[j];
        b.swap(c);
    }
};
