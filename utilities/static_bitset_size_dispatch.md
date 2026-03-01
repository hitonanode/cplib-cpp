---
title: Static bitset size dispatch （コンパイル時 bitset サイズの実行時分岐）
documentation_of: ./static_bitset_size_dispatch.hpp
---

実行時に決まるサイズ $n$ に対して，$n$ 以上の最小のコンパイル時定数をテンプレート引数として `std::bitset` 等を利用できるようにするユーティリティ．サイズの候補は $1$ から約 $\alpha = 1.5$ 倍ずつ増加し，$2^{30}$ を上限とする．

## 使用方法

```cpp
static_bitset_size_dispatch(n, [&]<size_t BS_SIZE>() {
    std::bitset<BS_SIZE> bs;
    // BS_SIZE >= n が保証される
});
```

- `n`: 必要なビットサイズ（`unsigned long long`）．
- `callback`: テンプレート引数 `BS_SIZE`（`n` 以上のコンパイル時定数）を受け取るジェネリックラムダ．

コンパイル時にサイズ候補ごとのインスタンスが生成される．増加率を $\alpha$ として， `n` がおおよそ $2^{30} / \alpha$ 以上の場合は何も実行されない可能性がある．

## 問題例

- [Codeforces Round 1079 (Div. 1) E2. Fuzzy Concatenation (Hard version)](https://codeforces.com/contest/2196/problem/E2)
  - [Submission #362639741 - Codeforces](https://codeforces.com/contest/2196/submission/362639741)

## リンク

- [Variable size bitset (kind of) - Codeforces](https://codeforces.com/blog/entry/143059)
