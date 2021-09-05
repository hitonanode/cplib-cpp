#pragma once
#include "../graph/shortest_path.hpp"
#include <cassert>
#include <vector>

// CUT begin
// (Min weight) matroid intersection solver
// Algorithm based on http://dopal.cs.uec.ac.jp/okamotoy/lect/2015/matroid/
// Complexity: O(CE^2 + E^3) (C : circuit query, non-weighted)
template <class M1, class M2, class T = int>
std::vector<bool> MatroidIntersection(M1 matroid1, M2 matroid2, std::vector<T> weights = {}) {
    using State = std::vector<bool>;
    using Element = int;
    assert(matroid1.size() == matroid2.size());
    const int M = matroid1.size();

    for (auto &x : weights) x *= M + 1;
    if (weights.empty()) weights.assign(M, 0);

    const Element gs = M, gt = M + 1;
    State I(M);

    while (true) {
        ShortestPath<T> sssp(M + 2);
        matroid1.set(I);
        matroid2.set(I);
        for (int e = 0; e < M; e++) {
            if (I[e]) continue;
            auto c1 = matroid1.circuit(e), c2 = matroid2.circuit(e);
            if (c1.empty()) sssp.add_edge(e, gt, 0);
            for (Element f : c1) {
                if (f != e) sssp.add_edge(e, f, -weights[f] + 1);
            }
            if (c2.empty()) sssp.add_edge(gs, e, weights[e] + 1);
            for (Element f : c2) {
                if (f != e) sssp.add_edge(f, e, weights[e] + 1);
            }
        }
        sssp.solve(gs);
        auto aug_path = sssp.retrieve_path(gt);
        if (aug_path.empty()) break;
        for (auto e : aug_path) {
            if (e != gs and e != gt) I[e] = !I[e];
        }
    }
    return I;
}
