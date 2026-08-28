---
title: Random number generators （乱数生成器）
documentation_of: ./rand_nondeterministic.hpp
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
