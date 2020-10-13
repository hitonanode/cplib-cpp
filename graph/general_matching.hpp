#pragma once
#include "linear_algebra_matrix/linalg_modint.hpp"
#include <chrono>
#include <random>
#include <utility>
#include <vector>


// CUT begin
template <typename MODINT>
std::vector<std::pair<int, int>> generalMatching(int N, const std::vector<std::pair<int, int>>& ed)
{
    std::mt19937 mt(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> d(MODINT::get_mod());

    std::vector<std::vector<MODINT>> mat(N, std::vector<MODINT>(N));
    for (auto p : ed) {
        int a = p.first, b = p.second;
        if (a == b) continue;
        mat[a][b] = d(mt), mat[b][a] = -mat[a][b];
    }
    matrix<MODINT> A = mat;
    const int rank = A.inverse(), M = 2 * N - rank;
    if (M != N) {
        do {
            mat.resize(M, std::vector<MODINT>(M));
            for (int i = 0; i < N; i++) {
                mat[i].resize(M);
                for (int j = N; j < M; j++) {
                    mat[i][j] = d(mt), mat[j][i] = -mat[i][j];
                }
            }
            A = mat;
        } while (A.inverse() != M);
    }

    std::vector<int> has(M, 1);
    std::vector<std::pair<int, int>> ret;
    int fi = -1, fj = -1;
    for (int it = 0; it < M / 2; it++) {
        [&]() {
            for (int i = 0; i < M; i++) {
                if (has[i]) {
                    for (int j = i + 1; j < M; j++) {
                        if (A[i][j] and mat[i][j]) {
                            fi = i, fj = j;
                            return;
                        }
                    }
                }
            }
        }();
        if (fj < N) {
            ret.emplace_back(fi, fj);
        }
        has[fi] = has[fj] = 0;
        for (int sw = 0; sw < 2; sw++) {
            MODINT a = A[fi][fj].inv();
            for (int i = 0; i < M; i++) {
                if (has[i] and A[i][fj]) {
                    MODINT b = A[i][fj] * a;
                    for (int j = 0; j < M; j++) {
                        A[i][j] -= A[fi][j] * b;
                    }
                }
            }
            std::swap(fi, fj);
        }
    }
    return ret;
}
