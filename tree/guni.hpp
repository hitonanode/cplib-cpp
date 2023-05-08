#pragma once
#include <vector>

// Guni / Sack / DSU on tree
// https://codeforces.com/blog/entry/44351
struct guni {
    int n;
    int last_root;
    std::vector<std::vector<int>> to;
    std::vector<int> sz, ver, st, ft; // subtree size / dfs order / subtree start / subtree fin

    guni(int n_ = 0) : n(n_), last_root(-1), to(n_) {}

    void add_bi_edge(int u, int v) { to.at(u).push_back(v), to.at(v).push_back(u); }

    void sdfs(int v, int p) { // Build sz / ver / st / ft
        st.at(v) = ver.size(), ver.push_back(v);
        for (int u : to.at(v)) sz.at(v) += (u != p) ? (sdfs(u, v), sz.at(u)) : 0;
        ft.at(v) = ver.size();
    }

    template <class F1, class F2, class F3>
    void dfs(int v, int p, bool keep, F1 Add, F2 Remove, F3 Solve) {
        int mx = -1, big_child = -1;
        for (int u : to.at(v)) {
            if (u != p and sz.at(u) > mx) mx = sz.at(u), big_child = u;
        }
        for (int u : to.at(v)) {
            if (u != p and u != big_child) dfs(u, v, false, Add, Remove, Solve);
        }
        if (big_child != -1) dfs(big_child, v, true, Add, Remove, Solve);

        for (int u : to.at(v)) {
            if (u != p and u != big_child) {
                for (int i = st.at(u); i < ft.at(u); ++i) Add(ver.at(i));
            }
        }
        Add(v);
        Solve(v);

        if (!keep) {
            for (int i = st.at(v); i < ft.at(v); ++i) Remove(ver.at(i));
        }
    }

    template <class F1, class F2, class F3> void run(const int root, F1 Add, F2 Remove, F3 Solve) {
        if (last_root != root) {
            last_root = root, ver.clear(), st.resize(n), ft.resize(n), sz.assign(n, 1);
            sdfs(root, -1);
        }
        dfs(root, -1, false, Add, Remove, Solve);
    }
};
