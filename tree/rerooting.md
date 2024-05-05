---
title: Rerooting （全方位木 DP）
documentation_of: ./rerooting.hpp
---

## できること

- ここに記述する内容はリンク [1] で説明されていることとほぼ同等．
- 木の各頂点・各辺になんらかのデータ構造が載っている．
- 根付き木について，各頂点 $v$ を根とする部分木に対して計算される `Subtree` 型の情報を $X_v$ とする．また，各辺 $uv$ が持つ `Edge` 型の情報を $e_{uv}$ とする．
- $X_v$ は $X_v = \mathrm{add\_vertex}\left(\mathrm{rake}\left(\mathrm{add\_edge}(X\_{c\_1}, c\_1, e\_{v c\_1}), \dots, \mathrm{add\_edge}(X\_{c\_k}, c\_k, e\_{v c\_k})\right), v \right)$ を満たす．ここで $c\_1, \dots, c\_k$ は $v$ の子の頂点たち．
  - $\mathrm{add\_edge}(X\_v, v, e\_{uv})$ は $u$ の子 $v$ について `Children` 型の情報を計算する関数．
  - $\mathrm{add\_vertex}(y, v)$ は `Children` 型の引数 $y$ をもとに頂点 $v$ における `Subtree` 型の情報を計算する関数．
  - $\mathrm{rake}(y\_1, \dots, y\_k)$ は任意個の `Children` 型の引数の積を計算する関数．
  - $\mathrm{rake}()$ には結合法則が成立しなければならない．また， `Children` 型の単位元を `e()` とする．
- 以上のような性質を満たすデータ構造を考えたとき，本ライブラリは森の各頂点 $r$ を根とみなしたときの連結成分に関する $X_r$ の値を全ての $r$ について線形時間で計算する．

## 使用方法（例）

```cpp
vector<int> inD;
struct Subtree {
    bool exist;
    int oneway, round;
};
struct Children {
    bool exist;
    int oneway, round;
};
Children rake(Children x, Children y) {
    if (!x.exist) return y;
    if (!y.exist) return x;
    return Children{true, min(x.oneway + y.round, y.oneway + x.round), x.round + y.round};
}
Children add_edge(Subtree x, int, tuple<>) {
    if (!x.exist) return {false, 0, 0};
    return {true, x.oneway + 1, x.round + 2};
}
Subtree add_vertex(Children x, int v) {
    if (x.exist) return {true, x.oneway, x.round};
    return {inD[v], 0, 0};
    return {false, 0, 0};
}
Children e() { return {false, 0, 0}; }


vector<vector<pair<int, tuple<>>>> to;
rerooting<tuple<>, Subtree, Children, rake, add_edge, add_vertex, e> tree(to);
tree.run();
for (auto x : tree.dpall) cout << x.oneway << '\n';
```

また，メソッド `get_subtree(int root, int par)` によって，木を頂点 `par` （`par` が $-1$ の場合は `root`）を根とした根付き木として見た場合の頂点 `root` を根とする部分木の情報が取得できる．

```cpp
int u, v;  // u-v 間に辺が存在
Subtree s1 = tree.get_subtree(u, v);
```

## 問題例

- [エクサウィザーズプログラミングコンテスト2021（AtCoder Beginner Contest 222） F - Expensive Expense](https://atcoder.jp/contests/abc222/tasks/abc222_f)
- [AOJ 1595: Traffic Tree](https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1595)
- [No.1718 Random Squirrel - yukicoder](https://yukicoder.me/problems/no/1718)
- [トヨタ自動車プログラミングコンテスト2023#1(AtCoder Beginner Contest 298) Ex - Sum of Min of Length](https://atcoder.jp/contests/abc298/tasks/abc298_h)
  - `get_subtree()` を使用するのが楽．

## リンク

1. [全方位木DP(ReRooting)の抽象化について - メモ帳](https://null-mn.hatenablog.com/entry/2020/04/14/124151)
2. [解説 - エクサウィザーズプログラミングコンテスト2021（AtCoder Beginner Contest 222）](https://atcoder.jp/contests/abc222/editorial/2749)
3. [競技プログラミングにおける全方位木DP問題まとめ - はまやんはまやんはまやん](https://blog.hamayanhamayan.com/entry/2017/02/09/155738)
