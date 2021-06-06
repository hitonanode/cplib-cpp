---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: modint.hpp
    title: modint.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - http://xorshift.di.unimi.it/splitmix64.c
    - https://atcoder.jp/contests/nikkei2019-2-final/submissions/9044698
    - https://atcoder.jp/contests/nikkei2019-2-final/submissions/9044745
    - https://codeforces.com/blog/entry/62393
    - https://snuke.hatenablog.com/entry/2017/02/03/054210
  bundledCode: "#line 2 \"modint.hpp\"\n#include <iostream>\n#include <set>\n#include\
    \ <vector>\n\n// CUT begin\ntemplate <int md> struct ModInt {\n#if __cplusplus\
    \ >= 201402L\n#define MDCONST constexpr\n#else\n#define MDCONST\n#endif\n    using\
    \ lint = long long;\n    MDCONST static int mod() { return md; }\n    static int\
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
    \ primitive_root;\n    }\n    int val;\n    MDCONST ModInt() : val(0) {}\n   \
    \ MDCONST ModInt &_setval(lint v) { return val = (v >= md ? v - md : v), *this;\
    \ }\n    MDCONST ModInt(lint v) { _setval(v % md + md); }\n    MDCONST explicit\
    \ operator bool() const { return val != 0; }\n    MDCONST ModInt operator+(const\
    \ ModInt &x) const { return ModInt()._setval((lint)val + x.val); }\n    MDCONST\
    \ ModInt operator-(const ModInt &x) const { return ModInt()._setval((lint)val\
    \ - x.val + md); }\n    MDCONST ModInt operator*(const ModInt &x) const { return\
    \ ModInt()._setval((lint)val * x.val % md); }\n    MDCONST ModInt operator/(const\
    \ ModInt &x) const { return ModInt()._setval((lint)val * x.inv() % md); }\n  \
    \  MDCONST ModInt operator-() const { return ModInt()._setval(md - val); }\n \
    \   MDCONST ModInt &operator+=(const ModInt &x) { return *this = *this + x; }\n\
    \    MDCONST ModInt &operator-=(const ModInt &x) { return *this = *this - x; }\n\
    \    MDCONST ModInt &operator*=(const ModInt &x) { return *this = *this * x; }\n\
    \    MDCONST ModInt &operator/=(const ModInt &x) { return *this = *this / x; }\n\
    \    friend MDCONST ModInt operator+(lint a, const ModInt &x) { return ModInt()._setval(a\
    \ % md + x.val); }\n    friend MDCONST ModInt operator-(lint a, const ModInt &x)\
    \ { return ModInt()._setval(a % md - x.val + md); }\n    friend MDCONST ModInt\
    \ operator*(lint a, const ModInt &x) { return ModInt()._setval(a % md * x.val\
    \ % md); }\n    friend MDCONST ModInt operator/(lint a, const ModInt &x) {\n \
    \       return ModInt()._setval(a % md * x.inv() % md);\n    }\n    MDCONST bool\
    \ operator==(const ModInt &x) const { return val == x.val; }\n    MDCONST bool\
    \ operator!=(const ModInt &x) const { return val != x.val; }\n    MDCONST bool\
    \ operator<(const ModInt &x) const { return val < x.val; } // To use std::map<ModInt,\
    \ T>\n    friend std::istream &operator>>(std::istream &is, ModInt &x) {\n   \
    \     lint t;\n        return is >> t, x = ModInt(t), is;\n    }\n    MDCONST\
    \ friend std::ostream &operator<<(std::ostream &os, const ModInt &x) { return\
    \ os << x.val; }\n    MDCONST ModInt pow(lint n) const {\n        ModInt ans =\
    \ 1, tmp = *this;\n        while (n) {\n            if (n & 1) ans *= tmp;\n \
    \           tmp *= tmp, n >>= 1;\n        }\n        return ans;\n    }\n\n  \
    \  static std::vector<ModInt> facs, facinvs, invs;\n    MDCONST static void _precalculation(int\
    \ N) {\n        int l0 = facs.size();\n        if (N > md) N = md;\n        if\
    \ (N <= l0) return;\n        facs.resize(N), facinvs.resize(N), invs.resize(N);\n\
    \        for (int i = l0; i < N; i++) facs[i] = facs[i - 1] * i;\n        facinvs[N\
    \ - 1] = facs.back().pow(md - 2);\n        for (int i = N - 2; i >= l0; i--) facinvs[i]\
    \ = facinvs[i + 1] * (i + 1);\n        for (int i = N - 1; i >= l0; i--) invs[i]\
    \ = facinvs[i] * facs[i - 1];\n    }\n    MDCONST lint inv() const {\n       \
    \ if (this->val < std::min(md >> 1, 1 << 21)) {\n            while (this->val\
    \ >= int(facs.size())) _precalculation(facs.size() * 2);\n            return invs[this->val].val;\n\
    \        } else {\n            return this->pow(md - 2).val;\n        }\n    }\n\
    \    MDCONST ModInt fac() const {\n        while (this->val >= int(facs.size()))\
    \ _precalculation(facs.size() * 2);\n        return facs[this->val];\n    }\n\
    \    MDCONST ModInt facinv() const {\n        while (this->val >= int(facs.size()))\
    \ _precalculation(facs.size() * 2);\n        return facinvs[this->val];\n    }\n\
    \    MDCONST ModInt doublefac() const {\n        lint k = (this->val + 1) / 2;\n\
    \        return (this->val & 1) ? ModInt(k * 2).fac() / (ModInt(2).pow(k) * ModInt(k).fac())\n\
    \                               : ModInt(k).fac() * ModInt(2).pow(k);\n    }\n\
    \    MDCONST ModInt nCr(const ModInt &r) const {\n        return (this->val <\
    \ r.val) ? 0 : this->fac() * (*this - r).facinv() * r.facinv();\n    }\n    MDCONST\
    \ ModInt nPr(const ModInt &r) const {\n        return (this->val < r.val) ? 0\
    \ : this->fac() * (*this - r).facinv();\n    }\n\n    ModInt sqrt() const {\n\
    \        if (val == 0) return 0;\n        if (md == 2) return val;\n        if\
    \ (pow((md - 1) / 2) != 1) return 0;\n        ModInt b = 1;\n        while (b.pow((md\
    \ - 1) / 2) == 1) b += 1;\n        int e = 0, m = md - 1;\n        while (m %\
    \ 2 == 0) m >>= 1, e++;\n        ModInt x = pow((m - 1) / 2), y = (*this) * x\
    \ * x;\n        x *= (*this);\n        ModInt z = b.pow(m);\n        while (y\
    \ != 1) {\n            int j = 0;\n            ModInt t = y;\n            while\
    \ (t != 1) j++, t *= t;\n            z = z.pow(1LL << (e - j - 1));\n        \
    \    x *= z, z *= z, y *= z;\n            e = j;\n        }\n        return ModInt(std::min(x.val,\
    \ md - x.val));\n    }\n};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::facs\
    \ = {1};\ntemplate <int md> std::vector<ModInt<md>> ModInt<md>::facinvs = {1};\n\
    template <int md> std::vector<ModInt<md>> ModInt<md>::invs = {0};\n// using mint\
    \ = ModInt<998244353>;\n// using mint = ModInt<1000000007>;\n#line 3 \"tree/tree_isomorphism.hpp\"\
    \n// #include \"number/modint_runtime.hpp\"\n#include <chrono>\n#include <utility>\n\
    #line 7 \"tree/tree_isomorphism.hpp\"\nusing namespace std;\n\n// CUT begin\n\
    // Tree isomorphism with hashing \uFF08\u30CF\u30C3\u30B7\u30E5\u306B\u3088\u308B\
    \u6728\u306E\u540C\u578B\u5224\u5B9A\uFF09\n// Dependence: ModInt or ModIntRuntime\n\
    // Reference: https://snuke.hatenablog.com/entry/2017/02/03/054210\n// Verified:\
    \ https://atcoder.jp/contests/nikkei2019-2-final/submissions/9044698 (ModInt)\n\
    //           https://atcoder.jp/contests/nikkei2019-2-final/submissions/9044745\
    \ (ModIntRuntime)\nusing mint = ModInt<1000000007>;\n// using mint = ModIntRuntime;\n\
    // int ModIntRuntime::mod = 1000000007;\nusing DoubleHash = pair<mint, mint>;\n\
    struct UndirectedTree {\n    using Edges = vector<vector<int>>; // vector<set<int>>;\n\
    \    int V;\n    Edges e;\n    UndirectedTree(int v) : V(v), e(v) {}\n    void\
    \ add_edge(int u, int v) {\n        e[u].emplace_back(v);\n        e[v].emplace_back(u);\n\
    \    }\n\n    static uint64_t splitmix64(uint64_t x) {\n        // https://codeforces.com/blog/entry/62393\
    \ http://xorshift.di.unimi.it/splitmix64.c\n        x += 0x9e3779b97f4a7c15;\n\
    \        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;\n        x = (x ^ (x >> 27))\
    \ * 0x94d049bb133111eb;\n        return x ^ (x >> 31);\n    }\n    DoubleHash\
    \ get_hash(DoubleHash x) const {\n        static const uint64_t FIXED_RANDOM =\
    \ chrono::steady_clock::now().time_since_epoch().count();\n        return {splitmix64(x.first.val\
    \ + FIXED_RANDOM), splitmix64(x.second.val + FIXED_RANDOM)};\n    }\n\n    static\
    \ void add_hash(DoubleHash &l, const DoubleHash &r) { l.first += r.first, l.second\
    \ += r.second; }\n    static DoubleHash subtract_hash(const DoubleHash &l, const\
    \ DoubleHash &r) {\n        return {l.first - r.first, l.second - r.second};\n\
    \    }\n\n    vector<DoubleHash> hash;         // hash of the tree, each node\
    \ regarded as root\n    vector<DoubleHash> hash_subtree; // hash of the subtree\n\
    \    vector<DoubleHash> hash_par;     // hash of the subtree whose root is parent[i],\
    \ not containing i\n    DoubleHash hash_p;               // \\in [1, hmod), should\
    \ be set randomly\n    DoubleHash hash_dfs1_(int now, int prv) {\n        hash_subtree[now]\
    \ = hash_p;\n        for (auto nxt : e[now])\n            if (nxt != prv) add_hash(hash_subtree[now],\
    \ hash_dfs1_(nxt, now));\n        return get_hash(hash_subtree[now]);\n    }\n\
    \    void hash_dfs2_(int now, int prv) {\n        add_hash(hash[now], hash_subtree[now]);\n\
    \        if (prv >= 0) hash_par[now] = subtract_hash(hash[prv], get_hash(hash_subtree[now]));\n\
    \        for (auto nxt : e[now])\n            if (nxt != prv) {\n            \
    \    DoubleHash tmp = subtract_hash(hash[now], get_hash(hash_subtree[nxt]));\n\
    \                add_hash(hash[nxt], get_hash(tmp));\n                hash_dfs2_(nxt,\
    \ now);\n            }\n    }\n    void build_hash(int root, int p1, int p2) {\n\
    \        hash_p = make_pair(p1, p2);\n        hash.resize(V), hash_subtree.resize(V),\
    \ hash_par.resize(V);\n        hash_dfs1_(root, -1);\n        hash_dfs2_(root,\
    \ -1);\n    }\n};\n"
  code: "#pragma once\n#include \"modint.hpp\"\n// #include \"number/modint_runtime.hpp\"\
    \n#include <chrono>\n#include <utility>\n#include <vector>\nusing namespace std;\n\
    \n// CUT begin\n// Tree isomorphism with hashing \uFF08\u30CF\u30C3\u30B7\u30E5\
    \u306B\u3088\u308B\u6728\u306E\u540C\u578B\u5224\u5B9A\uFF09\n// Dependence: ModInt\
    \ or ModIntRuntime\n// Reference: https://snuke.hatenablog.com/entry/2017/02/03/054210\n\
    // Verified: https://atcoder.jp/contests/nikkei2019-2-final/submissions/9044698\
    \ (ModInt)\n//           https://atcoder.jp/contests/nikkei2019-2-final/submissions/9044745\
    \ (ModIntRuntime)\nusing mint = ModInt<1000000007>;\n// using mint = ModIntRuntime;\n\
    // int ModIntRuntime::mod = 1000000007;\nusing DoubleHash = pair<mint, mint>;\n\
    struct UndirectedTree {\n    using Edges = vector<vector<int>>; // vector<set<int>>;\n\
    \    int V;\n    Edges e;\n    UndirectedTree(int v) : V(v), e(v) {}\n    void\
    \ add_edge(int u, int v) {\n        e[u].emplace_back(v);\n        e[v].emplace_back(u);\n\
    \    }\n\n    static uint64_t splitmix64(uint64_t x) {\n        // https://codeforces.com/blog/entry/62393\
    \ http://xorshift.di.unimi.it/splitmix64.c\n        x += 0x9e3779b97f4a7c15;\n\
    \        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;\n        x = (x ^ (x >> 27))\
    \ * 0x94d049bb133111eb;\n        return x ^ (x >> 31);\n    }\n    DoubleHash\
    \ get_hash(DoubleHash x) const {\n        static const uint64_t FIXED_RANDOM =\
    \ chrono::steady_clock::now().time_since_epoch().count();\n        return {splitmix64(x.first.val\
    \ + FIXED_RANDOM), splitmix64(x.second.val + FIXED_RANDOM)};\n    }\n\n    static\
    \ void add_hash(DoubleHash &l, const DoubleHash &r) { l.first += r.first, l.second\
    \ += r.second; }\n    static DoubleHash subtract_hash(const DoubleHash &l, const\
    \ DoubleHash &r) {\n        return {l.first - r.first, l.second - r.second};\n\
    \    }\n\n    vector<DoubleHash> hash;         // hash of the tree, each node\
    \ regarded as root\n    vector<DoubleHash> hash_subtree; // hash of the subtree\n\
    \    vector<DoubleHash> hash_par;     // hash of the subtree whose root is parent[i],\
    \ not containing i\n    DoubleHash hash_p;               // \\in [1, hmod), should\
    \ be set randomly\n    DoubleHash hash_dfs1_(int now, int prv) {\n        hash_subtree[now]\
    \ = hash_p;\n        for (auto nxt : e[now])\n            if (nxt != prv) add_hash(hash_subtree[now],\
    \ hash_dfs1_(nxt, now));\n        return get_hash(hash_subtree[now]);\n    }\n\
    \    void hash_dfs2_(int now, int prv) {\n        add_hash(hash[now], hash_subtree[now]);\n\
    \        if (prv >= 0) hash_par[now] = subtract_hash(hash[prv], get_hash(hash_subtree[now]));\n\
    \        for (auto nxt : e[now])\n            if (nxt != prv) {\n            \
    \    DoubleHash tmp = subtract_hash(hash[now], get_hash(hash_subtree[nxt]));\n\
    \                add_hash(hash[nxt], get_hash(tmp));\n                hash_dfs2_(nxt,\
    \ now);\n            }\n    }\n    void build_hash(int root, int p1, int p2) {\n\
    \        hash_p = make_pair(p1, p2);\n        hash.resize(V), hash_subtree.resize(V),\
    \ hash_par.resize(V);\n        hash_dfs1_(root, -1);\n        hash_dfs2_(root,\
    \ -1);\n    }\n};\n"
  dependsOn:
  - modint.hpp
  isVerificationFile: false
  path: tree/tree_isomorphism.hpp
  requiredBy: []
  timestamp: '2021-06-06 15:23:40+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: tree/tree_isomorphism.hpp
layout: document
redirect_from:
- /library/tree/tree_isomorphism.hpp
- /library/tree/tree_isomorphism.hpp.html
title: tree/tree_isomorphism.hpp
---
