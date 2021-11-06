---
title: Cumulative sum of arithmetic functions （数論的関数の累積和）
documentation_of: ./arithmetic_cumsum.hpp
---

$f(s) = \sum_{k=1}^N a\_k k^s$ のような形式で表される数論的関数に対して，以下の処理をサポートする．

- 2つの数論的関数の積の計算（$O(N^{2/3} (\log N)^{1/3})$）．
- $\sum_{k=1}^{\lfloor N / i \rfloor} a\_k$ の値の取得（$O(1)$）．

なお，一つの関数の保持に $O(\sqrt{N})$ の空間計算量を要する．

## 使用方法

### 関数定義

有名な数学関数は専用の関数によって直ちに生成できる．

#### ゼータ関数

関数 $\sum\_{k = 1, \dots} k^x$ （$\mathbf{a} = (1, 1, \dots,)$）は
```cpp
long long n;
arithmetic_cumsum<mint> z = zeta_cumsum<mint>(n);
```
によって生成できる．生成に要する計算量は $O(n)$．

#### ゼータ関数のシフト

$\sum\_{i = 1, \dots} i^d i^x$ （$\mathbf{a} = (1^d, 2^d, \dots,)$）は以下で生成できる．与える型は `ModInt<>` や `atcoder::static_modint<>` を想定している．
```cpp
int k;
auto f = zeta_shift_cumsum<mint>(n, k);
```
生成に要する計算量は $O(nk)$．

#### 約数関数

$\sum\_{i = 1, \dots} \sum\_{d \mid i} d^k i^x$ は以下で生成できる．
```cpp
arithmetic_cumsum<mint> d = divisor_func_cumsum<mint>(n, k);
```
生成に要する計算量は $O(nk)$．

#### 自分で定義した関数

具体的に各項の係数を手で与えるには，以下のようにメンバ変数を設定すればよい．

- `a` : 長さ $K$．第 $i$ 要素（$0 \le i < K$）は $a\_{i + 1}$ の値に対応する．
- `A` : 長さ $K$．第 $i$ 要素（$0 \le i < K$）には $\sum\_{j = 1}^{i + 1} a\_{j}$ の値に対応する（`a` の累積和を持たせればよい）．
- `invA` : 長さ $L$．第 $i$ 要素（$0 \le i < L$）には $\sum\_{j=1}^{\lfloor N / (i + 1)\rfloor} a\_j$ の値を持たせる．

### サポートする演算

```cpp
arithmetic_cumsum<mint> f(N), g(N);  // 同一の N をもつもの同士に対してのみ演算が可能．

auto f2 = f + g;
auto f3 = f - g;
auto id = arithmetic_cumsum<mint>::identity(N);
auto h = f * g;
auto i = h / g;  // g の a_1 の値が逆元を持てば可能
assert(f == i);
mint t = f.sum(k);  // a_1 + ... + a_k を返す． k = floor(N / t) を満たす 1 <= t <= N が存在するような k のみ可能．
```

## 問題例

- [Library Checker: Sum of Totient Function](https://judge.yosupo.jp/problem/sum_of_totient_function)
- [AtCoder Regular Contest 116 C - Multiple Sequences](https://atcoder.jp/contests/arc116/tasks/arc116_c)

## リンク

- [Dirichlet 積と、数論関数の累積和 \| maspyのHP](https://maspypy.com/dirichlet-%e7%a9%8d%e3%81%a8%e3%80%81%e6%95%b0%e8%ab%96%e9%96%a2%e6%95%b0%e3%81%ae%e7%b4%af%e7%a9%8d%e5%92%8c)
