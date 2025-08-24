---
title: Monotone minima （Monotone な行列の行最小値の効率的な探索）
documentation_of: ./monotone_minima.hpp
---

`SMAWK()` 関数は，monotone な $N \times M$ 行列，すなわち各行の最小値の位置が行を下るにつれ右に移動していくような行列について，各行の最小値の位置およびその値を $O((N + M) \log (N + M))$ で取得する．

[SMAWK](./smawk.md) のライブラリと互換性があり，SMAWK が使用されている箇所は本関数で代替可能（最悪計算量のオーダーはこちらの方に log がつくが，問題によってはこちらの方が実測上速い）．

## 使用方法

例えば辺重みが Monge な $N$ 頂点の DAG で頂点 $0$ から各頂点への最短路重みを求めたいとき， $N$ 行 $N - 1$ 列の行列を $(j, i)$ 成分が「直前に頂点 $i$ を経由し頂点 $j$ に到達する場合の最短路重み」であるようなものとして定めると本関数が適用できる（SMAWK も適用できるが）．

```cpp
using T = long long;
T inf = 1LL << 60;
int N;
vector<T> dp(N, inf);
dp[0] = 0;

auto weight = [&](int s, int t) -> T { /* Implement */ };

const auto res = MonotoneMinima<T>(
    N, N - 1, [&](int j, int i) -> T { return i < j ? dp[i] + weight(i, j) : inf; });
```

## 問題例

- [K. Coupon - Monoxer Programming Contest for Engineers](https://mofecoder.com/contests/monoxercon_202508/tasks/monoxercon_202508_k)

## Links

- [Totally Monotone Matrix Searching (SMAWK algorithm) - 週刊 spaghetti_source - TopCoder部](https://topcoder-g-hatena-ne-jp.jag-icpc.org/spaghetti_source/20120923/1348327542.html)
