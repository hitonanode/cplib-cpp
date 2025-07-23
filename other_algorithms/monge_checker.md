---
title: Monge checker
documentation_of: ./monge_checker.hpp
---

与えられた一般の $n \times m$ 行列や $n$ 頂点 DAG の重み行列の Monge 性および Anti-Monge 性を確認し，以下の結果を出力する．

- Monge であった場合， `Monge OK` と出力
- Monge ではないが anti-Monge であった場合， `Not Monge, but Anti-Monge OK` と出力
- Monge でも anti-Monge でもない場合， `Not Monge!` と出力し，続けて Monge 性に反する $2 \times 2$ 小行列を出力

計算量は $O(nm)$ や $O(n^2)$ なので，ジャッジへの提出にこの関数の実行を含めると TLE となりうるので注意．

## 使用方法

行列を `std::vector<std::vector<long long>>` 等の形で直接与えるのではなく， `int` 2 つを引数として重みを返す関数 `cost(int, int)` を引数として与えればよい．

### $n$ 頂点 DAG の辺重み関数の Monge 性判定

```cpp
int n;  // 頂点: 0, 1, ..., (n - 1)
using T = long long;
T INF;
auto cost = [&](int i, int j) -> T {
    // Return weight of directed edge i->j, or INF if the edge does not exist.
};

cerr << check_dag_monge(cost, INF, n) << endl;
```

## Monge 性の確認方法

隣接する 2 行と 2 列の要素からなる全ての $2 \times 2$ 小行列に対する Monge 性を確認すればよい [1]．

## Links

- [1] [[Monge まとめ①] Monge 性とは？ - HackMD](https://hackmd.io/@tatyam-prime/monge1)
