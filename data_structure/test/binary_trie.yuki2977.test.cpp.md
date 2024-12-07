---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/binary_trie.hpp
    title: Binary trie
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/no/2977
    links:
    - https://yukicoder.me/problems/no/2977
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
    \    }\n};\n#line 2 \"data_structure/test/binary_trie.yuki2977.test.cpp\"\n#define\
    \ PROBLEM \"https://yukicoder.me/problems/no/2977\"\n\n#include <iostream>\nusing\
    \ namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \n    int N;\n    long long K;\n    cin >> N >> K;\n\n    vector<int> A(N);\n\
    \    for (auto &x : A) cin >> x;\n\n    constexpr int D = 30;\n\n    BinaryTrie<int>\
    \ trie(D);\n    for (int a : A) trie.insert(a);\n\n    int lo = 0, hi = 1 << D;\
    \ // [lo, hi)\n    while (lo + 1 < hi) {\n        const int mid = (lo + hi) /\
    \ 2;\n\n        long long cnt = 0;\n        for (int a : A) cnt += trie.count_less_xor(a,\
    \ mid);\n        (cnt >= K * 2 + N ? hi : lo) = mid;\n    }\n\n    cout << lo\
    \ << '\\n';\n}\n"
  code: "#include \"../binary_trie.hpp\"\n#define PROBLEM \"https://yukicoder.me/problems/no/2977\"\
    \n\n#include <iostream>\nusing namespace std;\n\nint main() {\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n\n    int N;\n    long long K;\n    cin >> N >>\
    \ K;\n\n    vector<int> A(N);\n    for (auto &x : A) cin >> x;\n\n    constexpr\
    \ int D = 30;\n\n    BinaryTrie<int> trie(D);\n    for (int a : A) trie.insert(a);\n\
    \n    int lo = 0, hi = 1 << D; // [lo, hi)\n    while (lo + 1 < hi) {\n      \
    \  const int mid = (lo + hi) / 2;\n\n        long long cnt = 0;\n        for (int\
    \ a : A) cnt += trie.count_less_xor(a, mid);\n        (cnt >= K * 2 + N ? hi :\
    \ lo) = mid;\n    }\n\n    cout << lo << '\\n';\n}\n"
  dependsOn:
  - data_structure/binary_trie.hpp
  isVerificationFile: true
  path: data_structure/test/binary_trie.yuki2977.test.cpp
  requiredBy: []
  timestamp: '2024-12-07 22:13:21+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: data_structure/test/binary_trie.yuki2977.test.cpp
layout: document
redirect_from:
- /verify/data_structure/test/binary_trie.yuki2977.test.cpp
- /verify/data_structure/test/binary_trie.yuki2977.test.cpp.html
title: data_structure/test/binary_trie.yuki2977.test.cpp
---
