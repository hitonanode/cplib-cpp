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
  bundledCode: "#line 2 \"tree/rerooting.hpp\"\n#include <cassert>\n#include <utility>\n\
    #include <vector>\n\n// Rerooting\n// Reference:\n// - https://atcoder.jp/contests/abc222/editorial/2749\n\
    // - https://null-mn.hatenablog.com/entry/2020/04/14/124151\ntemplate <class Edge,\
    \ class St, class Ch, Ch (*merge)(Ch, Ch), Ch (*f)(St, int, Edge),\n         \
    \ St (*g)(Ch, int), Ch (*e)()>\nstruct rerooting {\n    int n_;\n    std::vector<int>\
    \ par, visited;\n    std::vector<std::vector<std::pair<int, Edge>>> to;\n    std::vector<St>\
    \ dp_subtree;\n    std::vector<St> dp_par;\n    std::vector<St> dpall;\n    rerooting(const\
    \ std::vector<std::vector<std::pair<int, Edge>>> &to_)\n        : n_(to_.size()),\
    \ par(n_, -1), visited(n_, 0), to(to_) {\n        for (int i = 0; i < n_; ++i)\
    \ dp_subtree.push_back(g(e(), i));\n        dp_par = dpall = dp_subtree;\n   \
    \ }\n\n    void run_connected(int root) {\n        if (visited[root]) return;\n\
    \        visited[root] = 1;\n        std::vector<int> visorder{root};\n\n    \
    \    for (int t = 0; t < int(visorder.size()); ++t) {\n            int now = visorder[t];\n\
    \            for (const auto &edge : to[now]) {\n                int nxt = edge.first;\n\
    \                if (visited[nxt]) continue;\n                visorder.push_back(nxt);\n\
    \                visited[nxt] = 1;\n                par[nxt] = now;\n        \
    \    }\n        }\n\n        for (int t = int(visorder.size()) - 1; t >= 0; --t)\
    \ {\n            int now = visorder[t];\n            Ch ch = e();\n          \
    \  for (const auto &edge : to[now]) {\n                int nxt = edge.first;\n\
    \                if (nxt == par[now]) continue;\n                ch = merge(ch,\
    \ f(dp_subtree[nxt], nxt, edge.second));\n            }\n            dp_subtree[now]\
    \ = g(ch, now);\n        }\n\n        std::vector<Ch> left;\n        for (int\
    \ now : visorder) {\n            int m = int(to[now].size());\n            left.assign(m\
    \ + 1, e());\n            for (int j = 0; j < m; j++) {\n                int nxt\
    \ = to[now][j].first;\n                const St &st = (nxt == par[now] ? dp_par[now]\
    \ : dp_subtree[nxt]);\n                left[j + 1] = merge(left[j], f(st, nxt,\
    \ to[now][j].second));\n            }\n            dpall[now] = g(left.back(),\
    \ now);\n\n            Ch rprod = e();\n            for (int j = m - 1; j >= 0;\
    \ --j) {\n                int nxt = to[now][j].first;\n                if (nxt\
    \ != par[now]) dp_par[nxt] = g(merge(left[j], rprod), now);\n\n              \
    \  const St &st = (nxt == par[now] ? dp_par[now] : dp_subtree[nxt]);\n       \
    \         rprod = merge(f(st, nxt, to[now][j].second), rprod);\n            }\n\
    \        }\n    }\n\n    void run() {\n        for (int i = 0; i < n_; ++i) {\n\
    \            if (!visited[i]) run_connected(i);\n        }\n    }\n};\n/* Template:\n\
    struct Subtree {};\nstruct Child {};\nstruct Edge {};\nChild e() { return Child();\
    \ }\nChild merge(Child x, Child y) { return Child(); }\nChild f(Subtree x, int\
    \ ch_id, Edge edge) { return Child(); }\nSubtree g(Child x, int v_id) { return\
    \ Subtree(); }\n\nvector<vector<pair<int, Edge>>> to;\nrerooting<Edge, Subtree,\
    \ Child, merge, f, g, e> tree(to);\n*/\n"
  code: "#pragma once\n#include <cassert>\n#include <utility>\n#include <vector>\n\
    \n// Rerooting\n// Reference:\n// - https://atcoder.jp/contests/abc222/editorial/2749\n\
    // - https://null-mn.hatenablog.com/entry/2020/04/14/124151\ntemplate <class Edge,\
    \ class St, class Ch, Ch (*merge)(Ch, Ch), Ch (*f)(St, int, Edge),\n         \
    \ St (*g)(Ch, int), Ch (*e)()>\nstruct rerooting {\n    int n_;\n    std::vector<int>\
    \ par, visited;\n    std::vector<std::vector<std::pair<int, Edge>>> to;\n    std::vector<St>\
    \ dp_subtree;\n    std::vector<St> dp_par;\n    std::vector<St> dpall;\n    rerooting(const\
    \ std::vector<std::vector<std::pair<int, Edge>>> &to_)\n        : n_(to_.size()),\
    \ par(n_, -1), visited(n_, 0), to(to_) {\n        for (int i = 0; i < n_; ++i)\
    \ dp_subtree.push_back(g(e(), i));\n        dp_par = dpall = dp_subtree;\n   \
    \ }\n\n    void run_connected(int root) {\n        if (visited[root]) return;\n\
    \        visited[root] = 1;\n        std::vector<int> visorder{root};\n\n    \
    \    for (int t = 0; t < int(visorder.size()); ++t) {\n            int now = visorder[t];\n\
    \            for (const auto &edge : to[now]) {\n                int nxt = edge.first;\n\
    \                if (visited[nxt]) continue;\n                visorder.push_back(nxt);\n\
    \                visited[nxt] = 1;\n                par[nxt] = now;\n        \
    \    }\n        }\n\n        for (int t = int(visorder.size()) - 1; t >= 0; --t)\
    \ {\n            int now = visorder[t];\n            Ch ch = e();\n          \
    \  for (const auto &edge : to[now]) {\n                int nxt = edge.first;\n\
    \                if (nxt == par[now]) continue;\n                ch = merge(ch,\
    \ f(dp_subtree[nxt], nxt, edge.second));\n            }\n            dp_subtree[now]\
    \ = g(ch, now);\n        }\n\n        std::vector<Ch> left;\n        for (int\
    \ now : visorder) {\n            int m = int(to[now].size());\n            left.assign(m\
    \ + 1, e());\n            for (int j = 0; j < m; j++) {\n                int nxt\
    \ = to[now][j].first;\n                const St &st = (nxt == par[now] ? dp_par[now]\
    \ : dp_subtree[nxt]);\n                left[j + 1] = merge(left[j], f(st, nxt,\
    \ to[now][j].second));\n            }\n            dpall[now] = g(left.back(),\
    \ now);\n\n            Ch rprod = e();\n            for (int j = m - 1; j >= 0;\
    \ --j) {\n                int nxt = to[now][j].first;\n                if (nxt\
    \ != par[now]) dp_par[nxt] = g(merge(left[j], rprod), now);\n\n              \
    \  const St &st = (nxt == par[now] ? dp_par[now] : dp_subtree[nxt]);\n       \
    \         rprod = merge(f(st, nxt, to[now][j].second), rprod);\n            }\n\
    \        }\n    }\n\n    void run() {\n        for (int i = 0; i < n_; ++i) {\n\
    \            if (!visited[i]) run_connected(i);\n        }\n    }\n};\n/* Template:\n\
    struct Subtree {};\nstruct Child {};\nstruct Edge {};\nChild e() { return Child();\
    \ }\nChild merge(Child x, Child y) { return Child(); }\nChild f(Subtree x, int\
    \ ch_id, Edge edge) { return Child(); }\nSubtree g(Child x, int v_id) { return\
    \ Subtree(); }\n\nvector<vector<pair<int, Edge>>> to;\nrerooting<Edge, Subtree,\
    \ Child, merge, f, g, e> tree(to);\n*/\n"
  dependsOn: []
  isVerificationFile: false
  path: tree/rerooting.hpp
  requiredBy: []
  timestamp: '2021-10-23 00:38:09+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - tree/test/rerooting.yuki1718.test.cpp
  - tree/test/rerooting.aoj1595.test.cpp
