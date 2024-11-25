---
title: Linear sum assignment problem, Hungarian algorithm （割当問題に対するハンガリアン法）
documentation_of: ./linear_sum_assignment.hpp
---

$r$ 行 $c$ 列の行列を入力とした割当問題（二部グラフの最小重み最大マッチング問題）を解く．計算量は `augment()` 一回あたり $O(rc)$ で，全体で $O(rc \min(r, c))$．

オーソドックスな Hungarian algorithm の実装ではなく， Jonker–Volgenant algorithm の工夫を一部取り入れることで定数倍高速化を試みている．

また，割当問題の上位 $k$ 個の解を効率的に列挙するクラス `best_assignments` も提供している．このクラスのコンストラクタや `yield()` を呼び出し毎に $O(rc \min{r, c})$ の時間計算量が発生する．

## 解いてくれる問題

主問題として，オーソドックスな線形重み割当問題を解く．

LP 緩和の双対問題を考えると，特に $r = c$ の場合，以下の問題のソルバとしても利用できる．

$\displaystyle
\begin{array}{rl}
\text{maximize} & \sum\_{i} f\_i + \sum\_j g\_j \\
\text{s.t.} & f\_{i} + g\_{j} \le C\_{ij}
\end{array}
$

## 使用方法

### 割当問題（最適解の計算）

```cpp
vector C(r, vector<long long>(c));

long long min_weight;
vector<int> mate;
vector<long long> f, g;

std::tie(min_weight, mate, f, g) = linear_sum_assignment::solve(r, c, C);
```

`mate[i]` は第 $i$ 行が何列目の要素と対応するかを示す（ $r > c$ で，第 $i$ 行に対応する要素が存在しない場合は $-1$）．

また， `f[i]` および `g[j]` は最適解における双対変数の一例を示す．すなわち，任意の $i, j$ について $f\_i + g\_j \le C\_{ij}$ が成立し，特に第 $i$ 行と第 $j$ 列が対応する場合は等号が成立する．この双対変数は，行列の一部要素に更新を加えた場合の最適解の変化を効率的に追うために利用できる．

### 割当問題の $k$-best 解列挙

```cpp
int r, c;

vector<vector<int>> C;
int inf;

best_assignments<int> gen(r, c, cost, inf);

// 解の生成
for (int t = 0; t < k; ++t) {
    if (ba.finished()) break;
    auto [opt, mate, f, g] = ba.yield();
}
```

## 問題例

- [Library Checker: Assignment Problem](https://judge.yosupo.jp/problem/assignment)

## 文献・リンク集

- [Lecture 8: Assignment Algorithms](https://cyberlab.engr.uconn.edu/wp-content/uploads/sites/2576/2018/09/Lecture_8.pdf)
- [1] K. G. Murty, "An algorithm for ranking all the assignments in order of increasing cost," Operations Research, 16(3), 682–687, 1968.
- [2] M.L. Miller, H.S. Stone, I.J. Cox, "Optimizing Murty's ranked assignment method," IEEE Transactions on Aerospace and Electronic Systems, 33(3), 851-862, 1997.
