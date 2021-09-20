---
title: Li-Chao tree
documentation_of: ./li_chao_tree.hpp
---

Li-Chao tree の実装．一次関数 $ax + b$ による区間 chmin が $O((\log N)^2)$，一点での最小値取得が $O(\log N)$ の計算量で可能（$N$ は最小値取得を行う $x$ の個数）．

## 使用方法

```cpp
vector<long long> xs;

li_chao_tree<long long, __int128> tree;
tree.init(xs); // xs が昇順である必要はない

tree.insert_segment(l, r, a, b, 0); // chmin by ax + b in [l, r)

ret = tree.get(x);
cout << ret.minval << endl;
```

## 参考文献・リンク

- [Li Chao Treeのメモ - 日々ｄｒｄｒする人のメモ](https://smijake3.hatenablog.com/entry/2018/06/16/144548)
- [[Tutorial] Li Chao Tree Extended - Codeforces](https://codeforces.com/blog/entry/86731) 更なる拡張も可能らしい．
