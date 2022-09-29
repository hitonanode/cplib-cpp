---
title: $\mathbb{F}_{2^{61} - 1}$ （ハッシュ用メルセンヌ素数 modint）
documentation_of: ./modint_mersenne61.hpp
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
