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
    - http://web.cs.unlv.edu/larmore/Courses/CSC477/monge.pdf
    - https://codeforces.com/contest/1423/submission/98368491
    - https://topcoder-g-hatena-ne-jp.jag-icpc.org/spaghetti_source/20120923/1348327542.html
    - https://www.codechef.com/problems/MAXPREFFLIP
  bundledCode: "#line 2 \"other_algorithms/smawk.hpp\"\n#include <cassert>\n#include\
    \ <functional>\n#include <numeric>\n#include <unordered_map>\n#include <utility>\n\
    #include <vector>\n\n// SMAWK: finding minima of totally monotone function f(i,\
    \ j) (0 <= i < N, 0 <= j < M) for each i\n// Constraints: every submatrix of f(i,\
    \ j) is monotone.\n// Complexity: O(N + M)\n// Option: `Memorization`: Memorize\
    \ all query results using hashmaps, effective when each query\n// requires heavy\
    \ complexity Rererence:\n// https://topcoder-g-hatena-ne-jp.jag-icpc.org/spaghetti_source/20120923/1348327542.html\n\
    // http://web.cs.unlv.edu/larmore/Courses/CSC477/monge.pdf\n// Verify: https://codeforces.com/contest/1423/submission/98368491\n\
    template <typename T, bool Memorization> struct SMAWK {\n    std::vector<std::pair<int,\
    \ T>> minima;\n    std::function<T(int, int)> oracle;\n    std::vector<std::unordered_map<int,\
    \ T>> memo;\n    T _query(int i, int j) {\n        if (Memorization)\n       \
    \     return memo[i].count(j) ? memo[i][j] : (memo[i][j] = oracle(i, j));\n  \
    \      else\n            return oracle(i, j);\n    }\n\n    void _smawk_rec(const\
    \ std::vector<int> &js, int ib, int ie, int id) {\n        if (ib > ie) return;\n\
    \        std::vector<int> js2;\n        int i = ib;\n        for (auto j : js)\
    \ {\n            while (!js2.empty() and _query(i, js2.back()) >= _query(i, j))\
    \ js2.pop_back(), i -= id;\n            if (int(js2.size()) != (ie - ib) / id)\
    \ js2.push_back(j), i += id;\n        }\n        _smawk_rec(js2, ib + id, ie,\
    \ id * 2);\n\n        for (int i = ib, q = 0; i <= ie; i += id * 2) {\n      \
    \      int jt = (i + id <= ie ? minima[i + id].first : js.back());\n         \
    \   T fm = 0;\n            bool init = true;\n            for (; q < int(js.size());\
    \ ++q) {\n                T fq = _query(i, js[q]);\n                if (init or\
    \ fm > fq) fm = fq, minima[i] = std::make_pair(js[q], fq);\n                init\
    \ = false;\n                if (js[q] == jt) break;\n            }\n        }\n\
    \    }\n    SMAWK(int N, int M, std::function<T(int i, int j)> oracle_) : minima(N),\
    \ oracle(oracle_) {\n        if (Memorization) memo.resize(N);\n        std::vector<int>\
    \ js(M);\n        std::iota(js.begin(), js.end(), 0);\n        _smawk_rec(js,\
    \ 0, N - 1, 1);\n    }\n};\n\n// Concave max-plus convolution\n// b must be concave\n\
    // Complexity: O(n + m)\n// Verify: https://www.codechef.com/problems/MAXPREFFLIP\n\
    template <class S, S INF>\nstd::vector<S> concave_max_plus_convolution(const std::vector<S>\
    \ &a, const std::vector<S> &b) {\n    const int n = a.size(), m = b.size();\n\n\
    \    auto is_concave = [&](const std::vector<S> &u) -> bool {\n        for (int\
    \ i = 1; i + 1 < int(u.size()); ++i) {\n            if (u[i - 1] + u[i + 1] >\
    \ u[i] + u[i]) return false;\n        }\n        return true;\n    };\n\n    bool\
    \ a_concave = is_concave(a), b_concave = is_concave(b);\n    assert(a_concave\
    \ or b_concave);\n    if (!b_concave) return concave_max_plus_convolution<S, INF>(b,\
    \ a);\n\n    auto select = [&](int i, int j) -> S {\n        int aidx = j, bidx\
    \ = i - j;\n        if (bidx < 0 or bidx >= m or aidx >= n) return INF;\n    \
    \    return -(a[aidx] + b[bidx]);\n    };\n    SMAWK<S, false> sm(n + m - 1, n,\
    \ select);\n    std::vector<S> ret;\n    for (auto x : sm.minima) ret.push_back(-x.second);\n\
    \    return ret;\n}\n"
  code: "#pragma once\n#include <cassert>\n#include <functional>\n#include <numeric>\n\
    #include <unordered_map>\n#include <utility>\n#include <vector>\n\n// SMAWK: finding\
    \ minima of totally monotone function f(i, j) (0 <= i < N, 0 <= j < M) for each\
    \ i\n// Constraints: every submatrix of f(i, j) is monotone.\n// Complexity: O(N\
    \ + M)\n// Option: `Memorization`: Memorize all query results using hashmaps,\
    \ effective when each query\n// requires heavy complexity Rererence:\n// https://topcoder-g-hatena-ne-jp.jag-icpc.org/spaghetti_source/20120923/1348327542.html\n\
    // http://web.cs.unlv.edu/larmore/Courses/CSC477/monge.pdf\n// Verify: https://codeforces.com/contest/1423/submission/98368491\n\
    template <typename T, bool Memorization> struct SMAWK {\n    std::vector<std::pair<int,\
    \ T>> minima;\n    std::function<T(int, int)> oracle;\n    std::vector<std::unordered_map<int,\
    \ T>> memo;\n    T _query(int i, int j) {\n        if (Memorization)\n       \
    \     return memo[i].count(j) ? memo[i][j] : (memo[i][j] = oracle(i, j));\n  \
    \      else\n            return oracle(i, j);\n    }\n\n    void _smawk_rec(const\
    \ std::vector<int> &js, int ib, int ie, int id) {\n        if (ib > ie) return;\n\
    \        std::vector<int> js2;\n        int i = ib;\n        for (auto j : js)\
    \ {\n            while (!js2.empty() and _query(i, js2.back()) >= _query(i, j))\
    \ js2.pop_back(), i -= id;\n            if (int(js2.size()) != (ie - ib) / id)\
    \ js2.push_back(j), i += id;\n        }\n        _smawk_rec(js2, ib + id, ie,\
    \ id * 2);\n\n        for (int i = ib, q = 0; i <= ie; i += id * 2) {\n      \
    \      int jt = (i + id <= ie ? minima[i + id].first : js.back());\n         \
    \   T fm = 0;\n            bool init = true;\n            for (; q < int(js.size());\
    \ ++q) {\n                T fq = _query(i, js[q]);\n                if (init or\
    \ fm > fq) fm = fq, minima[i] = std::make_pair(js[q], fq);\n                init\
    \ = false;\n                if (js[q] == jt) break;\n            }\n        }\n\
    \    }\n    SMAWK(int N, int M, std::function<T(int i, int j)> oracle_) : minima(N),\
    \ oracle(oracle_) {\n        if (Memorization) memo.resize(N);\n        std::vector<int>\
    \ js(M);\n        std::iota(js.begin(), js.end(), 0);\n        _smawk_rec(js,\
    \ 0, N - 1, 1);\n    }\n};\n\n// Concave max-plus convolution\n// b must be concave\n\
    // Complexity: O(n + m)\n// Verify: https://www.codechef.com/problems/MAXPREFFLIP\n\
    template <class S, S INF>\nstd::vector<S> concave_max_plus_convolution(const std::vector<S>\
    \ &a, const std::vector<S> &b) {\n    const int n = a.size(), m = b.size();\n\n\
    \    auto is_concave = [&](const std::vector<S> &u) -> bool {\n        for (int\
    \ i = 1; i + 1 < int(u.size()); ++i) {\n            if (u[i - 1] + u[i + 1] >\
    \ u[i] + u[i]) return false;\n        }\n        return true;\n    };\n\n    bool\
    \ a_concave = is_concave(a), b_concave = is_concave(b);\n    assert(a_concave\
    \ or b_concave);\n    if (!b_concave) return concave_max_plus_convolution<S, INF>(b,\
    \ a);\n\n    auto select = [&](int i, int j) -> S {\n        int aidx = j, bidx\
    \ = i - j;\n        if (bidx < 0 or bidx >= m or aidx >= n) return INF;\n    \
    \    return -(a[aidx] + b[bidx]);\n    };\n    SMAWK<S, false> sm(n + m - 1, n,\
    \ select);\n    std::vector<S> ret;\n    for (auto x : sm.minima) ret.push_back(-x.second);\n\
    \    return ret;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: other_algorithms/smawk.hpp
  requiredBy: []
  timestamp: '2022-11-14 22:38:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: other_algorithms/smawk.hpp
layout: document
title: Totally Monotone Matrix Searching (SMAWK)
---

Totally monotone な $N \times M$ 行列について，各行の最小値の位置を $O(N + M)$ で取得する．

## 使用方法

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

## 問題例

- [Communication Channel \| CodeChef](https://www.codechef.com/problems/COMMCHA)
- [Maximal Prefix After Flip \| CodeChef](https://www.codechef.com/problems/MAXPREFFLIP)

## Links

- [SMAWK Algorithm \| Library](https://noshi91.github.io/Library/algorithm/smawk.cpp.html)
