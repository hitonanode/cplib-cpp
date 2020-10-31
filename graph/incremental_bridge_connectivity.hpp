#pragma once
#include "unionfind/unionfind.hpp"
#include <cassert>
#include <numeric>
#include <unordered_set>
#include <vector>

// CUT begin
// Incremental Bridge-Connectivity
// two-edge-connected components
// Reference: <https://scrapbox.io/data-structures/Incremental_Bridge-Connectivity>
//            <https://ei1333.github.io/library/graph/connected-components/incremental-bridge-connectivity.cpp>
struct IncrementalBridgeConnectivity {
    int V;
    int nb_bridge;
    UnionFind con, bicon;
    std::vector<int> bbf;

    int _bicon_par(int x) {
        return bbf[x] == -1 ? -1 : bicon.find(bbf[x]);
    }
    int _lca(int x, int y) {
        std::unordered_set<int> us;
        while (true) {
            if (x != -1) {
                if (!us.insert(x).second) {
                    return x;
                }
                x = _bicon_par(x);
            }
            std::swap(x, y);
        }
    }
    void _compress(int now, int lca) {
        while (bicon.find(now) != bicon.find(lca)) {
            int nxt = _bicon_par(now);
            bbf[now] = bbf[lca], bicon.unite(now, lca), now = nxt, nb_bridge--;
        }
    }

    IncrementalBridgeConnectivity(int v = 0) : V(v), nb_bridge(0), con(v), bicon(v), bbf(v, -1) {}

    void add_edge(int u, int v) {
        assert(u >= 0 and u < V);
        assert(v >= 0 and v < V);
        u = bicon.find(u), v = bicon.find(v);
        if (con.find(u) == con.find(v)) {
            int lca = _lca(u, v);
            _compress(u, lca), _compress(v, lca);
        } else {
            if (con.count(u) > con.count(v)) std::swap(u, v);
            for (int now = u, pre = v; now != -1;) {
                int nxt = _bicon_par(now);
                bbf[now] = pre, pre = now, now = nxt;
            }
            con.unite(u, v), nb_bridge++;
        }
    }
    int count_bridge() const {
        return nb_bridge;
    }
    bool two_edge_connected(int x, int y) {
        return bicon.same(x, y);
    }
    int find(int x) {
        return bicon.find(x);
    }
};
