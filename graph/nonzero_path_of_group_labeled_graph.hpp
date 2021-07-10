#pragma once
#include <cassert>
#include <queue>
#include <tuple>
#include <vector>

// CUT begin
// Single-source unorthodox shortest paths
// Complexity: O(M log M)
// This implementation is based on: https://gist.github.com/wata-orz/d3037bd0b919c76dd9ddc0379e1e3192
// Reference:
// [1] Y. Iwata and Y. Yamaguchi, "Finding a Shortest Non-zero Path in Group-Labeled Graphs,"
//     https://arxiv.org/abs/1906.04062
template <class T, T INF, class G> struct ShortestNonzeroPath {
    int V;
    std::vector<std::vector<std::tuple<int, T, G>>> to;
    ShortestNonzeroPath(int n) : V(n), to(n) { static_assert(INF > 0, "INF must be positive"); }
    void add_bi_edge(int u, int v, T len, G g) {
        assert(u >= 0 and u < V);
        assert(v >= 0 and v < V);
        assert(len >= 0);
        to[u].emplace_back(v, len, g);
        to[v].emplace_back(u, len, -g);
    }

private:
    std::vector<T> dist_sp;
    std::vector<int> parent_sp, depth_sp;
    std::vector<G> psi; // psi[path = v0v1...vn] = psi[v0v1] * psi[v1v2] * ... * psi[v(n - 1)vn]

    std::vector<int> uf_ps;
    int _find(int x) {
        if (uf_ps[x] == -1) {
            return x;
        } else {
            return uf_ps[x] = _find(uf_ps[x]);
        }
    }
    void _unite(int r, int c) { uf_ps[c] = r; }

public:
    int s;
    std::vector<T> dist; // dist[i] = Shortest distance of nonzero path from s to i
    void solve(int s_) {
        s = s_;
        assert(s >= 0 and s < V);

        // Solve SSSP
        {
            dist_sp.assign(V, INF);
            depth_sp.assign(V, -1), parent_sp.assign(V, -1);
            psi.assign(V, G());
            std::priority_queue<std::pair<T, int>, std::vector<std::pair<T, int>>, std::greater<std::pair<T, int>>> que;
            dist_sp[s] = 0, depth_sp[s] = 0;
            que.emplace(0, s);
            while (que.size()) {
                T d, l;
                int u, v;
                G g;
                std::tie(d, u) = que.top();
                que.pop();
                if (dist_sp[u] != d) continue;
                for (const auto &p : to[u]) {
                    std::tie(v, l, g) = p;
                    const auto d2 = d + l;
                    if (dist_sp[v] > d2) {
                        dist_sp[v] = d2, depth_sp[v] = depth_sp[u] + 1, parent_sp[v] = u, psi[v] = psi[u] + g;
                        que.emplace(d2, v);
                    }
                }
            }
        }

        uf_ps.assign(V, -1);
        using P = std::tuple<T, int, int>;
        std::priority_queue<P, std::vector<P>, std::greater<P>> que;
        for (int u = 0; u < V; u++) {
            if (dist_sp[u] == INF) continue;
            for (int i = 0; i < int(to[u].size()); i++) {
                int v;
                T l;
                G g;
                std::tie(v, l, g) = to[u][i];
                if (u < v and !(psi[u] + g == psi[v])) que.emplace(dist_sp[u] + dist_sp[v] + l, u, i);
            }
        }

        dist.assign(V, INF);
        while (que.size()) {
            T h;
            int u0, i;
            std::tie(h, u0, i) = que.top();
            que.pop();
            const int v0 = std::get<0>(to[u0][i]);
            int u = _find(u0), v = _find(v0);
            std::vector<int> bs;
            while (u != v) {
                if (depth_sp[u] > depth_sp[v]) {
                    bs.push_back(u), u = _find(parent_sp[u]);
                } else {
                    bs.push_back(v), v = _find(parent_sp[v]);
                }
            }
            for (const int x : bs) {
                _unite(u, x);
                dist[x] = h - dist_sp[x];
                for (int i = 0; i < int(to[x].size()); i++) {
                    int y;
                    T l;
                    G g;
                    std::tie(y, l, g) = to[x][i];
                    if (psi[x] + g == psi[y]) { que.emplace(dist[x] + dist_sp[y] + l, x, i); }
                }
            }
        }
        for (int i = 0; i < V; i++) {
            if (!(psi[i] == G()) and dist_sp[i] < dist[i]) dist[i] = dist_sp[i];
        }
    }
};
/* Example of group G:
struct G {
    unsigned g;
    G(unsigned x = 0) : g(x) {}
    G operator-() const noexcept { return *this; }
    G operator+(const G &r) const noexcept { return G(g ^ r.g); }
    bool operator==(const G &x) const noexcept { return g == x.g; }
};
*/
