---
title: Permutation tree （順列木）
documentation_of: ./permutation_tree.hpp
---

与えられた $[0, \dots, N - 1]$ の置換 $\mathbf{A} = [A\_0, \dots, A\_{N - 1}]$ について，この連続部分列であってその長さがそれに含まれる要素の最大値と最小値の差に $1$ を加えた値と等しくなるようなものを全て列挙するのに役立つデータ構造．

Permutation tree は区間のマージ過程を表す木として表現される．$N$ 個の葉は長さ $1$ の区間（単一の要素）に対応し，根は $\mathbf{A}$ 全体に対応する．

葉以外の全ての頂点は `Join` と `Cut` いずれかの属性を持つ．`Join` 属性を持つ頂点は，その子を $c\_1, \dots, c\_k$ とおくと，任意の $1 \le i \le j \le k$ について頂点 $(c\_i, \dots, c\_j)$ が表す区間の和集合は上記の条件を満たす．また，全ての頂点について，その頂点が表す区間全体は上記の条件を満たす．そして，上記の条件を満たす区間はこれらに限られるというのが最も重要な性質である．


## 使用方法（例）

木の各頂点の情報はメンバ変数 `std::vector<node> nodes` に格納されている．特に根が格納されている位置を示す変数が `tree.root`．

```cpp
enum NodeType {
    JoinAsc,    // Join，特に A[i] の値が増加していく
    JoinDesc,   // Join，特に A[i] の値が減少していく
    Cut,        // Cut
    Leaf,       // 葉である
    None,
};
struct node {
    NodeType tp;
    int L, R;                // [L, R) : 頂点が表す区間
    int mini, maxi;          // 区間に含まれる A[i] (L <= i < R) の最小・最大値
    std::vector<int> child;  // 子の頂点番号（昇順）
};
```

また．`to_DOT(std::string filename)` によって DOT 言語でのグラフ出力が可能．

## 問題例

### [ZeptoLab Code Rush 2015 F. Pudding Monsters - Codeforces](https://codeforces.com/contest/526/problem/F)

上記の条件を満たす区間の個数だけを求めればよい問題．

```cpp
permutation_tree tree(A);

auto rec = [&](auto &&self, int now) -> long long {
    long long ret = 1;
    const auto &v = tree.nodes[now];
    if (v.tp == permutation_tree::JoinAsc or v.tp == permutation_tree::JoinDesc) {
        ret = (long long)v.child.size() * (v.child.size() - 1) / 2;
    }
    for (auto c : v.child) ret += self(self, c);
    return ret;
};
cout << rec(rec, tree.root) << '\n';
```

### [No.1720 Division Permutation - yukicoder](https://yukicoder.me/problems/no/1720)

木上を DFS しながら DP の遷移をさせていけばよく，これは以下のように再帰的に書ける．

```cpp
permutation_tree tree(P);
vector dp(K + 1, vector<mint>(N + 1));
dp[0][0] = 1;

auto rec = [&](auto &&self, int now) -> void {
    auto &v = tree.nodes[now];
    if (v.tp == permutation_tree::Cut or v.tp == permutation_tree::Leaf) {
        for (int k = 0; k < K; ++k) dp[k + 1][v.R] += dp[k][v.L];
    }

    vector<mint> sum(K);
    for (auto ch : v.child) {
        self(self, ch);
        if (v.tp == permutation_tree::JoinAsc or v.tp == permutation_tree::JoinDesc) {
            for (int k = 0; k < K; ++k) {
                dp[k + 1][tree.nodes[ch].R] += sum[k];
                sum[k] += dp[k][tree.nodes[ch].L];
            }
        }
    }
};
rec(rec, tree.root);

for (int i = 1; i <= K; i++) cout << dp[i][N].val() << '\n';
```

## リンク

1. [Tutorial on Permutation Tree (析合树） - Codeforces](https://codeforces.com/blog/entry/78898)
