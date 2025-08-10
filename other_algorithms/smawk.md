---
title: Totally Monotone Matrix Searching (SMAWK)
documentation_of: ./smawk.hpp
---

Totally monotone な $N \times M$ 行列について，各行の最小値の位置を $O(N + M)$ で取得する．

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

## 問題例

- [Communication Channel \| CodeChef](https://www.codechef.com/problems/COMMCHA)
- [Maximal Prefix After Flip \| CodeChef](https://www.codechef.com/problems/MAXPREFFLIP)

## Links

- [SMAWK Algorithm \| Library](https://noshi91.github.io/Library/algorithm/smawk.cpp.html)
