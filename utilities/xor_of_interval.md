---
title: XOR of interval
documentation_of: ./xor_of_interval.hpp
---

非負整数の半開区間 $[\mathrm{lo}, \mathrm{hi})$ に含まれるそれぞれの整数と $v$ の排他的論理和 (XOR) をとった値の集合はたかだか $O(\log ( \mathrm{hi} - \mathrm{lo}))$ 個の半開区間となる．本関数はその全ての半開区間を列挙する．全ての半開区間の長さは 2 べきである．

## 使用方法

```cpp

int lo, hi;

int v;

xor_of_interval(v, lo, hi, [&](int l, int r) {
    // Do something for [l, r).
    // This function is called O(log(hi - lo)) times.
});

```

## 問題例

- [Educational Codeforces Round 152 (Rated for Div. 2) F. XOR Partition - Codeforces](https://codeforces.com/contest/1849/problem/F)
