#pragma once
#include <algorithm>
#include <cassert>
#include <deque>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

// CUT begin
// 区間に辺を張って最短距離問題を解く
// Verify: Codeforces Round #406 (Div. 1), problem: (B) Legacy <https://codeforces.com/contest/786/submission/93412867>
template <typename T = long long> struct SegmentEdgeShortestPath {
    int V;
    int h;
    int INVALID = -1;
    std::vector<std::vector<std::pair<int, T>>> to;
    SegmentEdgeShortestPath() = default;
    SegmentEdgeShortestPath(int V) : V(V), h(1) {
        while (h < V) h *= 2;
        to.resize(h * 3);
        for (int i = 1; i < h; i++) {
            to[i].emplace_back(i * 2, 0);
            to[i].emplace_back(i * 2 + 1, 0);
            int j = i * 2 + h * 2;
            if (j >= h * 3) j -= h * 2;
            to[j].emplace_back(i + h * 2, 0);
            to[j + 1].emplace_back(i + h * 2, 0);
        }
    }
    void _add_dfs(int now, int l, int r, int begin, int end, std::vector<int> &vec_add) {
        if (end <= l or r <= begin) return;
        if (l <= begin and end <= r) {
            vec_add.emplace_back(now);
            return;
        }
        _add_dfs(now * 2, l, r, begin, (begin + end) / 2, vec_add);
        _add_dfs(now * 2 + 1, l, r, (begin + end) / 2, end, vec_add);
    }

    std::vector<int> from_vs, to_vs;
    void add_edge(int from_l, int from_r, int to_l, int to_r, T len) {
        from_vs.clear(), to_vs.clear();
        _add_dfs(1, from_l, from_r, 0, h, from_vs);
        _add_dfs(1, to_l, to_r, 0, h, to_vs);
        for (auto &x : from_vs)
            if (x < h) x += h * 2;
        for (const auto s : from_vs) {
            for (const auto t : to_vs) { to[s].emplace_back(t, len); }
        }
    }
    std::vector<T> dist;
    std::vector<T> _d_tmp;
    void solve01dfs(int s) {
        assert(s >= 0 and s < V);
        s += h;
        _d_tmp.assign(h * 3, std::numeric_limits<T>::max() / 2);
        _d_tmp[s] = 0;
        std::deque<int> q;
        q.emplace_back(s);
        while (q.size()) {
            int now = q.front();
            q.pop_front();
            for (const auto &p : to[now]) {
                const int nxt = p.first, d = p.second;
                if (_d_tmp[nxt] > _d_tmp[now] + d) {
                    _d_tmp[nxt] = _d_tmp[now] + d;
                    if (d)
                        q.emplace_back(nxt);
                    else
                        q.emplace_front(nxt);
                }
            }
        }
        dist.resize(V);
        std::copy(_d_tmp.begin() + h, _d_tmp.begin() + h + V, dist.begin());
    }

    void solve_dijkstra(int s) {
        assert(s >= 0 and s < V);
        s += h;
        _d_tmp.assign(h * 3, std::numeric_limits<T>::max() / 2);
        _d_tmp[s] = 0;
        using P = std::pair<T, int>;
        std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
        pq.emplace(0, s);
        while (pq.size()) {
            auto a = pq.top();
            pq.pop();
            int now = a.second;
            if (_d_tmp[now] < a.first) continue;
            for (const auto p : to[now]) {
                int nxt = p.first;
                T d = p.second;
                if (_d_tmp[nxt] > _d_tmp[now] + d) {
                    _d_tmp[nxt] = _d_tmp[now] + d;
                    pq.emplace(_d_tmp[nxt], nxt);
                }
            }
        }
        dist.resize(V);
        std::copy(_d_tmp.begin() + h, _d_tmp.begin() + h + V, dist.begin());
    }
};
