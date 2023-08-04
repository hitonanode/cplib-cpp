---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: string/test/rolling_hash_2d.aoj.test.cpp
    title: string/test/rolling_hash_2d.aoj.test.cpp
  - icon: ':heavy_check_mark:'
    path: string/test/rolling_hash_mersenne61.test.cpp
    title: string/test/rolling_hash_mersenne61.test.cpp
  - icon: ':heavy_check_mark:'
    path: string/test/run_enumerate_lyndon_mersenne61.test.cpp
    title: string/test/run_enumerate_lyndon_mersenne61.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://qiita.com/keymoon/items/11fac5627672a6d6a9f6
  bundledCode: "#line 2 \"number/modint_mersenne61.hpp\"\n#include <cassert>\n#include\
    \ <chrono>\n#include <random>\n\n// F_p, p = 2^61 - 1\n// https://qiita.com/keymoon/items/11fac5627672a6d6a9f6\n\
    class ModIntMersenne61 {\n    static const long long md = (1LL << 61) - 1;\n \
    \   long long _v;\n\n    inline unsigned hi() const noexcept { return _v >> 31;\
    \ }\n    inline unsigned lo() const noexcept { return _v & ((1LL << 31) - 1);\
    \ }\n\npublic:\n    static long long mod() { return md; }\n\n    ModIntMersenne61()\
    \ : _v(0) {}\n    // 0 <= x < md * 2\n    explicit ModIntMersenne61(long long\
    \ x) : _v(x >= md ? x - md : x) {}\n\n    long long val() const noexcept { return\
    \ _v; }\n\n    ModIntMersenne61 operator+(const ModIntMersenne61 &x) const {\n\
    \        return ModIntMersenne61(_v + x._v);\n    }\n\n    ModIntMersenne61 operator-(const\
    \ ModIntMersenne61 &x) const {\n        return ModIntMersenne61(_v + md - x._v);\n\
    \    }\n\n    ModIntMersenne61 operator*(const ModIntMersenne61 &x) const {\n\
    \        using ull = unsigned long long;\n\n        ull uu = (ull)hi() * x.hi()\
    \ * 2;\n        ull ll = (ull)lo() * x.lo();\n        ull lu = (ull)hi() * x.lo()\
    \ + (ull)lo() * x.hi();\n\n        ull sum = uu + ll + ((lu & ((1ULL << 30) -\
    \ 1)) << 31) + (lu >> 30);\n        ull reduced = (sum >> 61) + (sum & ull(md));\n\
    \        return ModIntMersenne61(reduced);\n    }\n\n    ModIntMersenne61 pow(long\
    \ long n) const {\n        assert(n >= 0);\n        ModIntMersenne61 ans(1), tmp\
    \ = *this;\n        while (n) {\n            if (n & 1) ans *= tmp;\n        \
    \    tmp *= tmp, n >>= 1;\n        }\n        return ans;\n    }\n\n    ModIntMersenne61\
    \ inv() const { return pow(md - 2); }\n\n    ModIntMersenne61 operator/(const\
    \ ModIntMersenne61 &x) const { return *this * x.inv(); }\n\n    ModIntMersenne61\
    \ operator-() const { return ModIntMersenne61(md - _v); }\n    ModIntMersenne61\
    \ &operator+=(const ModIntMersenne61 &x) { return *this = *this + x; }\n    ModIntMersenne61\
    \ &operator-=(const ModIntMersenne61 &x) { return *this = *this - x; }\n    ModIntMersenne61\
    \ &operator*=(const ModIntMersenne61 &x) { return *this = *this * x; }\n    ModIntMersenne61\
    \ &operator/=(const ModIntMersenne61 &x) { return *this = *this / x; }\n\n   \
    \ ModIntMersenne61 operator+(unsigned x) const { return ModIntMersenne61(this->_v\
    \ + x); }\n\n    bool operator==(const ModIntMersenne61 &x) const { return _v\
    \ == x._v; }\n    bool operator!=(const ModIntMersenne61 &x) const { return _v\
    \ != x._v; }\n    bool operator<(const ModIntMersenne61 &x) const { return _v\
    \ < x._v; } // To use std::map\n\n    template <class OStream> friend OStream\
    \ &operator<<(OStream &os, const ModIntMersenne61 &x) {\n        return os <<\
    \ x._v;\n    }\n\n    static ModIntMersenne61 randgen(bool force_update = false)\
    \ {\n        static ModIntMersenne61 b(0);\n        if (b == ModIntMersenne61(0)\
    \ or force_update) {\n            std::mt19937 mt(std::chrono::steady_clock::now().time_since_epoch().count());\n\
    \            std::uniform_int_distribution<long long> d(1, ModIntMersenne61::mod());\n\
    \            b = ModIntMersenne61(d(mt));\n        }\n        return b;\n    }\n\
    };\n"
  code: "#pragma once\n#include <cassert>\n#include <chrono>\n#include <random>\n\n\
    // F_p, p = 2^61 - 1\n// https://qiita.com/keymoon/items/11fac5627672a6d6a9f6\n\
    class ModIntMersenne61 {\n    static const long long md = (1LL << 61) - 1;\n \
    \   long long _v;\n\n    inline unsigned hi() const noexcept { return _v >> 31;\
    \ }\n    inline unsigned lo() const noexcept { return _v & ((1LL << 31) - 1);\
    \ }\n\npublic:\n    static long long mod() { return md; }\n\n    ModIntMersenne61()\
    \ : _v(0) {}\n    // 0 <= x < md * 2\n    explicit ModIntMersenne61(long long\
    \ x) : _v(x >= md ? x - md : x) {}\n\n    long long val() const noexcept { return\
    \ _v; }\n\n    ModIntMersenne61 operator+(const ModIntMersenne61 &x) const {\n\
    \        return ModIntMersenne61(_v + x._v);\n    }\n\n    ModIntMersenne61 operator-(const\
    \ ModIntMersenne61 &x) const {\n        return ModIntMersenne61(_v + md - x._v);\n\
    \    }\n\n    ModIntMersenne61 operator*(const ModIntMersenne61 &x) const {\n\
    \        using ull = unsigned long long;\n\n        ull uu = (ull)hi() * x.hi()\
    \ * 2;\n        ull ll = (ull)lo() * x.lo();\n        ull lu = (ull)hi() * x.lo()\
    \ + (ull)lo() * x.hi();\n\n        ull sum = uu + ll + ((lu & ((1ULL << 30) -\
    \ 1)) << 31) + (lu >> 30);\n        ull reduced = (sum >> 61) + (sum & ull(md));\n\
    \        return ModIntMersenne61(reduced);\n    }\n\n    ModIntMersenne61 pow(long\
    \ long n) const {\n        assert(n >= 0);\n        ModIntMersenne61 ans(1), tmp\
    \ = *this;\n        while (n) {\n            if (n & 1) ans *= tmp;\n        \
    \    tmp *= tmp, n >>= 1;\n        }\n        return ans;\n    }\n\n    ModIntMersenne61\
    \ inv() const { return pow(md - 2); }\n\n    ModIntMersenne61 operator/(const\
    \ ModIntMersenne61 &x) const { return *this * x.inv(); }\n\n    ModIntMersenne61\
    \ operator-() const { return ModIntMersenne61(md - _v); }\n    ModIntMersenne61\
    \ &operator+=(const ModIntMersenne61 &x) { return *this = *this + x; }\n    ModIntMersenne61\
    \ &operator-=(const ModIntMersenne61 &x) { return *this = *this - x; }\n    ModIntMersenne61\
    \ &operator*=(const ModIntMersenne61 &x) { return *this = *this * x; }\n    ModIntMersenne61\
    \ &operator/=(const ModIntMersenne61 &x) { return *this = *this / x; }\n\n   \
    \ ModIntMersenne61 operator+(unsigned x) const { return ModIntMersenne61(this->_v\
    \ + x); }\n\n    bool operator==(const ModIntMersenne61 &x) const { return _v\
    \ == x._v; }\n    bool operator!=(const ModIntMersenne61 &x) const { return _v\
    \ != x._v; }\n    bool operator<(const ModIntMersenne61 &x) const { return _v\
    \ < x._v; } // To use std::map\n\n    template <class OStream> friend OStream\
    \ &operator<<(OStream &os, const ModIntMersenne61 &x) {\n        return os <<\
    \ x._v;\n    }\n\n    static ModIntMersenne61 randgen(bool force_update = false)\
    \ {\n        static ModIntMersenne61 b(0);\n        if (b == ModIntMersenne61(0)\
    \ or force_update) {\n            std::mt19937 mt(std::chrono::steady_clock::now().time_since_epoch().count());\n\
    \            std::uniform_int_distribution<long long> d(1, ModIntMersenne61::mod());\n\
    \            b = ModIntMersenne61(d(mt));\n        }\n        return b;\n    }\n\
    };\n"
  dependsOn: []
  isVerificationFile: false
  path: number/modint_mersenne61.hpp
  requiredBy: []
  timestamp: '2022-11-15 00:34:03+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - string/test/rolling_hash_2d.aoj.test.cpp
  - string/test/run_enumerate_lyndon_mersenne61.test.cpp
  - string/test/rolling_hash_mersenne61.test.cpp
