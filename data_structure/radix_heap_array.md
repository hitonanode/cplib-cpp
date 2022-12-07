---
title: Array-like radix heap with decrease query（chmin 操作が可能な基数ヒープ）
documentation_of: ./radix_heap_array.hpp
---

`radix_heap.hpp` におけるラベルを非負整数に限り，更にラベル $i$ に対応したキーに対する decrease 操作（いわゆる `chmin`）を $O(1)$ で行えるもの．

## 使用方法

以下のように，Dijkstra 法を効率的に実行可能なクエリが揃っている．以下，$D$ を `UnsignedInt` 型のビット数とする．

- `radix_heap_array<UnsignedInt>()`: Radix heap の初期化．各 $i \ge 0$ について $A_i = \infty$ と初期化．計算量は $O(D)$．
- `bool empty()`: $A\_i < \infty$ である $i$ が存在しないとき，及びそのときに限り `true` を返す．$O(1)$
- `int argmin_pop()`: $A\_i$ が最小値をとる $i$ を一つとって $A\_i = \infty$ と更新し，$i$ を返す．償却 $O(D)$
- `void chmin(UnsignedInt x, int i)`: $A\_i$ を $\min(A\_i, x)$ で更新する．$x$ の値はこれまで `pop()` や `top()` の対象となった最大の値以上でなければならない．$O(1)$

以下は既存のライブラリとの互換性のために実装されている．

- `void pop()`: $A\_i$ が最小の $i$ の一つについて，$A_i = \infty$ と更新する．償却 $O(D)$
- `pair<UnsignedInt, int> top()`: $A\_i$ が最小の $i$ の一つについて，$(A\_i, i)$ の組を返す．償却 $O(D)$
- `void emplace(Uint vnew, int i)` （非推奨）: `chmin()` と同じ効果で，STL における同名の関数とは意味が大きく異なる．既存のライブラリに含まれる `priority_queue` をコンテスト中に素早くこのライブラリに置き換えることを可能にするためにのみ存在している．$O(1)$

Dijkstra 法による最短 $s$ - $t$ パスの計算は次のように書ける：
```cpp
vector<unsigned long long> dist(N, numeric_limits<unsigned long long>::max());
vector<int> prv(N, -1);
dist[s] = 0;
radix_heap_array<unsigned long long> pq;
pq.chmin(0, s);
while (!pq.empty()) {
    int now = pq.argmin_pop();
    if (now == t) break;
    for (const auto &nx : to[now]) {
        int nxt = nx.first;
        if (dist[nxt] > dist[now] + nx.second) {
            dist[nxt] = dist[now] + nx.second;
            prv[nxt] = now;
            pq.chmin(dist[nxt], nxt);
        }
    }
}
```
