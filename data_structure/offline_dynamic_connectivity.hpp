#pragma once
#include <algorithm>
#include <limits>
#include <set>
#include <utility>
#include <vector>

enum class DyConOperation {
    Begins = 1,
    Ends = 2,
    Event = 3,
};

template <class Tick = int> struct offline_dynamic_connectivity {

    std::vector<std::pair<Tick, int>> ops;

    struct Edge {
        Tick since;
        Tick until;
        int edge_id;
    };
    std::vector<Edge> edges;

    offline_dynamic_connectivity() = default;

    void add_observation(Tick clk, int event_id) { ops.emplace_back(clk, event_id); }

    void apply_time_range(Tick since, Tick until, int edge_id) {
        edges.push_back(Edge{since, until, edge_id});
    }

    struct Procedure {
        DyConOperation op;
        int id_;
    };

    std::vector<std::vector<Procedure>> nodes;
    std::vector<Procedure> ret_;

    void rec(int now) {
        ret_.insert(ret_.end(), nodes[now].cbegin(), nodes[now].cend());
        if (now * 2 < int(nodes.size())) rec(now * 2);
        if (now * 2 + 1 < int(nodes.size())) rec(now * 2 + 1);

        for (auto itr = nodes[now].rbegin(); itr != nodes[now].rend(); ++itr) {
            if (itr->op == DyConOperation::Begins) {
                ret_.push_back(Procedure{DyConOperation::Ends, itr->id_});
            }
        }
    }

    std::vector<Procedure> generate() {
        if (ops.empty()) return {};

        std::vector<Tick> query_ts;
        {
            query_ts.reserve(ops.size());
            for (const auto &p : ops) query_ts.push_back(p.first);
            std::sort(query_ts.begin(), query_ts.end());
            query_ts.erase(std::unique(query_ts.begin(), query_ts.end()), query_ts.end());

            std::vector<int> t_use(query_ts.size() + 1);
            t_use.at(0) = 1;

            for (const Edge &e : edges) {
                t_use[std::lower_bound(query_ts.begin(), query_ts.end(), e.since) - query_ts.begin()] =
                    1;
                t_use[std::lower_bound(query_ts.begin(), query_ts.end(), e.until) - query_ts.begin()] =
                    1;
            }
            for (int i = 1; i < int(query_ts.size()); ++i) {
                if (!t_use[i]) query_ts[i] = query_ts[i - 1];
            }

            query_ts.erase(std::unique(query_ts.begin(), query_ts.end()), query_ts.end());
        }

        const int N = query_ts.size();
        int D = 1;
        while (D < int(query_ts.size())) D *= 2;

        nodes.assign(D + N, {});

        for (const Edge &e : edges) {
            int l =
                D + (std::lower_bound(query_ts.begin(), query_ts.end(), e.since) - query_ts.begin());
            int r =
                D + (std::lower_bound(query_ts.begin(), query_ts.end(), e.until) - query_ts.begin());

            while (l < r) {
                if (l & 1) nodes[l++].push_back(Procedure{DyConOperation::Begins, e.edge_id});
                if (r & 1) nodes[--r].push_back(Procedure{DyConOperation::Begins, e.edge_id});
                l >>= 1, r >>= 1;
            }
        }

        for (const auto &op : ops) {
            int clk = op.first, qid = op.second;
            int t =
                D + (std::upper_bound(query_ts.begin(), query_ts.end(), clk) - query_ts.begin()) - 1;
            nodes[t].push_back(Procedure{DyConOperation::Event, qid});
        }
        ret_.clear();
        rec(1);
        return ret_;
    }
};
