---
title: Rolling hash (one dimensional) （一次元ローリングハッシュ）
documentation_of: ./rolling_hash_1d.hpp
---

文字列・数列に対する典型的なローリングハッシュ．長さ $N$ の入力に対して時間計算量 $O(N)$ で構築，区間ハッシュ値を $O(1)$ で取得．

## 使用方法

```cpp
using Hash = ModIntMersenne61;

string S = "sakanakanandaka";
rolling_hash<Hash> rh(S)

int l, r;
Hash h = rh.get(l, r);  // S[l:r], 半開区間
```

ハッシュの型 `PairHash` や `TupleHash3` は入れ子にすることも可能で，例えば

```cpp
using Hash = ModIntMersenne61;
using Hash = TupleHash3<ModInt998244353, ModInt998244353, ModInt998244353>>;
using Hash = TupleHash3<PH, ModInt998244353, PH>>;
using Hash = PairHash<PH, PairHash<ModInt998244353, ModInt998244353>>>;
```

は全て動作する．
