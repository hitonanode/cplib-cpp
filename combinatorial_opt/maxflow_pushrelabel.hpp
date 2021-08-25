#pragma once
#include <cassert>
#include <limits>
#include <utility>
#include <vector>

// Maxflow (push-relabel, highest-label)
// Complexity: O(N^2 M^(1/2))
template <class Cap, Cap INF = std::numeric_limits<Cap>::max() / 2, bool UseGlobalRelabeling = false>
struct mf_pushrelabel {
    int _n;
    struct _edge {
        int to, rev;
        Cap cap;
    };
    std::vector<std::vector<_edge>> g;
    std::vector<std::pair<int, int>> pos;
    mf_pushrelabel(int n) : _n(n), g(n) { static_assert(INF > 0, "INF must be positive."); }
    int add_edge(int from, int to, Cap cap) {
        assert(0 <= from and from < _n);
        assert(0 <= to and to < _n);
        assert(0 <= cap);
        int m = int(pos.size());
        pos.emplace_back(from, int(g[from].size()));
        int from_id = g[from].size(), to_id = g[to].size() + (from == to);
        g[from].push_back({to, to_id, cap});
        g[to].push_back({from, from_id, Cap(0)});
        return m;
    }

    std::vector<int> dist;
    std::vector<Cap> excess;
    std::vector<std::vector<int>> h2v;
    int max_height;
    void activate(int i) {
        h2v[dist[i]].push_back(i);
        if (dist[i] > max_height) max_height = dist[i];
    }
    void global_relabeling(int t) {
        if (!UseGlobalRelabeling) return;
        dist.assign(_n, _n), dist[t] = 0;
        static std::vector<int> q;
        q = {t};
        int qh = 0;
        h2v.assign(_n * 2, {});
        max_height = -1;
        while (qh < int(q.size())) {
            int now = q[qh++];
            if (excess[now] > 0) activate(now);
            for (const auto &e : g[now]) {
                if (g[e.to][e.rev].cap and dist[e.to] == _n) {
                    dist[e.to] = dist[now] + 1;
                    q.push_back(e.to);
                }
            }
        }
    }
    Cap flow(const int &s, const int &t) {
        assert(0 <= s and s < _n);
        assert(0 <= t and t < _n);
        assert(s != t);
        excess.assign(_n, 0);
        excess[s] = INF, excess[t] = -INF;
        dist.assign(_n, 0);
        dist[s] = _n;
        h2v.assign(_n * 2, {});
        max_height = -1;
        for (auto &e : g[s]) push(s, e);
        global_relabeling(t);
        int tick = _n;
        while (max_height >= 0) {
            if (h2v[max_height].empty()) {
                max_height--;
                continue;
            }
            int i = h2v[max_height].back();
            h2v[max_height].pop_back();
            int dnxt = _n * 2 - 1;
            for (auto &e : g[i]) {
                if (!e.cap) continue;
                if (dist[e.to] == dist[i] - 1) {
                    push(i, e);
                    if (excess[i] == 0) break;
                } else {
                    if (dist[e.to] + 1 < dnxt) dnxt = dist[e.to] + 1;
                }
            }
            if (excess[i] > 0) {
                dist[i] = dnxt;
                activate(i);
            }
            if (--tick == 0) tick = _n, global_relabeling(t);
        }
        return excess[t] + INF;
    }

    void push(int i, _edge &e) {
        Cap delta = e.cap < excess[i] ? e.cap : excess[i];
        excess[i] -= delta, e.cap -= delta;
        excess[e.to] += delta, g[e.to][e.rev].cap += delta;
        if (excess[e.to] > 0 and excess[e.to] <= delta) activate(e.to);
    }
};