documentation_of: tree/rerooting.hpp
layout: document
title: "Rerooting \uFF08\u5168\u65B9\u4F4D\u6728 DP\uFF09"
---

## できること

- ここに記述する内容はリンク [1] で説明されていることとほぼ同等．
- 木の各頂点・各辺になんらかのデータ構造が載っている．
- 根付き木について，各頂点 $v$ を根とする部分木に対して計算される `St` 型の情報を $X_v$ とする．また，各辺 $uv$ が持つ `Edge` 型の情報を $e_{uv}$ とする．
- $X_v$ は $X_v = g\left(\mathrm{merge}\left(f(X\_{c\_1}, c\_1, e\_{v c\_1}), \dots, f(X\_{c\_k}, c\_k, e\_{v c\_k})\right), v \right)$ を満たす．ここで $c\_1, \dots, c\_k$ は $v$ の子の頂点たち．
  - $f(X\_v, v, e\_{uv})$ は $u$ の子 $v$ について `Ch` 型の情報を計算する関数．
  - $\mathrm{merge}(y\_1, \dots, y\_k)$ は任意個の `Ch` 型の引数の積を計算する関数．
  - $g(y, v)$ は `Ch` 型の引数 $y$ をもとに頂点 $v$ における `St` 型の情報を計算する関数．
  - `Ch` 型には結合法則が成立しなければならない．また， `Ch` 型の単位元を `e()` とする．
