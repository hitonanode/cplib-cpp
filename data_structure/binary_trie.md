---
title: Binary trie
documentation_of: ./binary_trie.hpp
---

非負整数の集合や多重集合に対する一部のクエリを効率的に行うためのデータ構造．

## 使用方法

```cpp
using Key = int;
using Count = int;
const int D = 30;  // Key の桁数

BinaryTrie<Key, Count> trie(D);

for (int a : A) trie.insert(a);

Key t;
Count n = trie.count_less_xor(a, t);  // a ^ x < t を満たす x （x は現在存在する値）を数える

Key v = bt.xor_min(t);  // t ^ x （x は現在存在する値）の最小値を求める
```

## 問題例

- [Library Checker: Set Xor-Min](https://judge.yosupo.jp/problem/set_xor_min)
- [No.2977 Kth Xor Pair - yukicoder](https://yukicoder.me/problems/no/2977)
