---
title: Transversal matroid （横断マトロイド）
documentation_of: ./transversal_matroid.hpp
---

頂点集合 $U, V$，辺集合 $E$ からなる二部グラフ $G = (U, V, E)$ について定義されるマトロイド．台集合は $U$．$U$ の部分集合の独立性を，「その集合を被覆するようなマッチングが存在すること」で定義する．

計算量は，$\|U\| + \|V\| = n, \|E\| = m$ とすると，独立集合 $I \subset U$ の設定（`set()`）が $O((n + m) \sqrt{n})$，$I + \{e\}$ に対するサーキットの取得（`circuit()`）がクエリあたり $O(n + m)$．

## 使用例

```cpp
int U = 4, V = 2;
vector<pair<int, int>> edges;
edges.emplace_back(0, 0); // 0 <= u < U, 0 <= v < V
edges.emplace_back(1, 0);
edges.emplace_back(2, 1);

TransversalMatroid M1(U, V, edges);
vector<bool> I{1, 0, 0, 0};
M1.set(I);
vector<int> a = M1.circuit(1); // [0, 1]
vector<int> b = M1.circuit(2); // [] (I + {2} is still independent)
```

## 問題例

- [2021 ICPC Asia Taiwan Online Programming Contest I. ICPC Kingdom - Codeforces](http://codeforces.com/gym/103373/problem/I) 横断マトロイドとグラフマトロイドの重み付き交差．

## リンク

- [離散最適化基礎論 第 6回 マトロイドに対する貪欲アルゴリズム](http://dopal.cs.uec.ac.jp/okamotoy/lect/2015/matroid/handout06.pdf)
