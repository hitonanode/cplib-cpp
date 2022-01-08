#pragma once
#include <algorithm>
#include <vector>

// CUT begin
// Count elements in $[A_\mathrm{begin}, ..., A_{\mathrm{end}-1}]$ which satisfy $A_i < \mathrm{query}$
// Complexity: $O(N \log N)$ for initialization, $O(\log^2 N)$ for each query
// Verified: https://codeforces.com/contest/1288/submission/68865506
template <typename T> struct merge_sort_tree {
    int N;
    std::vector<std::vector<T>> x;
    merge_sort_tree() = default;
    merge_sort_tree(const std::vector<T> &vec) : N(vec.size()) {
        x.resize(N * 2);
        for (int i = 0; i < N; i++) x[N + i] = {vec[i]};
        for (int i = N - 1; i; i--) {
            std::merge(x[i * 2].begin(), x[i * 2].end(), x[i * 2 + 1].begin(), x[i * 2 + 1].end(),
                       std::back_inserter(x[i]));
        }
    }
    int cntLess(int l, int r, T query) const {
        l += N, r += N;
        int ret = 0;
        while (l < r) {
            if (l & 1)
                ret += std::lower_bound(x[l].begin(), x[l].end(), query) - x[l].begin(), l++;
            if (r & 1)
                r--, ret += std::lower_bound(x[r].begin(), x[r].end(), query) - x[r].begin();
            l >>= 1, r >>= 1;
        }
        return ret;
    }
    int cntLesseq(int l, int r, T query) const {
        l += N, r += N;
        int ret = 0;
        while (l < r) {
            if (l & 1)
                ret += std::upper_bound(x[l].begin(), x[l].end(), query) - x[l].begin(), l++;
            if (r & 1)
                r--, ret += std::upper_bound(x[r].begin(), x[r].end(), query) - x[r].begin();
            l >>= 1, r >>= 1;
        }
        return ret;
    }
    int cntMore(int begin, int end, T query) const {
        int tot = std::max(0, std::min(end, N) - std::max(begin, 0));
        return tot - cntLesseq(begin, end, query);
    }
    int cntMoreeq(int begin, int end, T query) const {
        int tot = std::max(0, std::min(end, N) - std::max(begin, 0));
        return tot - cntLess(begin, end, query);
    }

    template <class OStream> friend OStream &operator<<(OStream &os, const merge_sort_tree &clt) {
        os << '[';
        for (int i = 0; i < clt.N; i++) os << clt.x[clt.N + i][0] << ',';
        return os << ']';
    }
};
