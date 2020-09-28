#pragma once
#include "flow/maxflow.hpp"
#include <cassert>
#include <vector>

// CUT begin
// MaxFlow with lower bound
// <https://snuke.hatenablog.com/entry/2016/07/10/043918>
// <https://ei1333.github.io/library/graph/flow/maxflow-lower-bound.cpp>
// flush(s, t): Calculate maxflow (if solution exists), -1 (otherwise)
template <typename T>
struct MaxFlowLowerBound
{
    int N;
    MaxFlow<T> mf;
    std::vector<T> in;
    MaxFlowLowerBound(int N = 0) : N(N), mf(N + 2), in(N) {}
    void add_edge(int from, int to, T cap_lo, T cap_hi) {
        assert(0 <= from and from < N);
        assert(0 <= to and to < N);
        assert(0 <= cap_lo and cap_lo <= cap_hi);
        mf.add_edge(from, to, cap_hi - cap_lo);
        in[from] -= cap_lo;
        in[to] += cap_lo;
    }
    T flush(int s, int t) {
        assert(0 <= s and s < N);
        assert(0 <= t and t < N);
        for (int i = 0; i < N; i++) {
            if (in[i] > 0) mf.add_edge(N, i, in[i]);
            if (in[i] < 0) mf.add_edge(i, N + 1, -in[i]);
        }
        T ret = mf.Dinic(N, N + 1);
        ret += mf.Dinic(s, N + 1);
        ret += mf.Dinic(N, t);
        ret += mf.Dinic(s, t);
        for (const auto &e : mf.edges[N]) {
            if (e.cap > 0) return -1;
        }
        for (int i = 0; i < N; i++) {
            for (const auto &e : mf.edges[i]) {
                if (e.to == N + 1 and e.cap > 0) return -1;
            }
        }
        return ret;
    }
};
