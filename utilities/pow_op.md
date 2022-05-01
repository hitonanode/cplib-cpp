---
title: Power (general monoid)
documentation_of: ./pow_op.hpp
---

一般のモノイドの元 $x$ について繰り返し二乗法で $x^k$ を計算．単位元を必要としない構成にしたため，$k = 0$ はエラーとなることに注意．計算量は $O(\log n)$．

## 使用方法

数論関数の $k$ 乗（の先頭の数項）を計算したい場合：

```cpp
vector<mint> op(vector<mint> l, vector<mint> r) {
    S ret(l.size());
    for (int i = 1; i < int(l.size()); ++i) {
        for (int j = 1; i * j < int(l.size()); ++j) ret[i * j] += l[i] * r[j];
    }
    return ret;
}

vector<mint> f;
long long k;
f = pow_op<decltype(f), op>(f, k);
```
