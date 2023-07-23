---
title: Weighted matroid intersection using Dijkstra's algorithm
documentation_of: ./matroid_intersection_dijkstra.hpp
---

重み付きマトロイド交叉（交差）問題 (matroid intersection) のソルバ．二つのマトロイド $M\_{1} = (E, \mathcal{I}\_{1}), M_{2} = (E, \mathcal{I}\_{2})$ とそのサイズ $k$ 最大重み共通独立集合 $I\_k$ ，および $I\_k$ の導出に使われたポテンシャルを入力とし，サイズ $k + 1$ の最大重み共通独立集合を求めるか，これが存在しないことを示す．引数として与えたポテンシャルは適宜更新される．

計算量は $n = \|E\|$，マトロイドクラスのサーキットクエリ一回あたりの計算量を $c$ として $O(nc + nk \log n)$ である．ポテンシャルの利用により内部で解く最短経路問題の辺重みを全て非負にでき，高速な Dijkstra 法を利用できる．

## 使用方法

```cpp
UserDefinedMatroid m1, m2;
vector<T> weight(n);
vector<T> potential(n + 2);  // 2 個の補助頂点のポテンシャルの情報も持つ
vector<bool> I(n);

assert(m1.size() == n);
assert(m2.size() == n);

while (augment_matroid_intersection_dijkstra(m1, m2, I, weight, potential)) {
    continue;
}
```

## 問題例

- [AOJ GRL_2_B: 最小全域有向木](https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_B) 分割マトロイドとグラフマトロイドの重み付き交差でも解ける．
- [Deltix Round, Summer 2021 H. DIY Tree - Codeforces](https://codeforces.com/contest/1556/problem/H) グラフマトロイドと分割マトロイドの最小重み共通独立集合問題に帰着される．
- [AOJ 1605: Bridge Construction Planning （橋の建造計画）](https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1605&lang=ja) 分割マトロイドとグラフマトロイドの重み付き交差．
- [2021 ICPC Asia Taiwan Online Programming Contest I. ICPC Kingdom - Codeforces](http://codeforces.com/gym/103373/problem/I) 横断マトロイドとグラフマトロイドの重み付き交差（横断マトロイドを考える代わりに辺を仮想的に増やし，分割マトロイドと解釈することも可能）．

## 文献・リンク集

- [1] C. Brezovec, G. Cornuéjols, and F. Glover, "Two algorithms for weighted matroid intersection,"
  Mathematical Programming, 36(1), 39-53, 1986.
