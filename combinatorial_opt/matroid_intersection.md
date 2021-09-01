---
title: (Weighted) matroid intersecition （（重みつき）マトロイド交叉）
documentation_of: ./matroid_intersection.hpp
---

マトロイド交叉（交差）問題 (matroid intersection)・共通独立集合問題とは，同じ台集合 $E$ を持つ二つのマトロイド
$M\_{1} = (E, \mathcal{I}\_{1}), M_{2} = (E, \mathcal{I}\_{2})$ が与えられたとき，$X \in \mathcal{I}\_{1} \cap \mathcal{I}\_{2}$ を満たす要素数最大の $X \subset E$ の一つを求めるもの．本問題は更に，重み関数 $f(e) : E \rightarrow \mathbb{R}$ が与えられたとき，要素数最大のもののうち特に $\sum\_{e \in X} f(e)$ を最小化（最大化）するようなものを求める重みつき共通独立集合問題 （weighted matroid intersection problem） に一般化される．

本コードは，$n = \|E\|$，解となる集合の要素数の上界（例えば各マトロイドのランクの最小値）を $r$，マトロイドクラスのサーキットクエリ一回あたりの計算量を $c$ として，（重みなしの）マトロイド交叉を $O(nr(n + c))$ で求める．重みつきの場合は最短増加路を求めるパートが Bellman-Ford 法に置き換えられ，計算量は $O(nr(n^2 + c))$ となる（この計算量は例えば [2] のアルゴリズムを用いることで $O(nr(r + c + \log n))$ まで改善可能）．

## 使用方法

`weights` を与えた場合，最小重み共通独立集合を求める．

```cpp
UserDefinedMatroid m1, m2;
vector<int> weights(M);

assert(m1.size() == M);
assert(m2.size() == M);

std::vector<bool> maxindepset = MatroidIntersection(m1, m2, weights);
```

## 問題例

- [Hello 2020 G. Seollal - Codeforces](https://codeforces.com/contest/1284/problem/G) グラフマトロイドと分割マトロイドの交差に帰着される．
- [Deltix Round, Summer 2021 H. DIY Tree - Codeforces](https://codeforces.com/contest/1556/problem/H) グラフマトロイドと分割マトロイドの最小重み共通独立集合問題に帰着される．

## 文献・リンク集

- [1] A. Frank, "A weighted matroid intersection algorithm,"
  Journal of Algorithms, 2(4), 328-336, 1981.
- [2] C. Brezovec, G. Cornuéjols, and F. Glover, "Two algorithms for weighted matroid intersection,"
  Mathematical Programming, 36(1), 39-53, 1986.
- [離散最適化基礎論 (2015年度後学期) 組合せ最適化におけるマトロイドの役割](http://dopal.cs.uec.ac.jp/okamotoy/lect/2015/matroid/) とても初学者向き．
