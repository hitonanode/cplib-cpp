#pragma once
#include <algorithm>
#include <cassert>
#include <functional>
#include <stack>
#include <queue>
#include <utility>
#include <vector>


// Heavy-Light Decomposition of trees
// Based on <http://beet-aizu.hatenablog.com/entry/2017/12/12/235950>
struct HeavyLightDecomposition {
    int V;
    int k;
    int nb_heavy_path;
    std::vector<std::vector<int>> e;
    std::vector<int> par;  // par[i] = parent of vertex i (Default: -1)
    std::vector<int> depth;  // depth[i] = distance between root and vertex i
    std::vector<int> subtree_sz; // subtree_sz[i] = size of subtree whose root is i
    std::vector<int> heavy_child;  // heavy_child[i] = child of vertex i on heavy path (Default: -1)
    std::vector<int> tree_id;  // tree_id[i] = id of tree vertex i belongs to
    std::vector<int> aligned_id, aligned_id_inv;  // aligned_id[i] =  aligned id for vertex i (consecutive on heavy edges)
    std::vector<int> head;  // head[i] = id of vertex on heavy path of vertex i, nearest to root
    std::vector<int> head_ids;  // consist of head vertex id's
    std::vector<int> heavy_path_id;  // heavy_path_id[i] = heavy_path_id for vertex [i]

    HeavyLightDecomposition(int sz = 0) : V(sz), k(0), nb_heavy_path(0), e(sz), par(sz), depth(sz),
    subtree_sz(sz), heavy_child(sz), tree_id(sz, -1), aligned_id(sz), aligned_id_inv(sz), head(sz), heavy_path_id(sz, -1) {}
    void add_edge(int u, int v) {
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }

    void _build_dfs(int root) {
        std::stack<std::pair<int, int>> st;
        par[root] = -1;
        depth[root] = 0;
        st.emplace(root, 0);
        while (!st.empty()) {
            int now = st.top().first;
            int &i = st.top().second;
            if (i < (int)e[now].size()) {
                int nxt = e[now][i++];
                if (nxt == par[now]) continue;
                par[nxt] = now;
                depth[nxt] = depth[now] + 1;
                st.emplace(nxt, 0);
            } else {
                st.pop();
                int max_sub_sz = 0;
                subtree_sz[now] = 1;
                heavy_child[now] = -1;
                for (auto nxt : e[now]) {
                    if (nxt == par[now]) continue;
                    subtree_sz[now] += subtree_sz[nxt];
                    if (max_sub_sz < subtree_sz[nxt]) max_sub_sz = subtree_sz[nxt], heavy_child[now] = nxt;
                }
            }
        }
    }

    void _build_bfs(int root, int tree_id_now) {
        std::queue<int> q({root});
        while (!q.empty()) {
            int h = q.front();
            q.pop();
            head_ids.emplace_back(h);
            for (int now = h; now != -1; now = heavy_child[now]) {
                tree_id[now] = tree_id_now;
                aligned_id[now] = k++;
                aligned_id_inv[aligned_id[now]] = now;
                heavy_path_id[now] = nb_heavy_path;
                head[now] = h;
                for (int nxt : e[now]) if (nxt != par[now] and nxt != heavy_child[now]) q.push(nxt);
            }
            nb_heavy_path++;
        }
    }

    void build(std::vector<int> roots = {0}) {
        int tree_id_now = 0;
        for (auto r : roots) {
            _build_dfs(r);
            _build_bfs(r, tree_id_now++);
        }
    }

    // query for vertices on path [u, v] (INCLUSIVE)
    void for_each_vertex(int u, int v, const std::function<void(int, int)>& f) {
        while (true) {
            if (aligned_id[u] > aligned_id[v]) std::swap(u, v);
            f(std::max(aligned_id[head[v]], aligned_id[u]), aligned_id[v]);
            if (head[u] != head[v]) v = par[head[v]];
            else break;
        }
    }

    // query for edges on path [u, v]
    void for_each_edge(int u, int v, const std::function<void(int, int)>& f)
    {
        while (true) {
            if (aligned_id[u] > aligned_id[v]) std::swap(u, v);
            if (head[u] != head[v]) {
                f(aligned_id[head[v]], aligned_id[v]);
                v = par[head[v]];
            }
            else {
                if (u != v) f(aligned_id[u] + 1, aligned_id[v]);
                break;
            }
        }
    }

    // lowest_common_ancestor: O(logV)
    int lowest_common_ancestor(int u, int v) {
        assert(tree_id[u] == tree_id[v] and tree_id[u] >= 0);
        while (true) {
            if (aligned_id[u] > aligned_id[v]) std::swap(u, v);
            if (head[u] == head[v]) return u;
            v = par[head[v]];
        }
    }

    int distance(int u, int v) {
        assert(tree_id[u] == tree_id[v] and tree_id[u] >= 0);
        return depth[u] + depth[v] - 2 * depth[lowest_common_ancestor(u, v)];
    }
};
