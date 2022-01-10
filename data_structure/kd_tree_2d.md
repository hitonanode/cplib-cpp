---
title: k-d tree (2D)
documentation_of: ./kd_tree_2d.hpp
---

$k$-d tree の二次元平面の場合の実装．

木の各ノードにおいて平面を切断する方向は原則として $x$, $y$ 方向のうち最大値と最小値の差が大きい方を採用するが，ワーストケースでの計算量悪化を回避するため，同じ方向の切断が連続しすぎないよう簡単な工夫を入れている．

```cpp
vector<pair<long long, long long>> xys;

kd_tree<long long> kdt(xys);

long long xmin, xmax, ymin, ymax;
vector<int> ids = kdt.get_rect(xmin, xmax, ymin, ymax);  // 矩形に含まれる頂点番号取得
```

## 問題例

- [AtCoder Beginner Contest 234 Ex - Enumerate Pairs](https://atcoder.jp/contests/abc234/submissions/28456735)
