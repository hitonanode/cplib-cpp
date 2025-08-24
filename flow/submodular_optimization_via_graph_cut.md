---
title: Submodular function optimization via graph cut （最小カット帰着による劣モジュラ関数の最小化）
documentation_of: ./submodular_optimization_via_graph_cut.hpp
---

一定の条件を満たす [pseudo-boolean 関数](https://en.wikipedia.org/wiki/Pseudo-Boolean_function) の最小化問題（プログラミングコンテストの文脈における「燃やす埋める問題」）を，特定のグラフの最小カットに帰着させて解く．
解くのに失敗した場合は `Solve()` 関数の結果の `solved` が `false` となる．

本コードの特長として，入力されたコスト関数のいくつかの変数の真偽を反転させてコスト関数の各項を劣モジュラにする方法を予め探索する処理が含まれている．

## 使用方法

### 通常の pseudo-boolean 最適化（いわゆる「燃やす埋める問題」）

最小 $s$-$t$ カットを求め，始点側の連結成分の頂点に真偽値 `false`、終点側に `true` を割り当てる．

```cpp
using V = pair<int, int>;
SubmodularOptimizationViaGraphCut<V> so;  // 頂点の型は int でなくとも（ std::map の key にできれば）よい

so.Impose({0, 0}, true, 100);  // 頂点 (0, 0) が true をとる場合 100 のコスト（ペナルティ）

so.Impose(-500);  // コスト関数の定数項に -500 を加算

vector<pair<V, bool>> conditions;
so.ImposeIfNotAll(conditions, 50); // 「conditions に含まれる全頂点がそれぞれ与えられた真偽値を満たす」に反した場合 50 のコスト

const auto res = so.Solve();
assert(res.solved);
cout << res.total_cost << '\n';
```

### 変数が少数の整数値をとる場合（いわゆる $k$ 値最小カット問題）

この場合， $0$ 以上 $k$ 未満の値をとる整数変数を $k - 1$ 個の頂点 $(v\_1, \ldots, v\_{k - 1})$ で表現する．各頂点 $v\_{i + 1}$ から $v\_{i}$ に十分容量の大きい辺を張る． 解においてこれらの頂点における真偽値の割当が `F...FT...T` という形になることが保証される．これに含まれる `F` の個数がもとの整数変数の解における値である．

```cpp
using V = pair<int, int>;
SubmodularOptimizationViaGraphCut<V> so;
const long long inf = 1LL << 30;

const auto x = so.GenIntVar({V{i, 0}, V{i, 1}}, inf); // Create int value 0 <= x < 3
so.Impose(x, {5LL, 0LL, 3LL}); // Impose cost function f(x) = 5 (if x = 0), 0 (if x = 1), 3 (if x = 2).
so.ImposeLbUb(x, 2, y, 0, 5000); // If x >= 2 && y <= 0, impose cost by 5000
```

## 問題例

- [燃やす埋める練習問題１ \| MojaCoder](https://mojacoder.app/users/_kanpurin_/problems/project_selection_problem001)
- [燃やす埋める練習問題２ \| MojaCoder](https://mojacoder.app/users/_kanpurin_/problems/project_selection_problem002)
- [燃やす埋める練習問題３ \| MojaCoder](https://mojacoder.app/users/_kanpurin_/problems/project_selection_problem003)
- [燃やす埋める練習問題４ \| MojaCoder](https://mojacoder.app/users/_kanpurin_/problems/project_selection_problem004)
- [燃やす埋める練習問題5 \| MojaCoder](https://mojacoder.app/users/_kanpurin_/problems/project_selection_problem005)
- [25365번: Kingdom Partition](https://www.acmicpc.net/problem/25365)
  - そのままではこのライブラリでは解けず， 4 状態へと拡張してやる必要がある．

ほか，多くの問題を CI check に利用している．

## 参考文献・リンク

- [燃やす埋める問題と劣モジュラ関数のグラフ表現可能性 その① - 私と理論](https://theory-and-me.hatenablog.com/entry/2020/03/13/180935)
- [燃やす埋める問題と劣モジュラ関数のグラフ表現可能性 その② グラフ構築編 - 私と理論](https://theory-and-me.hatenablog.com/entry/2020/03/17/180157)
- [最小カット問題の k 値への一般化 - noshi91のメモ](https://noshi91.hatenablog.com/entry/2021/06/29/044225)
