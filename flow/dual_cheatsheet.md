# 最小費用流双対 チートシート

- [元ネタ1（iwiwiさん）](https://www.slideshare.net/wata_orz/ss-91375739)
- [元ネタ2（ei1333さん）](https://ei1333.hateblo.jp/entry/2019/12/15/094229)

## 「二変数の差または一変数」の区分線形関数の総和の最小化

$$ \min_{\mathbf{p}} \sum_v b_v p_v + \sum_{(u, v)} c_{uv} \cdot \max(0, p_v - p_u - w_{uv})  + \sum_v c_v \cdot \max(0, p_v - w_v)$$

ただし， 

- $c_{uv} > 0$
- $\sum_v b_v = 0$

### 解き方

- 最小費用流で解ける．各変数毎の頂点と，始点 $S$, 終点 $T$ を用意．また，一変数しかない項があるならば，仮想的な変数 $p_0$ を一個追加して， $p_v$ を$p_v - p_0$ に置き換える．
- 各項 $c_{uv} \cdot \max(0, p_v - p_u - w_{uv})$ について，$u \rightarrow v$ に $(Cap, Cost) = (c_{uv}, w_{uv})$ を張る
- 特に，絶対値 $c_{uv} \cdot |p_v - p_u - w_{uv}|$ の場合， $c_{uv} \cdot \max(0, p_v - p_u - w_{uv}) + c_{uv} \cdot \max(0, p_u - p_v - (-w_{uv}))$ なので，
  - （実装方針1） $u \rightarrow v$ に $(Cap, Cost) = (c_{uv}, w_{uv})$ を張り，更に $v \rightarrow u$ に $(Cap, Cost) = (c_{uv}, -w_{uv})$ を張る（コスト負の辺が張れるライブラリの場合）
  - （実装方針2） $v$ から $u$ に予め全量流してしまったものと仮定してしまう（コスト正の辺しか張れない・張りたくない場合）
- 各 $b_v \ne 0$ について，
  - $b_v>0$ なら $S \rightarrow v$ に $(Cap, Cost) = (b_v, 0)$ を張る
  - $b_v<0$ なら $v \rightarrow T$ に $(Cap, Cost) = (|b_v|, 0)$ を張る
- フローを $S \rightarrow T$ で流せるだけ流して，最小コストの $-1$ 倍が答え

### その他特記事項

- Dinicで使うヒープを [radix heap](https://github.com/iwiwi/radix-heap/blob/master/README_ja.md) にすると高速になる場合がある

## より一般的な形

流量下限制約付最小費用流で解ける一般的な形

$$ \max_{\mathbf{x}, \mathbf{y}, \mathbf{k}} \sum_e (l_e x_e - h_e y_e) - \sum_v D_v k_v$$

ただし，

- $(x_e - y_e) + (k_v - k_u) \le w_e$
- $x_e \ge 0$
- $y_e \ge 0$
- $k_v \ge 0$


### 解き方

- b-flowの一般的なライブラリを用意する
- 各頂点 $v$ に湧き出し $D_v$
- 各コスト $e = (u, v)$ について， $u\rightarrow v$ に容量制約 $l_e \le flow \le h_e$ コスト $w_e$ の辺を張る
- 最小費用循環流を流して，コストの値が答え
