---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: other_algorithms/test/north_east_lattice_paths.aoj3335.test.cpp
    title: other_algorithms/test/north_east_lattice_paths.aoj3335.test.cpp
  - icon: ':heavy_check_mark:'
    path: other_algorithms/test/north_east_lattice_paths.bruteforce.test.cpp
    title: other_algorithms/test/north_east_lattice_paths.bruteforce.test.cpp
  - icon: ':heavy_check_mark:'
    path: other_algorithms/test/north_east_lattice_paths.test.cpp
    title: other_algorithms/test/north_east_lattice_paths.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://judge.yosupo.jp/problem/number_of_increasing_sequences_between_two_sequences
    - https://noshi91.hatenablog.com/entry/2023/07/21/235339
  bundledCode: "#line 2 \"other_algorithms/north_east_lattice_paths.hpp\"\n#include\
    \ <algorithm>\n#include <cassert>\n#include <numeric>\n#include <vector>\n\n//\
    \ (i, 0) (0 <= i < bottom.size()) -> (dx_init + j, y) (0 <= j < len)\n// Input:\
    \ bottom[i] = Initial weight at (i, 0)\n// Output: top[j] = weight at (dx_init\
    \ + j, y) after transition\ntemplate <class MODINT>\nstd::vector<MODINT>\nNorthEastLatticePathsParallel(const\
    \ std::vector<MODINT> &bottom, long long dx_init, long long y,\n             \
    \                 int len, auto convolve) {\n    const long long min_x = std::max(dx_init,\
    \ 0LL), max_x = dx_init + len - 1;\n    if (max_x < 0 or y < 0) return std::vector<MODINT>(len);\n\
    \n    const long long min_shift = std::max<long long>(0, min_x - ((long long)bottom.size()\
    \ - 1)),\n                    max_shift = max_x;\n\n    std::vector<MODINT> trans(max_shift\
    \ - min_shift + 1);\n    for (int i = 0; i < (int)trans.size(); ++i)\n       \
    \ trans[i] = MODINT::binom(min_shift + i + y, y); // can be made faster if needed\n\
    \    std::vector<MODINT> top = convolve(trans, bottom);\n\n    top.erase(top.begin(),\
    \ top.begin() + std::min<long long>(min_x, (long long)bottom.size() - 1));\n \
    \   top.resize(max_x - min_x + 1);\n    if (dx_init < 0) {\n        std::vector<MODINT>\
    \ tmp(-dx_init);\n        top.insert(top.begin(), tmp.begin(), tmp.end());\n \
    \   }\n    top.shrink_to_fit();\n    assert((int)top.size() == len);\n\n    return\
    \ top;\n}\n\n// (i, 0) (0 <= i < bottom.size()) -> (x, dy_init + j) (0 <= j <\
    \ len)\n// Input: bottom[i] = Initial weight at (i, 0)\n// Output: right[j] =\
    \ weight at (x, dy_init + j) after transition\ntemplate <class MODINT>\nstd::vector<MODINT>\
    \ NorthEastLatticePathsVertical(const std::vector<MODINT> &bottom, int x,\n  \
    \                                                int dy_init, int len, auto convolve)\
    \ {\n    const int ylo = std::max(dy_init, 0), yhi = dy_init + len;\n    if (yhi\
    \ <= 0 or x < 0) return std::vector<MODINT>(len);\n\n    // (i, 0) -> (x, y) :\
    \ binom(x - i, y)\n    // f[i] -> g[x + y - ylo] : (x + y - i)! / (x - i)! y!\n\
    \    std::vector<MODINT> tmp = bottom;\n    if ((int)tmp.size() > x + 1) tmp.resize(x\
    \ + 1);\n\n    for (int i = 0; i < (int)tmp.size(); ++i) tmp[i] *= MODINT::facinv(x\
    \ - i);\n\n    std::vector<MODINT> trans(x + yhi);\n    for (int i = 0; i < (int)trans.size();\
    \ ++i) trans[i] = MODINT::fac(i + ylo);\n    tmp = convolve(trans, tmp);\n\n \
    \   std::vector<MODINT> right(yhi - ylo);\n    for (int y = ylo; y < yhi; ++y)\
    \ right.at(y - ylo) = tmp.at(x + y - ylo) * MODINT::facinv(y);\n\n    if (dy_init\
    \ < 0) {\n        std::vector<MODINT> tmp(-dy_init);\n        right.insert(right.begin(),\
    \ tmp.begin(), tmp.end());\n    }\n    right.shrink_to_fit();\n    assert((int)right.size()\
    \ == len);\n\n    return right;\n}\n\n// Solve DP below in O((h + w)log(h + w))\
    \ (if `convolve()` is O(n log n))\n// 1. dp[0, 0:h] += left[:]\n// 2. dp[0:w,\
    \ 0] += bottom[:]\n// 3. dp[i, j] := dp[i-1, j] + dp[i, j-1]\n// 4. return (right\
    \ = dp[w-1, 0:h], top = dp[0:w, h-1]\ntemplate <class MODINT>\nauto NorthEastLatticePathsInRectangle(const\
    \ std::vector<MODINT> &left,\n                                      const std::vector<MODINT>\
    \ &bottom, auto convolve) {\n    struct Result {\n        std::vector<MODINT>\
    \ right, top;\n    };\n\n    const int h = left.size(), w = bottom.size();\n \
    \   if (h == 0 or w == 0) return Result{left, bottom};\n\n    auto right = NorthEastLatticePathsParallel(left,\
    \ 0, w - 1, h, convolve);\n    auto top = NorthEastLatticePathsParallel(bottom,\
    \ 0, h - 1, w, convolve);\n\n    const auto right2 = NorthEastLatticePathsVertical(bottom,\
    \ w - 1, 0, h, convolve);\n    for (int i = 0; i < (int)right2.size(); ++i) right[i]\
    \ += right2[i];\n\n    const auto top2 = NorthEastLatticePathsVertical(left, h\
    \ - 1, 0, w, convolve);\n    for (int i = 0; i < (int)top2.size(); ++i) top[i]\
    \ += top2[i];\n\n    return Result{right, top};\n}\n\n// a) Lattice paths from\
    \ (*, 0) / (0, *). Count paths ending at (w - 1, *) or absorbed at (i, ub[i])s.\n\
    // b) In other words, count sequences satisfying 0 <= a_i < ub[i]\n// c) In other\
    \ words, solve DP below:\n//   1. dp[0:w, 0] += bottom[:], dp[0, 0:ub[0]] += left[:]\n\
    //   2. dp[i, j + 1] += dp[i, j]\n//   3. dp[i + 1, j] += dp[i, j] (j < ub[i])\n\
    //   4. return dp[w-1, 0:ub[w-1]] as right, dp[i, ub[i] - 1] as top\n// Complexity:\
    \ O((h + w) (log(h + w))^2) (if `convolve()` is O(n log n))\n// Requirement: ub\
    \ is non-decreasing\ntemplate <class MODINT>\nauto NorthEastLatticePathsBounded(const\
    \ std::vector<int> &ub, const std::vector<MODINT> &left,\n                   \
    \               const std::vector<MODINT> &bottom, auto convolve) {\n    struct\
    \ Result {\n        std::vector<MODINT> right, top;\n    };\n\n    assert(ub.size()\
    \ == bottom.size());\n    if (ub.empty()) return Result{left, {}};\n\n    assert(ub.front()\
    \ == (int)left.size());\n    assert(ub.front() >= 0);\n    for (int i = 1; i <\
    \ (int)ub.size(); ++i) assert(ub[i] >= ub[i - 1]);\n\n    if (ub.back() <= 0)\
    \ return Result{{}, bottom};\n\n    if (const int n = bottom.size(); n > 64 and\
    \ ub.back() > 64) { // 64: parameter\n        const int l = n / 2, r = n - l;\n\
    \        const int b = ub[l];\n\n        auto [right1, top1] = NorthEastLatticePathsBounded<MODINT>(\n\
    \            {ub.begin(), ub.begin() + l}, left, {bottom.begin(), bottom.begin()\
    \ + l}, convolve);\n        right1.resize(b);\n        auto [right, out2] = NorthEastLatticePathsInRectangle<MODINT>(\n\
    \            right1, {bottom.begin() + l, bottom.end()}, convolve);\n\n      \
    \  std::vector<int> ub_next(r);\n        for (int i = 0; i < r; ++i) ub_next[i]\
    \ = ub[l + i] - b;\n        const auto [right3, top3] =\n            NorthEastLatticePathsBounded<MODINT>(ub_next,\
    \ {}, out2, convolve);\n        right.insert(right.end(), right3.begin(), right3.end());\n\
    \        top1.insert(top1.end(), top3.begin(), top3.end());\n        return Result{right,\
    \ top1};\n    } else {\n        std::vector<MODINT> dp = left;\n        std::vector<MODINT>\
    \ top = bottom;\n        dp.reserve(ub.back());\n        for (int i = 0; i < n;\
    \ ++i) {\n            dp.resize(ub[i], 0);\n            if (dp.empty()) continue;\n\
    \            dp[0] += bottom[i];\n            for (int j = 1; j < (int)dp.size();\
    \ ++j) dp[j] += dp[j - 1];\n            top[i] = dp.back();\n        }\n     \
    \   return Result{dp, top};\n    }\n}\n\n// Lattice paths from (0, *). Count paths\
    \ ending at (w - 1, *). In other words, solve DP below:\n//   1. dp[0, lb[0]:ub[0]]\
    \ += left[:]\n//   2. dp[i, j + 1] += dp[i, j] (j + 1 < ub[i])\n//   3. dp[i +\
    \ 1, j] += dp[i, j] (lb[i + 1] <= j)\n//   4. return dp[w-1, lb[w-1]:ub[w-1]]\n\
    // Complexity: O((h + w) (log(h + w))^2) (if `convolve()` is O(n log n))\n// Requirement:\
    \ lb/ub is non-decreasing\ntemplate <class MODINT>\nstd::vector<MODINT>\nNorthEastLatticePathsBothBounded(const\
    \ std::vector<int> &lb, const std::vector<int> &ub,\n                        \
    \         const std::vector<MODINT> &left, auto convolve) {\n    assert(lb.size()\
    \ == ub.size());\n\n    const int n = ub.size();\n    if (n == 0) return left;\n\
    \n    assert((int)left.size() == ub[0] - lb[0]);\n    for (int i = 1; i < n; ++i)\
    \ {\n        assert(lb[i - 1] <= lb[i]);\n        assert(ub[i - 1] <= ub[i]);\n\
    \        if (ub[i - 1] <= lb[i]) return std::vector<MODINT>(ub.back() - lb.back());\n\
    \    }\n\n    for (int i = 0; i < n; ++i) {\n        if (lb[i] >= ub[i]) return\
    \ std::vector<MODINT>(ub.back() - lb.back());\n    }\n\n    int x = 0;\n    std::vector<MODINT>\
    \ dp_left = left;\n    std::vector<int> tmp_ub;\n    while (true) {\n        dp_left.resize(ub[x]\
    \ - lb[x], MODINT{0});\n\n        const int x1 = std::upper_bound(ub.begin() +\
    \ x + 1, ub.begin() + n, ub[x]) - ub.begin();\n        const int x2 = std::lower_bound(lb.begin()\
    \ + x1, lb.begin() + n, ub[x]) - lb.begin();\n        const int x3 = std::upper_bound(lb.begin()\
    \ + x2, lb.begin() + n, ub[x]) - lb.begin();\n\n        tmp_ub.assign(dp_left.size(),\
    \ x2 - x);\n        for (int i = x2 - 1; i >= x; --i) {\n            if (const\
    \ int d = lb[i] - lb[x] - 1; d >= 0 and d < (int)tmp_ub.size()) {\n          \
    \      tmp_ub[d] = i - x;\n            }\n        }\n        for (int j = (int)tmp_ub.size()\
    \ - 1; j; --j)\n            tmp_ub[j - 1] = std::min(tmp_ub[j - 1], tmp_ub[j]);\n\
    \n        auto [next_dp, southeast] = NorthEastLatticePathsBounded(\n        \
    \    tmp_ub, std::vector<MODINT>(tmp_ub.front()), dp_left, convolve);\n      \
    \  next_dp.erase(next_dp.begin(), next_dp.begin() + (x1 - x));\n        assert((int)next_dp.size()\
    \ == x2 - x1);\n\n        if (x1 < x3) {\n            next_dp.resize(x3 - x1,\
    \ MODINT{0});\n            tmp_ub.resize(x3 - x1);\n            for (int i = x1;\
    \ i < x3; ++i) tmp_ub[i - x1] = ub[i] - ub[x];\n            next_dp = NorthEastLatticePathsBounded(\n\
    \                          tmp_ub, std::vector<MODINT>(tmp_ub.front()), next_dp,\
    \ convolve)\n                          .right;\n        } else {\n           \
    \ next_dp.clear();\n        }\n\n        if (x3 >= n) {\n            std::vector<MODINT>\
    \ ret = southeast;\n            ret.insert(ret.end(), next_dp.begin(), next_dp.end());\n\
    \            ret.erase(ret.begin(), ret.begin() + (lb[n - 1] - lb[x]));\n    \
    \        assert((int)ret.size() == ub[n - 1] - lb[n - 1]);\n            return\
    \ ret;\n        } else {\n            next_dp.erase(next_dp.begin(), next_dp.begin()\
    \ + (lb[x3] - ub[x]));\n            x = x3;\n            dp_left = std::move(next_dp);\n\
    \        }\n    }\n}\n\n// Count nonnegative non-decreasing integer sequence `a`\
    \ satisfying a[i] < ub[i]\n// Complexity: O(n log^2(n)) (if `convolve()` is O(n\
    \ log n))\ntemplate <class MODINT> MODINT CountBoundedMonotoneSequence(std::vector<int>\
    \ ub, auto convolve) {\n    const int n = ub.size();\n    assert(n > 0);\n   \
    \ for (int i = n - 1; i; --i) ub[i - 1] = std::min(ub[i - 1], ub[i]);\n    if\
    \ (ub.front() <= 0) return MODINT{0};\n\n    std::vector<MODINT> bottom(ub.size()),\
    \ left(ub.front());\n    bottom.front() = 1;\n    std::vector<MODINT> ret = NorthEastLatticePathsBounded(ub,\
    \ left, bottom, convolve).right;\n    return std::accumulate(ret.begin(), ret.end(),\
    \ MODINT{});\n}\n\n// Count nonnegative non-decreasing integer sequence `a` satisfying\
    \ lb[i] <= a[i] < ub[i]\n// Complexity: O(n log^2(n)) (if `convolve()` is O(n\
    \ log n))\n// https://noshi91.hatenablog.com/entry/2023/07/21/235339\n// Verify:\
    \ https://judge.yosupo.jp/problem/number_of_increasing_sequences_between_two_sequences\n\
    template <class MODINT>\nMODINT CountBoundedMonotoneSequence(std::vector<int>\
    \ lb, std::vector<int> ub, auto convolve) {\n    assert(lb.size() == ub.size());\n\
    \n    const int n = ub.size();\n    if (n == 0) return MODINT{1};\n\n    for (int\
    \ i = 1; i < n; ++i) lb[i] = std::max(lb[i - 1], lb[i]);\n    for (int i = n -\
    \ 1; i; --i) ub[i - 1] = std::min(ub[i - 1], ub[i]);\n\n    for (int i = 0; i\
    \ < n; ++i) {\n        if (lb[i] >= ub[i]) return MODINT{0};\n    }\n\n    const\
    \ int k = lb.back();\n    lb.insert(lb.begin(), lb.front()); // len(lb) == n +\
    \ 1\n    lb.pop_back();\n\n    std::vector<MODINT> init(ub.front() - lb.front());\n\
    \    init.at(0) = 1;\n\n    auto res = NorthEastLatticePathsBothBounded(lb, ub,\
    \ init, convolve);\n    res.erase(res.begin(), res.begin() + (k - lb.back()));\n\
    \    return std::accumulate(res.begin(), res.end(), MODINT{});\n}\n"
  code: "#pragma once\n#include <algorithm>\n#include <cassert>\n#include <numeric>\n\
    #include <vector>\n\n// (i, 0) (0 <= i < bottom.size()) -> (dx_init + j, y) (0\
    \ <= j < len)\n// Input: bottom[i] = Initial weight at (i, 0)\n// Output: top[j]\
    \ = weight at (dx_init + j, y) after transition\ntemplate <class MODINT>\nstd::vector<MODINT>\n\
    NorthEastLatticePathsParallel(const std::vector<MODINT> &bottom, long long dx_init,\
    \ long long y,\n                              int len, auto convolve) {\n    const\
    \ long long min_x = std::max(dx_init, 0LL), max_x = dx_init + len - 1;\n    if\
    \ (max_x < 0 or y < 0) return std::vector<MODINT>(len);\n\n    const long long\
    \ min_shift = std::max<long long>(0, min_x - ((long long)bottom.size() - 1)),\n\
    \                    max_shift = max_x;\n\n    std::vector<MODINT> trans(max_shift\
    \ - min_shift + 1);\n    for (int i = 0; i < (int)trans.size(); ++i)\n       \
    \ trans[i] = MODINT::binom(min_shift + i + y, y); // can be made faster if needed\n\
    \    std::vector<MODINT> top = convolve(trans, bottom);\n\n    top.erase(top.begin(),\
    \ top.begin() + std::min<long long>(min_x, (long long)bottom.size() - 1));\n \
    \   top.resize(max_x - min_x + 1);\n    if (dx_init < 0) {\n        std::vector<MODINT>\
    \ tmp(-dx_init);\n        top.insert(top.begin(), tmp.begin(), tmp.end());\n \
    \   }\n    top.shrink_to_fit();\n    assert((int)top.size() == len);\n\n    return\
    \ top;\n}\n\n// (i, 0) (0 <= i < bottom.size()) -> (x, dy_init + j) (0 <= j <\
    \ len)\n// Input: bottom[i] = Initial weight at (i, 0)\n// Output: right[j] =\
    \ weight at (x, dy_init + j) after transition\ntemplate <class MODINT>\nstd::vector<MODINT>\
    \ NorthEastLatticePathsVertical(const std::vector<MODINT> &bottom, int x,\n  \
    \                                                int dy_init, int len, auto convolve)\
    \ {\n    const int ylo = std::max(dy_init, 0), yhi = dy_init + len;\n    if (yhi\
    \ <= 0 or x < 0) return std::vector<MODINT>(len);\n\n    // (i, 0) -> (x, y) :\
    \ binom(x - i, y)\n    // f[i] -> g[x + y - ylo] : (x + y - i)! / (x - i)! y!\n\
    \    std::vector<MODINT> tmp = bottom;\n    if ((int)tmp.size() > x + 1) tmp.resize(x\
    \ + 1);\n\n    for (int i = 0; i < (int)tmp.size(); ++i) tmp[i] *= MODINT::facinv(x\
    \ - i);\n\n    std::vector<MODINT> trans(x + yhi);\n    for (int i = 0; i < (int)trans.size();\
    \ ++i) trans[i] = MODINT::fac(i + ylo);\n    tmp = convolve(trans, tmp);\n\n \
    \   std::vector<MODINT> right(yhi - ylo);\n    for (int y = ylo; y < yhi; ++y)\
    \ right.at(y - ylo) = tmp.at(x + y - ylo) * MODINT::facinv(y);\n\n    if (dy_init\
    \ < 0) {\n        std::vector<MODINT> tmp(-dy_init);\n        right.insert(right.begin(),\
    \ tmp.begin(), tmp.end());\n    }\n    right.shrink_to_fit();\n    assert((int)right.size()\
    \ == len);\n\n    return right;\n}\n\n// Solve DP below in O((h + w)log(h + w))\
    \ (if `convolve()` is O(n log n))\n// 1. dp[0, 0:h] += left[:]\n// 2. dp[0:w,\
    \ 0] += bottom[:]\n// 3. dp[i, j] := dp[i-1, j] + dp[i, j-1]\n// 4. return (right\
    \ = dp[w-1, 0:h], top = dp[0:w, h-1]\ntemplate <class MODINT>\nauto NorthEastLatticePathsInRectangle(const\
    \ std::vector<MODINT> &left,\n                                      const std::vector<MODINT>\
    \ &bottom, auto convolve) {\n    struct Result {\n        std::vector<MODINT>\
    \ right, top;\n    };\n\n    const int h = left.size(), w = bottom.size();\n \
    \   if (h == 0 or w == 0) return Result{left, bottom};\n\n    auto right = NorthEastLatticePathsParallel(left,\
    \ 0, w - 1, h, convolve);\n    auto top = NorthEastLatticePathsParallel(bottom,\
    \ 0, h - 1, w, convolve);\n\n    const auto right2 = NorthEastLatticePathsVertical(bottom,\
    \ w - 1, 0, h, convolve);\n    for (int i = 0; i < (int)right2.size(); ++i) right[i]\
    \ += right2[i];\n\n    const auto top2 = NorthEastLatticePathsVertical(left, h\
    \ - 1, 0, w, convolve);\n    for (int i = 0; i < (int)top2.size(); ++i) top[i]\
    \ += top2[i];\n\n    return Result{right, top};\n}\n\n// a) Lattice paths from\
    \ (*, 0) / (0, *). Count paths ending at (w - 1, *) or absorbed at (i, ub[i])s.\n\
    // b) In other words, count sequences satisfying 0 <= a_i < ub[i]\n// c) In other\
    \ words, solve DP below:\n//   1. dp[0:w, 0] += bottom[:], dp[0, 0:ub[0]] += left[:]\n\
    //   2. dp[i, j + 1] += dp[i, j]\n//   3. dp[i + 1, j] += dp[i, j] (j < ub[i])\n\
    //   4. return dp[w-1, 0:ub[w-1]] as right, dp[i, ub[i] - 1] as top\n// Complexity:\
    \ O((h + w) (log(h + w))^2) (if `convolve()` is O(n log n))\n// Requirement: ub\
    \ is non-decreasing\ntemplate <class MODINT>\nauto NorthEastLatticePathsBounded(const\
    \ std::vector<int> &ub, const std::vector<MODINT> &left,\n                   \
    \               const std::vector<MODINT> &bottom, auto convolve) {\n    struct\
    \ Result {\n        std::vector<MODINT> right, top;\n    };\n\n    assert(ub.size()\
    \ == bottom.size());\n    if (ub.empty()) return Result{left, {}};\n\n    assert(ub.front()\
    \ == (int)left.size());\n    assert(ub.front() >= 0);\n    for (int i = 1; i <\
    \ (int)ub.size(); ++i) assert(ub[i] >= ub[i - 1]);\n\n    if (ub.back() <= 0)\
    \ return Result{{}, bottom};\n\n    if (const int n = bottom.size(); n > 64 and\
    \ ub.back() > 64) { // 64: parameter\n        const int l = n / 2, r = n - l;\n\
    \        const int b = ub[l];\n\n        auto [right1, top1] = NorthEastLatticePathsBounded<MODINT>(\n\
    \            {ub.begin(), ub.begin() + l}, left, {bottom.begin(), bottom.begin()\
    \ + l}, convolve);\n        right1.resize(b);\n        auto [right, out2] = NorthEastLatticePathsInRectangle<MODINT>(\n\
    \            right1, {bottom.begin() + l, bottom.end()}, convolve);\n\n      \
    \  std::vector<int> ub_next(r);\n        for (int i = 0; i < r; ++i) ub_next[i]\
    \ = ub[l + i] - b;\n        const auto [right3, top3] =\n            NorthEastLatticePathsBounded<MODINT>(ub_next,\
    \ {}, out2, convolve);\n        right.insert(right.end(), right3.begin(), right3.end());\n\
    \        top1.insert(top1.end(), top3.begin(), top3.end());\n        return Result{right,\
    \ top1};\n    } else {\n        std::vector<MODINT> dp = left;\n        std::vector<MODINT>\
    \ top = bottom;\n        dp.reserve(ub.back());\n        for (int i = 0; i < n;\
    \ ++i) {\n            dp.resize(ub[i], 0);\n            if (dp.empty()) continue;\n\
    \            dp[0] += bottom[i];\n            for (int j = 1; j < (int)dp.size();\
    \ ++j) dp[j] += dp[j - 1];\n            top[i] = dp.back();\n        }\n     \
    \   return Result{dp, top};\n    }\n}\n\n// Lattice paths from (0, *). Count paths\
    \ ending at (w - 1, *). In other words, solve DP below:\n//   1. dp[0, lb[0]:ub[0]]\
    \ += left[:]\n//   2. dp[i, j + 1] += dp[i, j] (j + 1 < ub[i])\n//   3. dp[i +\
    \ 1, j] += dp[i, j] (lb[i + 1] <= j)\n//   4. return dp[w-1, lb[w-1]:ub[w-1]]\n\
    // Complexity: O((h + w) (log(h + w))^2) (if `convolve()` is O(n log n))\n// Requirement:\
    \ lb/ub is non-decreasing\ntemplate <class MODINT>\nstd::vector<MODINT>\nNorthEastLatticePathsBothBounded(const\
    \ std::vector<int> &lb, const std::vector<int> &ub,\n                        \
    \         const std::vector<MODINT> &left, auto convolve) {\n    assert(lb.size()\
    \ == ub.size());\n\n    const int n = ub.size();\n    if (n == 0) return left;\n\
    \n    assert((int)left.size() == ub[0] - lb[0]);\n    for (int i = 1; i < n; ++i)\
    \ {\n        assert(lb[i - 1] <= lb[i]);\n        assert(ub[i - 1] <= ub[i]);\n\
    \        if (ub[i - 1] <= lb[i]) return std::vector<MODINT>(ub.back() - lb.back());\n\
    \    }\n\n    for (int i = 0; i < n; ++i) {\n        if (lb[i] >= ub[i]) return\
    \ std::vector<MODINT>(ub.back() - lb.back());\n    }\n\n    int x = 0;\n    std::vector<MODINT>\
    \ dp_left = left;\n    std::vector<int> tmp_ub;\n    while (true) {\n        dp_left.resize(ub[x]\
    \ - lb[x], MODINT{0});\n\n        const int x1 = std::upper_bound(ub.begin() +\
    \ x + 1, ub.begin() + n, ub[x]) - ub.begin();\n        const int x2 = std::lower_bound(lb.begin()\
    \ + x1, lb.begin() + n, ub[x]) - lb.begin();\n        const int x3 = std::upper_bound(lb.begin()\
    \ + x2, lb.begin() + n, ub[x]) - lb.begin();\n\n        tmp_ub.assign(dp_left.size(),\
    \ x2 - x);\n        for (int i = x2 - 1; i >= x; --i) {\n            if (const\
    \ int d = lb[i] - lb[x] - 1; d >= 0 and d < (int)tmp_ub.size()) {\n          \
    \      tmp_ub[d] = i - x;\n            }\n        }\n        for (int j = (int)tmp_ub.size()\
    \ - 1; j; --j)\n            tmp_ub[j - 1] = std::min(tmp_ub[j - 1], tmp_ub[j]);\n\
    \n        auto [next_dp, southeast] = NorthEastLatticePathsBounded(\n        \
    \    tmp_ub, std::vector<MODINT>(tmp_ub.front()), dp_left, convolve);\n      \
    \  next_dp.erase(next_dp.begin(), next_dp.begin() + (x1 - x));\n        assert((int)next_dp.size()\
    \ == x2 - x1);\n\n        if (x1 < x3) {\n            next_dp.resize(x3 - x1,\
    \ MODINT{0});\n            tmp_ub.resize(x3 - x1);\n            for (int i = x1;\
    \ i < x3; ++i) tmp_ub[i - x1] = ub[i] - ub[x];\n            next_dp = NorthEastLatticePathsBounded(\n\
    \                          tmp_ub, std::vector<MODINT>(tmp_ub.front()), next_dp,\
    \ convolve)\n                          .right;\n        } else {\n           \
    \ next_dp.clear();\n        }\n\n        if (x3 >= n) {\n            std::vector<MODINT>\
    \ ret = southeast;\n            ret.insert(ret.end(), next_dp.begin(), next_dp.end());\n\
    \            ret.erase(ret.begin(), ret.begin() + (lb[n - 1] - lb[x]));\n    \
    \        assert((int)ret.size() == ub[n - 1] - lb[n - 1]);\n            return\
    \ ret;\n        } else {\n            next_dp.erase(next_dp.begin(), next_dp.begin()\
    \ + (lb[x3] - ub[x]));\n            x = x3;\n            dp_left = std::move(next_dp);\n\
    \        }\n    }\n}\n\n// Count nonnegative non-decreasing integer sequence `a`\
    \ satisfying a[i] < ub[i]\n// Complexity: O(n log^2(n)) (if `convolve()` is O(n\
    \ log n))\ntemplate <class MODINT> MODINT CountBoundedMonotoneSequence(std::vector<int>\
    \ ub, auto convolve) {\n    const int n = ub.size();\n    assert(n > 0);\n   \
    \ for (int i = n - 1; i; --i) ub[i - 1] = std::min(ub[i - 1], ub[i]);\n    if\
    \ (ub.front() <= 0) return MODINT{0};\n\n    std::vector<MODINT> bottom(ub.size()),\
    \ left(ub.front());\n    bottom.front() = 1;\n    std::vector<MODINT> ret = NorthEastLatticePathsBounded(ub,\
    \ left, bottom, convolve).right;\n    return std::accumulate(ret.begin(), ret.end(),\
    \ MODINT{});\n}\n\n// Count nonnegative non-decreasing integer sequence `a` satisfying\
    \ lb[i] <= a[i] < ub[i]\n// Complexity: O(n log^2(n)) (if `convolve()` is O(n\
    \ log n))\n// https://noshi91.hatenablog.com/entry/2023/07/21/235339\n// Verify:\
    \ https://judge.yosupo.jp/problem/number_of_increasing_sequences_between_two_sequences\n\
    template <class MODINT>\nMODINT CountBoundedMonotoneSequence(std::vector<int>\
    \ lb, std::vector<int> ub, auto convolve) {\n    assert(lb.size() == ub.size());\n\
    \n    const int n = ub.size();\n    if (n == 0) return MODINT{1};\n\n    for (int\
    \ i = 1; i < n; ++i) lb[i] = std::max(lb[i - 1], lb[i]);\n    for (int i = n -\
    \ 1; i; --i) ub[i - 1] = std::min(ub[i - 1], ub[i]);\n\n    for (int i = 0; i\
    \ < n; ++i) {\n        if (lb[i] >= ub[i]) return MODINT{0};\n    }\n\n    const\
    \ int k = lb.back();\n    lb.insert(lb.begin(), lb.front()); // len(lb) == n +\
    \ 1\n    lb.pop_back();\n\n    std::vector<MODINT> init(ub.front() - lb.front());\n\
    \    init.at(0) = 1;\n\n    auto res = NorthEastLatticePathsBothBounded(lb, ub,\
    \ init, convolve);\n    res.erase(res.begin(), res.begin() + (k - lb.back()));\n\
    \    return std::accumulate(res.begin(), res.end(), MODINT{});\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: other_algorithms/north_east_lattice_paths.hpp
  requiredBy: []
  timestamp: '2026-01-18 14:24:38+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - other_algorithms/test/north_east_lattice_paths.test.cpp
  - other_algorithms/test/north_east_lattice_paths.bruteforce.test.cpp
  - other_algorithms/test/north_east_lattice_paths.aoj3335.test.cpp
