#pragma once

#include <cassert>
#include <utility>
#include <vector>

// Construct block cut tree (or forest) from a given graph
// Complexity: O(N + M), N = |vertices|, M = |edges|
// based on this idea: https://x.com/noshi91/status/1529858538650374144
// based on this implementation: https://ssrs-cp.github.io/cp_library/graph/extended_block_cut_tree.hpp.html
struct extended_block_cut_trees {
    int N;                            // number of vertices
    int B;                            // number of blocks
    std::vector<std::vector<int>> to; // (0, ..., N - 1): vertices, (N, ..., N + B - 1): blocks

    extended_block_cut_trees(int N, const std::vector<std::pair<int, int>> &edges)
        : N(N), B(0), to(N) {
        std::vector<std::vector<int>> adj(N);
        for (auto [u, v] : edges) {
            if (u != v) adj.at(u).push_back(v), adj.at(v).push_back(u);
        }

        std::vector<int> dfs_next(N, -1), dist(N, -1), back_cnt(N);

        auto rec1 = [&](auto &&self, int now) -> void {
            for (int nxt : adj[now]) {
                if (dist[nxt] == -1) {
                    dist[nxt] = dist[now] + 1;
                    dfs_next[now] = nxt;
                    self(self, nxt);
                    back_cnt[now] += back_cnt[nxt];
                } else if (dist[nxt] < dist[now] - 1) {
                    ++back_cnt[now];
                    --back_cnt[dfs_next[nxt]];
                }
            }
        };

        for (int i = 0; i < N; ++i) {
            if (dist[i] == -1) dist[i] = 0, rec1(rec1, i);
        }

        std::vector<bool> used(N);

        auto rec2 = [&](auto &&self, int now, int current_b) -> void {
            used[now] = true;
            bool ok = false;

            for (int nxt : adj[now]) {
                if (dist[nxt] == dist[now] + 1 and !used[nxt]) {
                    if (back_cnt[nxt] > 0) {
                        if (!ok) {
                            ok = true;
                            add_edge(now, current_b);
                        }
                        self(self, nxt, current_b);
                    } else {
                        to.push_back({});
                        ++B;
                        add_edge(now, B - 1);
                        self(self, nxt, B - 1);
                    }
                }
            }

            if (!ok and dist[now] > 0) { add_edge(now, current_b); }
        };

        for (int i = 0; i < N; ++i) {
            if (dist[i] == 0) { rec2(rec2, i, B - 1); }
            if (adj[i].empty()) {
                to.push_back({});
                ++B;
                add_edge(i, B - 1);
            }
        }
    }

    int size() const { return N + B; }

    bool is_articulation_point(int vertex) const {
        assert(0 <= vertex and vertex < N);
        return to[vertex].size() > 1;
    }

    int block_size(int block) const {
        assert(0 <= block and block < B);
        return to[N + block].size();
    }

    const std::vector<int> &block_vertices(int block) const {
        assert(0 <= block and block < B);
        return to[N + block];
    }

    std::vector<std::vector<int>> biconnected_components() const {
        return std::vector<std::vector<int>>(to.begin() + N, to.end());
    }

    // first < N (vertices), second >= N (blocks)
    std::vector<std::pair<int, int>> get_edges() const {
        std::vector<std::pair<int, int>> edges;
        for (int i = 0; i < N; ++i) {
            for (int j : to[i]) edges.emplace_back(i, j);
        }
        return edges;
    }

private:
    void add_edge(int vertex, int block) {
        assert(0 <= vertex and vertex < N);
        assert(0 <= block and block < B);
        to[vertex].push_back(N + block);
        to[N + block].push_back(vertex);
    }
};
