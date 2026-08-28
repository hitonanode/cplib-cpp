---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: graph/test/chromatic_number.test.cpp
    title: graph/test/chromatic_number.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"random/rand_nondeterministic.hpp\"\n#include <cassert>\n\
    #include <chrono>\n#include <cstdint>\n#include <random>\n\nstruct RNGMt19937\
    \ {\n    using lint = long long;\n    std::mt19937 mt;\n    RNGMt19937(long long\
    \ seed) : mt(seed) {}\n    lint operator()(lint x) { // [0, x)\n        assert(x\
    \ > 0);\n        return this->operator()(0, x);\n    }\n    lint operator()(lint\
    \ l, lint r) {\n        assert(l < r);\n        std::uniform_int_distribution<lint>\
    \ d(l, r - 1);\n        return d(mt);\n    }\n};\n// RNGMt19937 rnd(123456789);\n\
    // RNGMt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());\n\
    \n// Fast random number generator based on xoshiro256++.\nstruct FastRNG {\n \
    \   using ull = unsigned long long;\n    ull s[4];\n\n    static ull rotl(ull\
    \ x, int k) { return (x << k) | (x >> (64 - k)); }\n\n    static ull splitmix64(ull\
    \ &x) {\n        ull z = (x += 0x9e3779b97f4a7c15ULL);\n        z = (z ^ (z >>\
    \ 30)) * 0xbf58476d1ce4e5b9ULL;\n        z = (z ^ (z >> 27)) * 0x94d049bb133111ebULL;\n\
    \        return z ^ (z >> 31);\n    }\n\n    FastRNG(ull seed) {\n        for\
    \ (auto &x : s) x = splitmix64(seed);\n    }\n\n    ull next_u64() {\n       \
    \ ull res = rotl(s[0] + s[3], 23) + s[0];\n        ull t = s[1] << 17;\n\n   \
    \     s[2] ^= s[0];\n        s[3] ^= s[1];\n        s[1] ^= s[2];\n        s[0]\
    \ ^= s[3];\n\n        s[2] ^= t;\n        s[3] = rotl(s[3], 45);\n\n        return\
    \ res;\n    }\n\n    uint32_t next_u32() { return next_u64() >> 32; }\n\n    //\
    \ [0, n)\n    uint32_t operator()(uint32_t n) {\n        assert(n > 0);\n    \
    \    return (uint64_t(next_u32()) * n) >> 32;\n    }\n\n    // [l, r)\n    int\
    \ operator()(int l, int r) {\n        assert(l < r);\n        uint32_t width =\
    \ uint64_t(int64_t(r) - int64_t(l));\n        return int(int64_t(l) + (*this)(width));\n\
    \    }\n\n    uint16_t next_u16() { return next_u64() >> 48; }\n};\ninline FastRNG\
    \ rnd(123456789);\n// FastRNG rnd(std::chrono::steady_clock::now().time_since_epoch().count());\n"
  code: "#pragma once\n#include <cassert>\n#include <chrono>\n#include <cstdint>\n\
    #include <random>\n\nstruct RNGMt19937 {\n    using lint = long long;\n    std::mt19937\
    \ mt;\n    RNGMt19937(long long seed) : mt(seed) {}\n    lint operator()(lint\
    \ x) { // [0, x)\n        assert(x > 0);\n        return this->operator()(0, x);\n\
    \    }\n    lint operator()(lint l, lint r) {\n        assert(l < r);\n      \
    \  std::uniform_int_distribution<lint> d(l, r - 1);\n        return d(mt);\n \
    \   }\n};\n// RNGMt19937 rnd(123456789);\n// RNGMt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());\n\
    \n// Fast random number generator based on xoshiro256++.\nstruct FastRNG {\n \
    \   using ull = unsigned long long;\n    ull s[4];\n\n    static ull rotl(ull\
    \ x, int k) { return (x << k) | (x >> (64 - k)); }\n\n    static ull splitmix64(ull\
    \ &x) {\n        ull z = (x += 0x9e3779b97f4a7c15ULL);\n        z = (z ^ (z >>\
    \ 30)) * 0xbf58476d1ce4e5b9ULL;\n        z = (z ^ (z >> 27)) * 0x94d049bb133111ebULL;\n\
    \        return z ^ (z >> 31);\n    }\n\n    FastRNG(ull seed) {\n        for\
    \ (auto &x : s) x = splitmix64(seed);\n    }\n\n    ull next_u64() {\n       \
    \ ull res = rotl(s[0] + s[3], 23) + s[0];\n        ull t = s[1] << 17;\n\n   \
    \     s[2] ^= s[0];\n        s[3] ^= s[1];\n        s[1] ^= s[2];\n        s[0]\
    \ ^= s[3];\n\n        s[2] ^= t;\n        s[3] = rotl(s[3], 45);\n\n        return\
    \ res;\n    }\n\n    uint32_t next_u32() { return next_u64() >> 32; }\n\n    //\
    \ [0, n)\n    uint32_t operator()(uint32_t n) {\n        assert(n > 0);\n    \
    \    return (uint64_t(next_u32()) * n) >> 32;\n    }\n\n    // [l, r)\n    int\
    \ operator()(int l, int r) {\n        assert(l < r);\n        uint32_t width =\
    \ uint64_t(int64_t(r) - int64_t(l));\n        return int(int64_t(l) + (*this)(width));\n\
    \    }\n\n    uint16_t next_u16() { return next_u64() >> 48; }\n};\ninline FastRNG\
    \ rnd(123456789);\n// FastRNG rnd(std::chrono::steady_clock::now().time_since_epoch().count());\n"
  dependsOn: []
  isVerificationFile: false
  path: random/rand_nondeterministic.hpp
  requiredBy: []
  timestamp: '2026-08-28 22:52:49+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - graph/test/chromatic_number.test.cpp
documentation_of: random/rand_nondeterministic.hpp
layout: document
title: "Random number generators \uFF08\u4E71\u6570\u751F\u6210\u5668\uFF09"
---

整数の一様乱数を生成する乱数生成器．`std::mt19937` を利用する `RNGMt19937` と，高速な xoshiro256++ を利用する `FastRNG` を提供する．同じシードからは同じ乱数列が生成される．

## 使用方法

```cpp
// 再現可能な固定シード
RNGMt19937 rng_mt(123456789);
long long a = rng_mt(100);      // [0, 100)
long long b = rng_mt(-10, 10);  // [-10, 10)

FastRNG rng_fast(123456789);
uint32_t c = rng_fast(100U);  // [0, 100)
int d = rng_fast(-10, 10);    // [-10, 10)
uint64_t e = rng_fast.next_u64();
uint32_t f = rng_fast.next_u32();
uint16_t g = rng_fast.next_u16();
```

実行ごとに異なるシードを利用する場合は，例えば次のように初期化する．

```cpp
RNGMt19937 rng_mt(
    std::chrono::steady_clock::now().time_since_epoch().count());

FastRNG rng_fast(
    std::chrono::steady_clock::now().time_since_epoch().count());
```

`RNGMt19937` は `long long` の範囲を扱える．`FastRNG` は軽量で，`operator()(uint32_t n)` では乗算によって値を $[0, n)$ に写すため，剰余を利用する場合に生じる偏りを避けられる．区間を指定する関数には空でない半開区間を与えること．

ヘッダ内では固定シードで初期化したグローバル変数 `FastRNG rnd` も定義されているため，単に `rnd(r)` または `rnd(l, r)` として利用できる．
