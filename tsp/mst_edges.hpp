
#pragma once

#include <algorithm>
#include <limits>
#include <utility>
#include <vector>

template <class DistanceMatrix>
std::vector<std::pair<int, int>> mst_edges(const DistanceMatrix &dist) {
    using T = decltype((*dist.adjacents(0).begin()).second);

    if (dist.n() <= 1) return {};

    std::vector<T> dp(dist.n(), std::numeric_limits<T>::max());
    std::vector<int> prv(dist.n(), -1);
    std::vector<int> used(dist.n());
    std::vector<std::pair<int, int>> ret(dist.n() - 1);

    for (int t = 0; t < dist.n(); ++t) {
        int x = std::min_element(dp.cbegin(), dp.cend()) - dp.cbegin();
        dp.at(x) = std::numeric_limits<T>::max();
        used.at(x) = 1;
        if (t > 0) ret.at(t - 1) = {prv.at(x), x};

        for (auto [y, len] : dist.adjacents(x)) {
            if (!used.at(y) and len < dp.at(y)) dp.at(y) = len, prv.at(y) = x;
        }
    }

    return ret;
}
