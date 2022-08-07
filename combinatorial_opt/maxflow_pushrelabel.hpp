#pragma once
#include <cassert>
#include <limits>
#include <utility>
#include <vector>

// Maxflow (push-relabel, highest-label)
// Complexity: O(N^2 M^(1/2))
template <class Cap, int GlobalRelabelFreq = 5, bool UseGapRelabeling = true>
struct mf_pushrelabel {
    struct pque_ {
        std::vector<std::pair<int, int>> even_, odd_;
        int se, so;
        void init(int n) { even_.resize(n), odd_.resize(n), se = so = 0; };
        void clear() { se = so = 0; }
        bool empty() const { return se + so == 0; }
        void push(int i, int h) { (h & 1 ? odd_[so++] : even_[se++]) = {i, h}; }
        int highest() const {
            int a = se ? even_[se - 1].second : -1, b = so ? odd_[so - 1].second : -1;
            return a > b ? a : b;
        }
        int pop() {
            if (!se or (so and odd_[so - 1].second > even_[se - 1].second))
                return odd_[--so].first;
            return even_[--se].first;
        }
    } pque;
    int _n;
    struct _edge {
        int to, rev;
        Cap cap;
    };
    std::vector<std::vector<_edge>> g;
    std::vector<std::pair<int, int>> pos;
    mf_pushrelabel(int n) : _n(n), g(n) {
        static_assert(GlobalRelabelFreq >= 0, "Global relabel parameter must be nonnegative.");
    }
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

    struct edge {
        int from, to;
        Cap cap, flow;
    };

    edge get_edge(int i) const {
        int m = int(pos.size());
        assert(0 <= i and i < m);
        auto e = g[pos[i].first][pos[i].second], re = g[e.to][e.rev];
        return edge{pos[i].first, e.co, e.cap + re.cap, re.cap};
    }
    std::vector<edge> edges() const {
        std::vector<edge> ret(pos.size());
        for (int i = 0; i < int(pos.size()); i++) ret[i] = get_edge(i);
        return ret;
    }

    std::vector<int> dist;
    std::vector<int> dcnt;
    std::vector<Cap> excess;
    int gap;
    void global_relabeling(int t) {
        dist.assign(_n, _n), dist[t] = 0;
        static std::vector<int> q;
        if (q.empty()) q.resize(_n);
        q[0] = t;
        int qb = 0, qe = 1;
        pque.clear();
        if (UseGapRelabeling) gap = 1, dcnt.assign(_n + 1, 0);

        while (qb < qe) {
            int now = q[qb++];
            if (UseGapRelabeling) gap = dist[now] + 1, dcnt[dist[now]]++;
            if (excess[now] > 0) pque.push(now, dist[now]);
            for (const auto &e : g[now]) {
                if (g[e.to][e.rev].cap and dist[e.to] == _n) {
                    dist[e.to] = dist[now] + 1;
                    q[qe++] = e.to;
                }
            }
        }
    }
    Cap flow(int s, int t) { return flow(s, t, std::numeric_limits<Cap>::max(), true); }
    Cap flow(int s, int t, Cap flow_limit, bool retrieve = true) {
        assert(0 <= s and s < _n);
        assert(0 <= t and t < _n);
        assert(s != t);
        excess.resize(_n, 0);
        excess[s] += flow_limit, excess[t] -= flow_limit;
        dist.assign(_n, 0);
        dist[s] = _n;
        if (UseGapRelabeling) gap = 1, dcnt.assign(_n + 1, 0), dcnt[0] = _n - 1;
        pque.init(_n);
        for (auto &e : g[s]) _push(s, e);
        _run(t);
        Cap ret = excess[t] + flow_limit;
        excess[s] += excess[t], excess[t] = 0;
        if (retrieve) {
            global_relabeling(s);
            _run(s);
            assert(excess == std::vector<Cap>(_n, 0));
        }
        return ret;
    }
    void _run(int t) {
        if (GlobalRelabelFreq) global_relabeling(t);
        int tick = pos.size() * GlobalRelabelFreq;
        while (!pque.empty()) {
            int i = pque.pop();
            if (UseGapRelabeling and dist[i] > gap) continue;
            int dnxt = _n * 2 - 1;
            for (auto &e : g[i]) {
                if (!e.cap) continue;
                if (dist[e.to] == dist[i] - 1) {
                    _push(i, e);
                    if (excess[i] == 0) break;
                } else {
                    if (dist[e.to] + 1 < dnxt) dnxt = dist[e.to] + 1;
                }
            }
            if (excess[i] > 0) {
                if (UseGapRelabeling) {
                    if (dnxt != dist[i] and dcnt[dist[i]] == 1 and dist[i] < gap) gap = dist[i];
                    if (dnxt == gap) gap++;
                    while (pque.highest() > gap) pque.pop();
                    if (dnxt > gap) dnxt = _n;
                    if (dist[i] != dnxt) dcnt[dist[i]]--, dcnt[dnxt]++;
                }
                dist[i] = dnxt;
                if (!UseGapRelabeling or dist[i] < gap) pque.push(i, dist[i]);
            }
            if (GlobalRelabelFreq and --tick == 0) {
                tick = pos.size() * GlobalRelabelFreq, global_relabeling(t);
            }
        }
        return;
    }

    void _push(int i, _edge &e) {
        Cap delta = e.cap < excess[i] ? e.cap : excess[i];
        excess[i] -= delta, e.cap -= delta;
        excess[e.to] += delta, g[e.to][e.rev].cap += delta;
        if (excess[e.to] > 0 and excess[e.to] <= delta) {
            if (!UseGapRelabeling or dist[e.to] <= gap) pque.push(e.to, dist[e.to]);
        }
    }
};
