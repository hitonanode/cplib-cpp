---
title: Cost scaling minimum cost flow (Goldberg, Tarjan) （コストスケーリングによる最小費用流）
documentation_of: ./mcf_costscaling.hpp
---

コストスケーリングによる最小費用流．問題に実行可能解が存在しない場合無限ループに陥りうること，またコストを $n + 1$ 倍にする前処理を行うのでオーバーフローに注意．頂点数が多く流量が少ないようなケースなどでは最短路反復法の方が高速かもしれない．

## 使用方法

[AC Library の `mcf_graph`](https://atcoder.github.io/ac-library/production/document_ja/mincostflow.html) にインターフェースを寄せている．

```cpp
mcf_costscaling<Cap, Cost, 1, 20> mcf(N);

mcf.add_supply(s, flow);
mcf.add_demand(t, -flow);
mcf.add_edge(u, v, cap, cost);

auto ret = mcf.solve<__int128>();
vector<Cost> potential = mcf.potential();
auto ei = mcf.get_edge(i);
auto edges = mcf.get_edges();
```

## ヒューリスティックによる高速化

コストスケーリングには多くのヒューリスティックによる高速化手法が知られている．本コードでは [2] で price refinement と呼称されるテクニックをパラメータチューニング可能な形式で導入している（[プログラミングコンテストにおける提出を観察する](https://yukicoder.me/problems/no/1615/submissions?status=AC)と，このテクニックを導入している例は多い）．

### Price refinement

アルゴリズムの各ステップで，$2\epsilon$-optimal なフロー $f$ とポテンシャル $p$ の組が与えられたとき，$\epsilon$-optimal なフローとポテンシャルの組を新たに求めたい．これは本来のアルゴリズムでは push-relabel を実施すること等によって行われるが，状況によっては $f$ を更新することなく $p$ をうまく取り直すだけでこれが実現できることがある．具体的には，各辺のコストに $\epsilon$ のバイアスを加えた残余グラフ上のポテンシャルについて Bellman-Ford のアルゴリズムを実行し，負閉路が存在しなければそのときの解 $p'$ が所望の $p$ となる．

Bellman-Ford のアルゴリズムは愚直に実行すると $O(nm)$ の計算量を要するが，プログラミングコンテストではしばしば最大反復回数を本来の $n$ から小さい（$10$ 程度やそれ以下の）値に減らし，この回数のうちで $p'$ が求められた場合のみ price refinement を適用する高速化手法が見られる．本コードではテンプレート第 4 引数で最大反復回数をパラメータとして与える．

## 問題例

- [Library Checker: Minimum cost b-flow](https://judge.yosupo.jp/problem/min_cost_b_flow)
- [AtCoder Library Practice Contest E - MinCostFlow](https://atcoder.jp/contests/practice2/tasks/practice2_e)
- [No.1615 Double Down - yukicoder](https://yukicoder.me/problems/no/1615) （非想定解）

## Reference

- [1] A. V. Goldberg and R. E. Tarjan, "Finding minimum-cost circulations by successive approximation,"
      Mathematics of Operations Research, 15(3), 430-466, 1990.
- [2] A. V. Goldberg, "An Efficient Implementation of a Scaling Minimum-Cost Flow Algorithm,"
      Journal of algorithms, 22(1), 1-29, 1997.
- [ORIE 633: Network Flows](https://people.orie.cornell.edu/dpw/orie633/)
