---
title: LCA-based auxiliary tree / virtual tree, online （"虚树"）
documentation_of: ./auxiliary_tree.hpp
---

予め根付き木 $T$ が与えられる．$T$ の頂点部分集合 $S$ を $\emptyset$ で初期化した上で，以下のクエリをサポートする．

- $S$ に 1 頂点追加
- $S$ から 1 頂点削除
- $S$ の要素の組の最小共通祖先 (lowest common ancestor, LCA) 全てを頂点とし、もとの木と子孫関係を保った根付き木 $T'$ を考える． $T'$ に関して以下に答える：
  - $T$ の頂点 $v$ が $S$ に含まれるかどうか
  - $T$ の頂点 $v$ が $T'$ に含まれるかどうか
    - 特に $T'$ における $v$ の親
    - 特に $T'$ における $v$ の子の集合
  - $T'$ の根となる頂点

現実装では $T$ 上の LCA の計算を sparse table で行っているため， $\Theta(n \log n)$ の空間計算量を要する．

## 使用方法

```cpp
vector<vector<int>> to(N);  // edges of tree
int root = 0;

auxiliary_tree at(to, root);

int v;
at.activate(v);  // Add v to S
at.deactivate(v);  // Remove v from S

int r = at.auxiliary_root();  // Root of T' (if exists) or -1

int par = at.get_parent(v);  // Parent of v in T' (if exists) or -1
vector<int> children = at.get_children(v);  // Children of v in T'

bool b1 = at.is_active(v);  // v in S?
bool b2 = at.is_semiactive(v);  // v in T'?
```

## 問題例

- [鹿島建設プログラミングコンテスト2024（AtCoder Beginner Contest 340） G - Leaf Color](https://atcoder.jp/contests/abc340/tasks/abc340_g)
- [No.901 K-ary εxtrεεmε - yukicoder](https://yukicoder.me/problems/no/901)
