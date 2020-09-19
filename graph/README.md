# General Graph Algorithms

Algorithms for trees are not here.

## Contents

- Shortest path
  - `bellman_ford.hpp`
  - `dijkstra.hpp`
- Lowlink technique
  - `lowlink.hpp`
- Flow
  - `flow_mincost.hpp` : Minimum-cost flow problem solver for graphs with no negative cycle

## Lowlinkについて

- Articulation points （関節点）
  - その一点を消去するとグラフが連結でなくなるような頂点
- Bridge （橋）
  - その一辺を消去するとグラフが連結でなくなるような辺
