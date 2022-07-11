---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: convolution/test/convolution_on_tree.test.cpp
    title: convolution/test/convolution_on_tree.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links:
    - https://yukicoder.me/problems/no/2004
  bundledCode: "#line 2 \"convolution/convolution_on_tree.hpp\"\n#include <cassert>\n\
    #include <utility>\n#include <vector>\n\n// ConvolutionOnTree : \u6839\u4ED8\u304D\
    \u6728\u4E0A\u3067\u6839\u65B9\u5411\u3078\u7573\u307F\u8FBC\u307F\n// Input:\n\
    // - par_ : \u5404\u9802\u70B9\u306E\u89AA\u306E\u9802\u70B9\u756A\u53F7 \u6839\
    \u306E par_ \u306F -1\n// - f : \u5404\u9802\u70B9\u306E\u521D\u671F\u5024\n//\
    \ - trans : trans[i] = \u5404\u9802\u70B9\u304B\u3089 i \u4E16\u4EE3\u76EE\u306E\
    \u89AA\u9802\u70B9\u3078\u306E\u9077\u79FB\u4FC2\u6570\n// Verified: https://yukicoder.me/problems/no/2004\n\
    struct ConvolutionOnTree {\n    int N;\n    int root;\n    std::vector<int> par;\n\
    \    std::vector<std::vector<int>> children;\n\n    std::vector<int> depth;\n\
    \    std::vector<int> farthest_leaf;\n\n    void _rec_build_hld(int now) {\n \
    \       farthest_leaf[now] = now;\n        for (int nxt : children[now]) {\n \
    \           depth[nxt] = depth[now] + 1;\n            _rec_build_hld(nxt);\n \
    \           if (depth[farthest_leaf[now]] < depth[farthest_leaf[nxt]]) {\n   \
    \             farthest_leaf[now] = farthest_leaf[nxt];\n            }\n      \
    \  }\n    }\n\n    void _build_hld() {\n        depth.assign(N, 0);\n        farthest_leaf.assign(N,\
    \ -1);\n        _rec_build_hld(root);\n    }\n\n    ConvolutionOnTree(std::vector<int>\
    \ par_) : N(par_.size()), par(par_), children(par.size()) {\n        root = -1;\n\
    \        for (int i = 0; i < N; ++i) {\n            if (par[i] >= 0 and par[i]\
    \ < N) {\n                children[par[i]].push_back(i);\n            } else {\n\
    \                assert(root == -1);\n                par[i] = -1;\n         \
    \       root = i;\n            }\n        }\n        assert(root != -1);\n\n \
    \       _build_hld();\n    }\n\n    template <class T, class F>\n    std::vector<T>\
    \ _run_rec(const int r, int h, std::vector<T> &ret, const std::vector<T> &f,\n\
    \                            const std::vector<T> &trans, F convolver) {\n   \
    \     const int leaf = farthest_leaf[r], d = depth[leaf] - depth[r] + 1;\n   \
    \     std::vector<T> g;\n        std::vector<int> ids;\n        g.reserve(d),\
    \ ids.reserve(d);\n\n        for (int cur = leaf, prv = -1;; prv = cur, cur =\
    \ par[cur]) {\n            ids.push_back(cur);\n            g.push_back(f[cur]);\n\
    \n            for (int nxt : children[cur]) {\n                if (nxt == prv)\
    \ continue;\n                int nxtlen = depth[farthest_leaf[nxt]] - depth[cur];\n\
    \                std::vector<T> gchild =\n                    _run_rec(nxt, ids.at(int(ids.size())\
    \ - nxtlen - 1), ret, f, trans, convolver);\n                for (int i = 0; i\
    \ < int(gchild.size()); ++i) {\n                    g.at(int(g.size()) - int(gchild.size())\
    \ - 1 + i) += gchild[i];\n                }\n            }\n\n            if (cur\
    \ == r) break;\n        }\n\n        std::vector<T> trans_sub(trans.begin(), trans.begin()\
    \ + std::min(trans.size(), g.size()));\n        // trans_sub = nttconv(g, trans_sub);\n\
    \        trans_sub = convolver(g, trans_sub);\n\n        for (int cur = leaf,\
    \ i = 0;; cur = par[cur], ++i, h = h >= 0 ? par[h] : h) {\n            ret.at(cur)\
    \ += trans_sub.at(i);\n            if (h >= 0) ret.at(h) -= trans_sub.at(i);\n\
    \            if (cur == r) break;\n        }\n        return g;\n    }\n\n   \
    \ template <class T, class F>\n    std::vector<T> run(const std::vector<T> &f,\
    \ const std::vector<T> &trans, F convolver) {\n        std::vector<T> ret(N, T());\n\
    \        _run_rec<T, F>(root, -1, ret, f, trans, convolver);\n        return ret;\n\
    \    }\n};\n/* example:\nConvolutionOnTree tree(par);\n\nauto convolve = [&](vector<mint>\
    \ &l, vector<mint> &r) { return nttconv(l, r); };\nauto ret = tree.run(A, trans,\
    \ convolve);\n*/\n"
  code: "#pragma once\n#include <cassert>\n#include <utility>\n#include <vector>\n\
    \n// ConvolutionOnTree : \u6839\u4ED8\u304D\u6728\u4E0A\u3067\u6839\u65B9\u5411\
    \u3078\u7573\u307F\u8FBC\u307F\n// Input:\n// - par_ : \u5404\u9802\u70B9\u306E\
    \u89AA\u306E\u9802\u70B9\u756A\u53F7 \u6839\u306E par_ \u306F -1\n// - f : \u5404\
    \u9802\u70B9\u306E\u521D\u671F\u5024\n// - trans : trans[i] = \u5404\u9802\u70B9\
    \u304B\u3089 i \u4E16\u4EE3\u76EE\u306E\u89AA\u9802\u70B9\u3078\u306E\u9077\u79FB\
    \u4FC2\u6570\n// Verified: https://yukicoder.me/problems/no/2004\nstruct ConvolutionOnTree\
    \ {\n    int N;\n    int root;\n    std::vector<int> par;\n    std::vector<std::vector<int>>\
    \ children;\n\n    std::vector<int> depth;\n    std::vector<int> farthest_leaf;\n\
    \n    void _rec_build_hld(int now) {\n        farthest_leaf[now] = now;\n    \
    \    for (int nxt : children[now]) {\n            depth[nxt] = depth[now] + 1;\n\
    \            _rec_build_hld(nxt);\n            if (depth[farthest_leaf[now]] <\
    \ depth[farthest_leaf[nxt]]) {\n                farthest_leaf[now] = farthest_leaf[nxt];\n\
    \            }\n        }\n    }\n\n    void _build_hld() {\n        depth.assign(N,\
    \ 0);\n        farthest_leaf.assign(N, -1);\n        _rec_build_hld(root);\n \
    \   }\n\n    ConvolutionOnTree(std::vector<int> par_) : N(par_.size()), par(par_),\
    \ children(par.size()) {\n        root = -1;\n        for (int i = 0; i < N; ++i)\
    \ {\n            if (par[i] >= 0 and par[i] < N) {\n                children[par[i]].push_back(i);\n\
    \            } else {\n                assert(root == -1);\n                par[i]\
    \ = -1;\n                root = i;\n            }\n        }\n        assert(root\
    \ != -1);\n\n        _build_hld();\n    }\n\n    template <class T, class F>\n\
    \    std::vector<T> _run_rec(const int r, int h, std::vector<T> &ret, const std::vector<T>\
    \ &f,\n                            const std::vector<T> &trans, F convolver) {\n\
    \        const int leaf = farthest_leaf[r], d = depth[leaf] - depth[r] + 1;\n\
    \        std::vector<T> g;\n        std::vector<int> ids;\n        g.reserve(d),\
    \ ids.reserve(d);\n\n        for (int cur = leaf, prv = -1;; prv = cur, cur =\
    \ par[cur]) {\n            ids.push_back(cur);\n            g.push_back(f[cur]);\n\
    \n            for (int nxt : children[cur]) {\n                if (nxt == prv)\
    \ continue;\n                int nxtlen = depth[farthest_leaf[nxt]] - depth[cur];\n\
    \                std::vector<T> gchild =\n                    _run_rec(nxt, ids.at(int(ids.size())\
    \ - nxtlen - 1), ret, f, trans, convolver);\n                for (int i = 0; i\
    \ < int(gchild.size()); ++i) {\n                    g.at(int(g.size()) - int(gchild.size())\
    \ - 1 + i) += gchild[i];\n                }\n            }\n\n            if (cur\
    \ == r) break;\n        }\n\n        std::vector<T> trans_sub(trans.begin(), trans.begin()\
    \ + std::min(trans.size(), g.size()));\n        // trans_sub = nttconv(g, trans_sub);\n\
    \        trans_sub = convolver(g, trans_sub);\n\n        for (int cur = leaf,\
    \ i = 0;; cur = par[cur], ++i, h = h >= 0 ? par[h] : h) {\n            ret.at(cur)\
    \ += trans_sub.at(i);\n            if (h >= 0) ret.at(h) -= trans_sub.at(i);\n\
    \            if (cur == r) break;\n        }\n        return g;\n    }\n\n   \
    \ template <class T, class F>\n    std::vector<T> run(const std::vector<T> &f,\
    \ const std::vector<T> &trans, F convolver) {\n        std::vector<T> ret(N, T());\n\
    \        _run_rec<T, F>(root, -1, ret, f, trans, convolver);\n        return ret;\n\
    \    }\n};\n/* example:\nConvolutionOnTree tree(par);\n\nauto convolve = [&](vector<mint>\
    \ &l, vector<mint> &r) { return nttconv(l, r); };\nauto ret = tree.run(A, trans,\
    \ convolve);\n*/\n"
  dependsOn: []
  isVerificationFile: false
  path: convolution/convolution_on_tree.hpp
  requiredBy: []
  timestamp: '2022-07-10 22:54:46+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - convolution/test/convolution_on_tree.test.cpp
documentation_of: convolution/convolution_on_tree.hpp
layout: document
title: "Convolution on rooted tree \uFF08\u6839\u4ED8\u304D\u6728\u4E0A\u306E\u7573\
  \u307F\u8FBC\u307F\uFF09"
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
