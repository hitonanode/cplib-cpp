---
title: Binary lifting / doubling （ダブリング）
documentation_of: ./doubling.hpp
---

Functional graph 上のダブリングライブラリ． binary_lifting.hpp とは異なり辺に重みなどは載せられない．

## 使用方法

### `BinaryLifting binary_lifting(std::vector<int> to)`

コンストラクタ．引数として $g(0), \ldots, g(n - 1)$ を与える．

直感的には，各頂点 $i = 0, \ldots, n - 1$ について $i$ から頂点 $g(i)$ へ有向辺が張られている functional graph に相当する． $g(i)$ の値は $0$ 未満や $n$ 以上でも構わない（下記の各関数は， $[0, n)$ の範囲外の頂点 $i$ からは $i$ 自身への重み $e$ の自己ループが生えている，と解釈するとつじつまが合うように設計されている）．

### `int kth_next(int s, long long k)`

$g^k (s)$ の値（途中で $[0, n)$ の範囲外に出る場合はその値）を $O(\log k)$ で返す．

### `int distance(int l, int r)`

$g^k (s)$ の値が初めて `r` 以上になる $k$ を計算する．この条件が満たされることはない場合は `-1` を返す．

この条件に関する単調性が必要．

## 問題例

- [No.3305 Shift Sort - yukicoder](https://yukicoder.me/problems/no/3305)
