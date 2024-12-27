---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: data_structure/test/binary_trie.test.cpp
    title: data_structure/test/binary_trie.test.cpp
  - icon: ':heavy_check_mark:'
    path: data_structure/test/binary_trie.yuki2977.test.cpp
    title: data_structure/test/binary_trie.yuki2977.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"data_structure/binary_trie.hpp\"\n#include <vector>\n\n\
    template <class Int, class Count = int> struct BinaryTrie {\n    int maxD;\n \
    \   std::vector<Count> deg, subtree_sum;\n    std::vector<int> ch0, ch1, par;\n\
    \n    int _new_node(int id_par) {\n        deg.emplace_back(Count());\n      \
    \  subtree_sum.emplace_back(Count());\n        ch0.emplace_back(-1);\n       \
    \ ch1.emplace_back(-1);\n        par.emplace_back(id_par);\n        return (int)ch0.size()\
    \ - 1;\n    }\n\n    BinaryTrie(int maxD = 0) : maxD(maxD) { _new_node(-1); }\n\
    \n    // Return index of x.\n    // Create nodes to locate x if needed.\n    int\
    \ _get_create_index(Int x) {\n        int now = 0;\n        for (int d = maxD\
    \ - 1; d >= 0; --d) {\n            int nxt = ((x >> d) & 1) ? ch1[now] : ch0[now];\n\
    \            if (nxt == -1) {\n                nxt = _new_node(now);\n       \
    \         (((x >> d) & 1) ? ch1[now] : ch0[now]) = nxt;\n            }\n     \
    \       now = nxt;\n        }\n        return now;\n    }\n\n    // Return node\
    \ index of x.\n    // Return -1 if x is not in trie.\n    int _get_index(Int x)\
    \ const {\n        int now = 0;\n        for (int d = maxD - 1; d >= 0; --d) {\n\
    \            now = ((x >> d) & 1) ? ch1[now] : ch0[now];\n            if (now\
    \ == -1) return -1;\n        }\n        return now;\n    }\n\n    // insert x\n\
    \    void insert(Int x, Count c = Count(1)) {\n        int now = _get_create_index(x);\n\
    \        deg[now] += c;\n        while (now >= 0) subtree_sum[now] += c, now =\
    \ par[now];\n    }\n\n    // delete x if exists\n    void erase(Int x) {\n   \
    \     int now = _get_index(x);\n        if (now >= 0 and deg[now] != 0) {\n  \
    \          Count r = deg[now];\n            deg[now] = 0;\n            while (now\
    \ >= 0) subtree_sum[now] -= r, now = par[now];\n        }\n    }\n\n    Count\
    \ count(Int x) const {\n        int now = _get_index(x);\n        return now ==\
    \ -1 ? Count() : deg[now];\n    }\n\n    bool contains(Int x) const { return count(x)\
    \ > Count(); }\n\n    // min(y ^ x) for y in trie\n    Int xor_min(Int x) const\
    \ {\n        Int ret = 0;\n        int now = 0;\n        if (!subtree_sum[now])\
    \ return -1;\n        for (int d = maxD - 1; d >= 0; d--) {\n            int y\
    \ = ((x >> d) & 1) ? ch1[now] : ch0[now];\n            if (y != -1 and subtree_sum[y])\
    \ {\n                now = y;\n            } else {\n                ret += Int(1)\
    \ << d, now = ch0[now] ^ ch1[now] ^ y;\n            }\n        }\n        return\
    \ ret;\n    }\n\n    // Count elements y such that x ^ y < thres\n    Count count_less_xor(Int\
    \ x, Int thres) const {\n        Count ret = Count();\n        int now = 0;\n\n\
    \        for (int d = maxD - 1; d >= 0; d--) {\n            if (now == -1) break;\n\
    \n            const bool bit_x = (x >> d) & 1;\n\n            if ((thres >> d)\
    \ & 1) {\n                const int child = bit_x ? ch1[now] : ch0[now];\n   \
    \             if (child != -1) ret += subtree_sum[child];\n\n                now\
    \ = bit_x ? ch0[now] : ch1[now];\n            } else {\n                now =\
    \ bit_x ? ch1[now] : ch0[now];\n            }\n        }\n\n        return ret;\n\
    \    }\n};\n"
  code: "#pragma once\n#include <vector>\n\ntemplate <class Int, class Count = int>\
    \ struct BinaryTrie {\n    int maxD;\n    std::vector<Count> deg, subtree_sum;\n\
    \    std::vector<int> ch0, ch1, par;\n\n    int _new_node(int id_par) {\n    \
    \    deg.emplace_back(Count());\n        subtree_sum.emplace_back(Count());\n\
    \        ch0.emplace_back(-1);\n        ch1.emplace_back(-1);\n        par.emplace_back(id_par);\n\
    \        return (int)ch0.size() - 1;\n    }\n\n    BinaryTrie(int maxD = 0) :\
    \ maxD(maxD) { _new_node(-1); }\n\n    // Return index of x.\n    // Create nodes\
    \ to locate x if needed.\n    int _get_create_index(Int x) {\n        int now\
    \ = 0;\n        for (int d = maxD - 1; d >= 0; --d) {\n            int nxt = ((x\
    \ >> d) & 1) ? ch1[now] : ch0[now];\n            if (nxt == -1) {\n          \
    \      nxt = _new_node(now);\n                (((x >> d) & 1) ? ch1[now] : ch0[now])\
    \ = nxt;\n            }\n            now = nxt;\n        }\n        return now;\n\
    \    }\n\n    // Return node index of x.\n    // Return -1 if x is not in trie.\n\
    \    int _get_index(Int x) const {\n        int now = 0;\n        for (int d =\
    \ maxD - 1; d >= 0; --d) {\n            now = ((x >> d) & 1) ? ch1[now] : ch0[now];\n\
    \            if (now == -1) return -1;\n        }\n        return now;\n    }\n\
    \n    // insert x\n    void insert(Int x, Count c = Count(1)) {\n        int now\
    \ = _get_create_index(x);\n        deg[now] += c;\n        while (now >= 0) subtree_sum[now]\
    \ += c, now = par[now];\n    }\n\n    // delete x if exists\n    void erase(Int\
    \ x) {\n        int now = _get_index(x);\n        if (now >= 0 and deg[now] !=\
    \ 0) {\n            Count r = deg[now];\n            deg[now] = 0;\n         \
    \   while (now >= 0) subtree_sum[now] -= r, now = par[now];\n        }\n    }\n\
    \n    Count count(Int x) const {\n        int now = _get_index(x);\n        return\
    \ now == -1 ? Count() : deg[now];\n    }\n\n    bool contains(Int x) const { return\
    \ count(x) > Count(); }\n\n    // min(y ^ x) for y in trie\n    Int xor_min(Int\
    \ x) const {\n        Int ret = 0;\n        int now = 0;\n        if (!subtree_sum[now])\
    \ return -1;\n        for (int d = maxD - 1; d >= 0; d--) {\n            int y\
    \ = ((x >> d) & 1) ? ch1[now] : ch0[now];\n            if (y != -1 and subtree_sum[y])\
    \ {\n                now = y;\n            } else {\n                ret += Int(1)\
    \ << d, now = ch0[now] ^ ch1[now] ^ y;\n            }\n        }\n        return\
    \ ret;\n    }\n\n    // Count elements y such that x ^ y < thres\n    Count count_less_xor(Int\
    \ x, Int thres) const {\n        Count ret = Count();\n        int now = 0;\n\n\
    \        for (int d = maxD - 1; d >= 0; d--) {\n            if (now == -1) break;\n\
    \n            const bool bit_x = (x >> d) & 1;\n\n            if ((thres >> d)\
    \ & 1) {\n                const int child = bit_x ? ch1[now] : ch0[now];\n   \
    \             if (child != -1) ret += subtree_sum[child];\n\n                now\
    \ = bit_x ? ch0[now] : ch1[now];\n            } else {\n                now =\
    \ bit_x ? ch1[now] : ch0[now];\n            }\n        }\n\n        return ret;\n\
    \    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/binary_trie.hpp
  requiredBy: []
  timestamp: '2024-12-07 22:13:21+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - data_structure/test/binary_trie.test.cpp
  - data_structure/test/binary_trie.yuki2977.test.cpp
documentation_of: data_structure/binary_trie.hpp
layout: document
title: Binary trie
---

非負整数の集合や多重集合に対する一部のクエリを効率的に行うためのデータ構造．

## 使用方法

```cpp
using Key = int;
using Count = int;
const int D = 30;  // Key の桁数

BinaryTrie<Key, Count> trie(D);

for (int a : A) trie.insert(a);

Key t;
Count n = trie.count_less_xor(a, t);  // a ^ x < t を満たす x （x は現在存在する値）を数える

Key v = bt.xor_min(t);  // t ^ x （x は現在存在する値）の最小値を求める
```

## 問題例

- [Library Checker: Set Xor-Min](https://judge.yosupo.jp/problem/set_xor_min)
- [No.2977 Kth Xor Pair - yukicoder](https://yukicoder.me/problems/no/2977)
