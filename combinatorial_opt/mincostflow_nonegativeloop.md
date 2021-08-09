---
title: Minimum cost flow without negative cycle （負辺ループなしの最小費用流）
documentation_of: ./mincostflow_nonegativeloop.hpp
---

Negative cycle がない場合に使用可能な最小費用流．

負辺が存在する場合，以下の要領で双対変数（ポテンシャル）の初期化を行う：

- グラフが DAG であれば，$O(V + E)$ で求める．
- DAG でなければ，SPFA によって $O(VE)$ で求める．負ループが存在すれば例外を送出する．
