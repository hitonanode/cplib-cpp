---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: other_algorithms/monge_d_edge_shortest_paths_enum.hpp
    title: "Shortest paths of DAG with Monge weights using $d = 1, \\ldots, d_{\\\
      mathrm{max}}$ edges \uFF08Monge \u91CD\u307F DAG \u306E\u4F7F\u7528\u8FBA\u6570\
      \u6BCE\u306E\u6700\u77ED\u8DEF\u9577\u5217\u6319\uFF09"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: other_algorithms/test/concave_max_plus_convolution.test.cpp
    title: other_algorithms/test/concave_max_plus_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: other_algorithms/test/concave_min_plus_convolution.test.cpp
    title: other_algorithms/test/concave_min_plus_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: other_algorithms/test/monge_d_edge_shortest_paths_enum.yuki952.test.cpp
    title: other_algorithms/test/monge_d_edge_shortest_paths_enum.yuki952.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - http://web.cs.unlv.edu/larmore/Courses/CSC477/monge.pdf
    - https://codeforces.com/contest/1423/submission/98368491
    - https://topcoder-g-hatena-ne-jp.jag-icpc.org/spaghetti_source/20120923/1348327542.html
    - https://www.codechef.com/problems/MAXPREFFLIP
  bundledCode: "#line 2 \"other_algorithms/smawk.hpp\"\n#include <cassert>\n#include\
    \ <functional>\n#include <numeric>\n#include <utility>\n#include <vector>\n\n\
    // SMAWK: finding minima of totally monotone function f(i, j) (0 <= i < N, 0 <=\
    \ j < M) for each i\n// Constraints: every submatrix of f(i, j) is monotone (=\
    \ totally monotone).\n// Complexity: O(N + M)\n// Reference:\n// https://topcoder-g-hatena-ne-jp.jag-icpc.org/spaghetti_source/20120923/1348327542.html\n\
    // http://web.cs.unlv.edu/larmore/Courses/CSC477/monge.pdf\n// Verify: https://codeforces.com/contest/1423/submission/98368491\n\
    template <class T>\nstd::vector<std::pair<int, T>> SMAWK(int N, int M, const std::function<T(int\
    \ i, int j)> &weight) {\n    std::vector<std::pair<int, T>> minima(N);\n\n   \
    \ auto rec = [&](auto &&self, const std::vector<int> &js, int ib, int ie, int\
    \ id) {\n        if (ib > ie) return;\n        std::vector<int> js2;\n       \
    \ int i = ib;\n        for (int j : js) {\n            while (!js2.empty() and\
    \ weight(i, js2.back()) >= weight(i, j)) js2.pop_back(), i -= id;\n          \
    \  if (int(js2.size()) != (ie - ib) / id) js2.push_back(j), i += id;\n       \
    \ }\n        self(self, js2, ib + id, ie, id * 2);\n\n        for (int i = ib,\
    \ q = 0; i <= ie; i += id * 2) {\n            const int jt = (i + id <= ie ? minima[i\
    \ + id].first : js.back());\n            T fm = 0;\n            bool init = true;\n\
    \            for (; q < int(js.size()); ++q) {\n                const T fq = weight(i,\
    \ js[q]);\n                if (init or fm > fq) fm = fq, minima[i] = std::make_pair(js[q],\
    \ fq);\n                init = false;\n                if (js[q] == jt) break;\n\
    \            }\n        }\n    };\n\n    std::vector<int> js(M);\n    std::iota(js.begin(),\
    \ js.end(), 0);\n    rec(rec, js, 0, N - 1, 1);\n\n    return minima;\n}\n\n//\
    \ Find minima of totally ANTI-monotone function f(i, j) (0 <= i < N, 0 <= j <\
    \ M) for each i\n// Constraints: every submatrix of f(i, j) is anti-monotone.\n\
    // Complexity: O(N + M)\ntemplate <class T>\nstd::vector<std::pair<int, T>>\n\
    SMAWKAntiMonotone(int N, int M, const std::function<T(int i, int j)> &weight)\
    \ {\n    auto minima = SMAWK<T>(N, M, [&](int i, int j) -> T { return weight(i,\
    \ M - 1 - j); });\n    for (auto &p : minima) p.first = M - 1 - p.first;\n   \
    \ return minima;\n}\n\n// Concave max-plus convolution\n// **b MUST BE CONCAVE**\n\
    // Complexity: O(n + m)\n// Verify: https://www.codechef.com/problems/MAXPREFFLIP\n\
    template <class S, S INF>\nstd::vector<S> concave_max_plus_convolution(const std::vector<S>\
    \ &a, const std::vector<S> &b) {\n    const int n = a.size(), m = b.size();\n\n\
    \    auto is_concave = [&](const std::vector<S> &u) -> bool {\n        for (int\
    \ i = 1; i + 1 < int(u.size()); ++i) {\n            if (u[i - 1] + u[i + 1] >\
    \ u[i] + u[i]) return false;\n        }\n        return true;\n    };\n    assert(is_concave(b));\n\
    \n    auto select = [&](int i, int j) -> S {\n        int aidx = j, bidx = i -\
    \ j;\n        if (bidx < 0 or bidx >= m or aidx >= n) return INF;\n        return\
    \ -(a[aidx] + b[bidx]);\n    };\n    const auto minima = SMAWK<S>(n + m - 1, n,\
    \ select);\n    std::vector<S> ret;\n    for (auto x : minima) ret.push_back(-x.second);\n\
    \    return ret;\n}\n\n// Concave min-plus convolution\n// **b MUST BE CONCAVE**\n\
    // Complexity: O((n + m)log(n + m))\ntemplate <class S>\nstd::vector<S> concave_min_plus_convolution(const\
    \ std::vector<S> &a, const std::vector<S> &b) {\n    const int n = a.size(), m\
    \ = b.size();\n\n    auto is_concave = [&](const std::vector<S> &u) -> bool {\n\
    \        for (int i = 1; i + 1 < int(u.size()); ++i) {\n            if (u[i -\
    \ 1] + u[i + 1] > u[i] + u[i]) return false;\n        }\n        return true;\n\
    \    };\n    assert(is_concave(b));\n\n    std::vector<S> ret(n + m - 1);\n  \
    \  std::vector<int> argmin(n + m - 1, -1);\n\n    // mat[i][j] = a[j] + b[i -\
    \ j]\n    auto is_valid = [&](int i, int j) { return 0 <= i - j and i - j < m;\
    \ };\n    auto has_valid = [&](int il, int ir, int jl, int jr) {\n        if (il\
    \ >= ir or jl >= jr) return false;\n        return is_valid(il, jl) or is_valid(il,\
    \ jr - 1) or is_valid(ir - 1, jl) or\n               is_valid(ir - 1, jr - 1);\n\
    \    };\n\n    auto rec = [&](auto &&self, int il, int ir, int jl, int jr) ->\
    \ void {\n        if (!has_valid(il, ir, jl, jr)) return;\n\n        if (is_valid(il,\
    \ jr - 1) and is_valid(ir - 1, jl)) {\n            auto select = [&](int i, int\
    \ j) -> S { return a[j + jl] + b[(i + il) - (j + jl)]; };\n            const auto\
    \ res = SMAWKAntiMonotone<S>(ir - il, jr - jl, select);\n            for (int\
    \ idx = 0; idx < ir - il; ++idx) {\n                const int i = il + idx;\n\
    \                if (argmin[i] == -1 or res[idx].second < ret[i]) {\n        \
    \            ret[i] = res[idx].second;\n                    argmin[i] = res[idx].first\
    \ + jl;\n                }\n            }\n        } else {\n            if (const\
    \ int di = ir - il, dj = jr - jl; di > dj) {\n                const int im = (il\
    \ + ir) / 2;\n                self(self, il, im, jl, jr);\n                self(self,\
    \ im, ir, jl, jr);\n            } else {\n                const int jm = (jl +\
    \ jr) / 2;\n                self(self, il, ir, jl, jm);\n                self(self,\
    \ il, ir, jm, jr);\n            }\n        }\n    };\n\n    rec(rec, 0, n + m\
    \ - 1, 0, n);\n\n    return ret;\n    // return argmin;  // If you want argmin\
    \ (0 <= argmin[idx] < len(a))\n}\n"
  code: "#pragma once\n#include <cassert>\n#include <functional>\n#include <numeric>\n\
    #include <utility>\n#include <vector>\n\n// SMAWK: finding minima of totally monotone\
    \ function f(i, j) (0 <= i < N, 0 <= j < M) for each i\n// Constraints: every\
    \ submatrix of f(i, j) is monotone (= totally monotone).\n// Complexity: O(N +\
    \ M)\n// Reference:\n// https://topcoder-g-hatena-ne-jp.jag-icpc.org/spaghetti_source/20120923/1348327542.html\n\
    // http://web.cs.unlv.edu/larmore/Courses/CSC477/monge.pdf\n// Verify: https://codeforces.com/contest/1423/submission/98368491\n\
    template <class T>\nstd::vector<std::pair<int, T>> SMAWK(int N, int M, const std::function<T(int\
    \ i, int j)> &weight) {\n    std::vector<std::pair<int, T>> minima(N);\n\n   \
    \ auto rec = [&](auto &&self, const std::vector<int> &js, int ib, int ie, int\
    \ id) {\n        if (ib > ie) return;\n        std::vector<int> js2;\n       \
    \ int i = ib;\n        for (int j : js) {\n            while (!js2.empty() and\
    \ weight(i, js2.back()) >= weight(i, j)) js2.pop_back(), i -= id;\n          \
    \  if (int(js2.size()) != (ie - ib) / id) js2.push_back(j), i += id;\n       \
    \ }\n        self(self, js2, ib + id, ie, id * 2);\n\n        for (int i = ib,\
    \ q = 0; i <= ie; i += id * 2) {\n            const int jt = (i + id <= ie ? minima[i\
    \ + id].first : js.back());\n            T fm = 0;\n            bool init = true;\n\
    \            for (; q < int(js.size()); ++q) {\n                const T fq = weight(i,\
    \ js[q]);\n                if (init or fm > fq) fm = fq, minima[i] = std::make_pair(js[q],\
    \ fq);\n                init = false;\n                if (js[q] == jt) break;\n\
    \            }\n        }\n    };\n\n    std::vector<int> js(M);\n    std::iota(js.begin(),\
    \ js.end(), 0);\n    rec(rec, js, 0, N - 1, 1);\n\n    return minima;\n}\n\n//\
    \ Find minima of totally ANTI-monotone function f(i, j) (0 <= i < N, 0 <= j <\
    \ M) for each i\n// Constraints: every submatrix of f(i, j) is anti-monotone.\n\
    // Complexity: O(N + M)\ntemplate <class T>\nstd::vector<std::pair<int, T>>\n\
    SMAWKAntiMonotone(int N, int M, const std::function<T(int i, int j)> &weight)\
    \ {\n    auto minima = SMAWK<T>(N, M, [&](int i, int j) -> T { return weight(i,\
    \ M - 1 - j); });\n    for (auto &p : minima) p.first = M - 1 - p.first;\n   \
    \ return minima;\n}\n\n// Concave max-plus convolution\n// **b MUST BE CONCAVE**\n\
    // Complexity: O(n + m)\n// Verify: https://www.codechef.com/problems/MAXPREFFLIP\n\
    template <class S, S INF>\nstd::vector<S> concave_max_plus_convolution(const std::vector<S>\
    \ &a, const std::vector<S> &b) {\n    const int n = a.size(), m = b.size();\n\n\
    \    auto is_concave = [&](const std::vector<S> &u) -> bool {\n        for (int\
    \ i = 1; i + 1 < int(u.size()); ++i) {\n            if (u[i - 1] + u[i + 1] >\
    \ u[i] + u[i]) return false;\n        }\n        return true;\n    };\n    assert(is_concave(b));\n\
    \n    auto select = [&](int i, int j) -> S {\n        int aidx = j, bidx = i -\
    \ j;\n        if (bidx < 0 or bidx >= m or aidx >= n) return INF;\n        return\
    \ -(a[aidx] + b[bidx]);\n    };\n    const auto minima = SMAWK<S>(n + m - 1, n,\
    \ select);\n    std::vector<S> ret;\n    for (auto x : minima) ret.push_back(-x.second);\n\
    \    return ret;\n}\n\n// Concave min-plus convolution\n// **b MUST BE CONCAVE**\n\
    // Complexity: O((n + m)log(n + m))\ntemplate <class S>\nstd::vector<S> concave_min_plus_convolution(const\
    \ std::vector<S> &a, const std::vector<S> &b) {\n    const int n = a.size(), m\
    \ = b.size();\n\n    auto is_concave = [&](const std::vector<S> &u) -> bool {\n\
    \        for (int i = 1; i + 1 < int(u.size()); ++i) {\n            if (u[i -\
    \ 1] + u[i + 1] > u[i] + u[i]) return false;\n        }\n        return true;\n\
    \    };\n    assert(is_concave(b));\n\n    std::vector<S> ret(n + m - 1);\n  \
    \  std::vector<int> argmin(n + m - 1, -1);\n\n    // mat[i][j] = a[j] + b[i -\
    \ j]\n    auto is_valid = [&](int i, int j) { return 0 <= i - j and i - j < m;\
    \ };\n    auto has_valid = [&](int il, int ir, int jl, int jr) {\n        if (il\
    \ >= ir or jl >= jr) return false;\n        return is_valid(il, jl) or is_valid(il,\
    \ jr - 1) or is_valid(ir - 1, jl) or\n               is_valid(ir - 1, jr - 1);\n\
    \    };\n\n    auto rec = [&](auto &&self, int il, int ir, int jl, int jr) ->\
    \ void {\n        if (!has_valid(il, ir, jl, jr)) return;\n\n        if (is_valid(il,\
    \ jr - 1) and is_valid(ir - 1, jl)) {\n            auto select = [&](int i, int\
    \ j) -> S { return a[j + jl] + b[(i + il) - (j + jl)]; };\n            const auto\
    \ res = SMAWKAntiMonotone<S>(ir - il, jr - jl, select);\n            for (int\
    \ idx = 0; idx < ir - il; ++idx) {\n                const int i = il + idx;\n\
    \                if (argmin[i] == -1 or res[idx].second < ret[i]) {\n        \
    \            ret[i] = res[idx].second;\n                    argmin[i] = res[idx].first\
    \ + jl;\n                }\n            }\n        } else {\n            if (const\
    \ int di = ir - il, dj = jr - jl; di > dj) {\n                const int im = (il\
    \ + ir) / 2;\n                self(self, il, im, jl, jr);\n                self(self,\
    \ im, ir, jl, jr);\n            } else {\n                const int jm = (jl +\
    \ jr) / 2;\n                self(self, il, ir, jl, jm);\n                self(self,\
    \ il, ir, jm, jr);\n            }\n        }\n    };\n\n    rec(rec, 0, n + m\
    \ - 1, 0, n);\n\n    return ret;\n    // return argmin;  // If you want argmin\
    \ (0 <= argmin[idx] < len(a))\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: other_algorithms/smawk.hpp
  requiredBy:
  - other_algorithms/monge_d_edge_shortest_paths_enum.hpp
  timestamp: '2025-08-24 23:54:21+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - other_algorithms/test/monge_d_edge_shortest_paths_enum.yuki952.test.cpp
  - other_algorithms/test/concave_min_plus_convolution.test.cpp
  - other_algorithms/test/concave_max_plus_convolution.test.cpp
