---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: other_algorithms/test/doubling.yuki3305.test.cpp
    title: other_algorithms/test/doubling.yuki3305.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://atcoder.jp/contests/arc060/submissions/7039451
  bundledCode: "#line 2 \"other_algorithms/doubling.hpp\"\n#include <cassert>\n#include\
    \ <vector>\n\n// Binary lifting / `Doubling`\n// Complexity: O(NlogN) precalculation\
    \ / O(logN) per query\n// https://atcoder.jp/contests/arc060/submissions/7039451\n\
    struct BinaryLifting {\n    int N, lgD;\n\n    bool is_valid(int idx) const {\
    \ return 0 <= idx and idx < N; }\n\n    std::vector<std::vector<int>> mat;\n \
    \   BinaryLifting() : N(0), lgD(0) {}\n    BinaryLifting(const std::vector<int>\
    \ &to, int lgd = 0) : N(to.size()), lgD(lgd) {\n        while ((1LL << lgD) <\
    \ N) lgD++;\n        mat.assign(lgD, std::vector<int>(N));\n        mat[0] = to;\n\
    \n        for (int d = 0; d < lgD - 1; d++) {\n            for (int i = 0; i <\
    \ N; i++) {\n                mat[d + 1][i] = mat[d][is_valid(mat[d][i]) ? mat[d][i]\
    \ : i];\n            }\n        }\n    }\n\n    int kth_next(int now, long long\
    \ k) const {\n        assert(k >= 0);\n        assert(k < (1LL << lgD));\n   \
    \     for (int d = 0; k and is_valid(now); d++, k >>= 1) {\n            if (k\
    \ & 1) now = mat[d][now];\n        }\n        return now;\n    }\n\n    // Distance\
    \ from l to [r, \\infty)\n    // Requirement: mat[0][i] >= r (i = r, r + 1, ...)\
    \ (monotone)\n    int distance(int l, int r) const {\n        if (l >= r) return\
    \ 0;\n        int ret = 0;\n        for (int d = lgD - 1; d >= 0; d--) {\n   \
    \         if (mat[d][l] < r and is_valid(mat[d][l])) ret += 1 << d, l = mat[d][l];\n\
    \        }\n\n        if (!is_valid(mat[0][l]) or mat[0][l] >= r) {\n        \
    \    return ret + 1;\n        } else {\n            return -1; // Unable to reach\n\
    \        }\n    }\n};\n"
  code: "#pragma once\n#include <cassert>\n#include <vector>\n\n// Binary lifting\
    \ / `Doubling`\n// Complexity: O(NlogN) precalculation / O(logN) per query\n//\
    \ https://atcoder.jp/contests/arc060/submissions/7039451\nstruct BinaryLifting\
    \ {\n    int N, lgD;\n\n    bool is_valid(int idx) const { return 0 <= idx and\
    \ idx < N; }\n\n    std::vector<std::vector<int>> mat;\n    BinaryLifting() :\
    \ N(0), lgD(0) {}\n    BinaryLifting(const std::vector<int> &to, int lgd = 0)\
    \ : N(to.size()), lgD(lgd) {\n        while ((1LL << lgD) < N) lgD++;\n      \
    \  mat.assign(lgD, std::vector<int>(N));\n        mat[0] = to;\n\n        for\
    \ (int d = 0; d < lgD - 1; d++) {\n            for (int i = 0; i < N; i++) {\n\
    \                mat[d + 1][i] = mat[d][is_valid(mat[d][i]) ? mat[d][i] : i];\n\
    \            }\n        }\n    }\n\n    int kth_next(int now, long long k) const\
    \ {\n        assert(k >= 0);\n        assert(k < (1LL << lgD));\n        for (int\
    \ d = 0; k and is_valid(now); d++, k >>= 1) {\n            if (k & 1) now = mat[d][now];\n\
    \        }\n        return now;\n    }\n\n    // Distance from l to [r, \\infty)\n\
    \    // Requirement: mat[0][i] >= r (i = r, r + 1, ...) (monotone)\n    int distance(int\
    \ l, int r) const {\n        if (l >= r) return 0;\n        int ret = 0;\n   \
    \     for (int d = lgD - 1; d >= 0; d--) {\n            if (mat[d][l] < r and\
    \ is_valid(mat[d][l])) ret += 1 << d, l = mat[d][l];\n        }\n\n        if\
    \ (!is_valid(mat[0][l]) or mat[0][l] >= r) {\n            return ret + 1;\n  \
    \      } else {\n            return -1; // Unable to reach\n        }\n    }\n\
    };\n"
  dependsOn: []
  isVerificationFile: false
  path: other_algorithms/doubling.hpp
  requiredBy: []
  timestamp: '2025-10-07 09:40:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - other_algorithms/test/doubling.yuki3305.test.cpp
documentation_of: other_algorithms/doubling.hpp
layout: document
title: "Binary lifting / doubling \uFF08\u30C0\u30D6\u30EA\u30F3\u30B0\uFF09"
---

Functional graph 上のダブリングライブラリ． binary_lifting.hpp とは異なり辺に重みなどは載せられない．

## 使用方法

### `BinaryLifting binary_lifting(std::vector<int> to)`

コンストラクタ．引数として $g(0), \ldots, g(n - 1)$ を与える．

直感的には，各頂点 $i = 0, \ldots, n - 1$ について $i$ から頂点 $g(i)$ へ有向辺が張られている functional graph に相当する． $g(i)$ の値は $0$ 未満や $n$ 以上でも構わない（下記の各関数は， $[0, n)$ の範囲外の頂点 $i$ からは $i$ 自身への重み $e$ の自己ループが生えている，と解釈するとつじつまが合うように設計されている）．

### `int kth_next(int s, long long k)`

$g^k (s)$ の値（途中で $[0, n)$ の範囲外に出る場合はその値）を $O(\log k)$ で返す．

### `int distance(int l, int r)`

$g^k (s)$ の値が初めて `r` 以上になる $k$ を計算する．この条件が満たされることはない場合は `-1` を返す．

この条件に関する単調性が必要．

## 問題例

- [No.3305 Shift Sort - yukicoder](https://yukicoder.me/problems/no/3305)
