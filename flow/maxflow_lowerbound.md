---
title: Maxflow with lower bound （流量下限付き最大流）
documentation_of: ./maxflow_lowerbound.hpp
---

流量下限制約付の最大流を解く．

## 使用方法

```cpp
MaxFlowLowerBound<long long> mf(N);

int s, t;
long long lo, hi;

mf.add_edge(s, t, lo, hi);

long long f = mf.flow(s, t);  // f = flow (feasible) / -1 (infeasible)
```

## リンク

- [最小流量制限付き最大流 - あなたは嘘つきですかと聞かれたら「YES」と答えるブログ](https://snuke.hatenablog.com/entry/2016/07/10/043918)
