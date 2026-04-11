---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: tree/test/rerooting.aoj1595.test.cpp
    title: tree/test/rerooting.aoj1595.test.cpp
  - icon: ':heavy_check_mark:'
    path: tree/test/rerooting.yuki1718.test.cpp
    title: tree/test/rerooting.yuki1718.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://atcoder.jp/contests/abc222/editorial/2749
    - https://null-mn.hatenablog.com/entry/2020/04/14/124151
  bundledCode: "#line 2 \"tree/rerooting.hpp\"\n#include <cassert>\n#include <cstdlib>\n\
    #include <utility>\n#include <vector>\n\n// Rerooting\n// Reference:\n// - https://atcoder.jp/contests/abc222/editorial/2749\n\
    // - https://null-mn.hatenablog.com/entry/2020/04/14/124151\ntemplate <class Edge,\
    \ class Subtree, class Children, Children (*rake)(Children, Children),\n     \
    \     Children (*add_edge)(Subtree, int, Edge), Subtree (*add_vertex)(Children,\
    \ int),\n          Children (*e)()>\nstruct rerooting {\n    int n_;\n    std::vector<int>\
    \ par, visited;\n    std::vector<std::vector<std::pair<int, Edge>>> to;\n\n  \
    \  // dp_subtree[i] = DP(root=i, edge (i, par[i]) is removed).\n    std::vector<Subtree>\
    \ dp_subtree;\n\n    // dp_par[i] = DP(root=par[i], edge (i, par[i]) is removed).\
    \ dp_par[root] is meaningless.\n    std::vector<Subtree> dp_par;\n\n    // dpall[i]\
    \ = DP(root=i, all edges exist).\n    std::vector<Subtree> dpall;\n\n    rerooting(const\
    \ std::vector<std::vector<std::pair<int, Edge>>> &to_)\n        : n_(to_.size()),\
    \ par(n_, -1), visited(n_, 0), to(to_) {\n        for (int i = 0; i < n_; ++i)\
    \ dp_subtree.push_back(add_vertex(e(), i));\n        dp_par = dpall = dp_subtree;\n\
    \    }\n\n    void run_connected(int root) {\n        if (visited.at(root)) return;\n\
    \        visited.at(root) = 1;\n        std::vector<int> visorder{root};\n\n \
    \       for (int t = 0; t < int(visorder.size()); ++t) {\n            int now\
    \ = visorder.at(t);\n            for (const auto &[nxt, _] : to[now]) {\n    \
    \            if (visited.at(nxt)) continue;\n                visorder.push_back(nxt);\n\
    \                visited.at(nxt) = 1;\n                par.at(nxt) = now;\n  \
    \          }\n        }\n\n        for (int t = int(visorder.size()) - 1; t >=\
    \ 0; --t) {\n            const int now = visorder.at(t);\n            Children\
    \ ch = e();\n            for (const auto &[nxt, edge] : to.at(now)) {\n      \
    \          if (nxt != par.at(now)) ch = rake(ch, add_edge(dp_subtree.at(nxt),\
    \ nxt, edge));\n            }\n            dp_subtree.at(now) = add_vertex(ch,\
    \ now);\n        }\n\n        std::vector<Children> left;\n        for (int now\
    \ : visorder) {\n            const int m = to.at(now).size();\n            left.assign(m\
    \ + 1, e());\n            for (int j = 0; j < m; j++) {\n                const\
    \ auto &[nxt, edge] = to.at(now).at(j);\n                const Subtree &st = (nxt\
    \ == par.at(now) ? dp_par.at(now) : dp_subtree.at(nxt));\n                left.at(j\
    \ + 1) = rake(left.at(j), add_edge(st, nxt, edge));\n            }\n         \
    \   dpall.at(now) = add_vertex(left.back(), now);\n\n            Children rprod\
    \ = e();\n            for (int j = m - 1; j >= 0; --j) {\n                const\
    \ auto &[nxt, edge] = to.at(now).at(j);\n\n                if (nxt != par.at(now))\
    \ dp_par.at(nxt) = add_vertex(rake(left.at(j), rprod), now);\n\n             \
    \   const Subtree &st = (nxt == par.at(now) ? dp_par.at(now) : dp_subtree.at(nxt));\n\
    \                rprod = rake(add_edge(st, nxt, edge), rprod);\n            }\n\
    \        }\n    }\n\n    void run() {\n        for (int i = 0; i < n_; ++i) {\n\
    \            if (!visited.at(i)) run_connected(i);\n        }\n    }\n\n    const\
    \ Subtree &get_subtree(int root_, int par_) const {\n        if (par_ < 0) return\
    \ dpall.at(root_);\n        if (par.at(root_) == par_) return dp_subtree.at(root_);\n\
    \        if (par.at(par_) == root_) return dp_par.at(par_);\n        std::exit(1);\n\
    \    }\n};\n/* Template:\nstruct Subtree {};\nstruct Children {};\nstruct Edge\
    \ {};\nChildren e() { return Children(); }\nChildren rake(Children x, Children\
    \ y) { return Children(); }\nChildren add_edge(Subtree x, int ch_id, Edge edge)\
    \ { return Children(); }\nSubtree add_vertex(Children x, int v_id) { return Subtree();\
    \ }\n\nvector<vector<pair<int, Edge>>> to;\nrerooting<Edge, Subtree, Children,\
    \ rake, add_edge, add_vertex, e> tree(to);\n*/\n"
  code: "#pragma once\n#include <cassert>\n#include <cstdlib>\n#include <utility>\n\
    #include <vector>\n\n// Rerooting\n// Reference:\n// - https://atcoder.jp/contests/abc222/editorial/2749\n\
    // - https://null-mn.hatenablog.com/entry/2020/04/14/124151\ntemplate <class Edge,\
    \ class Subtree, class Children, Children (*rake)(Children, Children),\n     \
    \     Children (*add_edge)(Subtree, int, Edge), Subtree (*add_vertex)(Children,\
    \ int),\n          Children (*e)()>\nstruct rerooting {\n    int n_;\n    std::vector<int>\
    \ par, visited;\n    std::vector<std::vector<std::pair<int, Edge>>> to;\n\n  \
    \  // dp_subtree[i] = DP(root=i, edge (i, par[i]) is removed).\n    std::vector<Subtree>\
    \ dp_subtree;\n\n    // dp_par[i] = DP(root=par[i], edge (i, par[i]) is removed).\
    \ dp_par[root] is meaningless.\n    std::vector<Subtree> dp_par;\n\n    // dpall[i]\
    \ = DP(root=i, all edges exist).\n    std::vector<Subtree> dpall;\n\n    rerooting(const\
    \ std::vector<std::vector<std::pair<int, Edge>>> &to_)\n        : n_(to_.size()),\
    \ par(n_, -1), visited(n_, 0), to(to_) {\n        for (int i = 0; i < n_; ++i)\
    \ dp_subtree.push_back(add_vertex(e(), i));\n        dp_par = dpall = dp_subtree;\n\
    \    }\n\n    void run_connected(int root) {\n        if (visited.at(root)) return;\n\
    \        visited.at(root) = 1;\n        std::vector<int> visorder{root};\n\n \
    \       for (int t = 0; t < int(visorder.size()); ++t) {\n            int now\
    \ = visorder.at(t);\n            for (const auto &[nxt, _] : to[now]) {\n    \
    \            if (visited.at(nxt)) continue;\n                visorder.push_back(nxt);\n\
    \                visited.at(nxt) = 1;\n                par.at(nxt) = now;\n  \
    \          }\n        }\n\n        for (int t = int(visorder.size()) - 1; t >=\
    \ 0; --t) {\n            const int now = visorder.at(t);\n            Children\
    \ ch = e();\n            for (const auto &[nxt, edge] : to.at(now)) {\n      \
    \          if (nxt != par.at(now)) ch = rake(ch, add_edge(dp_subtree.at(nxt),\
    \ nxt, edge));\n            }\n            dp_subtree.at(now) = add_vertex(ch,\
    \ now);\n        }\n\n        std::vector<Children> left;\n        for (int now\
    \ : visorder) {\n            const int m = to.at(now).size();\n            left.assign(m\
    \ + 1, e());\n            for (int j = 0; j < m; j++) {\n                const\
    \ auto &[nxt, edge] = to.at(now).at(j);\n                const Subtree &st = (nxt\
    \ == par.at(now) ? dp_par.at(now) : dp_subtree.at(nxt));\n                left.at(j\
    \ + 1) = rake(left.at(j), add_edge(st, nxt, edge));\n            }\n         \
    \   dpall.at(now) = add_vertex(left.back(), now);\n\n            Children rprod\
    \ = e();\n            for (int j = m - 1; j >= 0; --j) {\n                const\
    \ auto &[nxt, edge] = to.at(now).at(j);\n\n                if (nxt != par.at(now))\
    \ dp_par.at(nxt) = add_vertex(rake(left.at(j), rprod), now);\n\n             \
    \   const Subtree &st = (nxt == par.at(now) ? dp_par.at(now) : dp_subtree.at(nxt));\n\
    \                rprod = rake(add_edge(st, nxt, edge), rprod);\n            }\n\
    \        }\n    }\n\n    void run() {\n        for (int i = 0; i < n_; ++i) {\n\
    \            if (!visited.at(i)) run_connected(i);\n        }\n    }\n\n    const\
    \ Subtree &get_subtree(int root_, int par_) const {\n        if (par_ < 0) return\
    \ dpall.at(root_);\n        if (par.at(root_) == par_) return dp_subtree.at(root_);\n\
    \        if (par.at(par_) == root_) return dp_par.at(par_);\n        std::exit(1);\n\
    \    }\n};\n/* Template:\nstruct Subtree {};\nstruct Children {};\nstruct Edge\
    \ {};\nChildren e() { return Children(); }\nChildren rake(Children x, Children\
    \ y) { return Children(); }\nChildren add_edge(Subtree x, int ch_id, Edge edge)\
    \ { return Children(); }\nSubtree add_vertex(Children x, int v_id) { return Subtree();\
    \ }\n\nvector<vector<pair<int, Edge>>> to;\nrerooting<Edge, Subtree, Children,\
    \ rake, add_edge, add_vertex, e> tree(to);\n*/\n"
  dependsOn: []
  isVerificationFile: false
  path: tree/rerooting.hpp
  requiredBy: []
  timestamp: '2024-05-05 15:10:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - tree/test/rerooting.aoj1595.test.cpp
  - tree/test/rerooting.yuki1718.test.cpp
documentation_of: tree/rerooting.hpp
layout: document
title: "Rerooting \uFF08\u5168\u65B9\u4F4D\u6728 DP\uFF09"
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