documentation_of: other_algorithms/north_east_lattice_paths.hpp
layout: document
title: "Counting north-east lattice paths \uFF082 \u6B21\u5143\u30B0\u30EA\u30C3\u30C9\
  \u4E0A\u306E\u6700\u77ED\u8DEF\u306E\u6570\u3048\u4E0A\u3052\uFF09"
---

2 次元グリッド上の最短路（特に， $(1, 0)$ 方向と $(0, 1)$ 方向のみ）の数え上げに関連する各種関数の実装．

## 使用方法

### `NorthEastLatticePathsParallel` 関数

2 次元平面上の $x$ 軸に平行なある線分上に初期重みが存在するとき， $x$ 軸に **平行な** 別の線分上の最終重みを取得する．

```cpp
using mint = ModInt998244353;

// bottom[i] := (i, 0) に置く初期重み
vector<mint> bottom = {/* ... */};

long long dx_init = 0;  // 最終重みを取り出す線分の左端の x 座標
long long y = 5;        // 最終重みを取り出す線分の y 座標
int len = 10;           // 最終重みを取り出す線分の長さ

// top[i] := (dx_init + i, y) 上の最終重み
auto top = NorthEastLatticePathsParallel<mint>(bottom, dx_init, y, len, convolve);
```

### `NorthEastLatticePathsVertical` 関数

