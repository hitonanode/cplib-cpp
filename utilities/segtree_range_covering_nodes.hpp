#pragma once
#include <algorithm>
#include <vector>

// CUT begin
// Enumerate nodes of nonrecursive segtree which cover [l, r)
std::vector<int> segtree_range_covering_nodes(int N, int l, int r) {
    std::vector<int> ret, ret_rev;
    l += N, r += N;
    while (l < r) {
        if (l & 1) ret.push_back(l++);
        if (r & 1) ret_rev.push_back(--r);
        l >>= 1, r >>= 1;
    }
    std::reverse(ret_rev.begin(), ret_rev.end());
    ret.insert(ret.end(), ret_rev.begin(), ret_rev.end());
    return ret;
}