documentation_of: other_algorithms/smawk.hpp
layout: document
title: Totally Monotone Matrix Searching (SMAWK), concave max-plus / min-plus convolution
---

`SMAWK()` 関数は，totally monotone な $N \times M$ 行列について，各行の最小値の位置およびその値を $O(N + M)$ で取得する．
また， totally anti-monotone （不等式の向きが逆，つまり行最小値の位置が行に対して単調非増加などの性質を持つ）な行列に対して同様に最小値を取得する `SMAWKAntiMonotone()` 関数も実装されている．

## 使用方法

### SMAWK

```cpp
using T = long long;
int H, W;
auto f = [&](int i, int j) -> T { return 0; };

const vector<pair<int, T>> argmin_min_pairs = SMAWK<T>(H, W, f);
```

### 応用例：concave max-plus convolution

列 $a = (a\_0, \dots, a\_{n - 1}), b = (b\_0, \dots, b\_{m - 1})$ で特に $b$ が concave なものが与えられたとき，$a$ と $b$ の max-plus convolution $c = (c\_0, \dots, c\_{n + m - 2})$:

$$
c_i = \max_{j + k = i} a_j + b_k
$$

は SMAWK を利用することで $O(n + m)$ で計算できる．

```cpp
vector<int> a, b;

vector<int> c = concave_max_plus_convolution<int, 1 << 30>(a, b);
```

### 応用例：concave min-plus convolution

上記と同様の状況設定で，逆に min-plus convolution も SMAWK を応用することで $O((n + m) \log (n + m))$ で計算できる．

このとき，SMAWK を適用したい仮想的な $(n + m - 1) \times n$ 行列は，無効値の位置の都合が悪く totally monotone でも totally anti-monotone でもないため直接扱えない．ここで，有効値が入った平行四辺形の領域をうまく矩形に分割していくことで `SMAWKAntiMonotone()` 関数が適用可能な状況にしている（この分割統治で計算量に log がつく）．

## 問題例

- [Communication Channel \| CodeChef](https://www.codechef.com/problems/COMMCHA)
- [Maximal Prefix After Flip \| CodeChef](https://www.codechef.com/problems/MAXPREFFLIP)
- [Min Plus Convolution (Convex and Arbitrary)](https://judge.yosupo.jp/problem/min_plus_convolution_convex_arbitrary)
- [Min Plus Convolution (Concave and Arbitrary)](https://judge.yosupo.jp/problem/min_plus_convolution_concave_arbitrary)

## Links

- [SMAWK Algorithm \| Library](https://noshi91.github.io/Library/algorithm/smawk.cpp.html)
