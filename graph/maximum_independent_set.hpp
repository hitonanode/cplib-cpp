#pragma once
#include <bitset>
#include <cassert>
#include <stack>
#include <vector>

// Maximum Independent Set for general graph （最大独立集合）
// Works with reasonable time complexity when N~40
// Given graph must not have self-edges
// Verified: https://judge.yosupo.jp/submission/1864 / https://yukicoder.me/problems/no/382
// Reference: https://www.slideshare.net/wata_orz/ss-12131479
template <int BS = 64> struct maximum_independent_set {
    std::vector<std::bitset<BS>> conn;
    int V;               // # of vertices
    int nret;            // Largest possible size of independent set
    std::bitset<BS> ret; // Result is saved here: use (1), don't use (0)
    std::bitset<BS> _avail;
    std::bitset<BS> _tmp_state;

    void mis_dfs() {
        bool retry = true;
        std::stack<int> st;
        while (retry) {
            retry = false;
            for (int i = _avail._Find_first(); i < V; i = _avail._Find_next(i)) {
                int nb = (_avail & conn[i]).count();
                if (nb <= 1) {
                    st.emplace(i), _avail.reset(i), _tmp_state.set(i);
                    retry = true;
                    if (nb == 1) {
                        int j = (_avail & conn[i])._Find_first();
                        st.emplace(j), _avail.reset(j);
                    }
                }
            }
        }

        int t = _tmp_state.count();
        if (t > nret) nret = t, ret = _tmp_state;

        int d = -1, n = -1;
        for (int i = _avail._Find_first(); i < V; i = _avail._Find_next(i)) {
            int c = (_avail & conn[i]).count();
            if (c > d) d = c, n = i;
        }

        if (d > 0) {
            std::bitset<BS> nxt = _avail & conn[n];
            _avail.reset(n);
            mis_dfs();
            _tmp_state.set(n);
            _avail &= ~nxt;
            mis_dfs();
            _avail |= nxt;
            _avail.set(n);
            _tmp_state.reset(n);
        }

        while (st.size()) {
            int i = st.top();
            _avail.set(i);
            _tmp_state.reset(i);
            st.pop();
        }
    }
    maximum_independent_set(const std::vector<std::vector<int>> &e)
        : conn(e.size()), V(e.size()), nret(-1) {
        assert(V <= BS);
        for (int i = 0; i < V; i++)
            for (auto &j : e[i])
                if (i != j) conn[i].set(j), conn[j].set(i);
        for (int i = 0; i < V; i++) _avail.set(i);
        _tmp_state.reset();
        mis_dfs();
    }
};

// A little fast implementation of MaximumIndependentSet
// by substituting long long int's bit for `ret` & `_tmp_state`
// Requirement: V <= 64
struct maximum_independent_set_int_based {
    std::vector<long long> conn;
    int V;         // # of vertices
    int nret;      // Largest possible size of independent set
    long long ret; // Result is saved here: use (1), don't use (0)
    long long _avail;
    long long _tmp_state;

    void mis_dfs() {
        bool retry = true;
        std::stack<int> st;
        while (retry) {
            retry = false;
            for (int i = 0; i < V; i++)
                if (_avail & (1LL << i)) {
                    int nb = __builtin_popcountll(_avail & conn[i]);
                    if (nb <= 1) {
                        st.emplace(i), _avail -= 1LL << i, _tmp_state |= 1LL << i;
                        retry = true;
                        if (nb == 1) {
                            int j = __builtin_ctzll(_avail & conn[i]);
                            st.emplace(j), _avail &= ~(1LL << j);
                        }
                    }
                }
        }

        int t = __builtin_popcountll(_tmp_state);
        if (t > nret) nret = t, ret = _tmp_state;

        int d = -1, n = -1;
        for (int i = 0; i < V; i++)
            if (_avail & (1LL << i)) {
                int c = __builtin_popcountll(_avail & conn[i]);
                if (c > d) d = c, n = i;
            }

        if (d > 0) {
            long long nxt = _avail & conn[n];
            _avail -= 1LL << n;
            mis_dfs();
            _tmp_state |= 1LL << n;
            _avail &= ~nxt;
            mis_dfs();
            _avail |= nxt;
            _avail |= 1LL << n;
            _tmp_state &= ~(1LL << n);
        }

        while (st.size()) {
            int i = st.top();
            _avail |= 1LL << i;
            _tmp_state &= ~(1LL << i);
            st.pop();
        }
    }
    maximum_independent_set_int_based(const std::vector<std::vector<int>> &e)
        : conn(e.size()), V(e.size()), nret(-1), _avail((1LL << V) - 1), _tmp_state(0) {
        assert(V <= 63);
        for (int i = 0; i < V; i++)
            for (auto &j : e[i])
                if (i != j) conn[i] |= 1LL << j, conn[j] |= 1LL << i;
        mis_dfs();
    }
};
