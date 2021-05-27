#pragma once
#include <algorithm>
#include <utility>
#include <vector>

// CUT begin
// This implementation is based on https://ei1333.github.io/library/graph/others/eulerian-trail.cpp
template <bool directed> struct EulerianTrail {
    using Vertex = int;
    using Edge = int;
    int M;
    std::vector<int> deg;
    std::vector<std::pair<Vertex, Vertex>> edges;
    std::vector<std::vector<std::pair<Vertex, Edge>>> to;
    std::vector<int> used_vertex, used_edge;
    EulerianTrail(int V = 0) : M(0), deg(V, 0), to(V), used_vertex(V) {}
    void add_edge(Vertex a, Vertex b) {
        to[a].emplace_back(b, M);
        if (directed) {
            deg[a]++;
            deg[b]--;
        } else {
            to[b].emplace_back(a, M);
            deg[a]++;
            deg[b]++;
        }
        edges.emplace_back(a, b);
        M++;
        used_edge.push_back(0);
    }

    std::vector<std::vector<Edge>> solve() {
        if (directed) {
            if (std::count_if(deg.begin(), deg.end(), [](int x) { return x != 0; })) return {};
        } else {
            if (std::count_if(deg.begin(), deg.end(), [](int x) { return (x & 1) != 0; })) return {};
        }
        std::vector<std::vector<Edge>> ret;
        for (int i = 0; i < int(to.size()); i++) {
            if (to[i].empty() or used_vertex[i]) continue;
            ret.emplace_back(go(i));
        }
        return ret;
    }

    std::vector<Edge> go(Vertex s) {
        std::vector<std::pair<Vertex, Edge>> st;
        std::vector<Edge> ord;
        st.emplace_back(s, -1);
        while (!st.empty()) {
            Vertex now = st.back().first;
            used_vertex[now] = true;
            if (to[now].empty()) {
                ord.emplace_back(st.back().second);
                st.pop_back();
            } else {
                auto e = to[now].back();
                to[now].pop_back();
                if (used_edge[e.second]) continue;
                used_edge[e.second] = true;
                st.emplace_back(e);
            }
        }
        ord.pop_back();
        std::reverse(ord.begin(), ord.end());
        return ord;
    }
};