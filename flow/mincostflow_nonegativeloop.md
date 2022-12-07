---
title: Minimum cost flow without negative cycle （負辺ループなしの最小費用流）
documentation_of: ./mincostflow_nonegativeloop.hpp
---

Negative cycle がない場合に使用可能な最小費用流．

負辺が存在する場合，DAG であれば線形時間でポテンシャルを求める．DAG でなければ例外を送出する．
