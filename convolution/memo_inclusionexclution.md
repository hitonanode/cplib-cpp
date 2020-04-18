# 包除原理について

## 定式化

### 基本形

$$ A = \{ S_i \}_{1 \leq i \leq n} $$
は何らかの集合の部分集合族．

集合$S_i$たちの和集合の要素数を数えたいとき，

$$
\left| \bigcup_{i=1}^n S_i \right|
= \sum_i  \left| S_i \right| - \sum_{i < j} \left| S_i \cap S_j \right| + \ldots 
+ (-1)^{n - 1} \left| S_1 \cap \ldots \cap S_n \right|
$$

- 奇数個の共通部分は足して，偶数個の共通部分は引く．
- 計算量は$O(2^n)$．

### 別の形

各$S_i$は**満たしてほしくない条件**$i$に抵触している要素全体の集合．このとき全ての条件に抵触しない要素数は

$$
\left| \overline{ \bigcup_{i=1}^n S_i } \right|
= \left| \bigcap_i \overline{S_i} \right|
= \sum_{B \subseteq A} (-1)^{|B|} \left| \bigcap_{S \in B} S \right|
$$

- **実装の際に考えること** 満たしてほしくない条件たちの中で特定の$k$個を選び，これらに全て抵触するようなものを数え上げ，**$k$が偶数ならばそのまま寄与，奇数ならば-1倍が寄与**するとして全ての選び方に関する和を計算．
- 最終的に数え上げるのは上の「基本形」の補集合になっている．$S=\phi$の場合の項が全体集合で，他の項は-1倍．
