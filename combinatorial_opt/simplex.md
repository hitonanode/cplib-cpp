---
title: Simplex method （単体法）
documentation_of: ./simplex.hpp
---

## 解いてくれる問題

$\mathbf{A} \mathbf{x} \le \mathbf{b}, \ \mathbf{x} \ge \mathbf{0}$ のもと $\mathbf{c}^T \mathbf{x}$ を最大化．

## コードの要点

本実装のテクニックの大部分は [2] を参考に書かれたものです．

### initialize() について

解きたい問題に実行可能解が存在するか，また解が有限の値に収まるかは自明ではない．この状況に効率的に対処するために，（カジュアルに $\infty$ が登場して全く厳密な表現ではないが）もとの問題を解く代わりに

$\displaystyle
    \mathbf{M} = \begin{pmatrix}
    -\mathbf{A} & \mathbf{1} & \mathbf{b} \newline\\
    \mathbf{c}^\top & -\infty & 0
    \end{pmatrix}, \quad
    \mathbf{x}' = \begin{pmatrix} \mathbf{x} \newline\\ x_{N + 1} \newline\\ 1
    \end{pmatrix}
$

とおいて， $\mathbf{M} \mathbf{x}'$ の最終要素以外の全ての要素が非負という条件のもと $\mathbf{M} \mathbf{x}'$ の最終要素を最大化する問題を解くことにする．$x_{N + 1}$ の値を十分大きくすることでこの問題には必ず実行可能解が存在することに注意．また本実装では行列を二行拡張し，目的関数の値を上位・下位の二桁の位取りで記述することで無限大を表現している．最終的に $x_{N + 1} > 0$ ならば解は存在しない．

### 基底変数の取り替え

本問題は，$N$ 個の独立変数 $\mathbf{x} = [x_1, \dots, x_N]$ と $M$ 個の従属変数 $\mathbf{y} = [y_1, \dots, y_M], \ y_i = f_i(\mathbf{x})$, $f_i$ はアフィン関数，があって，$\mathbf{x} \ge 0, \ \mathbf{y} \ge 0$ のもとでの何らかのアフィン関数 $g(\mathbf{x})$ の最大化問題とみなせる．このとき，$x_j$ と $y_i$ は対称的な関係にあるから，適宜 $x_j$ と $y_i$ の要素を交換し，別の座標系 $[x_1, \dots, x_{j - 1}, y_i, x_{j + 1}, \dots, x_N]$ に乗り換えてしまっても大丈夫そうである（$N$ 次元 Euclid 空間という多様体に，様々な局所座標が入っているということ）．最大値を求めるのに都合の良い座標系へと次々に乗り換えていく（座標系の原点が，実行可能領域である多面体の特定の頂点に対応する）というのが単体法のやっていることである．

ある時点での独立変数を $\mathbf{x} = [x_1, \dots, x_j, \dots, x_N]$，従属変数を $\mathbf{y} = [y_1, \dots, y_i, \dots, y_M]$ とおいて，$\mathbf{y} = \mathbf{M} \mathbf{x}$ と書けるとする（定数項は適宜ベクトルを拡張して表現したものとする）．
簡単のため，基底変数 $x_N$ と非基底変数 $y_M$ を取り替えるとする．これを行うには，$\mathbf{y}' = [y_1, \dots, y_{M - 1}, x_N], \ \mathbf{x}' = [x_1, \dots, x_{N - 1}, y_M]$ として，$\mathbf{y}' = \mathbf{M}' \mathbf{x}'$ をみたす $\mathbf{M}'$ を求めればよい．これは，もともと $\mathbf{M}$ が

$\displaystyle
\mathbf{M} = 
\begin{pmatrix}
\mathbf{A} & \mathbf{b} \newline\\
\mathbf{c}^\top & d
\end{pmatrix}
$

と書けていたとすると，

$\displaystyle
\mathbf{M}' = 
\begin{pmatrix}
\mathbf{A} - \frac{\mathbf{b}\mathbf{c}^\top}{d} & \frac{\mathbf{b}}{d} \newline\\
-\frac{\mathbf{c}^\top}{d} & \frac{1}{d}
\end{pmatrix}
$

と書き下せる．

### 次の反復で取り替える基底の決定法

#### $x_j$ の決定

- ひとまずその時点で $c_j$ が正となるものを選ぶ．
  - 複数存在する場合は添字番号最小（Bland's rule）
- $\mathbf{c}$ の全要素が $0$ ならこれ以上解が改善しないので終了．

#### $y_i$ の決定

- 最も不等式制約が厳しいものを選ぶ．
  - さもなくば原点が実行可能領域から飛び出るので
  - 複数存在する場合は添字番号最小（Bland's rule）

#### ワーストケースの回避

- 指数回のステップを要する恣意的なケースが知られている．
- 特に [1] の p.43 (2.71) で挙げられているケースに関しては，変数・制約の順序をランダムに取り換えることで回避が可能であることを経験的に確認したので，デフォルトでこれを行うことにした．

## 問題例

- [AtCoder jag2018summer-day3 H - Enlarge Circles](https://atcoder.jp/contests/jag2018summer-day3/tasks/jag2018summer_day3_h)
- [SRM 694 Div.1 900 SRMDiv0Easy](https://community.topcoder.com/tc?module=ProblemDetail&rd=16766&pm=14319)
  - $N - 1$ 個の等式制約（$2(N - 1)$ 個の不等式制約に翻訳）と $Q$ 個の不等式制約下での $Q$ 変数 LP として本ソルバに与える
  - System Test Passed (34 ms)

## Reference

- [1] 梅谷「しっかり学ぶ数理最適化」講談社 2020.
  - 単体法の導出にあたって新たに $M$ 個のスラック変数を導入していて，このライブラリのアルゴリズムとは少々（少なくとも見た目において）違う（あまりちゃんと読んでいないが，確かめると実は同じかもしれない）．
- [2] https://kopricky.github.io/code/Computation_Advanced/simplex.html
