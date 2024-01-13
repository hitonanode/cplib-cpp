---
title: Multidimensional index
documentation_of: ./multidim_index.hpp
---

多次元の添え字を 1 次元に潰す処理とその逆変換の実装．

## 使用方法

### 添字変換

以下のような C++ コードを実行すると，以下のような結果を得る．

```cpp
multidim_index mi({2, 3, 4});

for (int i = 0; i < mi.size(); ++i) {
    const auto vec = mi.encode(i);
    assert(mi.flat_index(vec) == i);

    cout << i << ": (";
    for (int x : vec) cout << x << ",";
    cout << ")\n";
}
```

```txt
0: (0,0,0,)
1: (1,0,0,)
2: (0,1,0,)
3: (1,1,0,)
4: (0,2,0,)
5: (1,2,0,)
6: (0,0,1,)
...
23: (1,2,3,)
```

### 累積和やその逆変換

通常の `+=` 演算子による累積和処理に関しては， `subset_sum()` / `subset_sum_inv()` （下側累積和およびその逆変換）・ `superset_sum()` / `superset_sum_inv()` （上側累積和およびその逆変換）が提供されている．

より一般の演算を行いたい場合は，ラムダ式　`f` を用意した上で `lo_to_hi(F f)` 関数を使えばよい．

## 問題例

- [AtCoder Beginner Contest 335（Sponsored by Mynavi） G - Discrete Logarithm Problems](https://atcoder.jp/contests/abc335/tasks/abc335_g)
  - $P - 1$ の正の約数全てをキーとする DP テーブルで，整序関係をもとに累積和を取る． [参考提出](https://atcoder.jp/contests/abc335/submissions/49118789)
