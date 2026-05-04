---
title: Persistent segtree （完全永続セグメント木）
documentation_of: ./persistent_segtree.hpp
---

完全永続版のセグメント木．各点更新のたびに新しい版の根を返し，過去の任意の版に対して 1 点更新や区間積クエリを行える．インターフェースは `atcoder::segtree` に近く，第一引数に更新のもととなる版の根を与える点が異なる．

## 使用方法

```cpp
struct S {
    unsigned long long sum;
    int len;
};
S op(S l, S r) { return {l.sum + r.sum, l.len + r.len}; }
S e() { return {0, 0}; }

vector<S> A(N, {0, 1});
persistent_segtree<S, op, e> seg(A);

auto root0 = seg.get_root();              // 初期版
auto root1 = seg.set(root0, idx, {x, 1});   // idx 番目を更新した新しい版

S x = seg.get(root0, idx);                  // root0 版の idx 番目の値
S y = seg.prod(root1, l, r);              // root1 版の [l, r) の積
S z = seg.all_prod(root1);                // root1 版の列全体の積

int i = seg.max_right(root1, l, [](S x) { return x.sum <= lim; });
int j = seg.min_left(root1, r, [](S x) { return x.sum <= lim; });
```

`max_right`, `min_left` の意味は `atcoder::segtree` と同じ．すなわち，`f(e()) = true` を満たす単調な述語 `f` に対して，

- `max_right(root, l, f)` は `prod(root, l, r)` が `f` を満たすような最大の `r` を返す．
- `min_left(root, r, f)` は `prod(root, l, r)` が `f` を満たすような最小の `l` を返す．

計算量は以下の通り．

- 構築 $O(N)$
- `set` $O(\log N)$ 時間，更新 1 回あたり追加ノード数 $O(\log N)$
- `get`, `prod`, `max_right`, `min_left` $O(\log N)$
- `all_prod` $O(1)$

## 問題例

- [The 1st Universal Cup. Stage 15: Hangzhou G. Game: Celeste - Problem - QOJ.ac](https://qoj.ac/contest/1221/problem/6400)
- [AtCoder Beginner Contest 453 G - Copy Query](https://atcoder.jp/contests/abc453/tasks/abc453_g)

## Link

- [永続セグメント木 - AtCoderInfo](https://info.atcoder.jp/entry/algorithm_lectures/persistent_segment_tree)
