#pragma once
#include <algorithm>
#include <cassert>
#include <stack>
#include <vector>

// Maximum weight independent set
// Requirement: n <= 63
// Complexity: exponential, O(1.381^n n)
// Reference: https://www.slideshare.net/wata_orz/ss-12131479, p.34
// Verified: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3519
template <class Weight> struct max_weight_independent_set {
    int V; // # of vertices
    std::vector<long long> conn;
    std::vector<Weight> ws;

    long long solution_set; // Solution set is saved here: use (1) / not use (0)
    Weight eval_solution;   // optimal value

private:
    long long state;
    Weight eval_state;
    long long avail;
    void mis_dfs() {
        std::stack<int, std::vector<int>> st;
        for (bool retry = true; retry;) { // Pruning
            retry = false;
            for (int i = 0; i < V; i++) {
                if (avail & (1LL << i)) {
                    int nb = __builtin_popcountll(avail & conn[i]);
                    if (nb == 0) {
                        st.emplace(i), avail -= 1LL << i, state |= 1LL << i;
                        eval_state += ws[i];
                        retry = true;
                    }
                    if (nb == 1) {
                        int j = __builtin_ctzll(avail & conn[i]);
                        if (ws[i] >= ws[j]) {
                            st.emplace(i), avail -= 1LL << i, state |= 1LL << i;
                            eval_state += ws[i];
                            retry = true;
                            st.emplace(j), avail &= ~(1LL << j);
                        }
                    }
                }
            }
        }

        if (eval_state > eval_solution) eval_solution = eval_state, solution_set = state;

        int d = -1, n = -1;
        for (int i = 0; i < V; i++) {
            if (avail & (1LL << i)) {
                int c = __builtin_popcountll(avail & conn[i]);
                if (c > d) d = c, n = i;
            }
        }

        if (d >= 0) {
            long long nxt = avail & conn[n];
            avail -= 1LL << n;
            mis_dfs();
            state |= 1LL << n;
            eval_state += ws[n];
            avail &= ~nxt;
            mis_dfs();
            avail |= nxt;
            avail |= 1LL << n;
            state &= ~(1LL << n);
            eval_state -= ws[n];
        }

        for (; st.size(); st.pop()) {
            int i = st.top();
            avail |= 1LL << i;
            if ((state >> i) & 1LL) state -= 1LL << i, eval_state -= ws[i];
        }
    }

public:
    max_weight_independent_set(const int V)
        : V(V), conn(V), ws(V, Weight(1)), solution_set(0), eval_solution(Weight()), state(0),
          eval_state(Weight()), avail((1LL << V) - 1) {}
    max_weight_independent_set(const std::vector<Weight> &ws_)
        : max_weight_independent_set(ws_.size()) {
        ws = ws_;
    }

    void add_edge(int u, int v) {
        assert(u != v);
        assert(0 <= u and u < V);
        assert(0 <= v and v < V);
        conn[u] |= 1LL << v;
        conn[v] |= 1LL << u;
    }

    Weight solve() {
        state = 0, eval_state = Weight(), avail = (1LL << V) - 1;
        solution_set = 0, eval_solution = Weight();
        mis_dfs();
        return eval_solution;
    }
};
