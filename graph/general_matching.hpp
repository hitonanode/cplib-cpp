#pragma once
#include "linear_algebra_matrix/linalg_modint.hpp"
#include "modint.hpp"
#include <algorithm>
#include <chrono>
#include <queue>
#include <random>
#include <utility>
#include <vector>

// CUT begin
// Find maximum matchings in general graph using the Tutte matrix (The Rabin-Vazirani algorithm)
// Complexity: O(N^3)
// Reference: <https://github.com/kth-competitive-programming/kactl/blob/master/content/graph/GeneralMatching.h>
//            <https://kopricky.github.io/code/Academic/maximum_matching.html>
std::vector<std::pair<int, int>> generalMatching(int N, std::vector<std::pair<int, int>> ed) {
    using MODINT = ModInt<1000000007>;
    std::vector<std::pair<int, int>> ed_tmp;
    for (auto p : ed) {
        if (p.first != p.second) { ed_tmp.emplace_back(std::minmax(p.first, p.second)); }
    }
    ed = ed_tmp, std::sort(ed.begin(), ed.end()), ed.erase(std::unique(ed.begin(), ed.end()), ed.end());
    std::vector<std::pair<int, int>> ret;

    std::vector<int> deg(N), used(N);
    std::vector<std::vector<int>> conn(N);
    for (auto p : ed) {
        deg[p.first]++, deg[p.second]++;
        conn[p.first].emplace_back(p.second), conn[p.second].emplace_back(p.first);
    }
    std::queue<int> q_deg1;
    for (int i = 0; i < N; i++) {
        if (deg[i] == 1) { q_deg1.emplace(i); }
    }
    while (q_deg1.size()) {
        int i = q_deg1.front(), j = -1;
        q_deg1.pop();
        if (!used[i]) {
            for (auto k : conn[i]) {
                if (!used[k]) {
                    j = k, ret.emplace_back(i, j);
                    break;
                }
            }
        }
        for (int t = 0; t < 2; t++) {
            if (i >= 0 and !used[i]) {
                used[i] = 1;
                for (auto k : conn[i]) {
                    deg[k]--;
                    if (deg[k] == 1) { q_deg1.emplace(k); }
                }
            }
            std::swap(i, j);
        }
    }

    std::vector<int> idx(N, -1), idx_inv;
    for (int i = 0; i < N; i++) {
        if (deg[i] > 0 and !used[i]) { idx[i] = idx_inv.size(), idx_inv.emplace_back(i); }
    }

    const int D = idx_inv.size();
    if (D == 0) { return ret; }
    std::mt19937 mt(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> d(MODINT::get_mod());

    std::vector<std::vector<MODINT>> mat(D, std::vector<MODINT>(D));
    for (auto p : ed) {
        int a = idx[p.first], b = idx[p.second];
        if (a < 0 or b < 0) continue;
        mat[a][b] = d(mt), mat[b][a] = -mat[a][b];
    }
    matrix<MODINT> A = mat;
    const int rank = A.inverse(), M = 2 * D - rank;
    if (M != D) {
        do {
            mat.resize(M, std::vector<MODINT>(M));
            for (int i = 0; i < D; i++) {
                mat[i].resize(M);
                for (int j = D; j < M; j++) { mat[i][j] = d(mt), mat[j][i] = -mat[i][j]; }
            }
            A = mat;
        } while (A.inverse() != M);
    }

    std::vector<int> has(M, 1);
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
        if (fj < D) { ret.emplace_back(idx_inv[fi], idx_inv[fj]); }
        has[fi] = has[fj] = 0;
        for (int sw = 0; sw < 2; sw++) {
            MODINT a = A[fi][fj].inv();
            for (int i = 0; i < M; i++) {
                if (has[i] and A[i][fj]) {
                    MODINT b = A[i][fj] * a;
                    for (int j = 0; j < M; j++) { A[i][j] -= A[fi][j] * b; }
                }
            }
            std::swap(fi, fj);
        }
    }
    return ret;
}