- 以上のような性質を満たすデータ構造を考えたとき，本ライブラリは森の各頂点 $r$ を根とみなしたときの連結成分に関する $X_r$ の値を全ての $r$ について線形時間で計算する．

## 使用方法（例）

```cpp
vector<int> inD;
struct Subtree {
    bool exist;
    int oneway, round;
};
struct Child {
    bool exist;
    int oneway, round;
};
Child merge(Child x, Child y) {
    if (!x.exist) return y;
    if (!y.exist) return x;
    return Child{true, min(x.oneway + y.round, y.oneway + x.round), x.round + y.round};
}
Child f(Subtree x, int, tuple<>) {
    if (!x.exist) return {false, 0, 0};
    return {true, x.oneway + 1, x.round + 2};
}
Subtree g(Child x, int v) {
    if (x.exist) return {true, x.oneway, x.round};
    return {inD[v], 0, 0};
    return {false, 0, 0};
}
Child e() { return {false, 0, 0}; }


vector<vector<pair<int, tuple<>>>> to;
rerooting<tuple<>, Subtree, Child, merge, f, g, e> tree(to);
tree.run();
for (auto x : tree.dpall) cout << x.oneway << '\n';
```

## 問題例

- [エクサウィザーズプログラミングコンテスト2021（AtCoder Beginner Contest 222） F - Expensive Expense](https://atcoder.jp/contests/abc222/tasks/abc222_f)
- [AOJ 1595: Traffic Tree](https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1595)
- [No.1718 Random Squirrel - yukicoder](https://yukicoder.me/problems/no/1718)

## リンク

1. [全方位木DP(ReRooting)の抽象化について - メモ帳](https://null-mn.hatenablog.com/entry/2020/04/14/124151)
2. [解説 - エクサウィザーズプログラミングコンテスト2021（AtCoder Beginner Contest 222）](https://atcoder.jp/contests/abc222/editorial/2749)
3. [競技プログラミングにおける全方位木DP問題まとめ - はまやんはまやんはまやん](https://blog.hamayanhamayan.com/entry/2017/02/09/155738)
