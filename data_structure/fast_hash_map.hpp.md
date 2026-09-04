---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: data_structure/test/fast_hash_map.test.cpp
    title: data_structure/test/fast_hash_map.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"data_structure/fast_hash_map.hpp\"\n\n#include <array>\n\
    #include <bit>\n#include <cassert>\n#include <chrono>\n#include <cstddef>\n#include\
    \ <cstdint>\n#include <random>\n#include <type_traits>\n\n// Fixed-capacity hash\
    \ map for integer keys.\n// N must be a power of two. At most N distinct keys\
    \ can be stored.\ntemplate <typename K, typename V, std::size_t N> struct HashMap\
    \ {\n    static_assert(std::has_single_bit(N));\n    static_assert(std::is_integral_v<K>);\n\
    \    static_assert(sizeof(K) <= sizeof(std::uint64_t));\n\nprivate:\n    std::array<K,\
    \ N> keys;\n    std::array<V, N> values;\n    std::array<std::uint32_t, N> versions{};\n\
    \n    std::uint32_t version = 1;\n    std::size_t count = 0;\n    std::uint64_t\
    \ multiplier;\n\n    static std::uint64_t make_multiplier() noexcept {\n     \
    \   // Use a nondeterministic seed\n        std::mt19937_64 mt(std::chrono::steady_clock::now().time_since_epoch().count());\n\
    \        return mt() | 1;\n    }\n\n    std::size_t hash(K key) const noexcept\
    \ {\n        if constexpr (N == 1) {\n            return 0;\n        } else {\n\
    \            constexpr int shift = 64 - std::countr_zero(N);\n            return\
    \ (static_cast<std::uint64_t>(key) * multiplier) >> shift;\n        }\n    }\n\
    \npublic:\n    HashMap() : multiplier(make_multiplier()) {}\n\n    void set(K\
    \ key, V value) noexcept {\n        std::size_t pos = hash(key);\n        for\
    \ (std::size_t step = 0; step < N; ++step) {\n            if (versions[pos] !=\
    \ version) {\n                keys[pos] = key;\n                values[pos] =\
    \ value;\n                versions[pos] = version;\n                assert(count\
    \ < N);\n                ++count;\n                return;\n            }\n  \
    \          if (keys[pos] == key) {\n                values[pos] = value;\n   \
    \             return;\n            }\n            pos = (pos + 1) & (N - 1);\n\
    \        }\n        assert(false && \"HashMap capacity exceeded\");\n    }\n\n\
    \    V get(K key) const noexcept {\n        std::size_t pos = hash(key);\n   \
    \     for (std::size_t step = 0; step < N; ++step) {\n            if (versions[pos]\
    \ != version) return V{};\n            if (keys[pos] == key) return values[pos];\n\
    \            pos = (pos + 1) & (N - 1);\n        }\n        return V{};\n    }\n\
    \n    std::size_t size() const noexcept { return count; }\n    bool empty() const\
    \ noexcept { return count == 0; }\n\n    void clear() noexcept {\n        ++version;\n\
    \        count = 0;\n    }\n    void reset() noexcept { clear(); }\n};\n"
  code: "#pragma once\n\n#include <array>\n#include <bit>\n#include <cassert>\n#include\
    \ <chrono>\n#include <cstddef>\n#include <cstdint>\n#include <random>\n#include\
    \ <type_traits>\n\n// Fixed-capacity hash map for integer keys.\n// N must be\
    \ a power of two. At most N distinct keys can be stored.\ntemplate <typename K,\
    \ typename V, std::size_t N> struct HashMap {\n    static_assert(std::has_single_bit(N));\n\
    \    static_assert(std::is_integral_v<K>);\n    static_assert(sizeof(K) <= sizeof(std::uint64_t));\n\
    \nprivate:\n    std::array<K, N> keys;\n    std::array<V, N> values;\n    std::array<std::uint32_t,\
    \ N> versions{};\n\n    std::uint32_t version = 1;\n    std::size_t count = 0;\n\
    \    std::uint64_t multiplier;\n\n    static std::uint64_t make_multiplier() noexcept\
    \ {\n        // Use a nondeterministic seed\n        std::mt19937_64 mt(std::chrono::steady_clock::now().time_since_epoch().count());\n\
    \        return mt() | 1;\n    }\n\n    std::size_t hash(K key) const noexcept\
    \ {\n        if constexpr (N == 1) {\n            return 0;\n        } else {\n\
    \            constexpr int shift = 64 - std::countr_zero(N);\n            return\
    \ (static_cast<std::uint64_t>(key) * multiplier) >> shift;\n        }\n    }\n\
    \npublic:\n    HashMap() : multiplier(make_multiplier()) {}\n\n    void set(K\
    \ key, V value) noexcept {\n        std::size_t pos = hash(key);\n        for\
    \ (std::size_t step = 0; step < N; ++step) {\n            if (versions[pos] !=\
    \ version) {\n                keys[pos] = key;\n                values[pos] =\
    \ value;\n                versions[pos] = version;\n                assert(count\
    \ < N);\n                ++count;\n                return;\n            }\n  \
    \          if (keys[pos] == key) {\n                values[pos] = value;\n   \
    \             return;\n            }\n            pos = (pos + 1) & (N - 1);\n\
    \        }\n        assert(false && \"HashMap capacity exceeded\");\n    }\n\n\
    \    V get(K key) const noexcept {\n        std::size_t pos = hash(key);\n   \
    \     for (std::size_t step = 0; step < N; ++step) {\n            if (versions[pos]\
    \ != version) return V{};\n            if (keys[pos] == key) return values[pos];\n\
    \            pos = (pos + 1) & (N - 1);\n        }\n        return V{};\n    }\n\
    \n    std::size_t size() const noexcept { return count; }\n    bool empty() const\
    \ noexcept { return count == 0; }\n\n    void clear() noexcept {\n        ++version;\n\
    \        count = 0;\n    }\n    void reset() noexcept { clear(); }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/fast_hash_map.hpp
  requiredBy: []
  timestamp: '2026-09-05 01:34:00+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - data_structure/test/fast_hash_map.test.cpp
documentation_of: data_structure/fast_hash_map.hpp
layout: document
title: Fast hash map
---

整数をキーとする固定容量の高速な連想配列．衝突は線形探索で解決する．ハッシュに使う乗数は実行時刻を seed として実行ごとに生成されるため，固定 seed を狙った衝突攻撃を受けにくい．

各スロットに世代番号を保持しており，`clear()` / `reset()` は現世代を更新するだけなので $O(1)$ で動作する．

## 使用方法

```cpp
// N は 2 の冪で，格納する相異なるキー数以上にする．
HashMap<long long, long long, 1 << 20> mp;

mp.set(10, 20);  // key 10 に value 20 を設定
mp.get(10);      // 20（存在しないキーに対しては V{}）
mp.size();       // 1
mp.empty();      // false
mp.clear();      // 全要素を O(1) で削除
```

キーは 64 bit 以下の整数型でなければならない．計算量は `set()` / `get()` が平均 $O(1)$，`clear()` / `reset()` / `size()` / `empty()` が $O(1)$．格納する相異なるキー数が `N` を超えないようにする必要がある．

## 問題例

- [Library Checker: Associative Array](https://judge.yosupo.jp/problem/associative_array)
