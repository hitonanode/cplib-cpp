---
title: Wavelet matrix （ウェーブレット行列）
documentation_of: ./wavelet_matrix.hpp
---

静的な数列の各種区間クエリをクエリあたり $O(\log \sigma)$ で行えるデータ構造．また，長さ $n$ の列の区間和クエリを高速に処理可能なデータ構造を外部で $\lceil \lg \sigma \rceil$ 個追加で持つことで，「数列の区間で値が特定の要素未満のもの」に関する総和取得が可能．ここで， $\sigma$ は入力の数列のとりうる値の個数．

### 扱える対象

#### 数列

長さ $n$ の数列 $a = (a\_0, \ldots, a\_{n - 1})$ を入力として扱える．

#### 2 次元平面上の頂点集合

2 次元平面上の相異なる点 $(x, y)$ たちを扱える．

## 使用方法

### 数列で初期化する場合

```cpp
vector<long long> A;
wavelet_matrix<long long> wm(A);
```

なお内部的には， 2 次元平面上の頂点 $(i, A\_i)$ $(i = 0, \ldots, n - 1)$ として扱われる．

### 2 次元平面上の頂点集合で初期化する場合

```cpp
wavelet_matrix<lint> wm;
vector<pair<lint, lint>> points;
for (auto [p, q] : points) {
    wm.add_point(p, q);
}
wm.build();
```

### 利用

#### Binary indexed tree を利用して point add rectangle sum を解く例

```cpp
wavelet_matrix<int> wm;
/* add points */
wm.build();

// Initialize external data structure
vector weights(wm.D(), BIT<long long>(wm.N()));

// Add weight
std::vector<std::tuple<int, int, long long>> points;
for (auto [i, j, x] : points) {
    wm.apply(i, j, [&weights, x](int d, int idx) { weights[d].add(idx, x); });
}

// Get rectangle sum
long long ans = 0;

int xl, xr, yl, yr;
wm.prod(xl, xr, yr, [&weights, &ans](int d, int l0, int r0) {
    ans += weights[d][r0] - weights[d][l0];
});
wm.prod(xl, xr, yl, [&weights, &ans](int d, int l0, int r0) {
    ans -= weights[d][r0] - weights[d][l0];
});

cout << ans << endl;
```

## 問題例

- [Library Checker: Point Add Rectangle Sum](https://judge.yosupo.jp/problem/point_add_rectangle_sum)
- [Library Checker: Static Range Sum with Upper Bound](https://judge.yosupo.jp/problem/static_range_sum_with_upper_bound)
- [yukicoder No.3207 Digital Font](https://yukicoder.me/problems/no/3207)

## 参考文献・リンク

- [ウェーブレット行列(wavelet matrix) - Eating Your Own Cat Food](https://miti-7.hatenablog.com/entry/2018/04/28/152259)
- [Wavelet Matrix \| Nyaan’s Library](https://nyaannyaan.github.io/library/data-structure-2d/wavelet-matrix.hpp.html)
