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
    std::vector<T> &potential     // Potential, size n, updated
) {
    const int n = I.size();

    assert((int)m1.size() == n);
    assert((int)m2.size() == n);
    assert((int)weight.size() == n);
    assert((int)potential.size() == n);

    m1.set(I);
    m2.set(I);

    {
        int arghi = -1;
        for (int e = 0; e < n; ++e) {
            if (I.at(e)) continue;
            if (arghi < 0 or weight.at(arghi) < weight.at(e)) arghi = e;
        }
        if (arghi < 0) return false;
        if (m1.circuit(arghi).empty() and m2.circuit(arghi).empty()) {
            I.at(arghi) = true;
            return true;
        }
    }

    auto l = [&](int e) -> T { return e < n ? (I.at(e) ? weight.at(e) : -weight.at(e)) : T(); };
    auto pot = [&](int e) -> T { return e < n ? potential.at(e) : T(); };
    auto edge_len = [&](int s, int t) -> T { return l(t) - pot(t) + pot(s); };

    const int gs = n, gt = n + 1;
    std::vector<int> on_set;
    for (int e = 0; e < n; ++e) {
        if (I.at(e)) on_set.push_back(e);
    }

    // Find minimum weight (& minimum num. of vertices) gs-gt path
    using Dist = std::pair<T, int>; // (sum of weights, num. of vertices)
    std::vector<Dist> dp(gt + 1, {-1, -1});
    std::vector<int> prv(gt + 1, -1); // prv[i] >= 0 => i is reachable (i != gs)

    using Tpl = std::pair<Dist, int>;
    std::priority_queue<Tpl, std::vector<Tpl>, std::greater<Tpl>> pq; // (dist, len, now)
    std::vector<std::vector<int>> to(dp.size());

    for (int e = 0; e < n; ++e) {
        if (I.at(e)) continue;

        const auto c1 = m1.circuit(e), c2 = m2.circuit(e);

        if (c1.empty()) {
            to.at(e).push_back(gt);
            for (int f : on_set) to.at(e).push_back(f);
        }
        for (int f : c1) {
            if (f != e) to.at(e).push_back(f);
        }

        if (c2.empty()) {
            dp.at(e) = Dist{edge_len(gs, e), 1};
            prv.at(e) = gs;
            pq.emplace(dp.at(e), e);
        }
        for (int f : c2) {
            if (f != e) to.at(f).push_back(e);
        }
    }

    while (!pq.empty()) {
        const auto [dnow, now] = pq.top();
        pq.pop();
        if (prv.at(now) >= 0 and dp.at(now) < dnow) continue;

        for (int nxt : to.at(now)) {
            const auto w = edge_len(now, nxt);
            // if (w < T() and now < n and nxt < n) assert(false); // for debug

            Dist dnxt(dnow.first + w, dnow.second + 1);

            if (prv.at(nxt) < 0 or dnxt < dp.at(nxt)) {
                dp.at(nxt) = dnxt;
                prv.at(nxt) = now;
                if (nxt != gt) pq.emplace(dnxt, nxt);
            }
        }
    }

    if (prv.at(gt) < 0) return false;

    for (int e = 0; e < n; ++e) {
        auto [dist, len] = dp.at(e);
        if (len >= 0) potential.at(e) += dist;
    }

    for (int e = prv.at(gt); e != gs; e = prv.at(e)) {
        potential.at(e) -= l(e);
        I.at(e) = !I.at(e);
    }

    return true;
}
