---
title: Lagrange interpolation（多項式の Lagrange 補間）
documentation_of: ./lagrange_interpolation.hpp
---

$N - 1$ 次多項式 $f(x)$ の $x = 0, \dots, N - 1$ における値から，所望の $x = x_\mathrm{eval}$ での $f(x)$ の値を復元する．計算量は $O(N + \log \mathrm{MOD})$．

## 原理

$N$ 点 $x_0, \dots, x_{N - 1}$ のうち $x_i$ で値 $y_i$ をとり他の $N - 1$ 点でゼロとなるような $N - 1$ 次多項式は

$\displaystyle
y_i \cdot \frac{(x - x_0)(x - x_1) \dots (x - x_{i - 1})(x - x_{i + 1}) \dots (x - x_{N - 1})}{(x_i - x_0)(x_i - x_1) \dots (x_i - x_{i - 1})(x_i - x_{i + 1}) \dots (x_i - x_{N - 1})}
$

と一意に定まる．よってこれを $i = 0, \dots, N - 1$ で重ね合わせればもとの $f(x)$ も復元できる．

$x = x_\mathrm{eval}$ での $f(x)$ の値を知るにはもとの関数を直接復元する必要はなく，各 $i$ について上の式に $x = x_\mathrm{eval}$ を代入して評価した結果を足し合わせればよい．$x_i$ たちが一般の配置の場合は分母の計算のため $O \left(N \left( \log N \right)^2 \right)$ の分割統治を行う必要があるが，$x_i$ が等間隔に並ぶ場合は分母の値が規則的になり，$O(N)$ で計算できる．具体的には， $x_{i + 1} = x_i + 1 \, (i = 0, \ldots, N - 2)$ のとき，

$\displaystyle
f(x_\mathrm{eval}) = \sum_{i = 0}^{N - 1} y_i \cdot \frac{\prod_{j=0}^{i-1} (x_\mathrm{eval} - x_j)\cdot \prod_{j=i+1}^{N-1} (x_\mathrm{eval} - x_j)}{i! (N - 1 - i)! \cdot(-1)^{N - 1 - i}}
$

と書ける．

## 使用方法

先頭の $d + 1$ 項を計算して `interpolate_iota()` 関数に与える．
```cpp
vector<mint> A(N + 1);
for (auto &a : A) cin >> a;

cout << interpolate_iota<mint>(A, 12345678910111213LL) << '\n';
```

## リンク

- [AtCoder Regular Contest 033 D - 見たことのない多項式](https://atcoder.jp/contests/arc033/submissions/22279922)
