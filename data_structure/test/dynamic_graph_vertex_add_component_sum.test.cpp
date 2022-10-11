#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_graph_vertex_add_component_sum"
#include "../../unionfind/undo_monoid_unionfind.hpp"
#include "../offline_dynamic_connectivity.hpp"

#include <iostream>
#include <map>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N, Q;
    cin >> N >> Q;

    using lint = long long;
    vector<lint> a(N);
    for (auto &x : a) cin >> x;

    vector<pair<int, int>> edges;
    map<pair<int, int>, pair<int, int>> edge_to_id_since;

    offline_dynamic_connectivity<int> dc;

    vector<pair<int, lint>> qs;

    vector<int> get_query;
    vector<lint> ret;
    for (int q = 0; q < Q; ++q) {
        int tp;
        cin >> tp;
        if (tp <= 1) {
            int u, v;
            cin >> u >> v;
            if (u > v) swap(u, v);

            if (tp == 0) {
                edge_to_id_since[make_pair(u, v)] = make_pair(edges.size(), q);
                edges.emplace_back(u, v);
            } else {
                int id_, since;
                tie(id_, since) = edge_to_id_since[make_pair(u, v)];
                dc.apply_time_range(since, q, id_);
                edge_to_id_since.erase(make_pair(u, v));
            }
        } else if (tp == 2) {
            int v;
            lint x;
            cin >> v >> x;

            dc.apply_time_range(q, 1 << 30, -1 - int(qs.size()));
            qs.emplace_back(v, x);
        } else if (tp == 3) {
            int v;
            cin >> v;

            dc.add_observation(q, ret.size());
            get_query.push_back(v);
            ret.push_back(0);
        }
    }

    for (auto p : edge_to_id_since) {
        dc.apply_time_range(p.second.second, 1 << 30, p.second.first);
    }

    undo_dsu<lint> dsu(a);

    for (auto p : dc.generate()) {
        if (p.op == DyConOperation::Begins) {
            if (p.id_ >= 0) {
                auto edge = edges.at(p.id_);
                dsu.unite(edge.first, edge.second);
            } else {
                auto q = qs.at(-p.id_ - 1);
                int v = q.first, x = q.second;
                dsu.set_weight(v, dsu.sum(v) + x);
            }
        } else if (p.op == DyConOperation::Ends) {
            dsu.undo();
        } else if (p.op == DyConOperation::Event) {
            int v = get_query.at(p.id_);
            ret.at(p.id_) = dsu.sum(v);
        }
    }

    for (auto x : ret) cout << x << '\n';
}
