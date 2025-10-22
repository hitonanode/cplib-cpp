#pragma once
#include <algorithm>
#include <cassert>
#include <numeric>
#include <vector>

// (i, 0) (0 <= i < bottom.size()) -> (dx_init + j, y) (0 <= j < len)
// Input: bottom[i] = Initial weight at (i, 0)
// Output: top[j] = weight at (dx_init + j, y) after transition
template <class MODINT>
std::vector<MODINT>
NorthEastLatticePathsParallel(const std::vector<MODINT> &bottom, long long dx_init, long long y,
                              int len, auto convolve) {
    const long long min_x = std::max(dx_init, 0LL), max_x = dx_init + len - 1;
    if (max_x < 0 or y < 0) return std::vector<MODINT>(len);

    const long long min_shift = std::max<long long>(0, min_x - ((long long)bottom.size() - 1)),
                    max_shift = max_x;

    std::vector<MODINT> trans(max_shift - min_shift + 1);
    for (int i = 0; i < (int)trans.size(); ++i)
        trans[i] = MODINT::binom(min_shift + i + y, y); // can be made faster if needed
    std::vector<MODINT> top = convolve(trans, bottom);

    top.erase(top.begin(), top.begin() + std::min<long long>(min_x, (long long)bottom.size() - 1));
    top.resize(max_x - min_x + 1);
    if (dx_init < 0) {
        std::vector<MODINT> tmp(-dx_init);
        top.insert(top.begin(), tmp.begin(), tmp.end());
    }
    top.shrink_to_fit();
    assert((int)top.size() == len);

    return top;
}

// (i, 0) (0 <= i < bottom.size()) -> (x, dy_init + j) (0 <= j < len)
// Input: bottom[i] = Initial weight at (i, 0)
// Output: right[j] = weight at (x, dy_init + j) after transition
template <class MODINT>
std::vector<MODINT> NorthEastLatticePathsVertical(const std::vector<MODINT> &bottom, int x,
                                                  int dy_init, int len, auto convolve) {
    const int ylo = std::max(dy_init, 0), yhi = dy_init + len;
    if (yhi <= 0 or x < 0) return std::vector<MODINT>(len);

    // (i, 0) -> (x, y) : binom(x - i, y)
    // f[i] -> g[x + y - ylo] : (x + y - i)! / (x - i)! y!
    std::vector<MODINT> tmp = bottom;
    if ((int)tmp.size() > x + 1) tmp.resize(x + 1);

    for (int i = 0; i < (int)tmp.size(); ++i) tmp[i] *= MODINT::facinv(x - i);

    std::vector<MODINT> trans(x + yhi);
    for (int i = 0; i < (int)trans.size(); ++i) trans[i] = MODINT::fac(i + ylo);
    tmp = convolve(trans, tmp);

    std::vector<MODINT> right(yhi - ylo);
    for (int y = ylo; y < yhi; ++y) right.at(y - ylo) = tmp.at(x + y - ylo) * MODINT::facinv(y);

    if (dy_init < 0) {
        std::vector<MODINT> tmp(-dy_init);
        right.insert(right.begin(), tmp.begin(), tmp.end());
    }
    right.shrink_to_fit();
    assert((int)right.size() == len);

    return right;
}

// Solve DP below in O((h + w)log(h + w)) (if `convolve()` is O(n log n))
// 1. dp[0, 0:h] += left[:]
// 2. dp[0:w, 0] += bottom[:]
// 3. dp[i, j] := dp[i-1, j] + dp[i, j-1]
// 4. return (right = dp[w-1, 0:h], top = dp[0:w, h-1]
template <class MODINT>
auto NorthEastLatticePathsInRectangle(const std::vector<MODINT> &left,
                                      const std::vector<MODINT> &bottom, auto convolve) {
    struct Result {
        std::vector<MODINT> right, top;
    };

    const int h = left.size(), w = bottom.size();
    if (h == 0 or w == 0) return Result{left, bottom};

    auto right = NorthEastLatticePathsParallel(left, 0, w - 1, h, convolve);
    auto top = NorthEastLatticePathsParallel(bottom, 0, h - 1, w, convolve);

    const auto right2 = NorthEastLatticePathsVertical(bottom, w - 1, 0, h, convolve);
    for (int i = 0; i < (int)right2.size(); ++i) right[i] += right2[i];

    const auto top2 = NorthEastLatticePathsVertical(left, h - 1, 0, w, convolve);
    for (int i = 0; i < (int)top2.size(); ++i) top[i] += top2[i];

    return Result{right, top};
}

