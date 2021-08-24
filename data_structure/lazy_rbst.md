---
title: Randomized binary search tree with lazy propagation
documentation_of: ./lazy_rbst.hpp
---

> Do your RuBeSTy! ⌒°( ・ω・)°⌒

Randomized binary search tree を用いた動的な列に対するクエリを扱うデータ構造．インターフェースを `atcoder::lazy_segtree` に寄せている．一応 [D - グラフではない](https://atcoder.jp/contests/arc030/tasks/arc030_4) のために作成した永続版も残しているが [計算量の保証はない](https://yosupo.hatenablog.com/entry/2015/10/29/222536)．

## 使用方法

内部で `evert()` を使用する関数は根を変更してしまうので注意．

```cpp
struct S {
    mint sum;
    int sz;
};
using F = pair<bool, pair<mint, mint>>;
S op(S l, S r);
S mapping(F f, S x);
S reversal(S x);
F composition(F fnew, F gold);
F id();

lazy_rbst<1000001, S, op, F, reversal, mapping, composition, id> rbst;
vector<S> A(N);
auto root = rbst.new_tree();
rbst.assign(root, A);
rbst.insert(root, i, S{x, 1});
rbst.erase(root, i);
rbst.reverse(root, l, r);
rbst.apply(root, l, r, F{true, {b, c}});

const S e;  // 単位元
int i = rbst.max_right(root, e, [](S f) { return e < f; }); // rbst.prod(root, 0, i) が true となるような最大の i を返す．単調性を仮定．atcoder::lazy_segtree と同じ．
int j = rbst.min_left(root, e, [](S f) { return e < f; }); // rbst.prod(root, j, size(root)) が true となるような最小の j を返す．単調性を仮定．atcoder::lazy_segtree と同じ．
cout << rbst.prod(root, l, r).sum << '\n';
```

## 問題例

- [D - グラフではない](https://atcoder.jp/contests/arc030/tasks/arc030_4)
- [Dashboard - Algorithms Thread Treaps Contest - Codeforces](https://codeforces.com/gym/102787)
- [Codeforces Round #740 (Div. 1, based on VK Cup 2021 - Final (Engine)) D. Top-Notch Insertions - Codeforces](https://codeforces.com/contest/1558/problem/D)

## 参考文献・リンク・参考にした実装

- [RBSTがコピー可能は嘘という疑惑 - よすぽの日記](https://yosupo.hatenablog.com/entry/2015/10/29/222536)
- [永続 RBST を撃墜するケース \| mitaki28.info blog](http://blog.mitaki28.info/1446205599273/)
