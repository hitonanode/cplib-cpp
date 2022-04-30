#pragma once
#include "../linear_algebra_matrix/matrix.hpp"
#include <cassert>
#include <chrono>
#include <numeric>
#include <random>
#include <utility>
#include <vector>

// Solve linear matroid parity problem and return (especially lexicographically smallest) binary
// vector
// Complexity: O(d^2 (d + m)), d: dimension, m: number of input vector pairs
// Reference:
// [1] H. Y. Cheung, L. C. Lau, K. M. Leung,
//     "Algebraic Algorithms for Linear Matroid Parity Problems,"
//     ACM Transactions on Algorithms, 10(3), 1-26, 2014.
template <class ModInt>
std::vector<bool>
linear_matroid_parity(std::vector<std::pair<std::vector<ModInt>, std::vector<ModInt>>> bcs,
                      long long seed = std::chrono::steady_clock::now().time_since_epoch().count()) {
    if (bcs.empty()) return {};
    const int r = bcs[0].first.size(), r2 = (r + 1) / 2;
    int m = bcs.size();
    for (auto &v : bcs) v.first.resize(r2 * 2), v.second.resize(r2 * 2);

    std::mt19937 mt(seed);
    std::uniform_int_distribution<int> d(0, ModInt::mod() - 1);

    std::vector<ModInt> x(m), xadd(r2);

    matrix<ModInt> Yinv; // (r2 * 2) * (r2 * 2) matrix
    int rankY = -1;
    while (rankY < r2 * 2) {
        Yinv = matrix<ModInt>(r2 * 2, r2 * 2);

        auto add_i = [&](int i) {
            x[i] = d(mt);
            const auto &b = bcs[i].first, &c = bcs[i].second;
            for (int j = 0; j < r2 * 2; j++) {
                for (int k = 0; k < r2 * 2; k++) Yinv[j][k] += x[i] * (b[j] * c[k] - c[j] * b[k]);
            }
        };
        for (int i = 0; i < m; ++i) add_i(i);

        int num_add_vec = (r2 * 2 - Yinv.rank()) / 2;

        bcs.resize(m + num_add_vec,
                   std::make_pair(std::vector<ModInt>(r2 * 2), std::vector<ModInt>(r2 * 2)));
        x.resize(bcs.size());
        for (int i = m; i < int(bcs.size()); ++i) {
            for (auto &x : bcs[i].first) x = d(mt);
            for (auto &x : bcs[i].second) x = d(mt);
        }

        for (int i = m; i < int(bcs.size()); i++) add_i(i);
        rankY = Yinv.inverse();
    }

    std::vector<bool> ret(bcs.size(), 1);

    auto try_erase_i = [&](int i) {
        auto b = bcs[i].first, c = bcs[i].second;
        b.resize(r2 * 2, 0), c.resize(r2 * 2, 0);
        std::vector<ModInt> Yib = Yinv * b, Yic = Yinv * c;
        ModInt bYic = std::inner_product(b.begin(), b.end(), Yic.begin(), ModInt());
        ModInt a00 = bYic * x[i] + 1;
        if (a00 == ModInt()) return;
        ret[i] = 0;
        const ModInt f = x[i] / a00;
        for (int j = 0; j < r2 * 2; ++j) {
            for (int k = 0; k < r2 * 2; ++k) {
                Yinv[j][k] -= f * (Yib[j] * Yic[k] - Yic[j] * Yib[k]);
            }
        }
    };

    for (int i = m; i < int(bcs.size()); ++i) try_erase_i(i);
    for (int i = 0; i < m; i++) try_erase_i(i);
    ret.resize(m);
    return ret;
}

// Solve linear matroid parity problem, size-only (no construction)
template <class ModInt>
int linear_matroid_parity_size(
    const std::vector<std::pair<std::vector<ModInt>, std::vector<ModInt>>> &bcs,
    long long seed = std::chrono::steady_clock::now().time_since_epoch().count()) {

    if (bcs.empty()) return 0;

    std::mt19937 mt(seed);
    std::uniform_int_distribution<int> d(0, ModInt::mod() - 1);

    const int r = bcs[0].first.size();
    matrix<ModInt> mat(r, r);
    for (const auto &bc : bcs) {
        const auto &b = bc.first, &c = bc.second;
        ModInt x = d(mt);
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < r; ++j) mat[i][j] += x * (b[i] * c[j] - b[j] * c[i]);
        }
    }
    return mat.rank() / 2;
}
