---
title: Convolution on rooted tree （根付き木上の畳み込み）
documentation_of: ./convolution_on_tree.hpp
---

根付き木において，各頂点から $i$ 世代親の頂点へ重み `trans[i]` で遷移を行う．各頂点に載せるデータ構造の長さ $n$ の列同士の畳み込みの計算量が $O(n \log n)$ ならば，木の頂点数を $n$ として本コードの計算量は $O(n \log n)$．


## アルゴリズムの概要

- まず Heavy-light decomposition を行う．その後各 heavy path 上でのみ畳み込みを実行するが，その際 heavy path から生える部分木の頂点重みも前もって加算し，畳み込みの後で多すぎる分を引く．詳細は下記問題の解説を参照のこと．

## 使用方法

```cpp
vector<int> par(N); // par[i] = -1 （i が根の場合） / （i の親頂点） （それ以外）

vector<mint> f(N);  // 各頂点の重み初期値

vector<mint> trans; // trans[i] = （各頂点から i 世代親の頂点への遷移重み）

auto convolve = [&](vector<mint> &l, vector<mint> &r) { return nttconv(l, r); };
vector<mint> g = ConvolutionOnTree(par).run(f, trans, convolve); // g = 遷移結果
```

## 問題例

- [No.2004 Incremental Coins - yukicoder](https://yukicoder.me/problems/no/2004)
