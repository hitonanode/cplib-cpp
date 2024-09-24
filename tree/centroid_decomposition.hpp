#pragma once
#include <cassert>
#include <utility>
#include <vector>

// Centroid Decomposition
// Verification: https://yukicoder.me/problems/no/2892
// find_current_centroids(int r, int conn_size): Enumerate centroid(s) of the subtree which `r` belongs to.
struct CentroidDecomposition {
    int V;
    std::vector<std::vector<int>> to;

private:
    std::vector<int> is_alive;
    std::vector<int> subtree_size;

    void decompose(int r, int conn_size, auto callback) {

        const int c = find_current_centroids(r, conn_size).first;
        is_alive.at(c) = 0;

        callback(c);

        for (int nxt : to.at(c)) {
            if (!is_alive.at(nxt)) continue;
            int next_size = subtree_size.at(nxt);
            if (subtree_size.at(nxt) > subtree_size.at(c))
                next_size = subtree_size.at(r) - subtree_size.at(c);
            decompose(nxt, next_size, callback);
        }
    }

public:
    CentroidDecomposition(int v = 0) : V(v), to(v), is_alive(v, 1), subtree_size(v) {}

    CentroidDecomposition(int v, const std::vector<std::pair<int, int>> &tree_edges)
        : CentroidDecomposition(v) {
        for (auto e : tree_edges) add_edge(e.first, e.second);
    }

    void add_edge(int v1, int v2) {
        assert(0 <= v1 and v1 < V and 0 <= v2 and v2 < V);
        assert(v1 != v2);
        to.at(v1).push_back(v2), to.at(v2).emplace_back(v1);
    }

    std::pair<int, int> find_current_centroids(int r, int conn_size) {
        assert(is_alive.at(r));

        const int thres = conn_size / 2;

        int c1 = -1, c2 = -1;

        auto rec_search = [&](auto &&self, int now, int prv) -> void {
            bool is_centroid = true;
            subtree_size.at(now) = 1;
            for (int nxt : to.at(now)) {
                if (nxt == prv or !is_alive.at(nxt)) continue;
                self(self, nxt, now);
                subtree_size.at(now) += subtree_size.at(nxt);
                if (subtree_size.at(nxt) > thres) is_centroid = false;
            }
            if (conn_size - subtree_size.at(now) > thres) is_centroid = false;

            if (is_centroid) (c1 < 0 ? c1 : c2) = now;
        };
        rec_search(rec_search, r, -1);

        return {c1, c2};
    }

    void run(int r, auto callback) {
        int conn_size = 0;

        auto rec = [&](auto &&self, int now, int prv) -> void {
            ++conn_size;
            is_alive.at(now) = 1;

            for (int nxt : to.at(now)) {
                if (nxt == prv) continue;
                self(self, nxt, now);
            }
        };
        rec(rec, r, -1);

        decompose(r, conn_size, callback);
    }

    std::vector<int> centroid_decomposition(int r) {
        std::vector<int> res;
        run(r, [&](int v) { res.push_back(v); });
        return res;
    }
};
