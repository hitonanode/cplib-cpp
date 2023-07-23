---
title: Binary lifting / doubling （ダブリング）
documentation_of: ./binary_lifting.hpp
---

Functional graph 上のダブリングライブラリ．

## 使用方法

### `binary_lifting(const std::vector<int> &g, const std::vector<S> &w)`

コンストラクタ．引数として $g(0), \ldots, g(n - 1)$ および $w(0), \ldots, w(n - 1)$ を与える．型 `S` は演算 `S op(S, S)` が結合法則を満たせばなんでもよい．

直感的には，各頂点 $i = 0, \ldots, n - 1$ について $i$ から頂点 $g(i)$ への重み $w(i)$ の有向辺が張られている functional graph に相当する． $g(i)$ の値は $0$ 未満や $n$ 以上でも構わない（下記の各関数は， $[0, n)$ の範囲外の頂点 $i$ からは $i$ 自身への重み $e$ の自己ループが生えている，と解釈するとつじつまが合うように設計されている）．

### `int kth_next(int s, Int k)`

$g^k (s)$ の値（途中で $[0, n)$ の範囲外に出る場合はその値）を前計算 $O(n \log k)$ ・クエリ $O(\log k)$ で返す．

#### `int pow_next(int s, int d)`

特に $g^{2^d}(s)$ の値を返す．前計算が済んでいればクエリ $O(1)$．

### `S prod(int s, Int len)`

列 $(s, g(s), \ldots, g^{\mathrm{len} - 1} (s))$ の各要素 $x$ に関する値 $w(x)$ をとり，これら全ての積をとる（途中で $[0, n)$ の範囲外に出る場合，それ以降の要素は無視される）．

#### `const S &pow_prod(int s, int d)`

特に $w(s) \cdot w(g(s)) \cdot \ldots \cdot w(g^{2^d - 1}(s))$ を返す．前計算が済んでいればクエリ $O(1)$．

### `int distance_monotone(int start, int left_goal, int right_goal)`

$g^k (s)$ の値が初めて `left_goal` 以下または `right_goal` 以上になる $k$ を計算する．この条件が満たされることはない場合は `-1` を返す．

この条件に関する単調性が必要． $O(n \log n)$ の前計算が済んでいればクエリ $O(\log n)$．

### `long long max_length(int s, F f, int maxd = 60)`

`f(prod(s, len))` が `true` と評価される $2^{\mathrm{maxd}}$ 以下の最大の `len` を返す． `f(prod(s, len))` の単調性が必要．

## 問題例

- [No.1013 〇マス進む - yukicoder](https://yukicoder.me/problems/no/1013)
- [No.2242 Cities and Teleporters - yukicoder](https://yukicoder.me/problems/no/2242)
