---
title: Subset convolution （集合関数の各種演算）
documentation_of: ./subset_convolution.hpp
---

集合関数 $f(S)$ に関する各種演算．

## 使用方法

```cpp
vector<mint> f(1 << n), g(1 << n);
subset_sum(f);                      // T ⊂ S なる T に関する和．O(n 2^n)
subset_sum_inv(f);                  // subset_sum() の逆関数．O(n 2^n)
superset_sum(f);                    // T ⊃ S なる T に関する和．O(n 2^n)
superset_sum_inv(f);                // superset_sum() の逆関数．O(n 2^n)
auto h = subset_convolution(f, g);  // T ∪ U = S なる T, U に関する積の和．O(n^2 2^n)
subset_log(f);                      // f(φ) == 1 なる f について，log(f(S))．O(n^2 2^n)
subset_exp(f);                      // f(φ) == 0 なる f について，exp(f(S))．O(n^2 2^n)
subset_sqrt(f);                     // f(φ) == 1 なる f について，sqrt(f(S))．O(n^2 2^n)
subset_pow(f);                      // f(S)^k (O(n^2 2^n))
```

## 問題例

- [Subset Convolution - Library Checker](https://judge.yosupo.jp/problem/subset_convolution) `subset_convolution()`
- [F - Lights Out on Connected Graph](https://atcoder.jp/contests/arc105/tasks/arc105_f) 連結二部グラフの数え上げ．`subset_log()`
- [G - Connectivity 2](https://atcoder.jp/contests/abc213/tasks/abc213_g) 連結グラフの数え上げ．`subset_log()`
- [H - Hierarchical Phylogeny](https://atcoder.jp/contests/xmascon20/tasks/xmascon20_h) `subset_sqrt()`
- [No.1594 Three Classes - yukicoder](https://yukicoder.me/problems/no/1594) `subset_pow()`

## リンク

- [Xmas Contest 2020 H: Hierarchical Phylogeny 解説 - hos.lyric's blog](https://hos-lyric.hatenablog.com/entry/2021/01/14/201231) $\sqrt{f(S)}$ の計算アルゴリズムとその一般化．
- [Optimal Algorithm on Polynomial Composite Set Power Series - Codeforces](https://codeforces.com/blog/entry/92183) $\exp (f(S))$ の計算アルゴリズム（逆元不要）と一般の関数への拡張．
