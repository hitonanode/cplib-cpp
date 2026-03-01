---
title: Dynamic Bitset （動的サイズ bitset）
documentation_of: ./dynamic_bitset.hpp
---

実行時にサイズを決定できる bitset．64 ビット整数のブロック列で表現し，ビット演算・シフト・集合探索を $O(n/64)$ で処理する．`std::bitset` はテンプレート引数でサイズをコンパイル時に固定する必要があるが，`dynamic_bitset` は `int n` を受け取って動的に確保する．

## 使用方法

```cpp
dynamic_bitset bs(n);          // n ビット，全 0 で初期化
dynamic_bitset bs(n, true);    // n ビット，全 1 で初期化
dynamic_bitset bs("1010");     // 文字列から構築（最下位ビット = s[size-1]）
```

### 個別ビット操作

```cpp
bs.test(i);       // i ビット目の値（bool）
bs.set(i);        // i ビット目を 1 に
bs.reset(i);      // i ビット目を 0 に
bs.flip(i);       // i ビット目を反転
bs.set(i, v);     // i ビット目を v に設定
```

### 全体操作

```cpp
bs.set_all();     // 全ビットを 1 に
bs.reset_all();   // 全ビットを 0 に
bs.flip_all();    // 全ビットを反転
```

### ビット演算

```cpp
bs1 &= bs2;  bs1 |= bs2;  bs1 ^= bs2;  // 代入形式
bs1 & bs2;   bs1 | bs2;   bs1 ^ bs2;   // コピー形式（同サイズが必要）
~bs;                                    // 反転
bs <<= k;  bs >>= k;                    // シフト（k ビット左右）
bs << k;   bs >> k;
```

### カウントと判定

```cpp
bs.popcount();  // （= bs.count()）立っているビット数
bs.any();       // 1 ビット以上立っているか
bs.none();      // 全ビットが 0 か
bs.size();      // ビット数 n
```

### 部分ビット列・連結

```cpp
// bs の [l, r) に対応する (r-l) ビットの bitset を返す
dynamic_bitset sub = bs.slice(l, r);

// 複数の bitset を低ビット側から順に連結
dynamic_bitset joined = dynamic_bitset::join(a, b);
dynamic_bitset joined = dynamic_bitset::join({a, b, c});          // 初期化リスト
dynamic_bitset joined = dynamic_bitset::join(vector_of_bitsets);  // vector
```

### 立っているビットの探索

```cpp
bs.first();     // 最小の 1 ビットのインデックス（なければ size()）
bs.next(i);     // i より大きい最小の 1 ビット（なければ size()）
bs.last();      // 最大の 1 ビットのインデックス（なければ -1）
bs.prev(i);     // i より小さい最大の 1 ビット（なければ -1）
```

`first` / `next` を使った列挙例:

```cpp
for (int i = bs.first(); i < bs.size(); i = bs.next(i)) {
    // i は立っているビット
}
```

## 問題例

- [No.1444 !Andd - yukicoder](https://yukicoder.me/problems/no/1444)
- [No.1514 Squared Matching - yukicoder](https://yukicoder.me/problems/no/1514)
- [No.1560 majority x majority - yukicoder](https://yukicoder.me/problems/no/1560)
- [No.1782 ManyCoins - yukicoder](https://yukicoder.me/problems/no/1782)
- [No.1861 Required Number - yukicoder](https://yukicoder.me/problems/no/1861)
- [No.2319 Friends+ - yukicoder](https://yukicoder.me/problems/no/2319)
- [No.2542 Yokan for Two - yukicoder](https://yukicoder.me/problems/no/2542)
- [No.3041 非対称じゃんけん - yukicoder](https://yukicoder.me/problems/no/3041)
- [No.3060 Erase Binary Matrix - yukicoder](https://yukicoder.me/problems/no/3060)
