#pragma once

#include <algorithm>
#include <cassert>
#include <limits>
#include <vector>

// CUT begin
// MaxFlow based and AtCoder Library, single class, no namespace, no private variables, compatible with C++11
// Document: <https://atcoder.github.io/ac-library/production/document_ja/maxflow.html>
template <class Cap>
struct mf_graph {
    struct simple_queue_int {
        std::vector<int> payload;
        int pos = 0;
        void reserve(int n) { payload.reserve(n); }
        int size() const { return int(payload.size()) - pos; }
        bool empty() const { return pos == int(payload.size()); }
        void push(const int &t) { payload.push_back(t); }
        int &front() { return payload[pos]; }
        void clear() {
            payload.clear();
            pos = 0;
        }
        void pop() { pos++; }
    };

    mf_graph() : _n(0) {}
    mf_graph(int n) : _n(n), g(n) {}

    int add_edge(int from, int to, Cap cap) {
        assert(0 <= from && from < _n);
        assert(0 <= to && to < _n);
        assert(0 <= cap);
        int m = int(pos.size());
        pos.push_back({from, int(g[from].size())});
        int from_id = int(g[from].size());
        int to_id = int(g[to].size());
        if (from == to) to_id++;
        g[from].push_back(_edge{to, to_id, cap});
        g[to].push_back(_edge{from, from_id, 0});
        return m;
    }

    struct edge {
        int from, to;
        Cap cap, flow;
    };

    edge get_edge(int i) {
        int m = int(pos.size());
        assert(0 <= i && i < m);
        auto _e = g[pos[i].first][pos[i].second];
        auto _re = g[_e.to][_e.rev];
        return edge{pos[i].first, _e.to, _e.cap + _re.cap, _re.cap};
    }
    std::vector<edge> edges() {
        int m = int(pos.size());
        std::vector<edge> result;
        for (int i = 0; i < m; i++) {
            result.push_back(get_edge(i));
        }
        return result;
    }
    void change_edge(int i, Cap new_cap, Cap new_flow) {
        int m = int(pos.size());
        assert(0 <= i && i < m);
        assert(0 <= new_flow && new_flow <= new_cap);
        auto &_e = g[pos[i].first][pos[i].second];
        auto &_re = g[_e.to][_e.rev];
        _e.cap = new_cap - new_flow;
        _re.cap = new_flow;
    }

    std::vector<int> level, iter;
    simple_queue_int que;

    void _bfs(int s, int t) {
        std::fill(level.begin(), level.end(), -1);
        level[s] = 0;
        que.clear();
        que.push(s);
        while (!que.empty()) {
            int v = que.front();
            que.pop();
            for (auto e : g[v]) {
                if (e.cap == 0 || level[e.to] >= 0) continue;
                level[e.to] = level[v] + 1;
                if (e.to == t) return;
                que.push(e.to);
            }
        }
    }
    Cap _dfs(int v, int s, Cap up) {
        if (v == s) return up;
        Cap res = 0;
        int level_v = level[v];
        for (int &i = iter[v]; i < int(g[v].size()); i++) {
            _edge &e = g[v][i];
            if (level_v <= level[e.to] || g[e.to][e.rev].cap == 0) continue;
            Cap d = _dfs(e.to, s, std::min(up - res, g[e.to][e.rev].cap));
            if (d <= 0) continue;
            g[v][i].cap += d;
            g[e.to][e.rev].cap -= d;
            res += d;
            if (res == up) break;
        }
        return res;
    }

    Cap flow(int s, int t) {
        return flow(s, t, std::numeric_limits<Cap>::max());
    }
    Cap flow(int s, int t, Cap flow_limit) {
        assert(0 <= s && s < _n);
        assert(0 <= t && t < _n);
        assert(s != t);

        level.assign(_n, 0), iter.assign(_n, 0);
        que.clear();

        Cap flow = 0;
        while (flow < flow_limit) {
            _bfs(s, t);
            if (level[t] == -1) break;
            std::fill(iter.begin(), iter.end(), 0);
            while (flow < flow_limit) {
                Cap f = _dfs(t, s, flow_limit - flow);
                if (!f) break;
                flow += f;
            }
        }
        return flow;
    }

    std::vector<bool> min_cut(int s) {
        std::vector<bool> visited(_n);
        simple_queue_int que;
        que.push(s);
        while (!que.empty()) {
            int p = que.front();
            que.pop();
            visited[p] = true;
            for (auto e : g[p]) {
                if (e.cap && !visited[e.to]) {
                    visited[e.to] = true;
                    que.push(e.to);
                }
            }
        }
        return visited;
    }

    int _n;
    struct _edge {
        int to, rev;
        Cap cap;
    };
    std::vector<std::pair<int, int>> pos;
    std::vector<std::vector<_edge>> g;
};
