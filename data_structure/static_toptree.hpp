#pragma once
#include <cassert>
#include <utility>
#include <vector>

// Structure of static top tree
// https://atcoder.jp/contests/abc351/submissions/52777033
struct static_toptree_structure {
    enum NodeType {
        Vertex,
        Compress,
        Rake,
        AddEdge,
        AddVertex,
    };

    const std::vector<std::vector<int>> &to;
    std::vector<int> par;
    std::vector<int> heavy_child; // heavy_child[i] = child of i on heavy path

    // toptree data
    int stt_root = -1;
    std::vector<int> P, L, R;
    std::vector<NodeType> T;

private:
    int hld_dfs(int now, int prv) {
        int sz = 1, max_sz = 0;
        for (int nxt : to.at(now)) {
            if (nxt == prv) continue;
            par.at(nxt) = now;
            int sub_sz = hld_dfs(nxt, now);
            sz += sub_sz;
            if (max_sz < sub_sz) max_sz = sub_sz, heavy_child.at(now) = nxt;
        }
        return sz;
    }

    int create(int k, int l, int r, NodeType t) {
        if (k == -1) {
            k = P.size();
            P.push_back(-1), L.push_back(l), R.push_back(r), T.push_back(t);
        } else {
            P.at(k) = -1, L.at(k) = l, R.at(k) = r, T.at(k) = t;
        }

        if (l != -1) P.at(l) = k;
        if (r != -1) P.at(r) = k;

        return k;
    }

    std::pair<int, int> merge(const std::vector<std::pair<int, int>> &a, NodeType t) {
        if (a.size() == 1) return a.front();

        int u = 0;
        for (auto &[idx, sz] : a) u += sz;

        std::vector<std::pair<int, int>> left, right;
        for (const auto &[idx, sz] : a) {
            (u > sz ? left : right).emplace_back(idx, sz), u -= sz * 2;
        }

        auto [left_idx, left_sz] = merge(left, t);
        auto [right_idx, right_sz] = merge(right, t);

        return {create(-1, left_idx, right_idx, t), left_sz + right_sz};
    }

    std::pair<int, int> compress(int i) {
        std::vector<std::pair<int, int>> chs{add_vertex(i)};
        while (heavy_child.at(i) != -1) {
            i = heavy_child.at(i);
            chs.push_back(add_vertex(i));
        }

        return merge(chs, Compress);
    }

    std::pair<int, int> rake(int i) {
        std::vector<std::pair<int, int>> chs;
        for (int j : to.at(i)) {
            if (j == par.at(i) or j == heavy_child.at(i)) continue;
            chs.push_back(add_edge(j));
        }

        return chs.empty() ? std::make_pair(-1, 0) : merge(chs, Rake);
    }

    std::pair<int, int> add_edge(int i) {
        auto [c, sz] = compress(i);
        return {create(-1, c, -1, AddEdge), sz};
    }

    std::pair<int, int> add_vertex(int i) {
        auto [c, sz] = rake(i);
        return {create(i, c, -1, c == -1 ? Vertex : AddVertex), sz + 1};
    }

public:
    static_toptree_structure(const std::vector<std::vector<int>> &to, int root) : to(to) {

        const int n = to.size();

        par.assign(n, -1), heavy_child.assign(n, -1);

        hld_dfs(root, -1);

        P.assign(n, -1), L.assign(n, -1), R.assign(n, -1), T.assign(n, Vertex);

        stt_root = compress(root).first;
    }

    int size() const { return P.size(); }

    // Top tree の帰りがけ順に f() を呼ぶ
    // データの初期化などに利用可能
    template <class Callback> void dfs_postorder(Callback f) const {
        auto rec = [&](auto &&self, int now) -> void {
            if (L.at(now) != -1) self(self, L.at(now));
            if (R.at(now) != -1) self(self, R.at(now));
            f(now);
        };
        rec(rec, stt_root);
    }

    // Top tree の v から根（!= もとの木の根）までのパス上で f() を呼ぶ
    // 一点更新などに利用可能
    template <class Callback> void path_to_root(int v, Callback f) const {
        while (v != -1) f(v), v = P.at(v);
    }
};

// Static top tree
template <class TreeDP> struct static_toptree {

    using Point = typename TreeDP::Point;
    using Path = typename TreeDP::Path;

    const static_toptree_structure &stts;
    TreeDP &tree_dp;

    std::vector<Point> point;
    std::vector<Path> path;

private:
    void _update(int i) {
        if (stts.T.at(i) == static_toptree_structure::Vertex) {
            path.at(i) = tree_dp.vertex(i);
        } else if (stts.T.at(i) == static_toptree_structure::Compress) {
            path.at(i) = tree_dp.compress(path.at(stts.L.at(i)), path.at(stts.R.at(i)));
        } else if (stts.T.at(i) == static_toptree_structure::Rake) {
            point.at(i) = tree_dp.rake(point.at(stts.L.at(i)), point.at(stts.R.at(i)));
        } else if (stts.T.at(i) == static_toptree_structure::AddEdge) {
            point.at(i) = tree_dp.add_edge(path.at(stts.L.at(i)));
        } else if (stts.T.at(i) == static_toptree_structure::AddVertex) {
            path.at(i) = tree_dp.add_vertex(point.at(stts.L.at(i)), i);
        } else {
            assert(false);
        }
    }

public:
    static_toptree(const static_toptree_structure &stts, TreeDP &tree_dp)
        : stts(stts), tree_dp(tree_dp), point(stts.size()), path(stts.size()) {
        stts.dfs_postorder([&](int k) { _update(k); });
    }

    void set(int i) {
        stts.path_to_root(i, [&](int k) { _update(k); });
    }

    Path all_prod() const { return path.at(stts.stt_root); }

    // Not verified yet
    Path get_subtree(int i) const {
        Path res = path.at(i);
        while (true) {
            const int p = stts.P.at(i);
            if (p == -1 or stts.T.at(p) != static_toptree_structure::Compress) break;

            if (stts.L.at(p) == i) res = tree_dp.compress(res, path.at(stts.R.at(p)));
            i = p;
        }

        return res;
    }
};

/*
struct tree_dp {
    struct Point;  // Point Cluster
    struct Path;  // Path Cluster

    Path vertex(int i);

    Path compress(const Path &p, const Path &c);

    Point rake(const Point &l, const Point &r);

    Point add_edge(const Path &d);

    Path add_vertex(const Point &d, int i);
};

vector<vector<int>> to(n);
int root;

const static_toptree_structure stts(to, root);

tree_dp dp;
static_toptree tree(stts, dp);
*/
