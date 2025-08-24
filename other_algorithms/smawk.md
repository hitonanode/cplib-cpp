---
title: Totally Monotone Matrix Searching (SMAWK), concave max-plus / min-plus convolution
documentation_of: ./smawk.hpp
---

`SMAWK()` 関数は，totally monotone な $N \times M$ 行列について，各行の最小値の位置およびその値を $O(N + M)$ で取得する．
また， totally anti-monotone （不等式の向きが逆，つまり行最小値の位置が行に対して単調非増加などの性質を持つ）な行列に対して同様に最小値を取得する `SMAWKAntiMonotone()` 関数も実装されている．

## 使用方法

### SMAWK

```cpp
using T = long long;
int H, W;
auto f = [&](int i, int j) -> T { return 0; };

const vector<pair<int, T>> argmin_min_pairs = SMAWK<T>(H, W, f);
```

### 応用例：concave max-plus convolution

列 $a = (a\_0, \dots, a\_{n - 1}), b = (b\_0, \dots, b\_{m - 1})$ で特に $b$ が concave なものが与えられたとき，$a$ と $b$ の max-plus convolution $c = (c\_0, \dots, c\_{n + m - 2})$:

$$
c_i = \max_{j + k = i} a_j + b_k
$$

は SMAWK を利用することで $O(n + m)$ で計算できる．

```cpp
vector<int> a, b;

vector<int> c = concave_max_plus_convolution<int, 1 << 30>(a, b);
```

### 応用例：concave min-plus convolution

上記と同様の状況設定で，逆に min-plus convolution も SMAWK を応用することで $O((n + m) \log (n + m))$ で計算できる．

このとき，SMAWK を適用したい仮想的な $(n + m - 1) \times n$ 行列は，無効値の位置の都合が悪く totally monotone でも totally anti-monotone でもないため直接扱えない．ここで，有効値が入った平行四辺形の領域をうまく矩形に分割していくことで `SMAWKAntiMonotone()` 関数が適用可能な状況にしている（この分割統治で計算量に log がつく）．

## 問題例

- [Communication Channel \| CodeChef](https://www.codechef.com/problems/COMMCHA)
- [Maximal Prefix After Flip \| CodeChef](https://www.codechef.com/problems/MAXPREFFLIP)
- [Min Plus Convolution (Convex and Arbitrary)](https://judge.yosupo.jp/problem/min_plus_convolution_convex_arbitrary)
- [Min Plus Convolution (Concave and Arbitrary)](https://judge.yosupo.jp/problem/min_plus_convolution_concave_arbitrary)

## Links

- [SMAWK Algorithm \| Library](https://noshi91.github.io/Library/algorithm/smawk.cpp.html)
