---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: convolution/ntt.hpp
    title: convolution/ntt.hpp
  - icon: ':heavy_check_mark:'
    path: modint.hpp
    title: modint.hpp
  - icon: ':heavy_check_mark:'
    path: other_algorithms/north_east_lattice_paths.hpp
    title: "Counting north-east lattice paths \uFF082 \u6B21\u5143\u30B0\u30EA\u30C3\
      \u30C9\u4E0A\u306E\u6700\u77ED\u8DEF\u306E\u6570\u3048\u4E0A\u3052\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
  bundledCode: "#line 1 \"other_algorithms/test/north_east_lattice_paths.bruteforce.test.cpp\"\
    \n#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \ // DUMMY\n\n#line 2 \"other_algorithms/north_east_lattice_paths.hpp\"\n#include\
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
    \    return std::accumulate(res.begin(), res.end(), MODINT{});\n}\n#line 3 \"\
    modint.hpp\"\n#include <iostream>\n#include <set>\n#line 6 \"modint.hpp\"\n\n\
    template <int md> struct ModInt {\n    static_assert(md > 1);\n    using lint\
    \ = long long;\n    constexpr static int mod() { return md; }\n    static int\
    \ get_primitive_root() {\n        static int primitive_root = 0;\n        if (!primitive_root)\
    \ {\n            primitive_root = [&]() {\n                std::set<int> fac;\n\
    \                int v = md - 1;\n                for (lint i = 2; i * i <= v;\
    \ i++)\n                    while (v % i == 0) fac.insert(i), v /= i;\n      \
    \          if (v > 1) fac.insert(v);\n                for (int g = 1; g < md;\
    \ g++) {\n                    bool ok = true;\n                    for (auto i\
    \ : fac)\n                        if (ModInt(g).pow((md - 1) / i) == 1) {\n  \
    \                          ok = false;\n                            break;\n \
    \                       }\n                    if (ok) return g;\n           \
    \     }\n                return -1;\n            }();\n        }\n        return\
    \ primitive_root;\n    }\n    int val_;\n    int val() const noexcept { return\
    \ val_; }\n    constexpr ModInt() : val_(0) {}\n    constexpr ModInt &_setval(lint\
    \ v) { return val_ = (v >= md ? v - md : v), *this; }\n    constexpr ModInt(lint\
    \ v) { _setval(v % md + md); }\n    constexpr explicit operator bool() const {\
    \ return val_ != 0; }\n    constexpr ModInt operator+(const ModInt &x) const {\n\
    \        return ModInt()._setval((lint)val_ + x.val_);\n    }\n    constexpr ModInt\
    \ operator-(const ModInt &x) const {\n        return ModInt()._setval((lint)val_\
    \ - x.val_ + md);\n    }\n    constexpr ModInt operator*(const ModInt &x) const\
    \ {\n        return ModInt()._setval((lint)val_ * x.val_ % md);\n    }\n    constexpr\
    \ ModInt operator/(const ModInt &x) const {\n        return ModInt()._setval((lint)val_\
    \ * x.inv().val() % md);\n    }\n    constexpr ModInt operator-() const { return\
    \ ModInt()._setval(md - val_); }\n    constexpr ModInt &operator+=(const ModInt\
    \ &x) { return *this = *this + x; }\n    constexpr ModInt &operator-=(const ModInt\
    \ &x) { return *this = *this - x; }\n    constexpr ModInt &operator*=(const ModInt\
    \ &x) { return *this = *this * x; }\n    constexpr ModInt &operator/=(const ModInt\
    \ &x) { return *this = *this / x; }\n    friend constexpr ModInt operator+(lint\
    \ a, const ModInt &x) { return ModInt(a) + x; }\n    friend constexpr ModInt operator-(lint\
    \ a, const ModInt &x) { return ModInt(a) - x; }\n    friend constexpr ModInt operator*(lint\
    \ a, const ModInt &x) { return ModInt(a) * x; }\n    friend constexpr ModInt operator/(lint\
    \ a, const ModInt &x) { return ModInt(a) / x; }\n    constexpr bool operator==(const\
    \ ModInt &x) const { return val_ == x.val_; }\n    constexpr bool operator!=(const\
    \ ModInt &x) const { return val_ != x.val_; }\n    constexpr bool operator<(const\
    \ ModInt &x) const {\n        return val_ < x.val_;\n    } // To use std::map<ModInt,\
    \ T>\n    friend std::istream &operator>>(std::istream &is, ModInt &x) {\n   \
    \     lint t;\n        return is >> t, x = ModInt(t), is;\n    }\n    constexpr\
    \ friend std::ostream &operator<<(std::ostream &os, const ModInt &x) {\n     \
    \   return os << x.val_;\n    }\n\n    constexpr ModInt pow(lint n) const {\n\
    \        ModInt ans = 1, tmp = *this;\n        while (n) {\n            if (n\
    \ & 1) ans *= tmp;\n            tmp *= tmp, n >>= 1;\n        }\n        return\
    \ ans;\n    }\n\n    static constexpr int cache_limit = std::min(md, 1 << 21);\n\
    \    static std::vector<ModInt> facs, facinvs, invs;\n\n    constexpr static void\
    \ _precalculation(int N) {\n        const int l0 = facs.size();\n        if (N\
    \ > md) N = md;\n        if (N <= l0) return;\n        facs.resize(N), facinvs.resize(N),\
    \ invs.resize(N);\n        for (int i = l0; i < N; i++) facs[i] = facs[i - 1]\
    \ * i;\n        facinvs[N - 1] = facs.back().pow(md - 2);\n        for (int i\
    \ = N - 2; i >= l0; i--) facinvs[i] = facinvs[i + 1] * (i + 1);\n        for (int\
    \ i = N - 1; i >= l0; i--) invs[i] = facinvs[i] * facs[i - 1];\n    }\n\n    constexpr\
    \ ModInt inv() const {\n        if (this->val_ < cache_limit) {\n            if\
    \ (facs.empty()) facs = {1}, facinvs = {1}, invs = {0};\n            while (this->val_\
    \ >= int(facs.size())) _precalculation(facs.size() * 2);\n            return invs[this->val_];\n\
    \        } else {\n            return this->pow(md - 2);\n        }\n    }\n\n\
    \    constexpr static ModInt fac(int n) {\n        assert(n >= 0);\n        if\
    \ (n >= md) return ModInt(0);\n        while (n >= int(facs.size())) _precalculation(facs.size()\
    \ * 2);\n        return facs[n];\n    }\n\n    constexpr static ModInt facinv(int\
    \ n) {\n        assert(n >= 0);\n        if (n >= md) return ModInt(0);\n    \
    \    while (n >= int(facs.size())) _precalculation(facs.size() * 2);\n       \
    \ return facinvs[n];\n    }\n\n    constexpr static ModInt doublefac(int n) {\n\
    \        assert(n >= 0);\n        if (n >= md) return ModInt(0);\n        long\
    \ long k = (n + 1) / 2;\n        return (n & 1) ? ModInt::fac(k * 2) / (ModInt(2).pow(k)\
    \ * ModInt::fac(k))\n                       : ModInt::fac(k) * ModInt(2).pow(k);\n\
    \    }\n\n    constexpr static ModInt nCr(int n, int r) {\n        assert(n >=\
    \ 0);\n        if (r < 0 or n < r) return ModInt(0);\n        return ModInt::fac(n)\
    \ * ModInt::facinv(r) * ModInt::facinv(n - r);\n    }\n\n    constexpr static\
    \ ModInt nPr(int n, int r) {\n        assert(n >= 0);\n        if (r < 0 or n\
    \ < r) return ModInt(0);\n        return ModInt::fac(n) * ModInt::facinv(n - r);\n\
    \    }\n\n    static ModInt binom(long long n, long long r) {\n        static\
    \ long long bruteforce_times = 0;\n\n        if (r < 0 or n < r) return ModInt(0);\n\
    \        if (n <= bruteforce_times or n < (int)facs.size()) return ModInt::nCr(n,\
    \ r);\n\n        r = std::min(r, n - r);\n        assert((int)r == r);\n\n   \
    \     ModInt ret = ModInt::facinv(r);\n        for (int i = 0; i < r; ++i) ret\
    \ *= n - i;\n        bruteforce_times += r;\n\n        return ret;\n    }\n\n\
    \    // Multinomial coefficient, (k_1 + k_2 + ... + k_m)! / (k_1! k_2! ... k_m!)\n\
    \    // Complexity: O(sum(ks))\n    // Verify: https://yukicoder.me/problems/no/3178\n\
    \    template <class Vec> static ModInt multinomial(const Vec &ks) {\n       \
    \ ModInt ret{1};\n        int sum = 0;\n        for (int k : ks) {\n         \
    \   assert(k >= 0);\n            ret *= ModInt::facinv(k), sum += k;\n       \
    \ }\n        return ret * ModInt::fac(sum);\n    }\n    template <class... Args>\
    \ static ModInt multinomial(Args... args) {\n        int sum = (0 + ... + args);\n\
    \        ModInt result = (1 * ... * ModInt::facinv(args));\n        return ModInt::fac(sum)\
    \ * result;\n    }\n\n    // Catalan number, C_n = binom(2n, n) / (n + 1) = #\
    \ of Dyck words of length 2n\n    // C_0 = 1, C_1 = 1, C_2 = 2, C_3 = 5, C_4 =\
    \ 14, ...\n    // https://oeis.org/A000108\n    // Complexity: O(n)\n    static\
    \ ModInt catalan(int n) {\n        if (n < 0) return ModInt(0);\n        return\
    \ ModInt::fac(n * 2) * ModInt::facinv(n + 1) * ModInt::facinv(n);\n    }\n\n \
    \   ModInt sqrt() const {\n        if (val_ == 0) return 0;\n        if (md ==\
    \ 2) return val_;\n        if (pow((md - 1) / 2) != 1) return 0;\n        ModInt\
    \ b = 1;\n        while (b.pow((md - 1) / 2) == 1) b += 1;\n        int e = 0,\
    \ m = md - 1;\n        while (m % 2 == 0) m >>= 1, e++;\n        ModInt x = pow((m\
    \ - 1) / 2), y = (*this) * x * x;\n        x *= (*this);\n        ModInt z = b.pow(m);\n\
    \        while (y != 1) {\n            int j = 0;\n            ModInt t = y;\n\
    \            while (t != 1) j++, t *= t;\n            z = z.pow(1LL << (e - j\
    \ - 1));\n            x *= z, z *= z, y *= z;\n            e = j;\n        }\n\
    \        return ModInt(std::min(x.val_, md - x.val_));\n    }\n};\ntemplate <int\
    \ md> std::vector<ModInt<md>> ModInt<md>::facs = {1};\ntemplate <int md> std::vector<ModInt<md>>\
    \ ModInt<md>::facinvs = {1};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::invs\
    \ = {0};\n\nusing ModInt998244353 = ModInt<998244353>;\n// using mint = ModInt<998244353>;\n\
    // using mint = ModInt<1000000007>;\n#line 3 \"convolution/ntt.hpp\"\n\n#line\
    \ 5 \"convolution/ntt.hpp\"\n#include <array>\n#line 7 \"convolution/ntt.hpp\"\
    \n#include <tuple>\n#line 9 \"convolution/ntt.hpp\"\n\n// CUT begin\n// Integer\
    \ convolution for arbitrary mod\n// with NTT (and Garner's algorithm) for ModInt\
    \ / ModIntRuntime class.\n// We skip Garner's algorithm if `skip_garner` is true\
    \ or mod is in `nttprimes`.\n// input: a (size: n), b (size: m)\n// return: vector\
    \ (size: n + m - 1)\ntemplate <typename MODINT>\nstd::vector<MODINT> nttconv(std::vector<MODINT>\
    \ a, std::vector<MODINT> b, bool skip_garner);\n\nconstexpr int nttprimes[3] =\
    \ {998244353, 167772161, 469762049};\n\n// Integer FFT (Fast Fourier Transform)\
    \ for ModInt class\n// (Also known as Number Theoretic Transform, NTT)\n// is_inverse:\
    \ inverse transform\n// ** Input size must be 2^n **\ntemplate <typename MODINT>\
    \ void ntt(std::vector<MODINT> &a, bool is_inverse = false) {\n    int n = a.size();\n\
    \    if (n == 1) return;\n    static const int mod = MODINT::mod();\n    static\
    \ const MODINT root = MODINT::get_primitive_root();\n    assert(__builtin_popcount(n)\
    \ == 1 and (mod - 1) % n == 0);\n\n    static std::vector<MODINT> w{1}, iw{1};\n\
    \    for (int m = w.size(); m < n / 2; m *= 2) {\n        MODINT dw = root.pow((mod\
    \ - 1) / (4 * m)), dwinv = 1 / dw;\n        w.resize(m * 2), iw.resize(m * 2);\n\
    \        for (int i = 0; i < m; i++) w[m + i] = w[i] * dw, iw[m + i] = iw[i] *\
    \ dwinv;\n    }\n\n    if (!is_inverse) {\n        for (int m = n; m >>= 1;) {\n\
    \            for (int s = 0, k = 0; s < n; s += 2 * m, k++) {\n              \
    \  for (int i = s; i < s + m; i++) {\n                    MODINT x = a[i], y =\
    \ a[i + m] * w[k];\n                    a[i] = x + y, a[i + m] = x - y;\n    \
    \            }\n            }\n        }\n    } else {\n        for (int m = 1;\
    \ m < n; m *= 2) {\n            for (int s = 0, k = 0; s < n; s += 2 * m, k++)\
    \ {\n                for (int i = s; i < s + m; i++) {\n                    MODINT\
    \ x = a[i], y = a[i + m];\n                    a[i] = x + y, a[i + m] = (x - y)\
    \ * iw[k];\n                }\n            }\n        }\n        int n_inv = MODINT(n).inv().val();\n\
    \        for (auto &v : a) v *= n_inv;\n    }\n}\ntemplate <int MOD>\nstd::vector<ModInt<MOD>>\
    \ nttconv_(const std::vector<int> &a, const std::vector<int> &b) {\n    int sz\
    \ = a.size();\n    assert(a.size() == b.size() and __builtin_popcount(sz) == 1);\n\
    \    std::vector<ModInt<MOD>> ap(sz), bp(sz);\n    for (int i = 0; i < sz; i++)\
    \ ap[i] = a[i], bp[i] = b[i];\n    ntt(ap, false);\n    if (a == b)\n        bp\
    \ = ap;\n    else\n        ntt(bp, false);\n    for (int i = 0; i < sz; i++) ap[i]\
    \ *= bp[i];\n    ntt(ap, true);\n    return ap;\n}\nlong long garner_ntt_(int\
    \ r0, int r1, int r2, int mod) {\n    using mint2 = ModInt<nttprimes[2]>;\n  \
    \  static const long long m01 = 1LL * nttprimes[0] * nttprimes[1];\n    static\
    \ const long long m0_inv_m1 = ModInt<nttprimes[1]>(nttprimes[0]).inv().val();\n\
    \    static const long long m01_inv_m2 = mint2(m01).inv().val();\n\n    int v1\
    \ = (m0_inv_m1 * (r1 + nttprimes[1] - r0)) % nttprimes[1];\n    auto v2 = (mint2(r2)\
    \ - r0 - mint2(nttprimes[0]) * v1) * m01_inv_m2;\n    return (r0 + 1LL * nttprimes[0]\
    \ * v1 + m01 % mod * v2.val()) % mod;\n}\ntemplate <typename MODINT>\nstd::vector<MODINT>\
    \ nttconv(std::vector<MODINT> a, std::vector<MODINT> b, bool skip_garner) {\n\
    \    if (a.empty() or b.empty()) return {};\n    int sz = 1, n = a.size(), m =\
    \ b.size();\n    while (sz < n + m) sz <<= 1;\n    if (sz <= 16) {\n        std::vector<MODINT>\
    \ ret(n + m - 1);\n        for (int i = 0; i < n; i++) {\n            for (int\
    \ j = 0; j < m; j++) ret[i + j] += a[i] * b[j];\n        }\n        return ret;\n\
    \    }\n    int mod = MODINT::mod();\n    if (skip_garner or\n        std::find(std::begin(nttprimes),\
    \ std::end(nttprimes), mod) != std::end(nttprimes)) {\n        a.resize(sz), b.resize(sz);\n\
    \        if (a == b) {\n            ntt(a, false);\n            b = a;\n     \
    \   } else {\n            ntt(a, false), ntt(b, false);\n        }\n        for\
    \ (int i = 0; i < sz; i++) a[i] *= b[i];\n        ntt(a, true);\n        a.resize(n\
    \ + m - 1);\n    } else {\n        std::vector<int> ai(sz), bi(sz);\n        for\
    \ (int i = 0; i < n; i++) ai[i] = a[i].val();\n        for (int i = 0; i < m;\
    \ i++) bi[i] = b[i].val();\n        auto ntt0 = nttconv_<nttprimes[0]>(ai, bi);\n\
    \        auto ntt1 = nttconv_<nttprimes[1]>(ai, bi);\n        auto ntt2 = nttconv_<nttprimes[2]>(ai,\
    \ bi);\n        a.resize(n + m - 1);\n        for (int i = 0; i < n + m - 1; i++)\n\
    \            a[i] = garner_ntt_(ntt0[i].val(), ntt1[i].val(), ntt2[i].val(), mod);\n\
    \    }\n    return a;\n}\n\ntemplate <typename MODINT>\nstd::vector<MODINT> nttconv(const\
    \ std::vector<MODINT> &a, const std::vector<MODINT> &b) {\n    return nttconv<MODINT>(a,\
    \ b, false);\n}\n#line 6 \"other_algorithms/test/north_east_lattice_paths.bruteforce.test.cpp\"\
    \n\nusing mint = ModInt998244353;\n\n#line 10 \"other_algorithms/test/north_east_lattice_paths.bruteforce.test.cpp\"\
    \n#include <map>\n#include <utility>\nusing namespace std;\n\nvoid Check() {\n\
    \    const int n = 30, d = 10;\n    vector<mint> init(d);\n    for (int i = 0;\
    \ i < d; ++i) init[i] = mint(2).pow(i);\n\n    map<pair<int, int>, mint> dp;\n\
    \    for (int x = 0; x < d; ++x) dp[{x, 0}] = init[x];\n\n    for (int x = -n;\
    \ x <= n; ++x) {\n        for (int y = -n; y <= n; ++y) {\n            if (x +\
    \ 1 <= n) dp[{x + 1, y}] += dp[{x, y}];\n            if (y + 1 <= n) dp[{x, y\
    \ + 1}] += dp[{x, y}];\n        }\n    }\n\n    for (int dx_init = -n; dx_init\
    \ <= n; ++dx_init) {\n        for (int y = -n; y <= n; ++y) {\n            for\
    \ (int len = 1; dx_init + len - 1 <= n; ++len) {\n                vector<mint>\
    \ expected(len);\n                for (int i = 0; i < len; ++i) expected[i] =\
    \ dp[{dx_init + i, y}];\n\n                auto res = NorthEastLatticePathsParallel<mint>(\n\
    \                    init, dx_init, y, len, [&](auto &&a, auto &&b) { return nttconv(a,\
    \ b); });\n                if (res != expected) {\n                    cerr <<\
    \ \"Failed Parallel: \" << dx_init << ' ' << y << ' ' << len\n               \
    \          << \"\\nExpected: \";\n                    for (auto e : expected)\
    \ cerr << \" \" << e;\n                    cerr << \"\\nResult: \";\n        \
    \            for (auto e : res) cerr << \" \" << e;\n                    cerr\
    \ << '\\n';\n                    exit(1);\n                }\n            }\n\
    \        }\n    }\n\n    for (int x = -n; x <= n; ++x) {\n        for (int dy_init\
    \ = -n; dy_init <= n; ++dy_init) {\n            for (int len = 1; dy_init + len\
    \ - 1 <= n; ++len) {\n                vector<mint> expected(len);\n          \
    \      for (int i = 0; i < len; ++i) expected[i] = dp[{x, dy_init + i}];\n\n \
    \               auto res = NorthEastLatticePathsVertical<mint>(\n            \
    \        init, x, dy_init, len, [&](auto &&a, auto &&b) { return nttconv(a, b);\
    \ });\n                if (res != expected) {\n                    cerr << \"\
    Failed Vertical: \" << x << ' ' << dy_init << ' ' << len\n                   \
    \      << \"\\nExpected: \";\n                    for (auto e : expected) cerr\
    \ << \" \" << e;\n                    cerr << \"\\nResult: \";\n             \
    \       for (auto e : res) cerr << \" \" << e;\n                    cerr << '\\\
    n';\n                    exit(1);\n                }\n            }\n        }\n\
    \    }\n}\n\nint main() {\n    Check();\n    puts(\"Hello World\");\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \ // DUMMY\n\n#include \"../north_east_lattice_paths.hpp\"\n#include \"../../modint.hpp\"\
    \n#include \"../../convolution/ntt.hpp\"\n\nusing mint = ModInt998244353;\n\n\
    #include <iostream>\n#include <map>\n#include <utility>\nusing namespace std;\n\
    \nvoid Check() {\n    const int n = 30, d = 10;\n    vector<mint> init(d);\n \
    \   for (int i = 0; i < d; ++i) init[i] = mint(2).pow(i);\n\n    map<pair<int,\
    \ int>, mint> dp;\n    for (int x = 0; x < d; ++x) dp[{x, 0}] = init[x];\n\n \
    \   for (int x = -n; x <= n; ++x) {\n        for (int y = -n; y <= n; ++y) {\n\
    \            if (x + 1 <= n) dp[{x + 1, y}] += dp[{x, y}];\n            if (y\
    \ + 1 <= n) dp[{x, y + 1}] += dp[{x, y}];\n        }\n    }\n\n    for (int dx_init\
    \ = -n; dx_init <= n; ++dx_init) {\n        for (int y = -n; y <= n; ++y) {\n\
    \            for (int len = 1; dx_init + len - 1 <= n; ++len) {\n            \
    \    vector<mint> expected(len);\n                for (int i = 0; i < len; ++i)\
    \ expected[i] = dp[{dx_init + i, y}];\n\n                auto res = NorthEastLatticePathsParallel<mint>(\n\
    \                    init, dx_init, y, len, [&](auto &&a, auto &&b) { return nttconv(a,\
    \ b); });\n                if (res != expected) {\n                    cerr <<\
    \ \"Failed Parallel: \" << dx_init << ' ' << y << ' ' << len\n               \
    \          << \"\\nExpected: \";\n                    for (auto e : expected)\
    \ cerr << \" \" << e;\n                    cerr << \"\\nResult: \";\n        \
    \            for (auto e : res) cerr << \" \" << e;\n                    cerr\
    \ << '\\n';\n                    exit(1);\n                }\n            }\n\
    \        }\n    }\n\n    for (int x = -n; x <= n; ++x) {\n        for (int dy_init\
    \ = -n; dy_init <= n; ++dy_init) {\n            for (int len = 1; dy_init + len\
    \ - 1 <= n; ++len) {\n                vector<mint> expected(len);\n          \
    \      for (int i = 0; i < len; ++i) expected[i] = dp[{x, dy_init + i}];\n\n \
    \               auto res = NorthEastLatticePathsVertical<mint>(\n            \
    \        init, x, dy_init, len, [&](auto &&a, auto &&b) { return nttconv(a, b);\
    \ });\n                if (res != expected) {\n                    cerr << \"\
    Failed Vertical: \" << x << ' ' << dy_init << ' ' << len\n                   \
    \      << \"\\nExpected: \";\n                    for (auto e : expected) cerr\
    \ << \" \" << e;\n                    cerr << \"\\nResult: \";\n             \
    \       for (auto e : res) cerr << \" \" << e;\n                    cerr << '\\\
    n';\n                    exit(1);\n                }\n            }\n        }\n\
    \    }\n}\n\nint main() {\n    Check();\n    puts(\"Hello World\");\n}\n"
  dependsOn:
  - other_algorithms/north_east_lattice_paths.hpp
  - modint.hpp
  - convolution/ntt.hpp
  isVerificationFile: true
  path: other_algorithms/test/north_east_lattice_paths.bruteforce.test.cpp
  requiredBy: []
  timestamp: '2025-09-11 21:33:22+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: other_algorithms/test/north_east_lattice_paths.bruteforce.test.cpp
layout: document
redirect_from:
- /verify/other_algorithms/test/north_east_lattice_paths.bruteforce.test.cpp
- /verify/other_algorithms/test/north_east_lattice_paths.bruteforce.test.cpp.html
title: other_algorithms/test/north_east_lattice_paths.bruteforce.test.cpp
---
