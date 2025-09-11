---
title: Counting north-east lattice paths （2 次元グリッド上の最短路の数え上げ）
documentation_of: ./north_east_lattice_paths.hpp
---

2 次元グリッド上の最短路（特に， $(1, 0)$ 方向と $(0, 1)$ 方向のみ）の数え上げに関連する各種関数の実装．

## 使用方法

### `NorthEastLatticePathsParallel` 関数

2 次元平面上の $x$ 軸に平行なある線分上に初期重みが存在するとき， $x$ 軸に **平行な** 別の線分上の最終重みを取得する．

```cpp
using mint = ModInt998244353;

// bottom[i] := (i, 0) に置く初期重み
vector<mint> bottom = {/* ... */};

long long dx_init = 0;  // 最終重みを取り出す線分の左端の x 座標
long long y = 5;        // 最終重みを取り出す線分の y 座標
int len = 10;           // 最終重みを取り出す線分の長さ

// top[i] := (dx_init + i, y) 上の最終重み
auto top = NorthEastLatticePathsParallel<mint>(bottom, dx_init, y, len, convolve);
```

### `NorthEastLatticePathsVertical` 関数

2 次元平面上の $x$ 軸に平行なある線分上に初期重みが存在するとき， $x$ 軸に **垂直な** 別の線分上の最終重みを取得する．

```cpp
using mint = ModInt998244353;
auto convolve = [&](const vector<mint> &l, const vector<mint> &r) { return nttconv(l, r); }

// bottom[i] := (i, 0) に置く初期重み
vector<mint> bottom = {/* ... */};

int x = 7;        // 最終重みを取り出す線分の x 座標
int dy_init = 0;  // 最終重みを取り出す線分の下端の y 座標
int len = 8;      // 最終重みを取り出す線分の長さ

// right[i] := (x, dy_init + i) 上の最終重み
auto right = NorthEastLatticePathsVertical<mint>(bottom, x, dy_init, len, convolve);
```

### `NorthEastLatticePathsInRectangle` 関数

2 次元平面上の矩形の左辺と下辺上に初期重みが存在するとき，右辺と上辺上の最終重みを取得する．

```cpp
using mint = ModInt998244353;
auto convolve = [&](const vector<mint> &l, const vector<mint> &r) { return nttconv(l, r); }

// 左辺と下辺に置く初期重み
vector<mint> left   = {/* height = H */};   // (0, j)
vector<mint> bottom = {/* width  = W */};   // (i, 0)

// DP: dp[i,j] = dp[i-1,j] + dp[i,j-1] を矩形全域に伝播
auto res = NorthEastLatticePathsInRectangle<mint>(left, bottom, convolve);

// res.right: 右辺 (W-1, 0..H-1)、res.top: 上辺 (0..W-1, H-1)
const vector<mint> &right = res.right;
const vector<mint> &top   = res.top;
```

### `NorthEastLatticePathsBounded` 関数

2 次元平面上の矩形から左上部分を（へこみができないように）削った領域の左辺と下辺上に初期重みが存在するとき，右辺と上端における最終重みを取得する．

```cpp
using mint = ModInt998244353;
auto convolve = [&](const vector<mint> &l, const vector<mint> &r) { return nttconv(l, r); }

// 吸収境界 y = ub[i] （非減少）
vector<int> ub = {/* size = W, nondecreasing */};

// 左辺 (0, j) / 下辺 (i, 0) の初期重み
vector<mint> left(ub.front());
vector<mint> bottom(ub.size());

auto res = NorthEastLatticePathsBounded<mint>(ub, left, bottom, convolve);

// res.right: (W-1, 0..ub[W-1]-1)
// res.top[i]: (i, ub[i]-1) に到達する重み
```

### `NorthEastLatticePathsBothBounded` 関数

2 次元平面上の矩形から左上部分と右下部分を（へこみができないように）削った領域の左辺上に初期重みが存在するとき，右辺における最終重みを取得する．

```cpp
using mint = ModInt998244353;
auto convolve = [&](const vector<mint> &l, const vector<mint> &r) { return nttconv(l, r); }

// 各列ごとの下限/上限（いずれも非減少）
vector<int> lb = {/* size = W */};
vector<int> ub = {/* size = W */};

// 左辺の区間 [lb[0], ub[0]) に対応する初期重み
vector<mint> left(ub.front() - lb.front());
left[0] = 1;  // 例: (0, lb[0]) に 1 を置く

// 右端列 (W-1) の区間 [lb[W-1], ub[W-1]) に対応する配列を返す
auto col = NorthEastLatticePathsBothBounded<mint>(lb, ub, left, convolve);
```

### 応用：各項の上下限が指定された単調非減少整数列の数え上げ

上下限が指定された場合の関数 `template <class MODINT> MODINT CountBoundedMonotoneSequence(std::vector<int> lb, std::vector<int> ub, auto convolve)` と，上限のみが指定される場合（下限は $0$ で固定）の関数 `template <class MODINT> MODINT CountBoundedMonotoneSequence(std::vector<int> ub, auto convolve)` が用意されている．

```cpp
using mint = ModInt998244353;
auto convolve = [&](const vector<mint> &l, const vector<mint> &r) { return nttconv(l, r); }

// 上限のみ: 0 <= a[i] < ub[i]
vector<int> ub = {/* ... */};
mint ways1 = CountBoundedMonotoneSequence<mint>(ub, convolve);

// 下限/上限とも: lb[i] <= a[i] < ub[i]
vector<int> lb = {/* ... */};
mint ways2 = CountBoundedMonotoneSequence<mint>(lb, ub, convolve);
```

内部的には，下限側を 1 だけ右にシフトすることで，グリッド上の最短路の数え上げに帰着させている．

## 問題例

- [Good Bye 2022: 2023 is NEAR G. Koxia and Bracket - Codeforces](https://codeforces.com/contest/1770/problem/G)
- [AOJ 3335: 01 Swap](https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3335)
- [AtCoder Beginner Contest 357 G - Stair-like Grid](https://atcoder.jp/contests/abc357/tasks/abc357_g)
  - このライブラリのままのコードでは不足していて，若干工夫する必要がある．
- [Library Checker: Number of Increasing Sequences Between Two Sequences](https://judge.yosupo.jp/problem/number_of_increasing_sequences_between_two_sequences)

## リンク

- [上限付き単調増加列の数え上げ - noshi91のメモ](https://noshi91.hatenablog.com/entry/2023/07/21/235339)
- [グリッドの最短経路の数え上げまとめ - かんプリンの学習記録](https://kanpurin.hatenablog.com/entry/2021/09/15/220913#aruryoiki)
