---
title: Fast hash map
documentation_of: ./fast_hash_map.hpp
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
