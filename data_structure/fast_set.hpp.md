---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: tree/auxiliary_tree.hpp
    title: "LCA-based auxiliary tree / virtual tree, online \uFF08\"\u865A\u6811\"\
      \uFF09"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: data_structure/test/fast_set.test.cpp
    title: data_structure/test/fast_set.test.cpp
  - icon: ':heavy_check_mark:'
    path: tree/test/auxiliary_tree.yuki901.test.cpp
    title: tree/test/auxiliary_tree.yuki901.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"data_structure/fast_set.hpp\"\n\n#include <cassert>\n#include\
    \ <cstdint>\n#include <vector>\n\n// Sorted set of integers [0, n)\n// Space complexity:\
    \ (64 / 63) n + O(log n) bit\nclass fast_set {\n    static constexpr int B = 64;\n\
    \n    int n;\n    int cnt;\n    std::vector<std::vector<uint64_t>> _d;\n\n   \
    \ static int bsf(uint64_t x) { return __builtin_ctzll(x); }\n    static int bsr(uint64_t\
    \ x) { return 63 - __builtin_clzll(x); }\n\npublic:\n    // 0 \u4EE5\u4E0A n_\
    \ \u672A\u6E80\u306E\u6574\u6570\u304C\u5165\u308C\u3089\u308C\u308B sorted set\
    \ \u3092\u4F5C\u6210\n    fast_set(int n_) : n(n_), cnt(0) {\n        do { n_\
    \ = (n_ + B - 1) / B, _d.push_back(std::vector<uint64_t>(n_)); } while (n_ > 1);\n\
    \    }\n\n    bool contains(int i) const {\n        assert(0 <= i and i < n);\n\
    \        return (_d.front().at(i / B) >> (i % B)) & 1;\n    }\n\n    void insert(int\
    \ i) {\n        assert(0 <= i and i < n);\n        if (contains(i)) return;\n\
    \        ++cnt;\n        for (auto &vec : _d) {\n            bool f = vec.at(i\
    \ / B);\n            vec.at(i / B) |= 1ULL << (i % B), i /= B;\n            if\
    \ (f) break;\n        }\n    }\n\n    void erase(int i) {\n        assert(0 <=\
    \ i and i < n);\n        if (!contains(i)) return;\n        --cnt;\n        for\
    \ (auto &vec : _d) {\n            vec.at(i / B) &= ~(1ULL << (i % B)), i /= B;\n\
    \            if (vec.at(i)) break;\n        }\n    }\n\n    // i \u4EE5\u4E0A\u306E\
    \u6700\u5C0F\u8981\u7D20 \u306A\u3051\u308C\u3070 default_val\n    int next(int\
    \ i, const int default_val) const {\n        assert(0 <= i and i <= n);\n\n  \
    \      for (auto itr = _d.cbegin(); itr != _d.cend(); ++itr, i = i / B + 1) {\n\
    \            if (i / B >= int(itr->size())) break;\n\n            if (auto d =\
    \ itr->at(i / B) >> (i % B); d) {\n                i += bsf(d);\n            \
    \    while (itr != _d.cbegin()) i = i * B + bsf((--itr)->at(i));\n           \
    \     return i;\n            }\n        }\n\n        return default_val;\n   \
    \ }\n    int next(const int i) const { return next(i, n); }\n\n    // i \u4EE5\
    \u4E0B\u306E\u6700\u5C0F\u8981\u7D20 \u306A\u3051\u308C\u3070 default_val\n  \
    \  int prev(int i, int default_val = -1) const {\n        assert(-1 <= i and i\
    \ < n);\n\n        for (auto itr = _d.cbegin(); itr != _d.cend() and i >= 0; ++itr,\
    \ i = i / B - 1) {\n            if (auto d = itr->at(i / B) << (B - 1 - i % B);\
    \ d) {\n                i += bsr(d) - (B - 1);\n                while (itr !=\
    \ _d.cbegin()) i = i * B + bsr((--itr)->at(i));\n                return i;\n \
    \           }\n        }\n\n        return default_val;\n    }\n\n    // return\
    \ minimum element (if exists) or `n` (empty)\n    int min() const { return next(0);\
    \ }\n    // return maximum element (if exists) or `-1` (empty)\n    int max()\
    \ const { return prev(n - 1); }\n    int size() const { return cnt; }\n    bool\
    \ empty() const { return cnt == 0; }\n\n    void clear() {\n        if (!cnt)\
    \ return;\n        cnt = 0;\n        auto rec = [&](auto &&self, int d, int x)\
    \ -> void {\n            if (d) {\n                for (auto m = _d.at(d).at(x);\
    \ m;) {\n                    int i = bsf(m);\n                    m -= 1ULL <<\
    \ i, self(self, d - 1, x * B + i);\n                }\n            }\n       \
    \     _d.at(d).at(x) = 0;\n        };\n        rec(rec, _d.size() - 1, 0);\n \
    \   }\n};\n"
  code: "#pragma once\n\n#include <cassert>\n#include <cstdint>\n#include <vector>\n\
    \n// Sorted set of integers [0, n)\n// Space complexity: (64 / 63) n + O(log n)\
    \ bit\nclass fast_set {\n    static constexpr int B = 64;\n\n    int n;\n    int\
    \ cnt;\n    std::vector<std::vector<uint64_t>> _d;\n\n    static int bsf(uint64_t\
    \ x) { return __builtin_ctzll(x); }\n    static int bsr(uint64_t x) { return 63\
    \ - __builtin_clzll(x); }\n\npublic:\n    // 0 \u4EE5\u4E0A n_ \u672A\u6E80\u306E\
    \u6574\u6570\u304C\u5165\u308C\u3089\u308C\u308B sorted set \u3092\u4F5C\u6210\
    \n    fast_set(int n_) : n(n_), cnt(0) {\n        do { n_ = (n_ + B - 1) / B,\
    \ _d.push_back(std::vector<uint64_t>(n_)); } while (n_ > 1);\n    }\n\n    bool\
    \ contains(int i) const {\n        assert(0 <= i and i < n);\n        return (_d.front().at(i\
    \ / B) >> (i % B)) & 1;\n    }\n\n    void insert(int i) {\n        assert(0 <=\
    \ i and i < n);\n        if (contains(i)) return;\n        ++cnt;\n        for\
    \ (auto &vec : _d) {\n            bool f = vec.at(i / B);\n            vec.at(i\
    \ / B) |= 1ULL << (i % B), i /= B;\n            if (f) break;\n        }\n   \
    \ }\n\n    void erase(int i) {\n        assert(0 <= i and i < n);\n        if\
    \ (!contains(i)) return;\n        --cnt;\n        for (auto &vec : _d) {\n   \
    \         vec.at(i / B) &= ~(1ULL << (i % B)), i /= B;\n            if (vec.at(i))\
    \ break;\n        }\n    }\n\n    // i \u4EE5\u4E0A\u306E\u6700\u5C0F\u8981\u7D20\
    \ \u306A\u3051\u308C\u3070 default_val\n    int next(int i, const int default_val)\
    \ const {\n        assert(0 <= i and i <= n);\n\n        for (auto itr = _d.cbegin();\
    \ itr != _d.cend(); ++itr, i = i / B + 1) {\n            if (i / B >= int(itr->size()))\
    \ break;\n\n            if (auto d = itr->at(i / B) >> (i % B); d) {\n       \
    \         i += bsf(d);\n                while (itr != _d.cbegin()) i = i * B +\
    \ bsf((--itr)->at(i));\n                return i;\n            }\n        }\n\n\
    \        return default_val;\n    }\n    int next(const int i) const { return\
    \ next(i, n); }\n\n    // i \u4EE5\u4E0B\u306E\u6700\u5C0F\u8981\u7D20 \u306A\u3051\
    \u308C\u3070 default_val\n    int prev(int i, int default_val = -1) const {\n\
    \        assert(-1 <= i and i < n);\n\n        for (auto itr = _d.cbegin(); itr\
    \ != _d.cend() and i >= 0; ++itr, i = i / B - 1) {\n            if (auto d = itr->at(i\
    \ / B) << (B - 1 - i % B); d) {\n                i += bsr(d) - (B - 1);\n    \
    \            while (itr != _d.cbegin()) i = i * B + bsr((--itr)->at(i));\n   \
    \             return i;\n            }\n        }\n\n        return default_val;\n\
    \    }\n\n    // return minimum element (if exists) or `n` (empty)\n    int min()\
    \ const { return next(0); }\n    // return maximum element (if exists) or `-1`\
    \ (empty)\n    int max() const { return prev(n - 1); }\n    int size() const {\
    \ return cnt; }\n    bool empty() const { return cnt == 0; }\n\n    void clear()\
    \ {\n        if (!cnt) return;\n        cnt = 0;\n        auto rec = [&](auto\
    \ &&self, int d, int x) -> void {\n            if (d) {\n                for (auto\
    \ m = _d.at(d).at(x); m;) {\n                    int i = bsf(m);\n           \
    \         m -= 1ULL << i, self(self, d - 1, x * B + i);\n                }\n \
    \           }\n            _d.at(d).at(x) = 0;\n        };\n        rec(rec, _d.size()\
    \ - 1, 0);\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/fast_set.hpp
  requiredBy:
  - tree/auxiliary_tree.hpp
  timestamp: '2023-03-23 22:42:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - data_structure/test/fast_set.test.cpp
  - tree/test/auxiliary_tree.yuki901.test.cpp
