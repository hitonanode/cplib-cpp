---
title: Centroid decomposition （森の重心分解）
documentation_of: ./centroid_decomposition.hpp
---

与えられた森について，指定された頂点に関する連結成分の重心分解を行う．

## 使用方法

```cpp
int v = 0;

// 頂点 v の連結成分を重心分解していく
for (int c : cd.centroid_decomposition(v)) {
    // 頂点 c を削除する
}
```

## 問題例

- [No.2892 Lime and Karin - yukicoder](https://yukicoder.me/problems/no/2892)
