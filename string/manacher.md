---
title: Longest palindromic substring enumeration (Manacher's algorithm) （回文長配列構築）
documentation_of: ./manacher.hpp
---

文字列・数列などの列に対して Manacher's algorithm を適用．長さ $N$ の入力に対し時間計算量 $O(N)$．

## 使用方法

```cpp
string S = "sakanakanandaka";
vector<int> v = manacher(S); // Manacher's algorithm を適用（奇数長の回文だけならこれでOK）．
vector<pair<int, int>> palindromes = enumerate_palindromes(S);
for (auto [l, r] : palindromes) {
    cout << r - l << ' '; // S[l, r) は最長回文連続部分列（[1, 1) のような空文字列も含む）．
}
```

## 文献

- [1] G. Manacher, "A new linear-time "on-line" algorithm for finding the smallest initial palindrome of a string", Journal of the ACM, 22 (3), 346-351, 1975.
