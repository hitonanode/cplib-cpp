---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: modint.hpp
    title: modint.hpp
  - icon: ':heavy_check_mark:'
    path: tree/tree_isomorphism.hpp
    title: "Tree isomrphism \uFF08\u6728\u306E\u540C\u578B\u5224\u5B9A\uFF09"
  - icon: ':heavy_check_mark:'
    path: utilities/groupby.hpp
    title: groupby
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/rooted_tree_isomorphism_classification
    links:
    - https://judge.yosupo.jp/problem/rooted_tree_isomorphism_classification
  bundledCode: "#line 1 \"tree/test/subtree_isomorphism.lc.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/rooted_tree_isomorphism_classification\"\n\
    #line 2 \"tree/tree_isomorphism.hpp\"\n#include <chrono>\n#include <utility>\n\
    #include <vector>\n\n// Tree isomorphism with hashing \uFF08\u30CF\u30C3\u30B7\
    \u30E5\u306B\u3088\u308B\u6728\u306E\u540C\u578B\u5224\u5B9A\uFF09\n// Dependence:\
    \ ModInt or ModIntRuntime\n// Reference: https://snuke.hatenablog.com/entry/2017/02/03/054210\n\
    // Verified: https://atcoder.jp/contests/nikkei2019-2-final/submissions/9044698\
    \ (ModInt)\n//           https://atcoder.jp/contests/nikkei2019-2-final/submissions/9044745\
    \ (ModIntRuntime)\ntemplate <typename ModInt> struct tree_isomorphism {\n    using\
    \ DoubleHash = std::pair<ModInt, ModInt>;\n    using Edges = std::vector<std::vector<int>>;\
    \ // vector<set<int>>;\n    int V;\n    Edges e;\n    tree_isomorphism(int v)\
    \ : V(v), e(v) {}\n    void add_edge(int u, int v) {\n        e[u].emplace_back(v);\n\
    \        e[v].emplace_back(u);\n    }\n\n    static uint64_t splitmix64(uint64_t\
    \ x) {\n        // https://codeforces.com/blog/entry/62393 http://xorshift.di.unimi.it/splitmix64.c\n\
    \        x += 0x9e3779b97f4a7c15;\n        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;\n\
    \        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;\n        return x ^ (x >> 31);\n\
    \    }\n    DoubleHash get_hash(DoubleHash x) const {\n        static const uint64_t\
    \ FIXED_RANDOM =\n            std::chrono::steady_clock::now().time_since_epoch().count();\n\
    \        return {splitmix64(x.first.val() + FIXED_RANDOM), splitmix64(x.second.val()\
    \ + FIXED_RANDOM)};\n    }\n\n    static void add_hash(DoubleHash &l, const DoubleHash\
    \ &r) {\n        l.first += r.first, l.second += r.second;\n    }\n    static\
    \ DoubleHash subtract_hash(const DoubleHash &l, const DoubleHash &r) {\n     \
    \   return {l.first - r.first, l.second - r.second};\n    }\n\n    std::vector<DoubleHash>\
    \ hash;         // hash of the tree, each node regarded as root\n    std::vector<DoubleHash>\
    \ hash_subtree; // hash of the subtree\n    std::vector<DoubleHash> hash_par;\
    \ // hash of the subtree whose root is parent[i], not containing i\n    DoubleHash\
    \ hash_p;                // \\in [1, hmod), should be set randomly\n    DoubleHash\
    \ hash_dfs1_(int now, int prv) {\n        hash_subtree[now] = hash_p;\n      \
    \  for (auto nxt : e[now]) {\n            if (nxt != prv) add_hash(hash_subtree[now],\
    \ hash_dfs1_(nxt, now));\n        }\n        return get_hash(hash_subtree[now]);\n\
    \    }\n    void hash_dfs2_(int now, int prv) {\n        add_hash(hash[now], hash_subtree[now]);\n\
    \        if (prv >= 0) hash_par[now] = subtract_hash(hash[prv], get_hash(hash_subtree[now]));\n\
    \        for (auto nxt : e[now])\n            if (nxt != prv) {\n            \
    \    DoubleHash tmp = subtract_hash(hash[now], get_hash(hash_subtree[nxt]));\n\
    \                add_hash(hash[nxt], get_hash(tmp));\n                hash_dfs2_(nxt,\
    \ now);\n            }\n    }\n    void build_hash(int root, int p1, int p2) {\n\
    \        hash_p = std::make_pair(p1, p2);\n        hash.resize(V), hash_subtree.resize(V),\
    \ hash_par.resize(V);\n        hash_dfs1_(root, -1);\n        hash_dfs2_(root,\
    \ -1);\n    }\n};\n#line 2 \"utilities/groupby.hpp\"\n#include <algorithm>\n#line\
    \ 5 \"utilities/groupby.hpp\"\n\n// Key class must be comparable\n// Example:\
    \ [(2, 3), (1, 5), (2, 2), (2, 3), (1, 4)] -> [(1, [5, 4]), (2, [3, 2, 3])]\n\
    // Verified: https://atcoder.jp/contests/abc259/tasks/abc259_h\ntemplate <class\
    \ Key, class Value>\nstd::vector<std::pair<Key, std::vector<Value>>> groupby(std::vector<std::pair<Key,\
    \ Value>> xs) {\n    using KV = std::pair<Key, Value>;\n    std::stable_sort(\n\
    \        xs.begin(), xs.end(), [&](const KV &l, const KV &r) { return l.first\
    \ < r.first; });\n\n    std::vector<std::pair<Key, std::vector<Value>>> ret;\n\
    \    for (const auto &x : xs) {\n        if (ret.empty() or ret.back().first !=\
    \ x.first) {\n            ret.emplace_back(x.first, std::vector<Value>());\n \
    \       }\n        ret.back().second.push_back(x.second);\n    }\n    return ret;\n\
    }\n#line 2 \"modint.hpp\"\n#include <cassert>\n#include <iostream>\n#include <set>\n\
    #line 6 \"modint.hpp\"\n\ntemplate <int md> struct ModInt {\n    using lint =\
    \ long long;\n    constexpr static int mod() { return md; }\n    static int get_primitive_root()\
    \ {\n        static int primitive_root = 0;\n        if (!primitive_root) {\n\
    \            primitive_root = [&]() {\n                std::set<int> fac;\n  \
    \              int v = md - 1;\n                for (lint i = 2; i * i <= v; i++)\n\
    \                    while (v % i == 0) fac.insert(i), v /= i;\n             \
    \   if (v > 1) fac.insert(v);\n                for (int g = 1; g < md; g++) {\n\
    \                    bool ok = true;\n                    for (auto i : fac)\n\
    \                        if (ModInt(g).pow((md - 1) / i) == 1) {\n           \
    \                 ok = false;\n                            break;\n          \
    \              }\n                    if (ok) return g;\n                }\n \
    \               return -1;\n            }();\n        }\n        return primitive_root;\n\
    \    }\n    int val_;\n    int val() const noexcept { return val_; }\n    constexpr\
    \ ModInt() : val_(0) {}\n    constexpr ModInt &_setval(lint v) { return val_ =\
    \ (v >= md ? v - md : v), *this; }\n    constexpr ModInt(lint v) { _setval(v %\
    \ md + md); }\n    constexpr explicit operator bool() const { return val_ != 0;\
    \ }\n    constexpr ModInt operator+(const ModInt &x) const {\n        return ModInt()._setval((lint)val_\
    \ + x.val_);\n    }\n    constexpr ModInt operator-(const ModInt &x) const {\n\
    \        return ModInt()._setval((lint)val_ - x.val_ + md);\n    }\n    constexpr\
    \ ModInt operator*(const ModInt &x) const {\n        return ModInt()._setval((lint)val_\
    \ * x.val_ % md);\n    }\n    constexpr ModInt operator/(const ModInt &x) const\
    \ {\n        return ModInt()._setval((lint)val_ * x.inv().val() % md);\n    }\n\
    \    constexpr ModInt operator-() const { return ModInt()._setval(md - val_);\
    \ }\n    constexpr ModInt &operator+=(const ModInt &x) { return *this = *this\
    \ + x; }\n    constexpr ModInt &operator-=(const ModInt &x) { return *this = *this\
    \ - x; }\n    constexpr ModInt &operator*=(const ModInt &x) { return *this = *this\
    \ * x; }\n    constexpr ModInt &operator/=(const ModInt &x) { return *this = *this\
    \ / x; }\n    friend constexpr ModInt operator+(lint a, const ModInt &x) { return\
    \ ModInt(a) + x; }\n    friend constexpr ModInt operator-(lint a, const ModInt\
    \ &x) { return ModInt(a) - x; }\n    friend constexpr ModInt operator*(lint a,\
    \ const ModInt &x) { return ModInt(a) * x; }\n    friend constexpr ModInt operator/(lint\
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
    \        } else {\n            return this->pow(md - 2);\n        }\n    }\n \
    \   constexpr ModInt fac() const {\n        while (this->val_ >= int(facs.size()))\
    \ _precalculation(facs.size() * 2);\n        return facs[this->val_];\n    }\n\
    \    constexpr ModInt facinv() const {\n        while (this->val_ >= int(facs.size()))\
    \ _precalculation(facs.size() * 2);\n        return facinvs[this->val_];\n   \
    \ }\n    constexpr ModInt doublefac() const {\n        lint k = (this->val_ +\
    \ 1) / 2;\n        return (this->val_ & 1) ? ModInt(k * 2).fac() / (ModInt(2).pow(k)\
    \ * ModInt(k).fac())\n                                : ModInt(k).fac() * ModInt(2).pow(k);\n\
    \    }\n\n    constexpr ModInt nCr(int r) const {\n        if (r < 0 or this->val_\
    \ < r) return ModInt(0);\n        return this->fac() * (*this - r).facinv() *\
    \ ModInt(r).facinv();\n    }\n\n    constexpr ModInt nPr(int r) const {\n    \
    \    if (r < 0 or this->val_ < r) return ModInt(0);\n        return this->fac()\
    \ * (*this - r).facinv();\n    }\n\n    static ModInt binom(int n, int r) {\n\
    \        static long long bruteforce_times = 0;\n\n        if (r < 0 or n < r)\
    \ return ModInt(0);\n        if (n <= bruteforce_times or n < (int)facs.size())\
    \ return ModInt(n).nCr(r);\n\n        r = std::min(r, n - r);\n\n        ModInt\
    \ ret = ModInt(r).facinv();\n        for (int i = 0; i < r; ++i) ret *= n - i;\n\
    \        bruteforce_times += r;\n\n        return ret;\n    }\n\n    // Multinomial\
    \ coefficient, (k_1 + k_2 + ... + k_m)! / (k_1! k_2! ... k_m!)\n    // Complexity:\
    \ O(sum(ks))\n    template <class Vec> static ModInt multinomial(const Vec &ks)\
    \ {\n        ModInt ret{1};\n        int sum = 0;\n        for (int k : ks) {\n\
    \            assert(k >= 0);\n            ret *= ModInt(k).facinv(), sum += k;\n\
    \        }\n        return ret * ModInt(sum).fac();\n    }\n\n    // Catalan number,\
    \ C_n = binom(2n, n) / (n + 1)\n    // C_0 = 1, C_1 = 1, C_2 = 2, C_3 = 5, C_4\
    \ = 14, ...\n    // https://oeis.org/A000108\n    // Complexity: O(n)\n    static\
    \ ModInt catalan(int n) {\n        if (n < 0) return ModInt(0);\n        return\
    \ ModInt(n * 2).fac() * ModInt(n + 1).facinv() * ModInt(n).facinv();\n    }\n\n\
    \    ModInt sqrt() const {\n        if (val_ == 0) return 0;\n        if (md ==\
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
    // using mint = ModInt<1000000007>;\n#line 8 \"tree/test/subtree_isomorphism.lc.test.cpp\"\
    \nusing namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \n    int n;\n    cin >> n;\n    tree_isomorphism<ModInt998244353> tree(n);\n\
    \    for (int i = 1, p = -1; i < n; ++i) tree.add_edge(i, (cin >> p, p));\n  \
    \  tree.build_hash(0, 15319159, 181263479);\n\n    vector<pair<tree_isomorphism<ModInt998244353>::DoubleHash,\
    \ int>> info;\n    for (int i = 0; i < n; ++i) info.emplace_back(tree.hash_subtree.at(i),\
    \ i);\n\n    const auto gs = groupby(info);\n    vector<int> ret(n);\n    for\
    \ (int g = 0; g < int(gs.size()); ++g) {\n        for (int i : gs.at(g).second)\
    \ ret.at(i) = g;\n    }\n    cout << gs.size() << '\\n';\n    for (int i = 0;\
    \ i < n; ++i) cout << ret.at(i) << (i + 1 == n ? '\\n' : ' ');\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/rooted_tree_isomorphism_classification\"\
    \n#include \"../tree_isomorphism.hpp\"\n#include \"../../utilities/groupby.hpp\"\
    \n#include \"../../modint.hpp\"\n#include <iostream>\n#include <utility>\n#include\
    \ <vector>\nusing namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \n    int n;\n    cin >> n;\n    tree_isomorphism<ModInt998244353> tree(n);\n\
    \    for (int i = 1, p = -1; i < n; ++i) tree.add_edge(i, (cin >> p, p));\n  \
    \  tree.build_hash(0, 15319159, 181263479);\n\n    vector<pair<tree_isomorphism<ModInt998244353>::DoubleHash,\
    \ int>> info;\n    for (int i = 0; i < n; ++i) info.emplace_back(tree.hash_subtree.at(i),\
    \ i);\n\n    const auto gs = groupby(info);\n    vector<int> ret(n);\n    for\
    \ (int g = 0; g < int(gs.size()); ++g) {\n        for (int i : gs.at(g).second)\
    \ ret.at(i) = g;\n    }\n    cout << gs.size() << '\\n';\n    for (int i = 0;\
    \ i < n; ++i) cout << ret.at(i) << (i + 1 == n ? '\\n' : ' ');\n}\n"
  dependsOn:
  - tree/tree_isomorphism.hpp
  - utilities/groupby.hpp
  - modint.hpp
  isVerificationFile: true
  path: tree/test/subtree_isomorphism.lc.test.cpp
  requiredBy: []
  timestamp: '2023-12-26 21:26:22+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: tree/test/subtree_isomorphism.lc.test.cpp
layout: document
redirect_from:
- /verify/tree/test/subtree_isomorphism.lc.test.cpp
- /verify/tree/test/subtree_isomorphism.lc.test.cpp.html
title: tree/test/subtree_isomorphism.lc.test.cpp
---
