---
title: groupby
documentation_of: ./groupby.hpp
---

`Key` と `Value` のペアからなる値の列を，`Key` の値に基づいて分類する．`std::map` などを使用しても同様のことは実現できるが，本実装では `std::vector` に対する `std::stable_sort` のみを用いているため定数倍が良い可能性がある．
AtCoder Library のコピー．

## 問題例

- [AtCoder Beginner Contest 259 Ex - Yet Another Path Counting](https://atcoder.jp/contests/abc259/tasks/abc259_h)
