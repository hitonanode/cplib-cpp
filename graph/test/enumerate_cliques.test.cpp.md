---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/enumerate_cliques.hpp
    title: "Enumerate cliques \uFF08\u30B0\u30E9\u30D5\u306E\u30AF\u30EA\u30FC\u30AF\
      \u5168\u5217\u6319\uFF09"
  - icon: ':question:'
    path: modint.hpp
    title: modint.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/enumerate_cliques
    links:
    - https://judge.yosupo.jp/problem/enumerate_cliques
  bundledCode: "#line 2 \"graph/enumerate_cliques.hpp\"\n\n/**\n * @file enumerate_cliques.hpp\n\
    \ * @brief Enumerate all cliques of given undirected graph\n * @author hitonanode\n\
    \ * @date 2023/03/10\n */\n\n#include <algorithm>\n#include <cassert>\n#include\
    \ <numeric>\n#include <queue>\n#include <utility>\n#include <vector>\n\n// Complexity:\
    \ O(2^sqrt(2m) * n)\n// Verify: https://judge.yosupo.jp/problem/enumerate_cliques\
    \ (~1ms for n <= 100, m <= 100)\n// p.15, https://www.slideshare.net/wata_orz/ss-12131479\n\
    struct enumerate_cliques {\n    std::vector<std::vector<int>> to;\n    std::vector<std::pair<int,\
    \ int>> edges;\n\n    int n() const { return to.size(); }\n    int m() const {\
    \ return edges.size(); }\n\n    enumerate_cliques(int n_) : to(n_) {}\n\n    void\
    \ add_bi_edge(int u, int v) {\n        assert(0 <= u and u < n());\n        assert(0\
    \ <= v and v < n());\n        if (u != v) edges.emplace_back(std::minmax(u, v));\n\
    \    }\n\n    // Build `to`\n    void precalc() {\n        std::sort(edges.begin(),\
    \ edges.end());\n        edges.erase(std::unique(edges.begin(), edges.end()),\
    \ edges.end());\n\n        for (auto &vec : to) vec.clear();\n        for (auto\
    \ [u, v] : edges) to.at(u).push_back(v), to.at(v).push_back(u);\n        for (auto\
    \ &vec : to) std::sort(vec.begin(), vec.end());\n    }\n\n    template <class\
    \ F>\n    void bruteforce(const std::vector<int> &cand_vs, int prefix_use, F op)\
    \ const {\n        const int k = cand_vs.size();\n        const int mask_all =\
    \ (1 << k) - 1;\n        std::vector<int> ok_masks(k, mask_all);\n\n        for\
    \ (int i = 0; i < k; ++i) {\n            for (int j = 0; j < i; ++j) {\n     \
    \           int u = cand_vs.at(i), v = cand_vs.at(j);\n                if (!std::binary_search(to.at(u).cbegin(),\
    \ to.at(u).cend(), v)) {\n                    ok_masks.at(i) &= ~(1 << j), ok_masks.at(j)\
    \ &= ~(1 << i);\n                }\n            }\n        }\n\n        std::vector<int>\
    \ seq;\n        if (prefix_use >= 0) seq.push_back(prefix_use);\n        seq.reserve(seq.size()\
    \ + k);\n\n        auto rec = [&](auto &&self, int now, const int last_mask) ->\
    \ void {\n            op(seq);\n            seq.push_back(-1);\n            for\
    \ (int i = now; i < k; ++i) {\n                if ((last_mask >> i) & 1) {\n \
    \                   seq.back() = cand_vs.at(i);\n                    self(self,\
    \ i + 1, last_mask & ok_masks.at(i));\n                }\n            }\n    \
    \        seq.pop_back();\n        };\n        rec(rec, 0, mask_all);\n       \
    \ return;\n    }\n\n    template <class F> void run(F op) {\n        precalc();\n\
    \n        std::vector<int> deg(n()), is_alive(n(), 1);\n        using P = std::pair<int,\
    \ int>;\n        std::priority_queue<P, std::vector<P>, std::greater<P>> pq;\n\
    \        for (int i = 0; i < n(); ++i) deg.at(i) = to.at(i).size(), pq.emplace(deg.at(i),\
    \ i);\n\n        int rem_n = n(), rem_m = m();\n\n        std::vector<int> cand_vs;\n\
    \        while (!pq.empty()) {\n            auto [di, i] = pq.top();\n       \
    \     pq.pop();\n            if (deg.at(i) != di) continue;\n\n            cand_vs.clear();\n\
    \n            if (di * di > rem_m * 2) { // Avoid \"deg[i] = 0\" case\n      \
    \          for (int i = 0; i < n(); ++i) {\n                    if (is_alive.at(i))\
    \ cand_vs.push_back(i);\n                }\n                bruteforce(cand_vs,\
    \ -1, op);\n                break;\n            }\n\n            for (int j :\
    \ to.at(i)) {\n                if (is_alive.at(j)) cand_vs.push_back(j);\n   \
    \         }\n            bruteforce(cand_vs, i, op);\n\n            --rem_n, deg.at(i)\
    \ = 0, is_alive.at(i) = 0;\n            for (int j : cand_vs) --rem_m, --deg.at(j),\
    \ pq.emplace(deg.at(j), j);\n        }\n    }\n};\n#line 2 \"modint.hpp\"\n#include\
    \ <iostream>\n#include <set>\n#line 5 \"modint.hpp\"\n\ntemplate <int md> struct\
    \ ModInt {\n#if __cplusplus >= 201402L\n#define MDCONST constexpr\n#else\n#define\
    \ MDCONST\n#endif\n    using lint = long long;\n    MDCONST static int mod() {\
    \ return md; }\n    static int get_primitive_root() {\n        static int primitive_root\
    \ = 0;\n        if (!primitive_root) {\n            primitive_root = [&]() {\n\
    \                std::set<int> fac;\n                int v = md - 1;\n       \
    \         for (lint i = 2; i * i <= v; i++)\n                    while (v % i\
    \ == 0) fac.insert(i), v /= i;\n                if (v > 1) fac.insert(v);\n  \
    \              for (int g = 1; g < md; g++) {\n                    bool ok = true;\n\
    \                    for (auto i : fac)\n                        if (ModInt(g).pow((md\
    \ - 1) / i) == 1) {\n                            ok = false;\n               \
    \             break;\n                        }\n                    if (ok) return\
    \ g;\n                }\n                return -1;\n            }();\n      \
    \  }\n        return primitive_root;\n    }\n    int val_;\n    int val() const\
    \ noexcept { return val_; }\n    MDCONST ModInt() : val_(0) {}\n    MDCONST ModInt\
    \ &_setval(lint v) { return val_ = (v >= md ? v - md : v), *this; }\n    MDCONST\
    \ ModInt(lint v) { _setval(v % md + md); }\n    MDCONST explicit operator bool()\
    \ const { return val_ != 0; }\n    MDCONST ModInt operator+(const ModInt &x) const\
    \ {\n        return ModInt()._setval((lint)val_ + x.val_);\n    }\n    MDCONST\
    \ ModInt operator-(const ModInt &x) const {\n        return ModInt()._setval((lint)val_\
    \ - x.val_ + md);\n    }\n    MDCONST ModInt operator*(const ModInt &x) const\
    \ {\n        return ModInt()._setval((lint)val_ * x.val_ % md);\n    }\n    MDCONST\
    \ ModInt operator/(const ModInt &x) const {\n        return ModInt()._setval((lint)val_\
    \ * x.inv().val() % md);\n    }\n    MDCONST ModInt operator-() const { return\
    \ ModInt()._setval(md - val_); }\n    MDCONST ModInt &operator+=(const ModInt\
    \ &x) { return *this = *this + x; }\n    MDCONST ModInt &operator-=(const ModInt\
    \ &x) { return *this = *this - x; }\n    MDCONST ModInt &operator*=(const ModInt\
    \ &x) { return *this = *this * x; }\n    MDCONST ModInt &operator/=(const ModInt\
    \ &x) { return *this = *this / x; }\n    friend MDCONST ModInt operator+(lint\
    \ a, const ModInt &x) {\n        return ModInt()._setval(a % md + x.val_);\n \
    \   }\n    friend MDCONST ModInt operator-(lint a, const ModInt &x) {\n      \
    \  return ModInt()._setval(a % md - x.val_ + md);\n    }\n    friend MDCONST ModInt\
    \ operator*(lint a, const ModInt &x) {\n        return ModInt()._setval(a % md\
    \ * x.val_ % md);\n    }\n    friend MDCONST ModInt operator/(lint a, const ModInt\
    \ &x) {\n        return ModInt()._setval(a % md * x.inv().val() % md);\n    }\n\
    \    MDCONST bool operator==(const ModInt &x) const { return val_ == x.val_; }\n\
    \    MDCONST bool operator!=(const ModInt &x) const { return val_ != x.val_; }\n\
    \    MDCONST bool operator<(const ModInt &x) const {\n        return val_ < x.val_;\n\
    \    } // To use std::map<ModInt, T>\n    friend std::istream &operator>>(std::istream\
    \ &is, ModInt &x) {\n        lint t;\n        return is >> t, x = ModInt(t), is;\n\
    \    }\n    MDCONST friend std::ostream &operator<<(std::ostream &os, const ModInt\
    \ &x) {\n        return os << x.val_;\n    }\n    MDCONST ModInt pow(lint n) const\
    \ {\n        ModInt ans = 1, tmp = *this;\n        while (n) {\n            if\
    \ (n & 1) ans *= tmp;\n            tmp *= tmp, n >>= 1;\n        }\n        return\
    \ ans;\n    }\n\n    static std::vector<ModInt> facs, facinvs, invs;\n    MDCONST\
    \ static void _precalculation(int N) {\n        int l0 = facs.size();\n      \
    \  if (N > md) N = md;\n        if (N <= l0) return;\n        facs.resize(N),\
    \ facinvs.resize(N), invs.resize(N);\n        for (int i = l0; i < N; i++) facs[i]\
    \ = facs[i - 1] * i;\n        facinvs[N - 1] = facs.back().pow(md - 2);\n    \
    \    for (int i = N - 2; i >= l0; i--) facinvs[i] = facinvs[i + 1] * (i + 1);\n\
    \        for (int i = N - 1; i >= l0; i--) invs[i] = facinvs[i] * facs[i - 1];\n\
    \    }\n    MDCONST ModInt inv() const {\n        if (this->val_ < std::min(md\
    \ >> 1, 1 << 21)) {\n            if (facs.empty()) facs = {1}, facinvs = {1},\
    \ invs = {0};\n            while (this->val_ >= int(facs.size())) _precalculation(facs.size()\
    \ * 2);\n            return invs[this->val_];\n        } else {\n            return\
    \ this->pow(md - 2);\n        }\n    }\n    MDCONST ModInt fac() const {\n   \
    \     while (this->val_ >= int(facs.size())) _precalculation(facs.size() * 2);\n\
    \        return facs[this->val_];\n    }\n    MDCONST ModInt facinv() const {\n\
    \        while (this->val_ >= int(facs.size())) _precalculation(facs.size() *\
    \ 2);\n        return facinvs[this->val_];\n    }\n    MDCONST ModInt doublefac()\
    \ const {\n        lint k = (this->val_ + 1) / 2;\n        return (this->val_\
    \ & 1) ? ModInt(k * 2).fac() / (ModInt(2).pow(k) * ModInt(k).fac())\n        \
    \                        : ModInt(k).fac() * ModInt(2).pow(k);\n    }\n    MDCONST\
    \ ModInt nCr(const ModInt &r) const {\n        return (this->val_ < r.val_) ?\
    \ 0 : this->fac() * (*this - r).facinv() * r.facinv();\n    }\n    MDCONST ModInt\
    \ nPr(const ModInt &r) const {\n        return (this->val_ < r.val_) ? 0 : this->fac()\
    \ * (*this - r).facinv();\n    }\n\n    ModInt sqrt() const {\n        if (val_\
    \ == 0) return 0;\n        if (md == 2) return val_;\n        if (pow((md - 1)\
    \ / 2) != 1) return 0;\n        ModInt b = 1;\n        while (b.pow((md - 1) /\
    \ 2) == 1) b += 1;\n        int e = 0, m = md - 1;\n        while (m % 2 == 0)\
    \ m >>= 1, e++;\n        ModInt x = pow((m - 1) / 2), y = (*this) * x * x;\n \
    \       x *= (*this);\n        ModInt z = b.pow(m);\n        while (y != 1) {\n\
    \            int j = 0;\n            ModInt t = y;\n            while (t != 1)\
    \ j++, t *= t;\n            z = z.pow(1LL << (e - j - 1));\n            x *= z,\
    \ z *= z, y *= z;\n            e = j;\n        }\n        return ModInt(std::min(x.val_,\
    \ md - x.val_));\n    }\n};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::facs\
    \ = {1};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::facinvs = {1};\n\
    template <int md> std::vector<ModInt<md>> ModInt<md>::invs = {0};\n\nusing ModInt998244353\
    \ = ModInt<998244353>;\n// using mint = ModInt<998244353>;\n// using mint = ModInt<1000000007>;\n\
    #line 5 \"graph/test/enumerate_cliques.test.cpp\"\nusing namespace std;\n\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/enumerate_cliques\"\n\nint main()\
    \ {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\n    int N, M;\n   \
    \ cin >> N >> M;\n    using mint = ModInt998244353;\n    vector<mint> X(N);\n\
    \    for (auto &x : X) cin >> x;\n\n    enumerate_cliques ec(N);\n    while (M--)\
    \ {\n        int u, v;\n        cin >> u >> v;\n        ec.add_bi_edge(u, v);\n\
    \    }\n    mint ret = mint();\n\n    auto op = [&](const std::vector<int> &clique)\
    \ -> void {\n        mint tmp = 1;\n        for (int x : clique) tmp *= X.at(x);\n\
    \        ret += tmp;\n    };\n    ec.run(op);\n\n    cout << ret << endl;\n}\n"
  code: "#include \"../enumerate_cliques.hpp\"\n#include \"../../modint.hpp\"\n#include\
    \ <iostream>\n#include <vector>\nusing namespace std;\n\n#define PROBLEM \"https://judge.yosupo.jp/problem/enumerate_cliques\"\
    \n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\n    int\
    \ N, M;\n    cin >> N >> M;\n    using mint = ModInt998244353;\n    vector<mint>\
    \ X(N);\n    for (auto &x : X) cin >> x;\n\n    enumerate_cliques ec(N);\n   \
    \ while (M--) {\n        int u, v;\n        cin >> u >> v;\n        ec.add_bi_edge(u,\
    \ v);\n    }\n    mint ret = mint();\n\n    auto op = [&](const std::vector<int>\
    \ &clique) -> void {\n        mint tmp = 1;\n        for (int x : clique) tmp\
    \ *= X.at(x);\n        ret += tmp;\n    };\n    ec.run(op);\n\n    cout << ret\
    \ << endl;\n}\n"
  dependsOn:
  - graph/enumerate_cliques.hpp
  - modint.hpp
  isVerificationFile: true
  path: graph/test/enumerate_cliques.test.cpp
  requiredBy: []
  timestamp: '2023-03-10 15:00:17+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: graph/test/enumerate_cliques.test.cpp
layout: document
redirect_from:
- /verify/graph/test/enumerate_cliques.test.cpp
- /verify/graph/test/enumerate_cliques.test.cpp.html
title: graph/test/enumerate_cliques.test.cpp
---
