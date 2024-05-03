---
title: Palindromic tree / eertree （回文木）
documentation_of: ./palindromic_tree.hpp
---

文字列に現れる回文を効率的に管理するデータ構造．与えられた文字列 $S$ に対して $O(|S| \log \sigma)$ $(\sigma = |\Sigma|)$ で構築可能．

## eertree とは

- 各頂点が，与えられた文字列の（連続）部分文字列である distinct な回文に対応する．
  - 例外として，長さ $-1$, $0$ の空文字列を表現するダミーの頂点がそれぞれ存在する．したがって頂点数は正確には回文の種類数 +2 となる．
  - 頂点数は $|S| + 2$ 以下である．
- 各頂点から，その回文の suffix である最長回文の頂点への辺 (suffix link) が生えている．
  - 例外として，長さ $0$ の空文字列のダミー頂点の suffix link は長さ $-1$ の空文字列へ生えている．
  - 長さ $-1$ の空文字列の suffix link は存在しない．つまり， suffix link を辺としたグラフはこの頂点を根とする根付き木となる．

## 使用方法

```cpp
string S = "sakanakanandaka";
palindromic_tree::Tree<char> tree;
tree.add_string(S);

// コールバック関数も使用可能．
// 第一引数は S 上の index (0, ..., |S| - 1), 第二引数は tree.nodes の index.
// 1 文字読む毎に tree 上のどこにいるか分かるので出現回数カウント等が可能．
vector<int> dp(S.size() + 2);
auto callback = [&](int str_idx, int node_idx) -> void { dp.at(node_idx)++; };

tree.add_string(S, callback);
```

## 問題例

- [No.263 Common Palindromes Extra - yukicoder](https://yukicoder.me/problems/no/263)
- [No.2606 Mirror Relay - yukicoder](https://yukicoder.me/problems/no/2606)

## 参考文献・リンク

- [1] M. Rubinchik and A. M. Shur, "EERTREE: An efficient data structure for processing palindromes in strings," European Journal of Combinatorics 68, 249-265, 2018. [arXiv](https://arxiv.org/abs/1506.04862)
- [Palindromic Tree - math314のブログ](https://math314.hateblo.jp/entry/2016/12/19/005919)
- [すごい！EERTREE！いごす - 誤読](https://mojashi.hatenablog.com/entry/2017/07/17/155520)
