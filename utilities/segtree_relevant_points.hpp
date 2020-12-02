#include <algorithm>
#include <vector>

// CUT begin
// Enumerate nodes of nonrecursive segtree which cover [l, r)
std::vector<int> segtree_relevant_points(int N, int l, int r) {
    std::vector<int> ret;
    l += N, r += N;
    while (l < r) {
        if (l & 1) ret.push_back(l++);
        if (r & 1) ret.push_back(--r);
        l >>= 1, r >>= 1;
    }
    std::sort(ret.begin(), ret.end());
    return ret;
}
