#pragma once
#include <cassert>
#include <utility>
#include <vector>

// GraphMatroid: subgraph of undirected graphs, without loops
class GraphMatroid {
    using Vertex = int;
    using Element = int;
    int M;
    int V; // # of vertices of graph
    std::vector<std::vector<std::pair<Vertex, Element>>> to;
    std::vector<std::pair<Vertex, Vertex>> edges;
    std::vector<Element> backtrack;
    std::vector<Vertex> vprev;
    std::vector<int> depth, root;

public:
    GraphMatroid(int V, std::vector<std::pair<Vertex, Vertex>> edges_)
        : M(edges_.size()), V(V), to(V), edges(edges_) {
        for (int e = 0; e < int(edges_.size()); e++) {
            assert(edges_[e].first < V and edges_[e].second < V);
            to[edges_[e].first].emplace_back(edges_[e].second, e);
            to[edges_[e].second].emplace_back(edges_[e].first, e);
        }
    }
    int size() const { return M; }

    template <class State> void set(State I) {
        assert(int(I.size()) == M);
        backtrack.assign(V, -1);
        vprev.resize(V);
        depth.assign(V, -1);
        root.resize(V);
        static std::vector<Vertex> que(V);
        int qb, qe;
        for (Vertex i = 0; i < V; i++) {
            if (backtrack[i] >= 0) continue;
            que[qb = 0] = i, qe = 1, depth[i] = 0;
            while (qb < qe) {
                Vertex now = que[qb++];
                root[now] = i;
                for (auto nxt : to[now]) {
                    if (depth[nxt.first] < 0 and I[nxt.second]) {
                        backtrack[nxt.first] = nxt.second;
                        vprev[nxt.first] = now;
                        depth[nxt.first] = depth[now] + 1;
                        que[qe++] = nxt.first;
                    }
                }
            }
        }
    }

    std::vector<Element> circuit(const Element e) const {
        assert(0 <= e and e < M);
        Vertex s = edges[e].first, t = edges[e].second;
        if (root[s] != root[t]) return {};
        std::vector<Element> ret{e};
        auto step = [&](Vertex &i) { ret.push_back(backtrack[i]), i = vprev[i]; };
        int ddepth = depth[s] - depth[t];
        for (; ddepth > 0; --ddepth) step(s);
        for (; ddepth < 0; ++ddepth) step(t);
        while (s != t) step(s), step(t);
        return ret;
    }
};
