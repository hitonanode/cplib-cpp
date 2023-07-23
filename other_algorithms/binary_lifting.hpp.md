---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: other_algorithms/test/binary_lifting.yuki1013.test.cpp
    title: other_algorithms/test/binary_lifting.yuki1013.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"other_algorithms/binary_lifting.hpp\"\n#include <cassert>\n\
    #include <vector>\n\n// Binary lifting (Doubling) on functional graphs\ntemplate\
    \ <class S, S (*op)(S, S)> class binary_lifting {\n    int n = 0;\n    std::vector<std::vector<int>>\
    \ _nexts;\n    std::vector<std::vector<S>> _prods;\n\n    void build_next() {\n\
    \        std::vector<int> _next(n);\n        std::vector<S> _prod(n);\n\n    \
    \    for (int i = 0; i < n; ++i) {\n            if (int j = _nexts.back().at(i);\
    \ isin(j)) {\n                _next.at(i) = _nexts.back().at(j);\n           \
    \     _prod.at(i) = op(_prods.back().at(i), _prods.back().at(j));\n          \
    \  } else {\n                _next.at(i) = j;\n                _prod.at(i) = _prods.back().at(i);\n\
    \            }\n        }\n\n        _nexts.emplace_back(std::move(_next));\n\
    \        _prods.emplace_back(std::move(_prod));\n    }\n\n    inline bool isin(int\
    \ i) const noexcept { return 0 <= i and i < n; }\n\npublic:\n    // (up to) 2^d\
    \ steps from `s`\n    // Complexity: O(d) (Already precalculated) / O(nd) (First\
    \ time)\n    int pow_next(int s, int d) {\n        assert(isin(s));\n        while\
    \ (int(_nexts.size()) <= d) build_next();\n        return _nexts.at(d).at(s);\n\
    \    }\n\n    // Product of (up to) 2^d elements from `s`\n    const S &pow_prod(int\
    \ s, int d) {\n        assert(isin(s));\n        while (int(_nexts.size()) <=\
    \ d) build_next();\n        return _prods.at(d).at(s);\n    }\n\n    binary_lifting()\
    \ = default;\n    binary_lifting(const std::vector<int> &g, const std::vector<S>\
    \ &w)\n        : n(g.size()), _nexts(1, g), _prods(1, w) {\n        assert(g.size()\
    \ == w.size());\n    }\n\n    // (up to) k steps from `s`\n    template <class\
    \ Int> int kth_next(int s, Int k) {\n        for (int d = 0; k > 0 and isin(s);\
    \ ++d, k >>= 1) {\n            if (k & 1) s = pow_next(s, d);\n        }\n   \
    \     return s;\n    }\n\n    // Product of (up to) `len` elements from `s`\n\
    \    template <class Int> S prod(int s, Int len) {\n        assert(isin(s));\n\
    \        assert(len > 0);\n        int d = 0;\n        while (!(len & 1)) ++d,\
    \ len /= 2;\n\n        S ret = pow_prod(s, d);\n        s = pow_next(s, d);\n\
    \        for (++d, len /= 2; len and isin(s); ++d, len /= 2) {\n            if\
    \ (len & 1) {\n                ret = op(ret, pow_prod(s, d));\n              \
    \  s = pow_next(s, d);\n            }\n        }\n        return ret;\n    }\n\
    \n    // `start` \u304B\u3089\u51FA\u767A\u3057\u3066\u300C`left_goal` \u4EE5\u4E0B\
    \u307E\u305F\u306F `right_goal` \u4EE5\u4E0A\u300D\u306B\u5230\u9054\u3059\u308B\
    \u307E\u3067\u306E\u30B9\u30C6\u30C3\u30D7\u6570\n    // \u5358\u8ABF\u6027\u304C\
    \u5FC5\u8981\n    int distance_monotone(int start, int left_goal, int right_goal)\
    \ {\n        assert(isin(start));\n\n        if (start <= left_goal or right_goal\
    \ <= start) return 0;\n\n        int d = 0;\n        while (left_goal < pow_next(start,\
    \ d) and pow_next(start, d) < right_goal) {\n            if ((1 << d) >= n) return\
    \ -1;\n            ++d;\n        }\n\n        int ret = 0, cur = start;\n    \
    \    for (--d; d >= 0; --d) {\n            if (int nxt = pow_next(cur, d); left_goal\
    \ < nxt and nxt < right_goal) {\n                ret += 1 << d, cur = nxt;\n \
    \           }\n        }\n\n        return ret + 1;\n    }\n\n    template <class\
    \ F> long long max_length(const int s, F f, const int maxd = 60) {\n        assert(isin(s));\n\
    \        int d = 0;\n        while (d <= maxd and f(pow_prod(s, d))) {\n     \
    \       if (!isin(pow_next(s, d))) return 1LL << maxd;\n            ++d;\n   \
    \     }\n        if (d > maxd) return 1LL << maxd;\n\n        --d;\n\n       \
    \ int cur = pow_next(s, d);\n        long long len = 1LL << d;\n        S p =\
    \ pow_prod(s, d);\n\n        for (int e = d - 1; e >= 0; --e) {\n            if\
    \ (S nextp = op(p, pow_prod(cur, e)); f(nextp)) {\n                std::swap(p,\
    \ nextp);\n                cur = pow_next(cur, e);\n                len += 1LL\
    \ << e;\n            }\n        }\n\n        return len;\n    }\n};\n"
  code: "#pragma once\n#include <cassert>\n#include <vector>\n\n// Binary lifting\
    \ (Doubling) on functional graphs\ntemplate <class S, S (*op)(S, S)> class binary_lifting\
    \ {\n    int n = 0;\n    std::vector<std::vector<int>> _nexts;\n    std::vector<std::vector<S>>\
    \ _prods;\n\n    void build_next() {\n        std::vector<int> _next(n);\n   \
    \     std::vector<S> _prod(n);\n\n        for (int i = 0; i < n; ++i) {\n    \
    \        if (int j = _nexts.back().at(i); isin(j)) {\n                _next.at(i)\
    \ = _nexts.back().at(j);\n                _prod.at(i) = op(_prods.back().at(i),\
    \ _prods.back().at(j));\n            } else {\n                _next.at(i) = j;\n\
    \                _prod.at(i) = _prods.back().at(i);\n            }\n        }\n\
    \n        _nexts.emplace_back(std::move(_next));\n        _prods.emplace_back(std::move(_prod));\n\
    \    }\n\n    inline bool isin(int i) const noexcept { return 0 <= i and i < n;\
    \ }\n\npublic:\n    // (up to) 2^d steps from `s`\n    // Complexity: O(d) (Already\
    \ precalculated) / O(nd) (First time)\n    int pow_next(int s, int d) {\n    \
    \    assert(isin(s));\n        while (int(_nexts.size()) <= d) build_next();\n\
    \        return _nexts.at(d).at(s);\n    }\n\n    // Product of (up to) 2^d elements\
    \ from `s`\n    const S &pow_prod(int s, int d) {\n        assert(isin(s));\n\
    \        while (int(_nexts.size()) <= d) build_next();\n        return _prods.at(d).at(s);\n\
    \    }\n\n    binary_lifting() = default;\n    binary_lifting(const std::vector<int>\
    \ &g, const std::vector<S> &w)\n        : n(g.size()), _nexts(1, g), _prods(1,\
    \ w) {\n        assert(g.size() == w.size());\n    }\n\n    // (up to) k steps\
    \ from `s`\n    template <class Int> int kth_next(int s, Int k) {\n        for\
    \ (int d = 0; k > 0 and isin(s); ++d, k >>= 1) {\n            if (k & 1) s = pow_next(s,\
    \ d);\n        }\n        return s;\n    }\n\n    // Product of (up to) `len`\
    \ elements from `s`\n    template <class Int> S prod(int s, Int len) {\n     \
    \   assert(isin(s));\n        assert(len > 0);\n        int d = 0;\n        while\
    \ (!(len & 1)) ++d, len /= 2;\n\n        S ret = pow_prod(s, d);\n        s =\
    \ pow_next(s, d);\n        for (++d, len /= 2; len and isin(s); ++d, len /= 2)\
    \ {\n            if (len & 1) {\n                ret = op(ret, pow_prod(s, d));\n\
    \                s = pow_next(s, d);\n            }\n        }\n        return\
    \ ret;\n    }\n\n    // `start` \u304B\u3089\u51FA\u767A\u3057\u3066\u300C`left_goal`\
    \ \u4EE5\u4E0B\u307E\u305F\u306F `right_goal` \u4EE5\u4E0A\u300D\u306B\u5230\u9054\
    \u3059\u308B\u307E\u3067\u306E\u30B9\u30C6\u30C3\u30D7\u6570\n    // \u5358\u8ABF\
    \u6027\u304C\u5FC5\u8981\n    int distance_monotone(int start, int left_goal,\
    \ int right_goal) {\n        assert(isin(start));\n\n        if (start <= left_goal\
    \ or right_goal <= start) return 0;\n\n        int d = 0;\n        while (left_goal\
    \ < pow_next(start, d) and pow_next(start, d) < right_goal) {\n            if\
    \ ((1 << d) >= n) return -1;\n            ++d;\n        }\n\n        int ret =\
    \ 0, cur = start;\n        for (--d; d >= 0; --d) {\n            if (int nxt =\
    \ pow_next(cur, d); left_goal < nxt and nxt < right_goal) {\n                ret\
    \ += 1 << d, cur = nxt;\n            }\n        }\n\n        return ret + 1;\n\
    \    }\n\n    template <class F> long long max_length(const int s, F f, const\
    \ int maxd = 60) {\n        assert(isin(s));\n        int d = 0;\n        while\
    \ (d <= maxd and f(pow_prod(s, d))) {\n            if (!isin(pow_next(s, d)))\
    \ return 1LL << maxd;\n            ++d;\n        }\n        if (d > maxd) return\
    \ 1LL << maxd;\n\n        --d;\n\n        int cur = pow_next(s, d);\n        long\
    \ long len = 1LL << d;\n        S p = pow_prod(s, d);\n\n        for (int e =\
    \ d - 1; e >= 0; --e) {\n            if (S nextp = op(p, pow_prod(cur, e)); f(nextp))\
    \ {\n                std::swap(p, nextp);\n                cur = pow_next(cur,\
    \ e);\n                len += 1LL << e;\n            }\n        }\n\n        return\
    \ len;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: other_algorithms/binary_lifting.hpp
  requiredBy: []
  timestamp: '2023-07-23 19:53:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - other_algorithms/test/binary_lifting.yuki1013.test.cpp
