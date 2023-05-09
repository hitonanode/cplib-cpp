---
title: Guni (Sack) / DSU on tree （根付き木の全ての部分木を経由するような頂点追加・削除操作列の生成）
documentation_of: ./guni.hpp
---

## できること

頂点数 $n$ の根付き木について，頂点集合の部分集合の列 $S = (S\_0, \ldots, S\_m)$ で，以下を満たすものを構築する．

- $S\_0 = S\_m = \emptyset$
- $\| S\_i \oplus S\_\{i + 1\} \| = 1$ （ $S\_\{i + 1\}$ は $S\_i$ から一個の頂点を追加または削除したもの）
- 各部分木について，それに含まれる頂点集合と $S\_k$ が一致するような $k$ が存在する
- $m =  O(n \log n)$

本コードはこのような $S$ の一つを implicit に構築する．根付き木の全ての部分木に関する特定の問題を全ての部分木に対して解く必要があるような状況で，効率的な実装に役立つ．

## 原理

木の上で DFS し，行きがけに頂点追加・帰りがけに頂点削除を行うのが基本方針だが，一部の頂点には複数回訪問する点で通常の DFS とは異なる．

Heavy-light decomposition を行う．ある頂点 $v$ に到達した際，以下の手続きを行う：

1. $v$ と light edge で繋がる子の部分木全てについて再帰的に DFS する
2. $v$ と heavy edge で繋がる子の部分木について再帰的に DFS する（ただし， 手順 5. の削除操作を省く）
3. $v$ light edge で繋がる子の部分木に含まれる全頂点を追加する
4. 頂点 $v$ を追加する
5. （ $S\_v$ ができる）
6. $v$ の部分木に含まれる全頂点を削除する

このアルゴリズムは以下の背景により $O(n \log n)$ である：

- 手順 3. の計算量は weighted-union heuristic （いわゆるマージテク）により $O(n \log n)$ である．
- 各頂点が手順 6. で削除対象になる回数は，その頂点から根への単純パスに存在する（distinct な） heavy path の本数と一致するので， 6. の計算量は $O(n \log n)$ である．

## 使用方法

本テクニックを使用するまでもない例だが，根付き木の全ての部分木について「部分木を構成する頂点の `id` の 2 乗和」は以下のように実装できる．

```cpp
int N, root;
vector<pair<int, int>> edges(N - 1);

guni g(N);
for (auto [u, v] : edges) g.add_bi_edge(u, v);

std::vector<long long> ret(N);
long long sum_of_i_quads = 0;

auto Add = [&](int i) { sum_of_i_quads += (long long)i * i; };
auto Remove = [&](int i) { sum_of_i_quads -= (long long)i * i; };
auto Solve = [&](int i) { ret.at(i) = sum_of_i_quads; };

g.run(0, Add, Remove, Solve);
```

## 問題例

- [Library Checker: Vertex Add Subtree Sum](https://judge.yosupo.jp/problem/vertex_add_subtree_sum)
- [Codeforces Round 862 (Div. 2) E. There Should Be a Lot of Maximums](https://codeforces.com/contest/1805/problem/E)

## 文献・リンク集

- [[Tutorial] Sack (dsu on tree) - Codeforces](https://codeforces.com/blog/entry/44351)
- [DSU on Tree - Speaker Deck](https://speakerdeck.com/camypaper/dsu-on-tree)
