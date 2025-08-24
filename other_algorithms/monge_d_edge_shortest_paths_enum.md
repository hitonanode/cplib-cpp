---
title: Shortest paths of DAG with Monge weights using $d = 1, \ldots, d_{\mathrm{max}}$ edges （Monge 重み DAG の使用辺数毎の最短路長列挙）
documentation_of: ./monge_d_edge_shortest_paths_enum.hpp
---

トポロジカルソート済の $N$ 頂点（頂点は $0$ から $N - 1$ の整数）の DAG で辺重みが Monge のとき，頂点 $0$ から $N - 1$ まで丁度 $d$ 個の辺を使う最短路長を $d = 1, \ldots, d\_{\mathrm{max}}$ についてそれぞれ求める．

計算量は $O(N d\_{\mathrm{max}})$ である．

内部で `SMAWK<T>` を利用しているが， `MonotoneMinima<T>()` に置き換えてもよい（計算量に log がつくが，問題によってはこちらの方が高速に動くこともある）．

## 使用方法

### [No.952 危険な火薬庫 - yukicoder](https://yukicoder.me/problems/no/952) の場合

```cpp
long long inf = 1LL << 60;
int N;
int max_d;

auto f = [&](int s, int t) -> lint {
    // Return weight from vertex s to vertex t
    // You can assume that `0 <= s < t < N ` always holds.
};
const std::vector<long long> res = MongeDEdgeShortestPaths<long long>(N, max_d, f, inf);
```

## 問題例

- [No.952 危険な火薬庫 - yukicoder](https://yukicoder.me/problems/no/952)
- [K. Coupon - Monoxer Programming Contest for Engineers](https://mofecoder.com/contests/monoxercon_202508/tasks/monoxercon_202508_k)

## Links

- [Knuth-Yao speedup - 週刊 spaghetti_source - TopCoder部](https://topcoder-g-hatena-ne-jp.jag-icpc.org/spaghetti_source/20120915/1347668163.html)
- [monge グラフ上の d-辺最短路の d=1,…,N における列挙 \| Nyaan’s Library](https://nyaannyaan.github.io/library/dp/monge-d-edge-shortest-path-enumerate.hpp.html)
