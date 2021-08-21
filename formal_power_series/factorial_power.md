---
title: factorial power （階乗冪に関する演算）
documentation_of: ./factorial_power.hpp
---

下降階乗冪（下降冪） $x^{\underline{i}} = x \cdot (x - 1) \cdots (x - (i - 1))$ を用いた多項式 $f(x)$ の展開係数

$\displaystyle
f(x) = \sum_{i=0}^{N-1} a_i x^{\underline{i}}
$

に関する各種演算．

## 階乗冪・サンプリング値の変換

高々 $(N - 1)$ 次の多項式 $f(x)$ について，値の列 $[f(0), \dots, f(N - 1)]$ と下降冪による展開係数 $\{ a_i \}_{i=0, \dots, N - 1}$ は $O(N \log N)$ で相互に変換可能．関数 `ys_to_factorial(vector<T> ys)` によって前者から後者の， `factorial_to_ys(vector<T> as)` によって後者から前者の変換がそれぞれ可能．

### アルゴリズムの概要

下降冪の定義より，

$\displaystyle
\frac{f(i)}{i!} = \sum_{j=0}^i \frac{a_j}{(i - j)!}
$

が成立．これより，$A(x) = \sum_i a_i x^i$ とおくと，

$\displaystyle
[[x^i]] (\exp(x) \cdot A(x)) = \frac{f(i)}{i!}
$

となり，これは畳み込みの形．

## 下降冪係数表現された多項式のシフト

多項式 $f(x)$ の下降冪表現 $\{a_i\}_{i = 0, \dots, N - 1}$ から $f(x + c)$ の下降冪表現は $O(N \log N)$ で計算可能．関数 `shift_of_factorial(vector<T> as, T shift)` が実装されている．

### アルゴリズムの概要

下降冪に関して（二項定理のような）等式

$\displaystyle
(a + b)^{\underline{n}} = \sum_{k=0}^n \binom{n}{k} a^{\underline{k}} b^{\underline{n - k}}
$

が成立することを用いると，シフトされた多項式 $f(x + c)$ は $f(x)$ の展開係数を用いて

$\displaystyle
f(x + c) = \sum_{i=0}^{N - 1} a_i (x + c)^{\underline{i}}
= \sum_{i = 0}^{N - 1} \sum_{j = 0}^{i} a_i \frac{i!}{j! (i - j)!} c^{\underline{j}} x^{\underline{i - j}}
$

と書けて，この等式の各次の係数は数列 $[a_{N - 1} (N - 1)!, \dots a_i i!, \dots, a_0]$ と $[c^{\underline{0}} / 0!, \dots, c^{\underline{i}} / i!, \dots, c^{\underline{N - 1}} / (N - 1)!]$ を畳み込むことで計算可能．

## 多項式関数の値の区間外挿

以上のアルゴリズムを組み合わせることで，高々 $(N - 1)$ 次の多項式関数 $f(x)$ について $f(0), \dots, f(N - 1)$ が既知のとき，$f(c), \dots, f(c + M - 1)$ の値の一括計算が $O((N + M)\log (N + M))$ で可能．関数 `shift_of_sampling_points(vector<T> ys, T c, int M)` が実装されている．


## 使用方法

```cpp
vector<mint> as{2, 3, 5}; // f(x) = 2 + 3x + 5x(x - 1) = 5x^2 - 2x + 2
auto ys = factorial_to_ys(as); // [2,5,18,] : f(0), f(1), f(2)
assert(ys_to_factorial(ys) == as);

auto shifted_as = shift_of_factorial<mint>(as, 10);  // f(x) => f(x + 10)

auto shifted_ys = shift_of_sampling_points<mint>(ys, 10000, 50); // f(10000), ..., f(10049) を計算
```

### 応用例：第二種スターリング数の計算

第二種スターリング数 $S(n, k)$ は

$\displaystyle
x^n = \sum_{k=0}^n S(n, k) x^{\underline{k}}
$

と定義される．固定した $n$ に対する $S(n, 0), \dots, S(n, n)$ の値は
```cpp
auto ys = Sieve(N).enumerate_kth_pows<mint>(N, N);
const auto stirling_number_of_2nd = ys_to_factorial(ys);
```
によって $O(n \log n)$ で計算できる．


## リンク

- [階乗冪 - Wikipedia](https://ja.wikipedia.org/wiki/%E9%9A%8E%E4%B9%97%E5%86%AA)
- [[問題案] Shift of Sampling Points · Issue #680 · yosupo06/library-checker-problems](https://github.com/yosupo06/library-checker-problems/issues/680)
- [Library Checker: Stirling Number of the Second Kind](https://judge.yosupo.jp/problem/stirling_number_of_the_second_kind)