documentation_of: number/modint_mersenne61.hpp
layout: document
title: "$\\mathbb{F}_{2^{61} - 1}$ \uFF08\u30CF\u30C3\u30B7\u30E5\u7528\u30E1\u30EB\
  \u30BB\u30F3\u30CC\u7D20\u6570 modint\uFF09"
---

$\mathbb{F}_{2^{61} - 1}$ の実装．$2^{61} - 1$ は素数．位数が通常よく用いられる modint より遥かに大きく，また乗算が bit 演算を用いて効率的に可能．`rolling_hash_id` クラスなどに与えて利用することを想定．

## 使用方法

```cpp
string S;
rolling_hash<ModIntMersenne61> rh(S);
```

`run_enumerate()` 関数と組み合わせることも可能．実験的に，通常の（位数 $10^9$ 程度の）modint を 2 個組み合わせる場合よりもかなり高速．

```cpp
auto ret = run_enumerate<rolling_hash<ModIntMersenne61>>(S);
```

## 問題例

- [Library Checker: Run Enumerate](https://judge.yosupo.jp/problem/runenumerate)

## 参考文献・リンク

- [安全で爆速なRollingHashの話 - Qiita](https://qiita.com/keymoon/items/11fac5627672a6d6a9f6#fnref1) : この記事の乗算のアイデアを参考にした．
