---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://mofecoder.com/contests/monoxercon_202508/tasks/monoxercon_202508_k
    - https://topcoder-g-hatena-ne-jp.jag-icpc.org/spaghetti_source/20120923/1348327542.html
  bundledCode: "#line 2 \"other_algorithms/monotone_minima.hpp\"\n#include <cassert>\n\
    #include <functional>\n#include <vector>\n\n// finding minimum element for each\
    \ row of N*M matrix\n// Constraints: the solution is monotonically non-decreasing\n\
    // Complexity: O(NM logM)\n// Reference:\n// https://topcoder-g-hatena-ne-jp.jag-icpc.org/spaghetti_source/20120923/1348327542.html\n\
    // Verify: https://mofecoder.com/contests/monoxercon_202508/tasks/monoxercon_202508_k\n\
    template <class T>\nstd::vector<std::pair<int, T>>\nMonotoneMinima(int N, int\
    \ M, const std::function<T(int i, int j)> &weight) {\n    std::vector<std::pair<int,\
    \ T>> minima(N);\n\n    auto rec = [&](auto &&self, int il, int ir, int jl, int\
    \ jr) -> void {\n        if (il >= ir or jl >= jr) return;\n        const int\
    \ im = (il + ir) / 2;\n        T w = weight(im, jl);\n        int j_argmin = jl;\n\
    \        for (int j = jl + 1; j < jr; ++j) {\n            if (T wt = weight(im,\
    \ j); wt < w) w = wt, j_argmin = j;\n        }\n        minima[im] = {j_argmin,\
    \ w};\n        self(self, il, im, jl, j_argmin + 1);\n        self(self, im +\
    \ 1, ir, j_argmin, jr);\n    };\n    rec(rec, 0, N, 0, M);\n\n    return minima;\n\
    }\n"
  code: "#pragma once\n#include <cassert>\n#include <functional>\n#include <vector>\n\
    \n// finding minimum element for each row of N*M matrix\n// Constraints: the solution\
    \ is monotonically non-decreasing\n// Complexity: O(NM logM)\n// Reference:\n\
    // https://topcoder-g-hatena-ne-jp.jag-icpc.org/spaghetti_source/20120923/1348327542.html\n\
    // Verify: https://mofecoder.com/contests/monoxercon_202508/tasks/monoxercon_202508_k\n\
    template <class T>\nstd::vector<std::pair<int, T>>\nMonotoneMinima(int N, int\
    \ M, const std::function<T(int i, int j)> &weight) {\n    std::vector<std::pair<int,\
    \ T>> minima(N);\n\n    auto rec = [&](auto &&self, int il, int ir, int jl, int\
    \ jr) -> void {\n        if (il >= ir or jl >= jr) return;\n        const int\
    \ im = (il + ir) / 2;\n        T w = weight(im, jl);\n        int j_argmin = jl;\n\
    \        for (int j = jl + 1; j < jr; ++j) {\n            if (T wt = weight(im,\
    \ j); wt < w) w = wt, j_argmin = j;\n        }\n        minima[im] = {j_argmin,\
    \ w};\n        self(self, il, im, jl, j_argmin + 1);\n        self(self, im +\
    \ 1, ir, j_argmin, jr);\n    };\n    rec(rec, 0, N, 0, M);\n\n    return minima;\n\
    }\n"
  dependsOn: []
  isVerificationFile: false
  path: other_algorithms/monotone_minima.hpp
  requiredBy: []
  timestamp: '2025-08-24 23:54:21+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: other_algorithms/monotone_minima.hpp
layout: document
title: "Monotone minima \uFF08Monotone \u306A\u884C\u5217\u306E\u884C\u6700\u5C0F\u5024\
  \u306E\u52B9\u7387\u7684\u306A\u63A2\u7D22\uFF09"
---

`SMAWK()` 関数は，monotone な $N \times M$ 行列，すなわち各行の最小値の位置が行を下るにつれ右に移動していくような行列について，各行の最小値の位置およびその値を $O((N + M) \log (N + M))$ で取得する．

[SMAWK](./smawk.md) のライブラリと互換性があり，SMAWK が使用されている箇所は本関数で代替可能（最悪計算量のオーダーはこちらの方に log がつくが，問題によってはこちらの方が実測上速い）．

## 使用方法

例えば辺重みが Monge な $N$ 頂点の DAG で頂点 $0$ から各頂点への最短路重みを求めたいとき， $N$ 行 $N - 1$ 列の行列を $(j, i)$ 成分が「直前に頂点 $i$ を経由し頂点 $j$ に到達する場合の最短路重み」であるようなものとして定めると本関数が適用できる（SMAWK も適用できるが）．

```cpp
using T = long long;
T inf = 1LL << 60;
int N;
vector<T> dp(N, inf);
dp[0] = 0;

auto weight = [&](int s, int t) -> T { /* Implement */ };

const auto res = MonotoneMinima<T>(
    N, N - 1, [&](int j, int i) -> T { return i < j ? dp[i] + weight(i, j) : inf; });
```

## 問題例

- [K. Coupon - Monoxer Programming Contest for Engineers](https://mofecoder.com/contests/monoxercon_202508/tasks/monoxercon_202508_k)

## Links

- [Totally Monotone Matrix Searching (SMAWK algorithm) - 週刊 spaghetti_source - TopCoder部](https://topcoder-g-hatena-ne-jp.jag-icpc.org/spaghetti_source/20120923/1348327542.html)
