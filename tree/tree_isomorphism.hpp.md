---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: tree/test/subtree_isomorphism.lc.test.cpp
    title: tree/test/subtree_isomorphism.lc.test.cpp
  - icon: ':heavy_check_mark:'
    path: tree/test/tree_isomorphism.aoj1613.test.cpp
    title: tree/test/tree_isomorphism.aoj1613.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - http://xorshift.di.unimi.it/splitmix64.c
    - https://atcoder.jp/contests/nikkei2019-2-final/submissions/9044698
    - https://atcoder.jp/contests/nikkei2019-2-final/submissions/9044745
    - https://codeforces.com/blog/entry/62393
    - https://snuke.hatenablog.com/entry/2017/02/03/054210
  bundledCode: "#line 2 \"tree/tree_isomorphism.hpp\"\n#include <chrono>\n#include\
    \ <utility>\n#include <vector>\n\n// Tree isomorphism with hashing \uFF08\u30CF\
    \u30C3\u30B7\u30E5\u306B\u3088\u308B\u6728\u306E\u540C\u578B\u5224\u5B9A\uFF09\
    \n// Dependence: ModInt or ModIntRuntime\n// Reference: https://snuke.hatenablog.com/entry/2017/02/03/054210\n\
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
    \ -1);\n    }\n};\n"
  code: "#pragma once\n#include <chrono>\n#include <utility>\n#include <vector>\n\n\
    // Tree isomorphism with hashing \uFF08\u30CF\u30C3\u30B7\u30E5\u306B\u3088\u308B\
    \u6728\u306E\u540C\u578B\u5224\u5B9A\uFF09\n// Dependence: ModInt or ModIntRuntime\n\
    // Reference: https://snuke.hatenablog.com/entry/2017/02/03/054210\n// Verified:\
    \ https://atcoder.jp/contests/nikkei2019-2-final/submissions/9044698 (ModInt)\n\
    //           https://atcoder.jp/contests/nikkei2019-2-final/submissions/9044745\
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
    \ -1);\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: tree/tree_isomorphism.hpp
  requiredBy: []
  timestamp: '2022-05-01 16:11:38+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - tree/test/subtree_isomorphism.lc.test.cpp
  - tree/test/tree_isomorphism.aoj1613.test.cpp
documentation_of: tree/tree_isomorphism.hpp
layout: document
title: "Tree isomrphism \uFF08\u6728\u306E\u540C\u578B\u5224\u5B9A\uFF09"
---

根付き木のハッシュをとる．

## 使用方法

```cpp
tree_isomorphism<mint> tree(N);
for (auto [u, v] : edges) tree.add_edge(u, v);
tree.build_hash(0, 15319159, 181263479);
auto h = tree.hash[r]; // r を根にとったときのハッシュ値
```

## 問題例

- [AtCoder 第二回全国統一プログラミング王決定戦本戦 D - 木、](https://atcoder.jp/contests/nikkei2019-2-final/tasks/nikkei2019_2_final_d)
- [AOJ 1613: Deciphering Characters](https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1613)
