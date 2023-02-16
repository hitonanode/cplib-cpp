#pragma once

#include "csr_distance_matrix.hpp"
#include "minimum_one_tree.hpp"

#include <algorithm>
#include <utility>
#include <vector>

// Held–Karp lower bound
// http://webhotel4.ruc.dk/~keld/research/LKH/LKH-2.0/DOC/LKH_REPORT.pdf
// p.26, p.33
template <class DistanceMatrix> auto held_karp_lower_bound(const DistanceMatrix &dist) {
    using T = decltype((*dist.adjacents(0).begin()).second);

    std::vector<T> best_pi(dist.n()), pi(dist.n());
    std::vector<int> V;
    T W;
    std::tie(W, V) = minimum_one_tree(dist, pi);
    if (std::count(V.cbegin(), V.cend(), 0) == dist.n()) return std::make_pair(W, pi);

    std::vector<int> lastV = V;

    T BestW = W;
    const int initial_period = (dist.n() + 1) / 2;
    bool is_initial_phase = true;
    int period = initial_period;

    const auto sparse_subgraph = build_adjacent_info(dist, 50); // p.47

    for (long long t0 = 1; t0 > 0; period /= 2, t0 /= 2) {
        for (int p = 1; t0 > 0 and p <= period; ++p) {
            for (int i = 0; i < dist.n(); ++i) {
                if (V.at(i) != 0) pi.at(i) += t0 * (7 * V.at(i) + 3 * lastV.at(i)) / 10;
            }
            std::swap(lastV, V);
            std::tie(W, V) = minimum_one_tree(sparse_subgraph, pi);
            if (std::count(begin(V), begin(V) + dist.n(), 0) == dist.n())
                return std::make_pair(W, pi);
            if (W > BestW) {
                BestW = W;
                best_pi = pi;
                if (is_initial_phase) t0 *= 2;
                if (p == period) period = std::min(period * 2, initial_period);

            } else if (is_initial_phase and p > period / 2) {
                is_initial_phase = false;
                p = 0;
                t0 = 3 * t0 / 4;
            }
        }
    }
    BestW = minimum_one_tree(dist, best_pi).first;
    return std::make_pair(BestW, best_pi);
}
