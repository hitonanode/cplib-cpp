#pragma once
#include "./smawk.hpp"

#include <cassert>
#include <functional>
#include <vector>

// Calculate min cost paths of N vertices DAG from 0 to (N - 1), whose weight is Monge
// returns vector<T> costs, where costs[d - 1] == (min cost from 0 to (N - 1) with exactly d edges)
// Complexity: O(N maxD) (if SMAWK is used)
// Verify: https://yukicoder.me/problems/no/952
// Verify: https://mofecoder.com/contests/monoxercon_202508/tasks/monoxercon_202508_k
template <class T>
std::vector<T>
MongeDEdgeShortestPaths(int N, int max_d, const std::function<T(int i, int j)> &weight, T inf) {
    assert(max_d < N);
    std::vector<T> ans;

    std::vector<T> dp(N, inf);
    dp.at(0) = 0;
    // std::vector prevs(max_d, std::vector<int>(N, -1)); // if you need to retrieve path

    std::vector<T> costs;
    for (int d = 1; d <= max_d; ++d) {
        // MonotoneMinima<T>() is Also OK
        const auto res = SMAWK<T>(
            N, N - 1, [&](int j, int i) -> T { return i < j ? dp[i] + weight(i, j) : inf; });

        for (int i = d; i < N; ++i) dp.at(i) = res.at(i).second;
        // for (int i = d; i < N; ++i) {
        //     prevs.at(d - 1).at(i) = res.at(i).first;
        // }
        costs.push_back(dp.at(N - 1));
    }

    return costs;
}