2 次元平面上の $x$ 軸に平行なある線分上に初期重みが存在するとき， $x$ 軸に **垂直な** 別の線分上の最終重みを取得する．

```cpp
using mint = ModInt998244353;
auto convolve = [&](const vector<mint> &l, const vector<mint> &r) { return nttconv(l, r); }

// bottom[i] := (i, 0) に置く初期重み
vector<mint> bottom = {/* ... */};

int x = 7;        // 最終重みを取り出す線分の x 座標
int dy_init = 0;  // 最終重みを取り出す線分の下端の y 座標
int len = 8;      // 最終重みを取り出す線分の長さ

// right[i] := (x, dy_init + i) 上の最終重み
auto right = NorthEastLatticePathsVertical<mint>(bottom, x, dy_init, len, convolve);
```

### `NorthEastLatticePathsInRectangle` 関数

2 次元平面上の矩形の左辺と下辺上に初期重みが存在するとき，右辺と上辺上の最終重みを取得する．

```cpp
using mint = ModInt998244353;
auto convolve = [&](const vector<mint> &l, const vector<mint> &r) { return nttconv(l, r); }

// 左辺と下辺に置く初期重み
vector<mint> left   = {/* height = H */};   // (0, j)
vector<mint> bottom = {/* width  = W */};   // (i, 0)

// DP: dp[i,j] = dp[i-1,j] + dp[i,j-1] を矩形全域に伝播
auto res = NorthEastLatticePathsInRectangle<mint>(left, bottom, convolve);

// res.right: 右辺 (W-1, 0..H-1)、res.top: 上辺 (0..W-1, H-1)
const vector<mint> &right = res.right;
const vector<mint> &top   = res.top;
```

