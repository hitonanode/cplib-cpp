---
title: Minimum cost flow without negative cycle （負辺ループなしの最小費用流）
documentation_of: ./mincostflow_nonegativeloop.hpp
---

Negative cycle がない場合に使用可能な最小費用流．

負辺が存在する場合，以下の要領でポテンシャルの初期化を行う：

- グラフが DAG であれば，$O(V + E)$ で求める．
- DAG でなければ，SPFA によって $O(VE)$ で求める．負ループが存在すれば例外を送出する．

また，フロー計算時に
```cpp
auto ret = graph.flow<radix_heap<unsigned long long, int>>(s, t, N);
```
のように指定することで，`priority_queue` より高速とされる radix heap が利用可能．
