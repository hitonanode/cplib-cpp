#pragma once

#include <cassert>
#include <queue>
#include <vector>

// Find maximum weight size k + 1 intersection of two matroids using Dijkstra's algorithm
// Return `true` iff larger intersection is found.
// Complexity: O(Cn + nk log n) (C: circuit query)
template <class Matroid1, class Matroid2, class T = int>
bool augment_matroid_intersection_dijkstra(
    Matroid1 &m1,                 // Matroid, size n, updated
    Matroid2 &m2,                 // Matroid, size n, updated
    std::vector<bool> &I,         // Size k maximum weight intersection, size n, updated
    const std::vector<T> &weight, // Weights of elements, size n
    std::vector<T> &potential     // Potential, size n + 2, updated
) {
    const int n = I.size();

    assert((int)m1.size() == n);
    assert((int)m2.size() == n);
    assert((int)weight.size() == n);
    assert(potential.empty() or ((int)potential.size() == n) or ((int)potential.size() == n + 2));

    m1.set(I);
    m2.set(I);

    potential.resize(n + 2);

    auto l = [&](int e) -> T { return e < n ? (I.at(e) ? weight.at(e) : -weight.at(e)) : T(); };
    auto edge_len = [&](int s, int t) -> T { return l(t) - potential.at(t) + potential.at(s); };

    // Find minimum length (& minimum num. of vertices) gs-gt path
    const int gs = n, gt = n + 1;
    std::vector<std::vector<int>> to(gt + 1);

    bool has_gs_edge = false, has_gt_edge = false;

    for (int e = 0; e < n; ++e) {
        if (I.at(e)) continue;

        const auto c1 = m1.circuit(e), c2 = m2.circuit(e);

        if (c1.empty()) {
            to.at(e).push_back(gt);
            if (!has_gt_edge) {
                has_gt_edge = true;
                potential.at(gt) = potential.at(e);
            }
            if (T el = edge_len(e, gt); el < T()) potential.at(gt) += el;
        }
        for (int f : c1) {
            if (f != e) to.at(e).push_back(f);
        }

        if (c2.empty()) {
            to.at(gs).push_back(e);
            if (!has_gs_edge) {
                has_gs_edge = true;
                potential.at(gs) = potential.at(e) - l(e);
            }
            if (T el = edge_len(gs, e); el < T()) potential.at(gs) -= el;
        }
        for (int f : c2) {
            if (f != e) to.at(f).push_back(e);
        }
    }

    if (const T e0 = potential.at(gs); e0 != T()) {
        for (auto &p : potential) p -= e0;
    }

    if (!has_gs_edge or !has_gt_edge) return false;

    std::vector<bool> potential_fixed(gt + 1);

    T potential_add_unfixed_es = T();

    auto fix_potential = [&](int e) -> void {
        assert(!potential_fixed.at(e));
        potential_fixed.at(e) = true;
        potential.at(e) += potential_add_unfixed_es;
    };

    std::priority_queue<std::pair<T, int>, std::vector<std::pair<T, int>>, std::greater<>> pq;
    std::vector<T> dijkstra(gt + 1);
    std::vector<int> prv(gt + 1, -1);

    pq.emplace(T(), gs);

    while (!pq.empty()) {
        const int e = pq.top().second;
        pq.pop();
        if (potential_fixed.at(e)) continue;
        if (e != gs) potential_add_unfixed_es = edge_len(prv.at(e), e);

        std::vector<std::pair<int, int>> push_cands;

        auto rec = [&](auto &&self, int cur) -> bool {
            if (cur == gt) return true;
            fix_potential(cur);

            for (int nxt : to.at(cur)) {
                if (potential_fixed.at(nxt)) continue;

                const T len = edge_len(cur, nxt) - potential_add_unfixed_es;
                // if (len < T()) std::cerr << cur << ' ' << nxt << ' ' << len << std::endl;
                assert(len >= T());

                if (len == T()) {
                    prv.at(nxt) = cur;
                    if (self(self, nxt)) return true;
                } else {
                    if (prv.at(nxt) == -1 or potential_add_unfixed_es + len < dijkstra.at(nxt)) {
                        dijkstra.at(nxt) = potential_add_unfixed_es + len;
                        prv.at(nxt) = cur;
                        push_cands.emplace_back(nxt, cur);
                    }
                }
            }
            return false;
        };
        if (rec(rec, e)) break;

        for (auto [nxt, now] : push_cands) {
            if (prv.at(nxt) == now) pq.emplace(dijkstra.at(nxt), nxt);
        }
    }

    for (int e = 0; e < gt + 1; ++e) {
        if (!potential_fixed.at(e)) fix_potential(e);
    }

    if (prv.at(gt) < 0) return false;

    prv.assign(gt + 1, -1);
    std::queue<int> q;
    q.push(gs);

    for (int now = q.front(); now != gt; now = q.front()) {
        q.pop();
        for (int nxt : to.at(now)) {
            if (prv.at(nxt) == -1 and edge_len(now, nxt) == T()) {
                prv.at(nxt) = now;
                q.push(nxt);
            }
        }
    }

    for (int e = prv.at(gt); e != gs; e = prv.at(e)) {
        potential.at(e) -= l(e);
        I.at(e) = !I.at(e);
    }

    return true;
}