### `NorthEastLatticePathsBounded` 関数

2 次元平面上の矩形から左上部分を（へこみができないように）削った領域の左辺と下辺上に初期重みが存在するとき，右辺と上端における最終重みを取得する．

```cpp
using mint = ModInt998244353;
auto convolve = [&](const vector<mint> &l, const vector<mint> &r) { return nttconv(l, r); }

// 吸収境界 y = ub[i] （非減少）
vector<int> ub = {/* size = W, nondecreasing */};

// 左辺 (0, j) / 下辺 (i, 0) の初期重み
vector<mint> left(ub.front());
vector<mint> bottom(ub.size());

auto res = NorthEastLatticePathsBounded<mint>(ub, left, bottom, convolve);

// res.right: (W-1, 0..ub[W-1]-1)
// res.top[i]: (i, ub[i]-1) に到達する重み
```

### `NorthEastLatticePathsBothBounded` 関数

2 次元平面上の矩形から左上部分と右下部分を（へこみができないように）削った領域の左辺上に初期重みが存在するとき，右辺における最終重みを取得する．

```cpp
using mint = ModInt998244353;
auto convolve = [&](const vector<mint> &l, const vector<mint> &r) { return nttconv(l, r); }

// 各列ごとの下限/上限（いずれも非減少）
vector<int> lb = {/* size = W */};
vector<int> ub = {/* size = W */};

// 左辺の区間 [lb[0], ub[0]) に対応する初期重み
vector<mint> left(ub.front() - lb.front());
left[0] = 1;  // 例: (0, lb[0]) に 1 を置く

// 右端列 (W-1) の区間 [lb[W-1], ub[W-1]) に対応する配列を返す
auto col = NorthEastLatticePathsBothBounded<mint>(lb, ub, left, convolve);
```

