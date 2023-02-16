#pragma once

#include <numeric>
#include <utility>
#include <vector>

template <class T, class DistanceMatrix>
std::pair<T, std::vector<int>>
minimum_one_tree(const DistanceMatrix &dist, const std::vector<T> &pi) {

    assert(dist.n() > 2);
    std::vector<T> dp(dist.n(), std::numeric_limits<T>::max());
    std::vector<int> prv(dist.n(), -1);
    std::vector<int> used(dist.n());

    auto fix_v = [&](int x) -> void {
        dp.at(x) = std::numeric_limits<T>::max();
        used.at(x) = 1;
        for (auto [y, d] : dist.adjacents(x)) {
            if (used.at(y)) continue;
            if (T len = pi.at(x) + pi.at(y) + d; len < dp.at(y)) dp.at(y) = len, prv.at(y) = x;
        }
    };

    T W = T();
    std::vector<int> V(dist.n(), -2);

    fix_v(0);
    for (int t = 0; t < dist.n() - 1; ++t) {
        int i = std::min_element(dp.cbegin(), dp.cend()) - dp.cbegin();
        W += dp.at(i);
        ++V.at(i);
        ++V.at(prv.at(i));
        fix_v(i);
    }

    // p.26, http://webhotel4.ruc.dk/~keld/research/LKH/LKH-2.0/DOC/LKH_REPORT.pdf
    T wlo = T();
    int ilo = -1, jlo = -1;
    for (int i = 0; i < dist.n(); ++i) {
        if (V.at(i) != -1) continue;
        T tmp = T();
        int jtmp = -1;
        for (auto [j, d] : dist.adjacents(i)) {
            if (prv.at(i) == j or prv.at(j) == i or i == j) continue;
            if (T len = pi.at(i) + pi.at(j) + d; jtmp == -1 or tmp > len) tmp = len, jtmp = j;
        }
        if (jtmp != -1 and (ilo == -1 or wlo < tmp)) wlo = tmp, ilo = i, jlo = jtmp;
    }
    ++V.at(ilo);
    ++V.at(jlo);

    W += wlo - std::accumulate(pi.cbegin(), pi.cend(), T()) * 2;

    return {W, V};
}
