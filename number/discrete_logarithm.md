---
title: Discrete logarithm / Baby-step giant-step （離散対数問題）
documentation_of: ./discrete_logarithm.hpp
---

以下， $S$ を集合， $F$ を $S$ から $S$ への写像の集合で，特に合成写像が効率的に計算できるものとする（ [AC Library の Lazy Segtree]([atcoder.github.io/ac-library/production/document_ja/lazysegtree.html](https://atcoder.github.io/ac-library/production/document_ja/lazysegtree.html)) とおおむね同様）．
このコードは， $s, t \in S$ および $f \in F$ が与えられたとき， $f^n (s) = t, 0 \le n \le m$ を満たす最小の非負整数 $n$ を $O(\sqrt{m})$ で求める．

ここで $S$ の位数が既知の場合， $m$ にはその値を指定すれば解が（存在すれば）必ず見つかるので， $S$ の位数があまり大きくない場合は高速に解が見つかることが期待できる．

また， $S$ が特にモノイドのとき， $S$ の元 $x, y$ について， $x^n = y$ を満たす最小の正の $n$ を求めることもできる．

## 実装されているアルゴリズムについて

$F$ の元 $f$ を固定すると， $S$ の各元 $x$ から $f(x)$ に有向辺を張ってできる有向グラフは functional graph となる．

$S$ の元 $s, t$ が与えられ， $f^n (s) = t$ を満たす $n$ を求めたい状況を考える．このコードは，適当な非負整数 $k$ をとって $t, f(t), f^2 (t), \ldots, f^{k - 1} (t)$ を予め計算しておき， $s$ に対して $f^k$ を繰り返し作用させてこれらのいずれかに一致するタイミングを検索する．

なおこの検索は， 2 度マッチするまでループを回す必要がある点に注意（上述の functional graph 上で， $s$ を始点とするパスが $t$ を始点とするパスと $t$ から少しだけ進んだタイミングで合流し，その後ぐるっと回って $t$ に初めて到達するようなケースがあるので）．

## 使用方法

### 一般の問題（ $f^n (s) = t$ ）

$f^n (s) = t$, $0 \le n \le m$ を満たす最小の整数 $n$ を以下のコードで求める．解がない場合は `-1` を返す． `DiscreteLogarithm()` の内部で`mapping()` は $O(\sqrt{m})$ 回， `composition()` は $O(\log m)$ 回呼ばれる．

```cpp
auto mapping = [&](F f, S x) -> S {
    /* Implement */
};
auto composition = [&](F f, F g) -> F {
    /* Implement */
};

F f;
S s, t;
long long m;

long long ret = DiscreteLogarithm<S, F, std::unordered_set<S>>(f, s, t, mapping, composition, m);
```

なお，特に $S = F$ の場合には $x, y \in S$ に対して以下のコードで $x^n = y$ を満たす最小の **正の** 整数 $n$ を以下のコードで求められる．

```cpp
auto op = [&](S x, S y) -> S {};
S x, y;
long long m;
long long ret = DiscreteLogarithmNonzero(x, y, op, m);
```

### 剰余類環の離散対数問題（ $x^n \equiv y \mod m$ ）

与えられた非負整数 $x, y, m$ について， $x^n \equiv y \mod m$ を満たす最小の非負整数 $n$ を返すか、存在しない場合 $-1$ を返す．計算量は $O(\sqrt{m})$ である．
なお内部で乗算オーバーフロー回避のため `__int128` を使用しているが， $m$ が $10^9$ 程度に収まるなら `long long` に書き換えると若干高速になる．

```cpp
int x, y, m;
const int res = DiscreteLogarithmMod(x, y, m);
```

最小の **正の** 整数解を求めたい場合は代わりに `DiscreteLogarithmModNonzero` 関数を使うとよい．

## 問題例

`S`, `F` の型に応じて分類した．

### 剰余環

- [Library Checker: Discrete Logarithm](https://judge.yosupo.jp/problem/discrete_logarithm_mod)
- [AtCoder Regular Contest 042 D - あまり](https://atcoder.jp/contests/arc042/tasks/arc042_d)
- [No.551 夏休みの思い出（２） - yukicoder](https://yukicoder.me/problems/no/551)

### $S, F$: 対称群

- [No.101 ぐるぐる！あみだくじ！ - yukicoder](https://yukicoder.me/problems/no/101)
- [No.261 ぐるぐるぐるぐる！あみだくじ！ - yukicoder](https://yukicoder.me/problems/no/261)

### $S, F$: 有限体上の 2 次正方行列

行列の det が初めて一致する時刻と，作用の行列の累乗が 1 になる周期をそれぞれ離散対数問題として求めて，その上で再度完全に行列が一致する時刻を求める必要がある．詳細は下記の問題に対する本リポジトリのテストコード参照．

- [No.3170 [Cherry 7th Tune KY] Even if you could say "See you ..." - yukicoder](https://yukicoder.me/problems/no/3170)
- [No.950 行列累乗 - yukicoder](https://yukicoder.me/problems/no/950)
- [Fibonacci Mod Round #59 (Div. 2 only)](https://csacademy.com/contest/round-59/task/fibonacci-mod)
- [L. FF?DLP - Monoxer Programming Contest for Engineers](https://mofecoder.com/contests/monoxercon_202508/tasks/monoxercon_202508_l)
  - 複素数 $x + yi$ を行列 $\begin{pmatrix} x & -y \\ y & x\end{pmatrix}$ と置き換えて考えるとよい．

### $S$: （位数があまり大きくない）環， $F$: $S$ 上の一次関数

- [N - Paken Machine](https://atcoder.jp/contests/pakencamp-2022-day1/tasks/pakencamp_2022_day1_n)
- [AtCoder Beginner Contest 222 G - 222](https://atcoder.jp/contests/abc222/tasks/abc222_g)
- [AtCoder Beginner Contest 270 G - Sequence in mod P](https://atcoder.jp/contests/abc270/tasks/abc270_g)

## 参考文献・リンク

- [モノイド作用に関する離散対数問題 | maspyのHP](https://maspypy.com/%e3%83%a2%e3%83%8e%e3%82%a4%e3%83%89%e4%bd%9c%e7%94%a8%e3%81%ab%e9%96%a2%e3%81%99%e3%82%8b%e9%9b%a2%e6%95%a3%e5%af%be%e6%95%b0%e5%95%8f%e9%a1%8c)
