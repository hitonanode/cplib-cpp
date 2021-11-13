---
title: (Weighted) matroid intersection （（重みつき）マトロイド交叉）
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
- [Deltix Round, Summer 2021 H. DIY Tree - Codeforces](https://codeforces.com/contest/1556/problem/H) 少数の頂点に次数制約がついた最小全域木問題．グラフマトロイドと分割マトロイドの最小重み共通独立集合問題に帰着される．
- [2019 Petrozavodsk Winter Camp, Yandex Cup D. Pick Your Own Nim - Codeforces](https://codeforces.com/gym/102156/problem/D) 二値マトロイドと分割マトロイドの交差．
- [2128 - Demonstration of Honesty! - URI Online Judge](https://www.urionlinejudge.com.br/judge/en/problems/view/2128) 各辺に色がついている無向グラフで，同色の辺は一度しか使えない全域木構築判定問題．グラフマトロイドと分割マトロイドの交差．このライブラリでは TL が厳しいが，独立性を満たす範囲で乱択のアプローチ等によりある程度 $I$ に要素を追加した状態から増加路アルゴリズムを回すことで定数倍高速化し TL に間に合わせられる．
- [CodeChef October Challenge 2019: Faulty System](https://www.codechef.com/problems/CNNCT2) グラフマトロイドとグラフマトロイドの交差．
- [Rainbow Graph – Kattis, NAIPC 2018](https://naipc18.kattis.com/problems/rainbowgraph)
- [Google Code Jam 2019 Round 3 Datacenter Duplex](https://codingcompetitions.withgoogle.com/codejam/round/0000000000051707/0000000000158f1c)
- [AOJ GRL_2_B: 最小全域有向木](https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_B) 分割マトロイドとグラフマトロイドの重み付き交差でも解ける．
- [AOJ 1605: Bridge Construction Planning （橋の建造計画）](https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1605&lang=ja) 分割マトロイドとグラフマトロイドの重み付き交差．
- [2021 ICPC Asia Taiwan Online Programming Contest I. ICPC Kingdom - Codeforces](http://codeforces.com/gym/103373/problem/I) 横断マトロイドとグラフマトロイドの重み付き交差（横断マトロイドを考える代わりに辺を仮想的に増やし，分割マトロイドと解釈することも可能）．

## 文献・リンク集

- [1] A. Frank, "A weighted matroid intersection algorithm,"
  Journal of Algorithms, 2(4), 328-336, 1981.
- [2] C. Brezovec, G. Cornuéjols, and F. Glover, "Two algorithms for weighted matroid intersection,"
  Mathematical Programming, 36(1), 39-53, 1986.
- [離散最適化基礎論 (2015年度後学期) 組合せ最適化におけるマトロイドの役割](http://dopal.cs.uec.ac.jp/okamotoy/lect/2015/matroid/) とても初学者向き．
- [[Tutorial] Matroid intersection in simple words - Codeforces](https://codeforces.com/blog/entry/69287) コメント欄に問題例が多い．
