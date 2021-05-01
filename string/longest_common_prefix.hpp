#pragma once
#include "../sparse_table/rmq_sparse_table.hpp"
#include "suffix_array.hpp"
#include <algorithm>
#include <string>
#include <utility>
#include <vector>

// CUT begin
struct LCPsparsetable {
    const int N;
    std::vector<int> sainv; // len = N
    StaticRMQ<int> rmq;
    template <typename String> LCPsparsetable(const String &s) : N(s.size()) {
        auto sa = suffix_array(s);
        auto lcp = lcp_array(s, sa);
        sainv.resize(N);
        for (int i = 0; i < N; i++) sainv[sa[i]] = i;
        rmq = {lcp, N};
    }
    int lcplen(int l1, int l2) const {
        if (l1 == l2) return N - l1;
        if (l1 == N or l2 == N) return 0;
        l1 = sainv[l1], l2 = sainv[l2];
        if (l1 > l2) std::swap(l1, l2);
        return rmq.get(l1, l2);
    }
};