// a) Lattice paths from (*, 0) / (0, *). Count paths ending at (w - 1, *) or absorbed at (i, ub[i])s.
// b) In other words, count sequences satisfying 0 <= a_i < ub[i]
// c) In other words, solve DP below:
//   1. dp[0:w, 0] += bottom[:], dp[0, 0:ub[0]] += left[:]
//   2. dp[i, j + 1] += dp[i, j]
//   3. dp[i + 1, j] += dp[i, j] (j < ub[i])
//   4. return dp[w-1, 0:ub[w-1]] as right, dp[i, ub[i] - 1] as top
// Complexity: O((h + w) (log(h + w))^2) (if `convolve()` is O(n log n))
// Requirement: ub is non-decreasing
template <class MODINT>
auto NorthEastLatticePathsBounded(const std::vector<int> &ub, const std::vector<MODINT> &left,
                                  const std::vector<MODINT> &bottom, auto convolve) {
    struct Result {
        std::vector<MODINT> right, top;
    };

    assert(ub.size() == bottom.size());
    if (ub.empty()) return Result{left, {}};

    assert(ub.front() == (int)left.size());
    assert(ub.front() >= 0);
    for (int i = 1; i < (int)ub.size(); ++i) assert(ub[i] >= ub[i - 1]);

    if (ub.back() <= 0) return Result{{}, bottom};

    if (const int n = bottom.size(); n > 64 and ub.back() > 64) { // 64: parameter
        const int l = n / 2, r = n - l;
        const int b = ub[l];

        auto [right1, top1] = NorthEastLatticePathsBounded<MODINT>(
            {ub.begin(), ub.begin() + l}, left, {bottom.begin(), bottom.begin() + l}, convolve);
        right1.resize(b);
        auto [right, out2] = NorthEastLatticePathsInRectangle<MODINT>(
            right1, {bottom.begin() + l, bottom.end()}, convolve);

        std::vector<int> ub_next(r);
        for (int i = 0; i < r; ++i) ub_next[i] = ub[l + i] - b;
        const auto [right3, top3] =
            NorthEastLatticePathsBounded<MODINT>(ub_next, {}, out2, convolve);
        right.insert(right.end(), right3.begin(), right3.end());
        top1.insert(top1.end(), top3.begin(), top3.end());
        return Result{right, top1};
    } else {
        std::vector<MODINT> dp = left;
        std::vector<MODINT> top = bottom;
        dp.reserve(ub.back());
        for (int i = 0; i < n; ++i) {
            dp.resize(ub[i], 0);
            if (dp.empty()) continue;
            dp[0] += bottom[i];
            for (int j = 1; j < (int)dp.size(); ++j) dp[j] += dp[j - 1];
            top[i] = dp.back();
        }
        return Result{dp, top};
    }
}