documentation_of: other_algorithms/binary_lifting.hpp
layout: document
title: "Binary lifting / doubling \uFF08\u30C0\u30D6\u30EA\u30F3\u30B0\uFF09"
---

Functional graph 上のダブリングライブラリ．

## 使用方法

### `binary_lifting(const std::vector<int> &g, const std::vector<S> &w)`

コンストラクタ．引数として $g(0), \ldots, g(n - 1)$ および $w(0), \ldots, w(n - 1)$ を与える．型 `S` は演算 `S op(S, S)` が結合法則を満たせばなんでもよい．

直感的には，各頂点 $i = 0, \ldots, n - 1$ について $i$ から頂点 $g(i)$ への重み $w(i)$ の有向辺が張られている functional graph に相当する． $g(i)$ の値は $0$ 未満や $n$ 以上でも構わない（下記の各関数は， $[0, n)$ の範囲外の頂点 $i$ からは $i$ 自身への重み $e$ の自己ループが生えている，と解釈するとつじつまが合うように設計されている）．

### `int kth_next(int s, Int k)`

$g^k (s)$ の値（途中で $[0, n)$ の範囲外に出る場合はその値）を前計算 $O(n \log k)$ ・クエリ $O(\log k)$ で返す．

#### `int pow_next(int s, int d)`

