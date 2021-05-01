#pragma once
#include <cassert>
#include <cmath>
#include <utility>
#include <vector>

// CUT begin
// Mo's algorithm
// - add_range(l, r) : Add [l, r) as query.
// - run(Add, Remove, Query) : run Mo's algorithm.
//   - Add(i) : Add i-th element ([i + 1, r) -> [i, r)).
//   - Remove(i) : Remove i-th element (Inverse of Add(i)).
//   - Query(q) : Solve q-th problem.
// Veirfied: https://codeforces.com/contest/375/submission/114665433
class MosAlgorithm {
    static const int INF = 1 << 30;
    int nmin, nmax;

public:
    std::vector<std::pair<int, int>> ranges;
    MosAlgorithm() : nmin(INF), nmax(-INF) {}

    void add_range(int l, int r) {
        assert(l <= r);
        nmin = std::min(nmin, l);
        nmax = std::max(nmax, r);
        ranges.emplace_back(l, r);
    }
    template <typename F1, typename F2, typename F3, typename F4, typename F5>
    void run(F1 AddRight, F2 AddLeft, F3 RemoveRight, F4 RemoveLeft, F5 Query) {
        const int Q = ranges.size();
        if (!Q) return;
        const int nbbucket = std::max(1, std::min<int>(nmax - nmin, sqrt(Q)));
        const int szbucket = (nmax - nmin + nbbucket - 1) / nbbucket;
        std::vector<int> qs(Q);
        std::iota(qs.begin(), qs.end(), 0);
        std::sort(qs.begin(), qs.end(), [&](int q1, int q2) {
            int b1 = (ranges[q1].first - nmin) / szbucket, b2 = (ranges[q2].first - nmin) / szbucket;
            if (b1 != b2)
                return b1 < b2;
            else {
                return (b1 & 1) ? (ranges[q1].second > ranges[q2].second) : (ranges[q1].second < ranges[q2].second);
            }
        });

        int l = ranges[qs[0]].first, r = l;
        for (auto q : qs) {
            while (r < ranges[q].second) AddRight(r++);
            while (l > ranges[q].first) AddLeft(--l);
            while (r > ranges[q].second) RemoveRight(--r);
            while (l < ranges[q].first) RemoveLeft(l++);
            assert(l == ranges[q].first and r == ranges[q].second);
            Query(q);
        }
    }
    template <typename F1, typename F3, typename F5> void run(F1 Add, F3 Remove, F5 Query) {
        run(Add, Add, Remove, Remove, Query);
    }
};
