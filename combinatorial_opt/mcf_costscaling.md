---
title: Cost scaling minimum cost flow (Goldberg, Tarjan) （コストスケーリングによる最小費用流）
documentation_of: ./mcf_costscaling.hpp
---

コストスケーリングによる最小費用流．問題に実行可能解が存在しない場合無限ループに陥ること，またコストを $n + 1$ 倍にする前処理を行うのでオーバーフローに注意．

## Reference

- [1] A. V. Goldberg and R. E. Tarjan, "Finding minimum-cost circulations by successive approximation,"
      Mathematics of Operations Research, 15(3), 430-466, 1990.
- [ORIE 633: Network Flows](https://people.orie.cornell.edu/dpw/orie633/)
