---
title: Range Tree with binary indexed tree （領域木）
documentation_of: ./rangetree_bit.hpp
---

二次元平面における以下のクエリをオンラインで効率的に処理．

- $(x, y)$ に重み $w$ を追加．
- 矩形領域 $\left[x_\mathrm{l}, x_\mathrm{r}\right) \times \left[y_\mathrm{l}, y_\mathrm{r}\right)$ の内側の重みの総和を回答．

ただし，重みを追加する候補となる点は予め列挙しておく必要がある．また，逆元が必要．モノイドを載せたい場合は `rangetree.hpp` を使用する．

## 使用方法

- `rangetree_bit<S, add, sub, e, Int>()` コンストラクタ．`S` は可換な群，`add(S&, S)`, `sub(S&, S)` は `S` 上の加減算，`e()` は `S` の零元を返す．`Int` は座標を表す数値の型．
- `void build()` 時間計算量，空間計算量とも $O(N \log N)$ （$N$ は候補点の個数）．
- `void add(Int x, Int y, S w)` 時間計算量 $O(N (\log N)^2)$．
- `S sum(Int xl, Int xr, Int yl, Int yr)` 時間計算量 $O(N (\log N)^2)$．

## 使用例

```cpp
using S = unsigned long long;
S e() noexcept { return 0; } // 単位元
void opadd(S &l, S r) noexcept { l += r; }
void opsub(S &l, S r) noexcept { l -= r; }

int main() {
    rangetree_bit<S, opadd, opsub, e, long long> tree;
    for (auto [x, y] : points) tree.add_point(x, y);
    tree.build();

    tree.add(x, y, w);

    cout << tree.sum(l, r, d, u) << '\n';
}
```

## 問題例

- [Library Checker: Point Add Rectangle Sum](https://judge.yosupo.jp/problem/point_add_rectangle_sum)
- [Codeforces Round #499 (Div. 1) E. Store](https://codeforces.com/contest/1010/problem/E)
