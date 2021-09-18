---
title: Lyndon factorization （Lyndon 分解）
documentation_of: ./lyndon_factorization.hpp
---

文字列・数列などの比較可能なものの列に対して Lyndon 分解を行う．

## Lyndon 文字列

- $S$ が Lyndon 文字列であるとは，$S$ の（非空な）接尾辞の中で $S$ 自身が辞書順最小であること

## Lyndon 分解

- （定義）Lyndon 分解とは，文字列 $S$ の分割 $S = w_1 w_2 \dots w_M$ で，各 $w_i$ は Lyndon 文字列で，しかも $w_i$ たちが辞書順非増加であるもの．
- （一意性）Lyndon 分解は一意．
- （構成）$w_1$ は，$S$ の接頭辞で Lyndon であるような最長のもの．

## 実装されている関数

### lyndon_factorization

```cpp
vector<pair<int, int>> ret = lyndon_factorization(s);
```

- 文字列など比較可能な要素の列 `s` を Lyndon 分解した際の，（先頭位置，長さ）の組の列を出力
- 計算量 $O(N)$

### longest_lyndon_prefixes

``` cpp
vector<int> ret = longest_lyndon_prefixes(s, LCPLEN_Callable_obj);
```

- 各 suffix `s[i:N)` に関する最長な Lyndon prefix `s[i:i+len(i))` の長さ `len(i)` を格納した配列を出力
- 計算量 $O(NL)$
  - $L$ は `s[i:)` と `s[j:)` の longest common prefix 長の計算一回に要する計算量

### run_enumerate

``` cpp
ret = run_enumerate<LCPLEN_Callable>(s);
```

- 各 run について `(c, l, r)` （`s[l:r)` が最小周期 `c`，2 周期以上）を全列挙
- 計算量 $O(NL)$

### enumerate_lyndon_words

```cpp
int k, n;
vector<vector<int>> seqs = enumerate_lyndon_words(k, n);
```

- 各要素が $0, \dots, (k - 1)$ で長さ $n$ 以下の Lyndon 列を辞書順に全列挙する．
- これを応用すると，「[de Bruijn sequence - Wikipedia](https://en.wikipedia.org/wiki/De_Bruijn_sequence)」 $B(k, n)$ が構築できる．
  - de Bruijn sequence $B(k, n)$ とは，各要素が $0$ 以上 $k - 1$ 以下の整数からなる長さ $k^n$ の列で，その長さ $n$ の全ての連続部分列 $k^n$ 個（端は周期的に見る）が互いに相異なるもの．
  - $B(k, n)$ のうち特に辞書順最小のものは，「各要素が $0$ 以上 $k - 1$ 以下の整数で長さが $n$ の約数であるような Lyndon 列」全てを辞書順に並べて結合することで構築できることが知られている．

## 問題例

- [Run Enumerate - Library Checker](https://judge.yosupo.jp/problem/runenumerate)
- [2012-2013 Petrozavodsk Winter Training Camp, Saratov SU Contest G. Lyndon Words - Codeforces](https://codeforces.com/gym/100162/problem/G) Lyndon words を列挙する．
- [2018 ICPC Asia Jakarta Regional Contest C. Smart Thief - Codeforces](https://codeforces.com/gym/102001/problem/C) de Bruijn sequence を構築する．

## 参考文献・リンク

- [1] K. T. Chen, R. H. Fox, R. C. Lyndon,
  "Free Differential Calculus, IV. The Quotient Groups of the Lower Central Series,"
  Annals of Mathematics, 68(1), 81-95, 1958.
- [2] J. P. Duval, "Factorizing words over an ordered alphabet,"
  Journal of Algorithms, 4(4), 363-381, 1983.
- [3] H. Bannai et al., "The "Runs" Theorem,"
  SIAM Journal on Computing, 46(5), 1501-1514, 2017.
- [Lyndon factorization - Competitive Programming Algorithms](https://cp-algorithms.com/string/lyndon_factorization.html)
- [Lyndon 文字列入門 - Qiita](https://qiita.com/nakashi18/items/66882bd6e0127174267a)
