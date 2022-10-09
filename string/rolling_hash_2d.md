---
title: Rolling hash (two dimensional) （二次元ローリングハッシュ）
documentation_of: ./rolling_hash_2d.hpp
---

行列に対する典型的なローリングハッシュ．構築・矩形取得が線形時間で可能．

## 使用方法

```cpp
using Hash = ModIntMersenne61;

vector<string> mat;
rolling_hash_2d<Hash> rh(mat)

int xl, xr, yl, yr;
Hash h = rh.get(xl, xr, yl, yr);  // [xl, xr) * [yl, yr) のハッシュ値を取得する
```

ハッシュの型 `PairHash` や `TupleHash3` は任意に入れ子にすることも可能で，例えば

```cpp
using Hash = ModIntMersenne61;
using Hash = TupleHash3<ModInt998244353, ModInt998244353, ModInt998244353>;
using PH = PairHash<ModInt998244353, ModInt998244353>;
using Hash = TupleHash3<PH, ModInt998244353, PH>;
using Hash = PairHash<PH, PairHash<ModInt998244353, ModInt998244353>>;
```

は全て動作する．