特に $g^{2^d}(s)$ の値を返す．前計算が済んでいればクエリ $O(1)$．

### `S prod(int s, Int len)`

列 $(s, g(s), \ldots, g^{\mathrm{len} - 1} (s))$ の各要素 $x$ に関する値 $w(x)$ をとり，これら全ての積をとる（途中で $[0, n)$ の範囲外に出る場合，それ以降の要素は無視される）．

#### `const S &pow_prod(int s, int d)`

特に $w(s) \cdot w(g(s)) \cdot \ldots \cdot w(g^{2^d - 1}(s))$ を返す．前計算が済んでいればクエリ $O(1)$．

### `int distance_monotone(int start, int left_goal, int right_goal)`

$g^k (s)$ の値が初めて `left_goal` 以下または `right_goal` 以上になる $k$ を計算する．この条件が満たされることはない場合は `-1` を返す．

この条件に関する単調性が必要． $O(n \log n)$ の前計算が済んでいればクエリ $O(\log n)$．

### `long long max_length(int s, F f, int maxd = 60)`

`f(prod(s, len))` が `true` と評価される $2^{\mathrm{maxd}}$ 以下の最大の `len` を返す． `f(prod(s, len))` の単調性が必要．

## 問題例

- [No.1013 〇マス進む - yukicoder](https://yukicoder.me/problems/no/1013)
- [No.2242 Cities and Teleporters - yukicoder](https://yukicoder.me/problems/no/2242)
