#pragma once
#include "../graph/shortest_path.hpp"
#include <cassert>
#include <utility>
#include <vector>

// CUT begin
// Union matroid augment
// From I1, I2 (independent, exclusive),
// - find I1' and I2' s.t. |I1'| + |I2'| = |I1| + |I2| + 1 and return true
// - or return false
// Complexity: O(n(c + r)) (r: current rank, c: circuit query)
// Algorithm based on https://math.mit.edu/~goemans/18438F09/lec13.pdf
// Verified: CodeChef HAMEL
template <class M1, class M2, class State1, class State2, class T = int>
bool augment_union_matroid(M1 &matroid1, M2 &matroid2, State1 &I1, State2 &I2,
                           const std::vector<T> &weights) {
    const int M = matroid1.size();
    const int gs = M, gt = M + 1;
    ShortestPath<T> sssp(M + 2);
    std::vector<int> color(M, -1);
    matroid1.set(I1);
    matroid2.set(I2);
    for (int e = 0; e < M; e++) {
        if (!I1[e] and !I2[e]) sssp.add_edge(gs, e, weights.size() ? weights[e] : 0);
        if (!I1[e]) {
            auto c = matroid1.circuit(e);
            if (c.empty()) sssp.add_edge(e, gt, 0), color[e] = 0;
            for (int f : c) {
                if (f != e) sssp.add_edge(e, f, 1);
            }
        }
        if (!I2[e]) {
            auto c = matroid2.circuit(e);
            if (c.empty()) sssp.add_edge(e, gt, 0), color[e] = 1;
            for (int f : c) {
                if (f != e) sssp.add_edge(e, f, 1);
            }
        }
    }
    sssp.solve(gs);
    auto aug_path = sssp.retrieve_path(gt);
    if (aug_path.empty()) return false;
    assert(aug_path.size() >= 3);
    int c0 = -1;
    if (I1[aug_path[aug_path.size() - 2]]) c0 = 1;
    if (I2[aug_path[aug_path.size() - 2]]) c0 = 0;
    if (c0 < 0) c0 = color[aug_path[aug_path.size() - 2]];
    for (int k = int(aug_path.size()) - 2, e = aug_path[k]; k; e = aug_path[--k]) {
        (c0 ? I2 : I1)[e] = 1, (c0 ? I1 : I2)[e] = 0;
        c0 ^= 1;
    }
    return true;
}

// (Min weight) matroid partition
template <class M1, class M2, class T = int>
std::pair<std::vector<bool>, std::vector<bool>>
MinWeightMaxIndepSetInUnionMatroid(M1 mat1, M2 mat2, const std::vector<T> &weights = {}) {
    using State = std::vector<bool>;
    assert(mat1.size() == mat2.size());
    const int M = mat1.size();
    State I1(M), I2(M);
    while (augment_union_matroid(mat1, mat2, I1, I2, weights)) {}
    return {I1, I2};
}
