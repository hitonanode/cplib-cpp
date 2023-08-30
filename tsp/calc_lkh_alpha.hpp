#pragma once

#include <vector>

#include "tsp/mst_edges.hpp"

// http://webhotel4.ruc.dk/~keld/research/LKH/LKH-2.0/DOC/LKH_REPORT.pdf, p.20
template <class DistanceMatrix> auto calc_lkh_alpha(const DistanceMatrix &dist) {
    using T = decltype((*dist.adjacents(0).begin()).second);

    std::vector<std::vector<int>> to(dist.n());

    for (auto [s, t] : mst_edges(dist)) {
        to.at(s).push_back(t);
        to.at(t).push_back(s);
    }

    std::vector ret(dist.n(), std::vector<T>(dist.n()));

    for (int s = 0; s < dist.n(); ++s) {
        auto rec = [&](auto &&self, int now, int prv, T hi) -> void {
            ret.at(s).at(now) = dist(s, now) - hi;
            for (int nxt : to.at(now)) {
                if (nxt == prv) continue;
                self(self, nxt, now, std::max(hi, dist(now, nxt)));
            }
        };
        rec(rec, s, -1, T());
    }

    // Determining special node for the 1-tree
    // Reference: p.26 of http://webhotel4.ruc.dk/~keld/research/LKH/LKH-2.0/DOC/LKH_REPORT.pdf
    int best_one = -1;
    T longest_2nd_nearest = T();

    for (int one = 0; one < dist.n(); ++one) {
        if (to.at(one).size() != 1) continue;
        const int ng = to.at(one).front();
        bool found = false;
        T second_nearest = T();

        for (auto [v, len] : dist.adjacents(one)) {
            if (v == ng) continue;
            if (!found) {
                found = true, second_nearest = len;
            } else if (len < second_nearest) {
                second_nearest = len;
            }
        }

        if (found and (best_one < 0 or second_nearest > longest_2nd_nearest))
            best_one = one, longest_2nd_nearest = second_nearest;
    }

    if (best_one != -1) {
        for (auto [v, len] : dist.adjacents(best_one)) {
            if (v == to.at(best_one).front()) continue;
            ret.at(best_one).at(v) = ret.at(v).at(best_one) = len - longest_2nd_nearest;
        }
    }

    return ret;
}
