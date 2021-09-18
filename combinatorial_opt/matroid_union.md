---
title: Matroid union （マトロイドの合併）
documentation_of: ./matroid_union.hpp
---

2つのマトロイド $M\_{1} = (E, \mathcal{I}\_{1}), M_{2} = (E, \mathcal{I}\_{2})$, $\mathcal{I}\_{1}$ に関して独立な集合 $I_1$, $\mathcal{I}\_{2}$ に関して独立な集合 $I\_2$ で $I\_1 \cup I\_2 = \emptyset$ を満たすものが与えられたとき，$I'\_1 + I'\_2 = I\_1 + I\_2 + \\{ e \\}$ を満たす新たな排反な独立集合 $I'\_1, I'\_2$ を見つけるアルゴリズム．特に重み最小の $e$ から貪欲に追加を試すことで，「合併したマトロイド」の最小重みサイズ $k$ 独立集合が $k = 1, 2, \dots$ について順次求められる．

これを応用すると，与えられた重み付き無向グラフについて，辺素な二つの全域木であって重みの総和が最小なものを見つけることも可能．

## アルゴリズムの概要

$\|E\| = n$ として，$e = 1, \dots, n$ に $s$, $t$ を加えた $n + 2$ 頂点のグラフに次の要領で辺を張る：

- $e \notin I\_1 \cup I\_2$ のとき，$s \rightarrow e$ （重み $0$）を張る．
- $e \notin I\_j$ かつ $I\_j + \\{e \\}$ が $M\_j$ における独立集合のとき， $e \rightarrow t$ （重み $w(e)$）を張る．$(j = 1, 2)$
- $e \notin I\_j$ かつ $I\_j + \\{e \\}$ が $M\_j$ における従属集合のとき，サーキットに含まれる各 $f$ について $e \rightarrow f$ （重み $1$）を張る．$(j=1, 2)$

このグラフで $s$ から $t$ への最短路を求め，$s$ の次に通った要素が新たに追加される（$s$ から $t$ に到達不能ならば $I\_1 \cup I\_2$ は既に合併したマトロイド上の最大独立集合である）．それ以降に通った要素は既に $I\_1$ または $I\_2$ に含まれているが，これらを集合間で出し入れすることで $I\_1$ と $I\_2$ の独立性が保たれる．

本コードには実装されていないが，3 個以上のマトロイドの合併に対しても同様のアルゴリズムが適用可能である．

## 使用方法

- `bool augment_union_matroid(matroid1, matroid2, I1, I2, weight)` 関数は，上述の追加可能な重み最小要素 $e$ を見つけ，$I\_1$ および $I\_2$ を追加後の状態に更新する．要素の追加が行われたならば `true` を，そうでなければ `false` を返す．
- `pair<vector<bool>, vector<bool>> MinWeightMaxIndepSetInUnionMatroid(matroid1, matroid2, weight)` 関数は，`augment_union_matroid()` 関数を繰り返し適用することで，2つのマトロイドを合併したマトロイドにおける（重み最小な）最大独立集合を構成する．

## 問題例

- [Hamel Paths \| CodeChef](https://www.codechef.com/problems/HAMEL) 無向グラフから2つの全域木を作る．
- [SRM 685 Div.1 450 FoxAirline2](https://community.topcoder.com/stat?c=problem_statement&pm=14194&rd=16689) 無向グラフから2つの全域木を作れるか判定する．
- [2018 TCO Round 3A 1000 ColoringEdgesDiv1](https://community.topcoder.com/stat?c=problem_statement&pm=14909&rd=17198) 各頂点の次数が3の単純無向グラフ（$n \le 1000, m = 3n/2$）の辺を2つの全域森に分割する方法を構成する．最初に乱択で辺を追加して全域森2つの初期解を構成し，その後全ての辺を割り当て終えるまで `augment_union_matroid()` を真面目に使用するというヒューリスティックによって [最大 200 ms 程度の実行時間で用意された全ケースに通る](https://vjudge.net/solution/32788901)（ただし，後述するように無向グラフの全域森への分割にはより高速なアルゴリズムが存在する：`edge_disjoint_min_spanning_forests.hpp` 参照）．

## 参考文献・リンク

- [1] J. Edmonds, "Minimum partition of a matroid into independent subsets,"
  J. Res. Nat. Bur. Standards Sect. B 69, 67-72, 1965.
- [18.438: Advanced Combinatorial Optimization, Fall 2009](http://www-math.mit.edu/~goemans/18438F09/18438.html): [lec13.pdf](http://www-math.mit.edu/~goemans/18438F09/lec13.pdf)
- [Matroid partitioning - Wikipedia](https://en.wikipedia.org/wiki/Matroid_partitioning#cite_ref-e65_3-0)
- [離散最適化基礎論 (2015年度後学期) 組合せ最適化におけるマトロイドの役割](http://dopal.cs.uec.ac.jp/okamotoy/lect/2015/matroid/): [handout12.pdf](http://dopal.cs.uec.ac.jp/okamotoy/lect/2015/matroid/handout12.pdf)
- [AlgoWiki - Matroid](https://wiki.algo.is/Matroid) 問題へのリンクが豊富．
- [様々な全域木問題](https://www.slideshare.net/tmaehara/ss-17402143) 特に無向グラフのの辺素な全域森への分割を考える場合，より高速なアルゴリズムが存在する．
