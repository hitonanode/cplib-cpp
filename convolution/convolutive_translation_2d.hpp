#include "convolution/ntt.hpp"
#include <algorithm>
#include <utility>
#include <vector>

// Two dimensional fast DP using FFT.
// Complexity: O(HW log (HW)) for each step.
// Verification: TCO 2020 Round 3A 1000 ZombieRPGDice
// Verification: TCO 2020 Round 3B 500 ShortBugPaths
template <typename MODINT>
std::vector<std::vector<MODINT>> convolutive_translation_2d(const std::vector<std::vector<MODINT>> &initial_dist,                    // size: H * W
                                                            const std::vector<std::pair<std::pair<int, int>, MODINT>> &trans_coeffs, // [((dx, dy), coefficient), ...]
                                                            int nb_step = 1) {
    int H = initial_dist.size(), W = initial_dist[0].size();
    int xlo = 0, xhi = 0, ylo = 0, yhi = 0;

    std::vector<std::pair<std::pair<int, int>, MODINT>> t2c_1d;
    for (auto p : trans_coeffs)
        if (p.second != 0) {
            if (p.first.first <= -H or p.first.first >= H) continue;
            if (p.first.second <= -W or p.first.second >= W) continue;
            xlo = std::max(xlo, -p.first.first), xhi = std::max(xhi, p.first.first);
            ylo = std::max(ylo, -p.first.second), yhi = std::max(yhi, p.first.second);
            t2c_1d.emplace_back(p);
        }
    const int WW = W + ylo + yhi;
    std::vector<MODINT> dp((H - 1) * WW + W);
    for (int i = 0; i < H; i++) { std::copy(initial_dist[i].begin(), initial_dist[i].end(), dp.begin() + i * WW); }

    int tlo = 0, thi = 0;
    for (auto p : t2c_1d) {
        int t = p.first.first * WW + p.first.second;
        tlo = std::max(tlo, -t), thi = std::max(thi, t);
    }

    std::vector<MODINT> trans1d(tlo + thi + 1);
    for (auto p : t2c_1d) { trans1d[tlo + p.first.first * WW + p.first.second] += p.second; }
    for (int t = 0; t < nb_step; t++) {
        auto dp_nxt = nttconv(dp, trans1d);
        for (int i = 0; i < H; i++) { std::copy(dp_nxt.begin() + i * WW + tlo, dp_nxt.begin() + i * WW + W + tlo, dp.begin() + i * WW); }
    }
    std::vector<std::vector<MODINT>> ret(H);
    for (int i = 0; i < H; i++) { ret[i].insert(ret[i].end(), dp.begin() + i * WW, dp.begin() + i * WW + W); }
    return ret;
}
