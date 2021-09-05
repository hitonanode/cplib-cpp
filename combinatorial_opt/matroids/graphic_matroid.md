---
title: Graphic matroid （グラフマトロイド）
documentation_of: ./graphic_matroid.hpp
---

無向グラフ $(V, E)$ によって定義されるマトロイド．辺集合 $E$ の部分集合 $I$ は，無向グラフ上に $I$ に属する辺のみによる閉路が存在しないときに独立．

## 使用例

```cpp
vector<pair<int, int>> edges;
edges.emplace_back(0, 1);
edges.emplace_back(0, 2);
edges.emplace_back(1, 3);
edges.emplace_back(1, 4);
edges.emplace_back(3, 4);
edges.emplace_back(2, 4);

GraphMatroid M(5, edges);
vector<bool> state{1, 1, 1, 1, 0, 0};
M.set(state);
vector<int> c1 = M.circuit(4); // [4, 2, 3]
vector<int> c2 = M.circuit(5); // [5, 3, 1, 0]
```
