---
title: Tree pop order optimization / "01 on Tree" （木の根から 2 次元ベクトルや 01 文字列などを pop する順列に関する最小化）
documentation_of: ./tree_pop_order_optimization.hpp
---

いわゆる "01 on Tree" を解く．

## 使用方法

### オーソドックスな "01 on Tree"

```cpp
int N;
vector<vector<int>> to(N);

vector<long long> x(N), y(N);

const auto [order, inversions] = Solve01OnTree(to, x, y, 0);
cout << inversions << '\n';
for (auto e : order) cout << e << ' ';
```

### より一般的な構造

以下は [28147번: Fail Fast](https://www.acmicpc.net/problem/28147) の例．まず各頂点が持つデータを表現する構造体を定義する． `operator+=` の内容に注意せよ．

```cpp
struct S {
    double x, y;
    S(double x, double y) : x(x), y(y) {}
    S() : x(0), y(0) {}
    bool operator<(const S &r) const {
        if (x == 0 and y == 0) return false;
        if (r.x == 0 and r.y == 0) return true;
        if (x == 0 and r.x == 0) return y < r.y;
        if (x == 0) return false;
        if (r.x == 0) return true;
        return y * r.x < x * r.y; // be careful of overflow
    }
    bool operator>(const S &r) const { return r < *this; }

    void operator+=(const S &r) {
        y += r.y * (1 - x);
        x = x + (1 - x) * r.x;
    }
};
```

あとは，以下のように `TreePopOrderOptimization()` を呼んでやればよい．戻り値の `.first` は最適な pop 順の順列， `.second` はその順に　`S` の元の総積を（ `+=` で）とったときの値である．

```cpp
vector<vector<int>> to(N);
vector<S> vals(N);

auto [seq, all_prod] = TreePopOrderOptimization(to, vals, 0).Solve();
```

## 問題例

- [Library Checker: Rooted Tree Topological Order with Minimum Inversions](https://judge.yosupo.jp/problem/rooted_tree_topological_order_with_minimum_inversions)
- [AtCoder Grand Contest 023 F - 01 on Tree](https://atcoder.jp/contests/agc023/tasks/agc023_f)
- [AtCoder Beginner Contest 376 G - Treasure Hunting](https://atcoder.jp/contests/abc376/tasks/abc376_g)
- [No.3148 Min-Cost Destruction of Parentheses - yukicoder](https://yukicoder.me/problems/no/3148)
- [28147번: Fail Fast](https://www.acmicpc.net/problem/28147)
  - 通常の 01 on Tree とは異なる演算の入ったデータ構造を載せるタイプの問題．

## リンク

- [解説 - AtCoder Beginner Contest 376（Promotion of AtCoder Career Design DAY）](https://atcoder.jp/contests/abc376/editorial/11196)
- [241203_01 on Tree](https://acompany-ac.notion.site/241203_01-on-Tree-151269d8558680b2b639d7bfcbff2b20)
