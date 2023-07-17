#pragma once
#include "../graph/shortest_path.hpp"
#include <cassert>
#include <vector>

// Find augmenting path of matroid intersection.
// m1, m2: matroids
// I: independent set (will be updated if augmenting path is found)
//
// Return `true` iff augmenting path is found.
// Complexity: O(Cn + n^2) (C: circuit query)
template <class Matroid1, class Matroid2, class T = int>
bool matroid_intersection_augment(Matroid1 &m1, Matroid2 &m2, std::vector<bool> &I,
                                  const std::vector<T> &weights = {}) {
    const int n = m1.size();
    assert(m2.size() == n);
    assert((int)I.size() == n);

    auto weight = [&](int e) { return weights.empty() ? T() : weights.at(e) * (n + 1); };

    const int gs = n, gt = n + 1;
    shortest_path<T> sssp(n + 2);
    m1.set(I);
    m2.set(I);
    for (int e = 0; e < n; ++e) {
        if (I.at(e)) continue;
        auto c1 = m1.circuit(e), c2 = m2.circuit(e);
        if (c1.empty()) sssp.add_edge(e, gt, T());
        for (int f : c1) {
            if (f != e) sssp.add_edge(e, f, -weight(f) + T(1));
        }
        if (c2.empty()) sssp.add_edge(gs, e, weight(e) + T(1));
        for (int f : c2) {
            if (f != e) sssp.add_edge(f, e, weight(e) + T(1));
        }
    }
    sssp.solve(gs, gt);

    if (auto aug_path = sssp.retrieve_path(gt); aug_path.empty()) {
        return false;
    } else {
        for (auto e : aug_path) {
            if (e != gs and e != gt) I.at(e) = !I.at(e);
        }
        return true;
    }
}

// (Min weight) matroid intersection solver
// Algorithm based on http://dopal.cs.uec.ac.jp/okamotoy/lect/2015/matroid/
// Complexity: O(Cn^2 + n^3) (C : circuit query, non-weighted)
template <class Matroid1, class Matroid2, class T = int>
std::vector<bool>
MatroidIntersection(Matroid1 matroid1, Matroid2 matroid2, std::vector<T> weights = {}) {
    const int n = matroid1.size();
    assert(matroid2.size() == n);
    assert(weights.empty() or (int) weights.size() == n);

    std::vector<bool> I(n);

    if (weights.empty()) {
        matroid1.set(I);
        matroid2.set(I);
        for (int e = 0; e < n; ++e) {
            if (matroid1.circuit(e).empty() and matroid2.circuit(e).empty()) {
                I.at(e) = true;
                matroid1.set(I);
                matroid2.set(I);
            }
        }
    }

    while (matroid_intersection_augment(matroid1, matroid2, I, weights)) {}
    return I;
}
