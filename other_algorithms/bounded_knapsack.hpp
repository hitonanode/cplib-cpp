/**
 * @file bounded_knapsack.hpp
 * @brief Bounded knapsack problem (Pisinger's algorithm)
 * @author hitonanode
 * @date 2023/01/01
 */

#pragma once
#include <algorithm>
#include <cassert>
#include <numeric>
#include <utility>
#include <vector>

/**
 * @fn bounded_knapsack_nonnegative(const std::vector<int> &, int)
 * Solve bounded knapsack problem: maximize weights(S) s.t. weights(S) <= capacity
 * Complexity: O(sum(weights) max(weights)) (Pisinger's linear time algorithm)
 * @param weights nonnegative integers describing weights.
 * @param capacity knapsack capacity limit.
 * @return std::pair<int, std::vector<bool>> {maximal value of weights(S), S that maximizes weights(S)}
 * @sa https://www.sciencedirect.com/science/article/abs/pii/S0196677499910349
 * @sa https://stackoverflow.com/a/9997386/20904249
 * @sa https://qiita.com/lowking/items/a9393f6afb9a4e662c38
 */
std::pair<int, std::vector<bool>>
bounded_knapsack_nonnegative(const std::vector<int> &weights, int capacity) {

    for (int w : weights) assert(w >= 0);
    assert(capacity >= 0);

    auto chmax = [](int &x, int y) { x = std::max(x, y); };

    int b = 0, w_bar = 0;
    const int n = weights.size();
    for (b = 0; b < n and w_bar + weights.at(b) <= capacity; ++b) w_bar += weights.at(b);

    if (b == n) return std::make_pair(w_bar, std::vector<bool>(n, true));

    int r = 0;
    for (int w : weights) r = std::max(r, w);

    const int O = r - 1; // DP table range: [capacity - r + 1, capacity + r]
    std::vector dp(n - b + 1, std::vector<int>(2 * r));
    for (int i = 0; i <= O; ++i) dp.front().at(i) = -1;
    dp.front().at(O + w_bar - capacity) = b;

    for (int t = b; t < n; ++t) {
        const std::vector<int> &dpprv = dp.at(t - b);
        std::vector<int> &dpnxt = dp.at(t - b + 1);
        dpnxt = dpprv;

        for (int i = 0; i <= O; ++i) chmax(dpnxt.at(i + weights.at(t)), dpprv.at(i));

        for (int i = O + weights.at(t); i >= O + 1; --i) {
            for (int j = dpnxt.at(i) - 1; j >= dpprv.at(i); --j) {
                chmax(dpnxt.at(i - weights.at(j)), j);
            }
        }
    }

    for (int z = O; z >= 0; --z) {
        if (dp.back().at(z) >= 0) {
            const int sol = capacity - O + z;
            std::vector<bool> ret(b, true);
            ret.resize(n, false);

            for (int t = n - 1; t >= b; --t) {
                const std::vector<int> &dpprv = dp.at(t - b), &dpnxt = dp.at(t - b + 1);
                while (dpnxt.at(z) < b) {
                    int znxt = z + weights.at(dpnxt.at(z));
                    if (znxt >= int(dpnxt.size()) or dpnxt.at(z) >= dpnxt.at(znxt)) break;
                    ret.at(dpnxt.at(z)) = false;
                    z = znxt;
                }
                if (z >= weights.at(t) and dpprv.at(z - weights.at(t)) >= dpnxt.at(z)) {
                    z -= weights.at(t);
                    ret.at(t) = true;
                }
            }

            return {sol, ret};
        }
    }
    exit(1); // Not occur
}

/**
 * @fn bounded_knapsack(const std::vector<int> &, int)
 * Solve bounded knapsack problem: maximize weights(S) s.t. weights(S) <= capacity
 * Complexity: O(sum(abs(weights)) max(abs(weights)))
 * @param weights Integers describing weights. Negative values are allowed.
 * @param capacity Knapsack capacity limit.
 * @return std::pair<int, std::vector<bool>> {maximal value of weights(S), S that maximizes weights(S)}
 */
std::pair<int, std::vector<bool>> bounded_knapsack(const std::vector<int> &weights, int capacity) {
    assert(capacity >= 0);
    std::vector<int> tmp = weights;
    for (int &w : tmp) {
        if (w < 0) w = -w, capacity += w;
    }
    auto sol = bounded_knapsack_nonnegative(tmp, capacity);
    for (int i = 0; i < int(weights.size()); ++i) {
        if (weights.at(i) < 0) {
            capacity += weights.at(i);
            sol.second.at(i).flip();
        }
    }
    return sol;
}
