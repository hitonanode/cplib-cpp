---
title: Hook length formula (フック長公式)
documentation_of: ./hook_length_formula.hpp
---

ヤング盤に対するフック長公式．

## 使用方法

```cpp
vector<int> a;

mint ret = hook_length_formula<mint>(a);
```

計算量は $n = \mathrm{len}(a)$ として $O(n \log n + \mathrm{sum}(a))$．

## 問題例

- [C - Numbering Blocks](https://atcoder.jp/contests/judge-update-202004/tasks/judge_update_202004_c)
- [No.2149 Vanitas Vanitatum - yukicoder](https://yukicoder.me/problems/no/2149)

## Links

- [フック長の公式 - Wikipedia](https://ja.wikipedia.org/wiki/%E3%83%95%E3%83%83%E3%82%AF%E9%95%B7%E3%81%AE%E5%85%AC%E5%BC%8F)
