#pragma once
#include <algorithm>
#include <cassert>
#include <functional>
#include <queue>
#include <stack>
#include <utility>
#include <vector>

// Heavy-light decomposition of trees (forest)
// Based on http://beet-aizu.hatenablog.com/entry/2017/12/12/235950
struct heavy_light_decomposition {
    int V;
    int k;
    std::vector<std::vector<int>> e;
    std::vector<int> par;         // par[i] = parent of vertex i (Default: -1)
    std::vector<int> depth;       // depth[i] = distance between root and vertex i
    std::vector<int> subtree_sz;  // subtree_sz[i] = size of subtree whose root is i
    std::vector<int> heavy_child; // heavy_child[i] = child of vertex i on heavy path (Default: -1)
    std::vector<int> tree_id;     // tree_id[i] = id of tree vertex i belongs to
    // subtree_begin[i] = aligned id for vertex i (consecutive on heavy edges)
    std::vector<int> subtree_begin, subtree_end;
    std::vector<int> vis_order; // vis_order[subtree_begin[i]] = i
    std::vector<int> head; // head[i] = id of vertex on heavy path of vertex i, nearest to root

    heavy_light_decomposition(int n, const std::vector<std::pair<int, int>> &edges)
        : V(n), k(0), e(n), par(n), depth(n), subtree_sz(n), heavy_child(n), tree_id(n, -1),
          subtree_begin(n), subtree_end(n), vis_order(0), head(n) {
        for (auto [u, v] : edges) {
            assert(u != v);
            e.at(u).emplace_back(v);
            e.at(v).emplace_back(u);
        }
    }

    void _build_dfs_1(int root) {
        std::vector<std::pair<int, int>> st;
        par[root] = -1;
        depth[root] = 0;
        st.emplace_back(root, 0);
        while (!st.empty()) {
            int now = st.back().first;
            int &i = st.back().second;
            if (i < (int)e[now].size()) {
                int nxt = e[now][i++];
                if (nxt == par[now]) continue;
                par[nxt] = now;
                depth[nxt] = depth[now] + 1;
                st.emplace_back(nxt, 0);
            } else {
                st.pop_back();
                int max_sub_sz = 0;
                subtree_sz[now] = 1;
                heavy_child[now] = -1;
                for (auto nxt : e[now]) {
                    if (nxt == par[now]) continue;
                    subtree_sz[now] += subtree_sz[nxt];
                    if (max_sub_sz < subtree_sz[nxt]) {
                        max_sub_sz = subtree_sz[nxt], heavy_child[now] = nxt;
                    }
                }
            }
        }
    }

    void _build_dfs_2(int now, int tree_id_now) {
        std::vector<std::pair<int, bool>> st;
        st.emplace_back(now, true);
        head[now] = now;

        while (!st.empty()) {
            auto [now, mode] = st.back();
            st.pop_back();

            if (mode) {
                tree_id[now] = tree_id_now;
                subtree_begin[now] = k++;
                vis_order.push_back(now);

                st.emplace_back(now, false);

                for (int nxt : e[now]) {
                    if (nxt == par[now] or nxt == heavy_child[now]) continue;
                    head[nxt] = nxt;
                    st.emplace_back(nxt, true);
                }

                if (heavy_child[now] != -1) {
                    head[heavy_child[now]] = head[now];
                    st.emplace_back(heavy_child[now], true);
                }
            } else {
                subtree_end[now] = k;
            }
        }
    }

    void build(std::vector<int> roots = {0}) {
        int tree_id_now = 0;
        for (int r : roots) {
            _build_dfs_1(r);
            _build_dfs_2(r, tree_id_now++);
        }
    }

    template <class T> std::vector<T> segtree_rearrange(const std::vector<T> &data) const {
        assert(int(data.size()) == V);
        std::vector<T> ret;
        ret.reserve(vis_order.size());
        for (int v : vis_order) ret.emplace_back(data[v]);
        return ret;
    }

    void for_vertex(int u, const std::function<void(int)> &f) const { f(subtree_begin[u]); }

    // query for vertices on path [u, v] (INCLUSIVE)
    void
    for_each_vertex(int u, int v, const std::function<void(int ancestor, int descendant)> &f) const {
        while (true) {
            if (subtree_begin[u] > subtree_begin[v]) std::swap(u, v);
            f(std::max(subtree_begin[head[v]], subtree_begin[u]), subtree_begin[v]);
            if (head[u] == head[v]) break;
            v = par[head[v]];
        }
    }

    void for_each_vertex_noncommutative(
        int from, int to, const std::function<void(int ancestor, int descendant)> &fup,
        const std::function<void(int ancestor, int descendant)> &fdown) const {
        int u = from, v = to;
        const int lca = lowest_common_ancestor(u, v), dlca = depth[lca];
        while (u >= 0 and depth[u] > dlca) {
            const int p = (depth[head[u]] > dlca ? head[u] : lca);
            fup(subtree_begin[p] + (p == lca), subtree_begin[u]), u = par[p];
        }
        static std::vector<std::pair<int, int>> lrs;
        int sz = 0;
        while (v >= 0 and depth[v] >= dlca) {
            const int p = (depth[head[v]] >= dlca ? head[v] : lca);
            if (int(lrs.size()) == sz) lrs.emplace_back(0, 0);
            lrs.at(sz++) = {p, v}, v = par.at(p);
        }
        while (sz--) fdown(subtree_begin[lrs.at(sz).first], subtree_begin[lrs.at(sz).second]);
    }

    // query for edges on path [u, v]
    void for_each_edge(int u, int v, const std::function<void(int, int)> &f) const {
        while (true) {
            if (subtree_begin[u] > subtree_begin[v]) std::swap(u, v);
            if (head[u] != head[v]) {
                f(subtree_begin[head[v]], subtree_begin[v]);
                v = par[head[v]];
            } else {
                if (u != v) f(subtree_begin[u] + 1, subtree_begin[v]);
                break;
            }
        }
    }

    // query for vertices in subtree rooted at u
    void for_subtree(int u, const std::function<void(int, int)> &f) const {
        f(subtree_begin[u], subtree_end[u] - 1);
    }

    // lowest_common_ancestor: O(log V)
    int lowest_common_ancestor(int u, int v) const {
        assert(tree_id[u] == tree_id[v] and tree_id[u] >= 0);
        while (true) {
            if (subtree_begin[u] > subtree_begin[v]) std::swap(u, v);
            if (head[u] == head[v]) return u;
            v = par[head[v]];
        }
    }

    int distance(int u, int v) const {
        assert(tree_id[u] == tree_id[v] and tree_id[u] >= 0);
        return depth[u] + depth[v] - 2 * depth[lowest_common_ancestor(u, v)];
    }

    // Level ancestor, O(log V)
    // if k-th parent is out of range, return -1
    int kth_parent(int v, int k) const {
        if (k < 0) return -1;
        while (v >= 0) {
            int h = head.at(v), len = depth.at(v) - depth.at(h);
            if (k <= len) return vis_order.at(subtree_begin.at(v) - k);
            k -= len + 1, v = par.at(h);
        }
        return -1;
    }

    // Jump on tree, O(log V)
    int s_to_t_by_k_steps(int s, int t, int k) const {
        if (k < 0) return -1;
        if (k == 0) return s;
        int lca = lowest_common_ancestor(s, t);
        if (k <= depth.at(s) - depth.at(lca)) return kth_parent(s, k);
        return kth_parent(t, depth.at(s) + depth.at(t) - depth.at(lca) * 2 - k);
    }
};
