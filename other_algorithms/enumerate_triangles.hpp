#pragma once
#include <cassert>
#include <utility>
#include <vector>

// CUT begin
// Enumerate triangles
// Complexity: O(N + M \sqrt{M})
// Reference:
// - https://www.slideshare.net/catupper/trianguler
struct EnumerateTriangles {
    int V;
    std::vector<int> deg;
    std::vector<std::vector<int>> to;
    std::vector<std::pair<int, int>> edges;
    EnumerateTriangles(int N = 0) : V(N), deg(N), to(N) {}
    void add_edge(int s, int t) {
        assert(s >= 0 and s < V);
        assert(t >= 0 and t < V);
        assert(s != t);
        edges.emplace_back(s, t);
        deg[s]++, deg[t]++;
    }
    template <class F> void run(F f) {
        auto comp = [&](int i, int j) { return deg[i] != deg[j] ? deg[i] < deg[j] : i < j; };
        for (auto p : edges) {
            int s = p.first, t = p.second;
            if (comp(s, t)) {
                to[s].push_back(t);
            } else {
                to[t].push_back(s);
            }
        }
        std::vector<char> flag(V);
        for (int i = 0; i < V; i++) {
            for (auto j : to[i]) flag[j] = 1;
            for (auto j : to[i]) {
                for (auto k : to[j]) {
                    if (flag[k]) f(i, j, k);
                }
            }
            for (auto j : to[i]) flag[j] = 0;
        }
    }
};
