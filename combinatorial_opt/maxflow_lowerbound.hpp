#pragma once
#include "maxflow.hpp"
#include <cassert>
#include <limits>
#include <vector>

// MaxFlow with lower bound
// https://snuke.hatenablog.com/entry/2016/07/10/043918
// https://ei1333.github.io/library/graph/flow/maxflow-lower-bound.cpp
// flush(s, t): Calculate maxflow (if solution exists), -1 (otherwise)
template <typename Cap> struct MaxFlowLowerBound {
    using Maxflow = mf_graph<Cap>;
    int N;
    Maxflow mf;
    std::vector<Cap> in;
    MaxFlowLowerBound(int N = 0) : N(N), mf(N + 2), in(N) {}

    std::vector<Cap> cap_lo_info;

    int add_edge(int from, int to, Cap cap_lo, Cap cap_hi) {
        assert(0 <= from and from < N);
        assert(0 <= to and to < N);
        assert(0 <= cap_lo and cap_lo <= cap_hi);
        in[from] -= cap_lo;
        in[to] += cap_lo;
        cap_lo_info.push_back(cap_lo);
        return mf.add_edge(from, to, cap_hi - cap_lo);
    }

    Cap flow(int s, int t) {
        assert(s != t);
        assert(0 <= s and s < N);
        assert(0 <= t and t < N);
        Cap sum = 0;
        for (int i = 0; i < N; i++) {
            if (in[i] > 0) mf.add_edge(N, i, in[i]), sum += in[i];
            if (in[i] < 0) mf.add_edge(i, N + 1, -in[i]);
        }
        mf.add_edge(t, s, std::numeric_limits<Cap>::max());
        if (mf.flow(N, N + 1) < sum) return -1;
        return mf.flow(s, t);
    }

    typename Maxflow::edge get_edge(int i) {
        auto ret = mf.get_edge(i);
        ret.cap += cap_lo_info.at(i);
        ret.flow += cap_lo_info.at(i);
        return ret;
    }

    std::vector<typename Maxflow::edge> edges() {
        std::vector<typename Maxflow::edge> result;
        for (int i = 0; i < int(cap_lo_info.size()); ++i) result.push_back(get_edge(i));
        return result;
    }
};
