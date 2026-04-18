#pragma once
#include <span>
#include <type_traits>
#include <vector>

// Guni / Sack / DSU on tree
// https://codeforces.com/blog/entry/44351
// https://atcoder.jp/contests/abc454/editorial/19112
struct guni {
    int n;
    int last_root;
    std::vector<std::vector<int>> to;
    std::vector<int> sz, ver, st, ft; // subtree size / dfs order / subtree start / subtree fin

    guni(int n_ = 0) : n(n_), last_root(-1), to(n_) {}

    void add_bi_edge(int u, int v) { to.at(u).push_back(v), to.at(v).push_back(u); }

    void sdfs(int v, int p) { // Build sz / ver / st / ft, and move heavy child to the back
        st.at(v) = ver.size(), ver.push_back(v);
        int heavy_idx = -1;
        for (int i = 0; i < int(to.at(v).size()); ++i) {
            int u = to.at(v).at(i);
            if (u == p) continue;
            sdfs(u, v);
            sz.at(v) += sz.at(u);
            if (heavy_idx == -1 or sz.at(u) > sz.at(to.at(v).at(heavy_idx))) heavy_idx = i;
        }
        if (heavy_idx != -1) std::swap(to.at(v).at(heavy_idx), to.at(v).back());
        ft.at(v) = ver.size();
    }

    std::span<const int> subtree(int v) const {
        return std::span<const int>(ver).subspan(st.at(v), ft.at(v) - st.at(v));
    }

    template <class F> void call_reset(F &ResetAll, int v) const {
        if constexpr (std::is_invocable_v<F &, std::span<const int>>) {
            ResetAll(subtree(v));
        } else {
            static_assert(std::is_invocable_v<F &>,
                          "ResetAll must be callable with std::span<const int> or with no argument");
            ResetAll();
        }
    }

    template <class F1, class F2, class F3>
    void dfs(int v, int p, F1 &Add, F2 &ResetAll, F3 &Solve) {
        const int big_child = (!to.at(v).empty() and to.at(v).back() != p) ? to.at(v).back() : -1;
        for (int u : to.at(v)) {
            if (u != p and u != big_child) {
                dfs(u, v, Add, ResetAll, Solve);
                call_reset(ResetAll, u);
            }
        }
        if (big_child != -1) dfs(big_child, v, Add, ResetAll, Solve);

        for (int u : to.at(v)) {
            if (u != p and u != big_child) {
                for (int i = st.at(u); i < ft.at(u); ++i) Add(ver.at(i));
            }
        }
        Add(v);
        Solve(v);
    }

    template <class F1, class F2, class F3>
    void run(const int root, F1 Add, F2 ResetAll, F3 Solve) {
        if (last_root != root) {
            last_root = root, ver.clear(), st.resize(n), ft.resize(n), sz.assign(n, 1);
            sdfs(root, -1);
        }
        dfs(root, -1, Add, ResetAll, Solve);
        call_reset(ResetAll, root);
    }
};
