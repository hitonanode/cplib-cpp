---
title: Dyadic rational, surreal number （二進分数・固定小数点数，Conway の構成）
documentation_of: ./dyadic_rational.hpp
---

分母が二冪の有理数 `DyadicRational<Int, Uint = unsigned long long>` の実装，また超現実数の構成法に基づく $\\{ l \mid r \\}$ の計算．組合せゲーム理論などへの応用がある．

`Int` が整数部分を表すための符号付整数型で `int` や `long long` の利用を想定，`Uint` が小数部分を表すための符号なし整数型で `unsigned` や `unsigned long long` の利用を想定（`__uint128_t` も動くかもしれない）．メンバ変数 `integ`, `frac` がそれぞれ整数部分と小数部分に対応し，

$\displaystyle
x = \mathrm{integ} + \frac{\mathrm{frac}}{2^\mathrm{FracLen}}
$

がこのクラスのインスタンスが表す有理数 $x$ である．
実装の制約上分母のオーダーは（`Uint = unsigned long long` の場合）$2^{63}$ が上限となる．

## 使用方法

### `DyadicRational<Int>(Int x)`

コンストラクタ．整数 `x` に対応する元を生成する．

### `double to_double()`

インスタンスが表す有理数 $x$ を `double` 型に変換．

### `DyadicRational<Int> right()`

[Surreal number （超現実数）の構成過程を表す木](https://en.wikipedia.org/wiki/Surreal_number#/media/File:Surreal_number_tree.svg) において，現在の値 $x$ の右側の子の値を返す．

### `DyadicRational<Int> left()`

`right()` とは逆に，現在の値 $x$ の左側の子の値を返す．

### `DyadicRational<Int> DyadicRational<Int>::surreal(DyadicRational<Int> l, DyadicRational<Int> r)`

$l < r$ を満たす二進分数 $l$, $r$ について，$l < x < r$ を満たし surreal number の構成過程を表す木で根（$0$）に最も近い要素（Conway の記法に基づくと $\\{ l \mid r \\}$）の値を返す．$l < r$ を満たさない場合 runtime error となる．

現在は根から一歩ずつ `right()` または `left()` で探索していく実装になっているが，場合分けと bit 演算を頑張れば $O(1)$ になると思われる．

## 問題例

- [AtCoder Beginner Contest 229 H - Advance or Eat](https://atcoder.jp/contests/abc229/tasks/abc229_h)

### リンク

- [組合せゲーム理論入門(1)](http://www.ivis.co.jp/text/20111102.pdf) 組合せゲーム理論の観点からの解説．
- [解説 - NECプログラミングコンテスト2021(AtCoder Beginner Contest 229)](https://atcoder.jp/contests/abc229/editorial/2977) 非不偏ゲーム（Partisan Game）の問題例とその解き方．
  - [提出 #27486895 - NECプログラミングコンテスト2021(AtCoder Beginner Contest 229)](https://atcoder.jp/contests/abc229/submissions/27486895) Nyaan さんの実装．