### 応用：各項の上下限が指定された単調非減少整数列の数え上げ

上下限が指定された場合の関数 `template <class MODINT> MODINT CountBoundedMonotoneSequence(std::vector<int> lb, std::vector<int> ub, auto convolve)` と，上限のみが指定される場合（下限は $0$ で固定）の関数 `template <class MODINT> MODINT CountBoundedMonotoneSequence(std::vector<int> ub, auto convolve)` が用意されている．

```cpp
using mint = ModInt998244353;
auto convolve = [&](const vector<mint> &l, const vector<mint> &r) { return nttconv(l, r); }

// 上限のみ: 0 <= a[i] < ub[i]
vector<int> ub = {/* ... */};
mint ways1 = CountBoundedMonotoneSequence<mint>(ub, convolve);

// 下限/上限とも: lb[i] <= a[i] < ub[i]
vector<int> lb = {/* ... */};
mint ways2 = CountBoundedMonotoneSequence<mint>(lb, ub, convolve);
```

内部的には，下限側を 1 だけ右にシフトすることで，グリッド上の最短路の数え上げに帰着させている．

## 問題例

- [Good Bye 2022: 2023 is NEAR G. Koxia and Bracket - Codeforces](https://codeforces.com/contest/1770/problem/G)
- [AOJ 3335: 01 Swap](https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3335)
- [AtCoder Beginner Contest 357 G - Stair-like Grid](https://atcoder.jp/contests/abc357/tasks/abc357_g)
  - このライブラリのままのコードでは不足していて，若干工夫する必要がある．
- [Library Checker: Number of Increasing Sequences Between Two Sequences](https://judge.yosupo.jp/problem/number_of_increasing_sequences_between_two_sequences)

## リンク

- [上限付き単調増加列の数え上げ - noshi91のメモ](https://noshi91.hatenablog.com/entry/2023/07/21/235339)
- [グリッドの最短経路の数え上げまとめ - かんプリンの学習記録](https://kanpurin.hatenablog.com/entry/2021/09/15/220913#aruryoiki)