// Lattice paths from (0, *). Count paths ending at (w - 1, *). In other words, solve DP below:
//   1. dp[0, lb[0]:ub[0]] += left[:]
//   2. dp[i, j + 1] += dp[i, j] (j + 1 < ub[i])
//   3. dp[i + 1, j] += dp[i, j] (lb[i + 1] <= j)
//   4. return dp[w-1, lb[w-1]:ub[w-1]]
// Complexity: O((h + w) (log(h + w))^2) (if `convolve()` is O(n log n))
// Requirement: lb/ub is non-decreasing
template <class MODINT>
std::vector<MODINT>
NorthEastLatticePathsBothBounded(const std::vector<int> &lb, const std::vector<int> &ub,
                                 const std::vector<MODINT> &left, auto convolve) {
    assert(lb.size() == ub.size());

    const int n = ub.size();
    if (n == 0) return left;

    assert((int)left.size() == ub[0] - lb[0]);
    for (int i = 1; i < n; ++i) {
        assert(lb[i - 1] <= lb[i]);
        assert(ub[i - 1] <= ub[i]);
    }

    for (int i = 0; i < n; ++i) {
        if (lb[i] >= ub[i]) return std::vector<MODINT>(ub.back() - lb.back());
    }

    int x = 0;
    std::vector<MODINT> dp_left = left;
    std::vector<int> tmp_ub;
    while (true) {
        dp_left.resize(ub[x] - lb[x], MODINT{0});

        const int x1 = std::upper_bound(ub.begin() + x + 1, ub.begin() + n, ub[x]) - ub.begin();
        const int x2 = std::lower_bound(lb.begin() + x1, lb.begin() + n, ub[x]) - lb.begin();
        const int x3 = std::upper_bound(lb.begin() + x2, lb.begin() + n, ub[x]) - lb.begin();

        tmp_ub.assign(dp_left.size(), x2 - x);
        for (int i = x2 - 1; i >= x; --i) {
            if (const int d = lb[i] - lb[x] - 1; d >= 0 and d < (int)tmp_ub.size()) {
                tmp_ub[d] = i - x;
            }
        }
        for (int j = (int)tmp_ub.size() - 1; j; --j)
            tmp_ub[j - 1] = std::min(tmp_ub[j - 1], tmp_ub[j]);

        auto [next_dp, southeast] = NorthEastLatticePathsBounded(
            tmp_ub, std::vector<MODINT>(tmp_ub.front()), dp_left, convolve);
        next_dp.erase(next_dp.begin(), next_dp.begin() + (x1 - x));
        assert((int)next_dp.size() == x2 - x1);

        if (x1 < x3) {
            next_dp.resize(x3 - x1, MODINT{0});
            tmp_ub.resize(x3 - x1);
            for (int i = x1; i < x3; ++i) tmp_ub[i - x1] = ub[i] - ub[x];
            next_dp = NorthEastLatticePathsBounded(
                          tmp_ub, std::vector<MODINT>(tmp_ub.front()), next_dp, convolve)
                          .right;
        } else {
            next_dp.clear();
        }

        if (x3 >= n) {
            std::vector<MODINT> ret = southeast;
            ret.insert(ret.end(), next_dp.begin(), next_dp.end());
            ret.erase(ret.begin(), ret.begin() + (lb[n - 1] - lb[x]));
            assert((int)ret.size() == ub[n - 1] - lb[n - 1]);
            return ret;
        } else {
            next_dp.erase(next_dp.begin(), next_dp.begin() + (lb[x3] - ub[x]));
            x = x3;
            dp_left = std::move(next_dp);
        }
    }
}

// Count nonnegative non-decreasing integer sequence `a` satisfying a[i] < ub[i]
// Complexity: O(n log^2(n)) (if `convolve()` is O(n log n))
template <class MODINT> MODINT CountBoundedMonotoneSequence(std::vector<int> ub, auto convolve) {
    const int n = ub.size();
    assert(n > 0);
    for (int i = n - 1; i; --i) ub[i - 1] = std::min(ub[i - 1], ub[i]);
    if (ub.front() <= 0) return MODINT{0};

    std::vector<MODINT> bottom(ub.size()), left(ub.front());
    bottom.front() = 1;
    std::vector<MODINT> ret = NorthEastLatticePathsBounded(ub, left, bottom, convolve).right;
    return std::accumulate(ret.begin(), ret.end(), MODINT{});
}

// Count nonnegative non-decreasing integer sequence `a` satisfying lb[i] <= a[i] < ub[i]
// Complexity: O(n log^2(n)) (if `convolve()` is O(n log n))
// https://noshi91.hatenablog.com/entry/2023/07/21/235339
// Verify: https://judge.yosupo.jp/problem/number_of_increasing_sequences_between_two_sequences
template <class MODINT>
MODINT CountBoundedMonotoneSequence(std::vector<int> lb, std::vector<int> ub, auto convolve) {
    assert(lb.size() == ub.size());

    const int n = ub.size();
    if (n == 0) return MODINT{1};

    for (int i = 1; i < n; ++i) lb[i] = std::max(lb[i - 1], lb[i]);
    for (int i = n - 1; i; --i) ub[i - 1] = std::min(ub[i - 1], ub[i]);

    for (int i = 0; i < n; ++i) {
        if (lb[i] >= ub[i]) return MODINT{0};
    }

    const int k = lb.back();
    lb.insert(lb.begin(), lb.front()); // len(lb) == n + 1
    lb.pop_back();

    std::vector<MODINT> init(ub.front() - lb.front());
    init.at(0) = 1;

    auto res = NorthEastLatticePathsBothBounded(lb, ub, init, convolve);
    res.erase(res.begin(), res.begin() + (k - lb.back()));
    return std::accumulate(res.begin(), res.end(), MODINT{});
}