documentation_of: data_structure/fast_set.hpp
layout: document
title: "Fast set of integers \uFF0864\u5206\u6728\u3067\u6574\u6570\u96C6\u5408\u3092\
  \u9AD8\u901F\u306B\u51E6\u7406\u3059\u308B\u30C7\u30FC\u30BF\u69CB\u9020\uFF09"
---

`std::set<int>` のように使えるが $0$ 以上 $N$ 未満の整数の集合に特化したデータ構造．各種クエリに対して非常に高速に動作するので， Mo's algorithm などと組み合わせると非常に有効．空間計算量 $N + O(\log N)$ bit.

## 使用方法

```cpp
int N;
fast_set fs(N);  // [0, N)

int a;

// Almost same as std::set<int>
fs.insert(a);
fs.erase(a);
bool has_a = fs.contains(a);
int sz = fs.size();
bool is_empty = fs.empty();
fs.clear();

// Additional methods
int nxt = fs.next(a);  // a 以上の最小の要素の取得（存在しなければ N を返す）
int prv = fs.prev(a);  // a 以下の最大の要素の取得（存在しなければ -1 を返す）
int lo = fs.min();     // 最小値
int hi = fs.max();     // 最大値
```

## 問題例

- [Library Checker: Predecessor Problem](https://judge.yosupo.jp/problem/predecessor_problem)
