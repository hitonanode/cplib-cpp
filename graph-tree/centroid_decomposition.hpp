/*
(Recursive) Centroid Decomposition
Verification: Codeforces #190 Div.1 C <https://codeforces.com/contest/321/submission/59093583>

fix_root(int r): Build information of the tree which `r` belongs to.
detect_centroid(int r): Enumerate centroid(s) of the tree which `r` belongs to.
*/

#pragma once
#include <utility>
#include <vector>
using namespace std;

struct Tree
{
    int NO_PARENT = -1;
    using pint = pair<int, int>;
    int V;
    int E;
    vector<vector<pint>> to;  // (node_id, edge_id)
    vector<int> par;          // parent node_id par[root] = -1
    vector<vector<int>> chi;  // children id's
    vector<int> subtree_size; // size of each subtree
    vector<int> available_edge; // If 0, ignore the corresponding edge.

    Tree() : Tree(0) {}
    Tree(int v) : V(v), E(0), to(v), par(v, NO_PARENT), chi(v), subtree_size(v) {}

    void add_edge(int v1, int v2)
    {
        to[v1].emplace_back(v2, E);
        to[v2].emplace_back(v1, E);
        E++;
        available_edge.emplace_back(1);
    }

    int _dfs_fixroot(int now, int prv)
    {
        chi[now].clear();
        subtree_size[now] = 1;
        for (auto nxt : to[now])
        {
            if (nxt.first != prv and available_edge[nxt.second])
            {
                par[nxt.first] = now;
                chi[now].push_back(nxt.first);
                subtree_size[now] += _dfs_fixroot(nxt.first, now);
            }
        }
        return subtree_size[now];
    }

    void fix_root(int root)
    {
        par[root] = NO_PARENT;
        _dfs_fixroot(root, -1);
    }

    //// Centroid Decpmposition ////
    vector<int> centroid_cand_tmp;
    void _dfs_detect_centroid(int now, int prv, int n)
    {
        bool is_centroid = true;
        for (auto nxt : to[now])
        {
            if (nxt.first != prv and available_edge[nxt.second])
            {
                _dfs_detect_centroid(nxt.first, now, n);
                if (subtree_size[nxt.first] > n / 2) is_centroid = false;
            }
        }
        if (n - subtree_size[now] > n / 2) is_centroid = false;
        if (is_centroid) centroid_cand_tmp.push_back(now);
    }
    pint detect_centroid(int r) // ([centroid_node_id1], ([centroid_node_id2]|-1))
    {
        centroid_cand_tmp.clear();
        while (par[r] != NO_PARENT) r = par[r];
        int n = subtree_size[r];
        _dfs_detect_centroid(r, -1, n);
        if (centroid_cand_tmp.size() == 1) return make_pair(centroid_cand_tmp[0], -1);
        else return make_pair(centroid_cand_tmp[0], centroid_cand_tmp[1]);
    }
};
