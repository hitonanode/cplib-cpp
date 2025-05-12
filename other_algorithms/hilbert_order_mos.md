---
title: Mo's algorithm by Hilbert order （Hilbert order による区間クエリ平方分割）
documentation_of: ./hilbert_order_mos.hpp
---

Mo's algorithm の一種で，2 次元平面上の点として表現可能なクエリ群を Hilbert 曲線上の順序に従って処理する． $x, y$ 座標の値の範囲が $N$ でクエリが $Q$ 個のときの計算量は $O(N \sqrt{Q})$.

## 使用方法

### 一般の 2 次元平面上の点クエリの場合

```cpp
vector<Result> ret(Q); // 答えを格納する領域
int x_init = 0, y_init = 0;

MosAlgorithmHilbertOrder mo(x_init, y_init);
for (int q = 0; q < Q; q++) {
    mo.add(X[q], Y[q]);
}
auto inc_x = [&](int old_x, int new_x) -> void { /* x 座標が 1 増えて old_x から new_x になったときの処理 */ };
auto dec_x = [&](int old_x, int new_x) -> void { /* x 座標が 1 減って old_x から new_x になったときの処理 */ };
auto inc_y = [&](int old_y, int new_y) -> void { /* y 座標が 1 増えて old_y から new_y になったときの処理 */ };
auto dec_y = [&](int old_y, int new_y) -> void { /* y 座標が 1 減って old_y から new_y になったときの処理 */ };
auto solve = [&](int q) -> void { ret[q] = f(q); /* q 個目のクエリを解く処理 */ };

mo.run(inc_x, dec_x, inc_y, dec_y, solve);

for (auto ans : ret) cout << ans << '\n';
```

### 特に半開区間 $[l, r)$ クエリで区間の左右の伸張・収縮が同一の関数で書ける場合

```cpp
MosAlgorithmHilbertOrder mos(0, 0);
for (auto [l, r] : queries) {
    mos.add(l, r);
}

mos.run(
    [&](int i) { /* Add i */ },
    [&](int i) { /* Remove i */ },
    [&](int q) { /* ret.at(q) = get_solution(); */ }
);
```

## 問題例

- [AtCoder Beginner Contest 384 G - Abs Sum](https://atcoder.jp/contests/abc384/tasks/abc384_g)
- [AtCoder Beginner Contest 405 G - Range Shuffle Query](https://atcoder.jp/contests/abc405/tasks/abc405_g)

## Links

- [An alternative sorting order for Mo's algorithm - Codeforces](https://codeforces.com/blog/entry/61203)
- [Mo's algorithm - アルゴリズムとデータ構造大全](https://take44444.github.io/Algorithm-Book/range/mo/main.html)
