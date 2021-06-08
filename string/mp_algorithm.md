---
title: MP algorithm
documentation_of: ./mp_algorithm.hpp
---

文字列・数列などの列に対して MP algorithm を適用．長さ $N$ の入力に対し時間計算量 $O(N)$．

## 使用方法

```cpp
string S = "teletelepathy";
vector<int> v = mp_algorithm(S); // [0,0,0,0,1,2,3,4,0,0,1,0,0] 長さ N
```

## 文献・リンク

- [1] D. Knuth, J. Morris, V. Pratt, "Fast pattern matching in strings," SIAM journal on computing, 6(2), 323-350, 1977.
- [文字列の頭良い感じの線形アルゴリズムたち - あなたは嘘つきですかと聞かれたら「YES」と答えるブログ](https://snuke.hatenablog.com/entry/2014/12/01/235807)
