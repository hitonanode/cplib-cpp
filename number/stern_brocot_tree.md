---
title: Stern–Brocot tree
documentation_of: ./stern_brocot_tree.hpp
---

Stern–Brocot tree に関連する処理・探索アルゴリズム．大半の関数は与えられる整数の対数時間で動作する．

## 使用方法

```cpp
long long a, b;  // coprime
auto path = SternBrocotTree::encode_path(a, b);  // path from root (= 1) to a/b

auto node = SternBrocotTree::decode_path(path);  // path to rational number
assert(node.num() == a);
assert(node.den() == b);

long long c, d;
auto path2 = SternBrocotTree::encode_path(c, d);
auto path_lca = SternBrocotTree::lca_path(path, path2);  // path to LCA
```

## 問題例

- [Library Checker: Stern–Brocot Tree](https://judge.yosupo.jp/problem/stern_brocot_tree)
