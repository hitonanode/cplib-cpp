#pragma once
#include <iostream>
#include <vector>

// CUT begin
// Bipartite matching of undirected bipartite graph
// <https://ei1333.github.io/luzhiled/snippets/graph/bipartite-matching.html>
// Comprexity: O(VE)
struct BipartiteMatching
{
    int V;                               // # of vertices
    std::vector<std::vector<int>> edges; // Adjacency list
    std::vector<int> match;              // match[i] = (Partner of i'th node) or -1 (No parter)
    std::vector<int> used;
    int timestamp;
    BipartiteMatching(int V = 0) : V(V), edges(V), match(V, -1), used(V, 0), timestamp(0) {}

    void add_edge(int u, int v)
    {
        edges[u].push_back(v);
        edges[v].push_back(u);
    }

    bool dfs(int v)
    {
        used[v] = timestamp;
        for (auto to : edges[v])
        {
            if (match[to] < 0 or (used[match[to]] != timestamp and dfs(match[to])))
            {
                match[v] = to;
                match[to] = v;
                return true;
            }
        }
        return false;
    }

    int solve() // Count up newly formed pairs
    {
        int ret = 0;
        for (int v = 0; v < V; v++) if (match[v] < 0)
        {
            ++timestamp;
            ret += dfs(v);
        }
        return ret;
    }

    friend std::ostream &operator<<(std::ostream &os, const BipartiteMatching &bm)
    {
        os << "{V=" << bm.V << ":";
        for (int i = 0; i < bm.V; i++) if (i < bm.match[i])
        {
            os << "(" << i << "-" << bm.match[i] << "),";
        }
        os << "}";
        return os;
    }
};
