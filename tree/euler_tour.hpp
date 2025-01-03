#pragma once
#include <cassert>
#include <utility>
#include <vector>

// Euler tour
// https://maspypy.com/euler-tour-%E3%81%AE%E3%81%8A%E5%8B%89%E5%BC%B7
struct euler_tour {
    int n;
    int root;

    std::vector<std::pair<int, int>> edges; // (parent, child)

    // - 頂点 v に関する部分木に含まれる辺は， [begins[v], ends[v]) に 2 回ずつ登場
    // - [begins[u], begins[v]) (begins[u] <= begins[v]) の半開区間に u-v パスを構成する辺が奇数回登場
    std::vector<int> begins;
    std::vector<int> ends;

    std::vector<int> par_eid;
    std::vector<std::pair<int, bool>> tour; // (edge_id, flg) flg=true: down, false: up

    void _build_dfs(int now, int prv_eid, const std::vector<std::vector<std::pair<int, int>>> &to) {
        tour.emplace_back(prv_eid, true);
        begins[now] = tour.size();

        for (auto [nxt, eid] : to[now]) {
            if (eid == prv_eid) continue;
            par_eid[nxt] = eid;
            if (edges[eid].first == nxt) std::swap(edges[eid].first, edges[eid].second);
            _build_dfs(nxt, eid, to);
        }

        ends[now] = tour.size();
        tour.emplace_back(prv_eid, false);
    }

    euler_tour() = default;

    euler_tour(int n, const std::vector<std::pair<int, int>> &edges_, int root)
        : n(n), root(root), edges(edges_), begins(n, -1), ends(n, -1), par_eid(n, -1) {
        std::vector<std::vector<std::pair<int, int>>> to(n);
        for (int eid = 0; eid < (int)edges.size(); ++eid) {
            auto [u, v] = edges[eid];
            assert(u != v);
            to.at(u).emplace_back(v, eid);
            to.at(v).emplace_back(u, eid);
        }

        _build_dfs(root, -1, to);
    }

    // 頂点 v の部分木の頂点数
    int subtree_size(int v) const { return (ends.at(v) - begins.at(v)) / 2 + 1; }

    int par(int v) const {
        int eid = par_eid.at(v);
        return eid == -1 ? -1 : edges[eid].first;
    }

    int tour_child(int idx) const {
        int eid = tour.at(idx).first;
        return eid < 0 ? root : edges[eid].second;
    }
};
