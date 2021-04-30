#pragma once
#include "../data_structure/light_forward_list.hpp"
#include "../unionfind/unionfind.hpp"
#include <cassert>
#include <tuple>
#include <utility>
#include <vector>

// 無向グラフを長さ2の道（**閉路を含む**）へ分解
// 各連結成分について，辺の本数が偶数なら完全な分解が可能
// Complexity: O(V + E)
// Verify: - https://codeforces.com/contest/1519/problem/E
//         - https://atcoder.jp/contests/agc035/tasks/agc035_b
struct PathsOfLength2Decomposition {
    int V, E;
    std::vector<std::pair<int, int>> edges;
    std::vector<light_forward_list<std::pair<int, int>>> to_nonmst;
    std::vector<light_forward_list<std::pair<int, int>>> to_mst;
    UnionFind uf;
    void _init(int V_) {
        V = V_, E = 0;
        edges.clear();
        to_nonmst.assign(V, {});
        to_mst.assign(V, {});
        uf = UnionFind(V);
    }
    PathsOfLength2Decomposition(int V = 0) { _init(V); }
    void add_edge(int u, int v) {
        assert(u >= 0 and u < V);
        assert(v >= 0 and v < V);
        if (uf.unite(u, v)) {
            to_mst[u].push_front({E, v}), to_mst[v].push_front({E, u});
        } else {
            to_nonmst[u].push_front({E, v}), to_nonmst[v].push_front({E, u});
        }
        edges.emplace_back(u, v);
        E++;
    }

    std::vector<std::pair<int, int>> _ret;
    std::vector<char> _visited;
    std::vector<char> _edge_used;
    void _dfs(int now, int prv) {
        _visited[now] = 1;
        int prveid = -1;
        std::vector<int> available_edges;
        for (auto ev : to_mst[now]) {
            int eid, nxt;
            std::tie(eid, nxt) = ev;
            if (nxt == prv)
                prveid = eid;
            else {
                _dfs(nxt, now);
                if (!_edge_used[eid]) available_edges.push_back(eid);
            }
        }
        for (auto ev : to_nonmst[now]) {
            int eid, nxt;
            std::tie(eid, nxt) = ev;
            if (!_edge_used[eid]) available_edges.push_back(eid);
        }
        if ((available_edges.size() & 1) and prv != -1) available_edges.push_back(prveid);
        for (unsigned h = 0; h + 1 < available_edges.size(); h += 2) {
            int e1 = available_edges[h], e2 = available_edges[h + 1];
            _edge_used[e1] = _edge_used[e2] = 1;
            _ret.emplace_back(e1, e2);
        }
    }
    std::vector<std::pair<int, int>> run() { // 辺番号（0-origin, 追加順）の組の列を返す
        _ret.clear();
        _visited.assign(V, 0);
        _edge_used.assign(E, 0);
        for (int i = 0; i < V; i++) {
            if (!_visited[i]) _dfs(i, -1);
        }
        return _ret;
    }
};
