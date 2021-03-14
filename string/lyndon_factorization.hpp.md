---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: string/test/run_enumerate_lyndon_hash.test.cpp
    title: string/test/run_enumerate_lyndon_hash.test.cpp
  - icon: ':heavy_check_mark:'
    path: string/test/run_enumerate_lyndon_rmq.test.cpp
    title: string/test/run_enumerate_lyndon_rmq.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://cp-algorithms.com/string/lyndon_factorization.html
    - https://qiita.com/nakashi18/items/66882bd6e0127174267a
  bundledCode: "#line 2 \"string/lyndon_factorization.hpp\"\n#include <algorithm>\n\
    #include <string>\n#include <tuple>\n#include <utility>\n#include <vector>\n\n\
    // CUT begin\n// Lyndon factorization based on Duval's algorithm\n// **NOT VERIFIED\
    \ YET**\n// Reference:\n// [1] K. T. Chen, R. H. Fox, R. C. Lyndon,\n//     \"\
    Free Differential Calculus, IV. The Quotient Groups of the Lower Central Series,\"\
    \n//     Annals of Mathematics, 81-95, 1958.\n// [2] J. P. Duval, \"Factorizing\
    \ words over an ordered alphabet,\"\n//     Journal of Algorithms, 4(4), 363-381,\
    \ 1983.\n// - https://cp-algorithms.com/string/lyndon_factorization.html\n// -\
    \ https://qiita.com/nakashi18/items/66882bd6e0127174267a\ntemplate <typename T>\
    \ std::vector<std::pair<int, int>> lyndon_factorization(const std::vector<T> &S)\
    \ {\n    const int N = S.size();\n    std::vector<std::pair<int, int>> ret;\n\
    \    for (int l = 0; l < N;) {\n        int i = l, j = i + 1;\n        while (j\
    \ < N and S[i] <= S[j]) i = (S[i] == S[j] ? i + 1 : l), j++;\n        int n =\
    \ (j - l) / (j - i);\n        for (int t = 0; t < n; t++) ret.emplace_back(l,\
    \ j - i), l += j - i;\n    }\n    return ret;\n}\n\nstd::vector<std::pair<int,\
    \ int>> lyndon_factorization(const std::string &s) {\n    const int N = int(s.size());\n\
    \    std::vector<int> v(N);\n    for (int i = 0; i < N; i++) v[i] = s[i];\n  \
    \  return lyndon_factorization<int>(v);\n}\n\n// Compute the longest Lyndon prefix\
    \ for each suffix s[i:N]\n// (Our implementation is $O(N \\cdot (complexity of\
    \ lcplen()))$)\n// Example:\n// - `teletelepathy` -> [1,4,1,2,1,4,1,2,1,4,1,2,1]\n\
    // Reference:\n// [1] H. Bannai et al., \"The \"Runs\" Theorem,\"\n//     SIAM\
    \ Journal on Computing, 46.5, 1501-1514, 2017.\ntemplate <typename String, typename\
    \ LCPLENCallable>\nstd::vector<int> longest_lyndon_prefixes(const String &s, const\
    \ LCPLENCallable &lcp) {\n    const int N = s.size();\n    std::vector<std::pair<int,\
    \ int>> st{{N, N}};\n    std::vector<int> ret(N);\n    for (int i = N - 1, j =\
    \ i; i >= 0; i--, j = i) {\n        while (st.size() > 1) {\n            int iv\
    \ = st.back().first, jv = st.back().second;\n            int l = lcp.lcplen(i,\
    \ iv);\n            if (!(iv + l < N and s[i + l] < s[iv + l])) break;\n     \
    \       j = jv;\n            st.pop_back();\n        }\n        st.emplace_back(i,\
    \ j);\n        ret[i] = j - i + 1;\n    }\n    return ret;\n}\n\n// Compute all\
    \ runs in given string\n// Complexity: $O(N \\cdot (complexity of lcplen()))$\
    \ in this implementation\n// (Theoretically $O(N)$ achievable)\n// N = 2e5 ->\
    \ ~120 ms\n// Reference:\n// [1] H. Bannai et al., \"The \"Runs\" Theorem,\"\n\
    //     SIAM Journal on Computing, 46.5, 1501-1514, 2017.\ntemplate <typename LCPLENCallable,\
    \ typename String> std::vector<std::tuple<int, int, int>> run_enumerate(String\
    \ s) {\n    if (s.empty()) return {};\n    LCPLENCallable lcp(s);\n    std::reverse(s.begin(),\
    \ s.end());\n    LCPLENCallable revlcp(s);\n    std::reverse(s.begin(), s.end());\n\
    \    auto t = s;\n    auto lo = *std::min_element(s.begin(), s.end()), hi = *std::max_element(s.begin(),\
    \ s.end());\n    for (auto &c : t) c = hi - (c - lo);\n    auto l1 = longest_lyndon_prefixes(s,\
    \ lcp), l2 = longest_lyndon_prefixes(t, lcp);\n    int N = s.size();\n    std::vector<std::tuple<int,\
    \ int, int>> ret;\n    for (int i = 0; i < N; i++) {\n        int j = i + l1[i],\
    \ L = i - revlcp.lcplen(N - i, N - j), R = j + lcp.lcplen(i, j);\n        if (R\
    \ - L >= (j - i) * 2) ret.emplace_back(j - i, L, R);\n\n        if (l1[i] != l2[i])\
    \ {\n            j = i + l2[i], L = i - revlcp.lcplen(N - i, N - j), R = j + lcp.lcplen(i,\
    \ j);\n            if (R - L >= (j - i) * 2) ret.emplace_back(j - i, L, R);\n\
    \        }\n    }\n    std::sort(ret.begin(), ret.end());\n    ret.erase(std::unique(ret.begin(),\
    \ ret.end()), ret.end());\n    return ret;\n}\n"
  code: "#pragma once\n#include <algorithm>\n#include <string>\n#include <tuple>\n\
    #include <utility>\n#include <vector>\n\n// CUT begin\n// Lyndon factorization\
    \ based on Duval's algorithm\n// **NOT VERIFIED YET**\n// Reference:\n// [1] K.\
    \ T. Chen, R. H. Fox, R. C. Lyndon,\n//     \"Free Differential Calculus, IV.\
    \ The Quotient Groups of the Lower Central Series,\"\n//     Annals of Mathematics,\
    \ 81-95, 1958.\n// [2] J. P. Duval, \"Factorizing words over an ordered alphabet,\"\
    \n//     Journal of Algorithms, 4(4), 363-381, 1983.\n// - https://cp-algorithms.com/string/lyndon_factorization.html\n\
    // - https://qiita.com/nakashi18/items/66882bd6e0127174267a\ntemplate <typename\
    \ T> std::vector<std::pair<int, int>> lyndon_factorization(const std::vector<T>\
    \ &S) {\n    const int N = S.size();\n    std::vector<std::pair<int, int>> ret;\n\
    \    for (int l = 0; l < N;) {\n        int i = l, j = i + 1;\n        while (j\
    \ < N and S[i] <= S[j]) i = (S[i] == S[j] ? i + 1 : l), j++;\n        int n =\
    \ (j - l) / (j - i);\n        for (int t = 0; t < n; t++) ret.emplace_back(l,\
    \ j - i), l += j - i;\n    }\n    return ret;\n}\n\nstd::vector<std::pair<int,\
    \ int>> lyndon_factorization(const std::string &s) {\n    const int N = int(s.size());\n\
    \    std::vector<int> v(N);\n    for (int i = 0; i < N; i++) v[i] = s[i];\n  \
    \  return lyndon_factorization<int>(v);\n}\n\n// Compute the longest Lyndon prefix\
    \ for each suffix s[i:N]\n// (Our implementation is $O(N \\cdot (complexity of\
    \ lcplen()))$)\n// Example:\n// - `teletelepathy` -> [1,4,1,2,1,4,1,2,1,4,1,2,1]\n\
    // Reference:\n// [1] H. Bannai et al., \"The \"Runs\" Theorem,\"\n//     SIAM\
    \ Journal on Computing, 46.5, 1501-1514, 2017.\ntemplate <typename String, typename\
    \ LCPLENCallable>\nstd::vector<int> longest_lyndon_prefixes(const String &s, const\
    \ LCPLENCallable &lcp) {\n    const int N = s.size();\n    std::vector<std::pair<int,\
    \ int>> st{{N, N}};\n    std::vector<int> ret(N);\n    for (int i = N - 1, j =\
    \ i; i >= 0; i--, j = i) {\n        while (st.size() > 1) {\n            int iv\
    \ = st.back().first, jv = st.back().second;\n            int l = lcp.lcplen(i,\
    \ iv);\n            if (!(iv + l < N and s[i + l] < s[iv + l])) break;\n     \
    \       j = jv;\n            st.pop_back();\n        }\n        st.emplace_back(i,\
    \ j);\n        ret[i] = j - i + 1;\n    }\n    return ret;\n}\n\n// Compute all\
    \ runs in given string\n// Complexity: $O(N \\cdot (complexity of lcplen()))$\
    \ in this implementation\n// (Theoretically $O(N)$ achievable)\n// N = 2e5 ->\
    \ ~120 ms\n// Reference:\n// [1] H. Bannai et al., \"The \"Runs\" Theorem,\"\n\
    //     SIAM Journal on Computing, 46.5, 1501-1514, 2017.\ntemplate <typename LCPLENCallable,\
    \ typename String> std::vector<std::tuple<int, int, int>> run_enumerate(String\
    \ s) {\n    if (s.empty()) return {};\n    LCPLENCallable lcp(s);\n    std::reverse(s.begin(),\
    \ s.end());\n    LCPLENCallable revlcp(s);\n    std::reverse(s.begin(), s.end());\n\
    \    auto t = s;\n    auto lo = *std::min_element(s.begin(), s.end()), hi = *std::max_element(s.begin(),\
    \ s.end());\n    for (auto &c : t) c = hi - (c - lo);\n    auto l1 = longest_lyndon_prefixes(s,\
    \ lcp), l2 = longest_lyndon_prefixes(t, lcp);\n    int N = s.size();\n    std::vector<std::tuple<int,\
    \ int, int>> ret;\n    for (int i = 0; i < N; i++) {\n        int j = i + l1[i],\
    \ L = i - revlcp.lcplen(N - i, N - j), R = j + lcp.lcplen(i, j);\n        if (R\
    \ - L >= (j - i) * 2) ret.emplace_back(j - i, L, R);\n\n        if (l1[i] != l2[i])\
    \ {\n            j = i + l2[i], L = i - revlcp.lcplen(N - i, N - j), R = j + lcp.lcplen(i,\
    \ j);\n            if (R - L >= (j - i) * 2) ret.emplace_back(j - i, L, R);\n\
    \        }\n    }\n    std::sort(ret.begin(), ret.end());\n    ret.erase(std::unique(ret.begin(),\
    \ ret.end()), ret.end());\n    return ret;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: string/lyndon_factorization.hpp
  requiredBy: []
  timestamp: '2021-03-14 17:31:33+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - string/test/run_enumerate_lyndon_rmq.test.cpp
  - string/test/run_enumerate_lyndon_hash.test.cpp
documentation_of: string/lyndon_factorization.hpp
layout: document
title: "Lyndon factorization \uFF08Lyndon \u5206\u89E3\uFF09"
---

文字列・数列などの比較可能なものの列に対して Lyndon 分解を行う．

## Lyndon 文字列

- $S$ が Lyndon 文字列であるとは，$S$ の（非空な）接尾辞の中で $S$ 自身が辞書順最小であること

## Lyndon 分解

- （定義）Lyndon 分解とは，文字列 $S$ の分割 $S = w_1 w_2 \dots w_M$ で，各 $w_i$ は Lyndon 文字列で，しかも $w_i$ たちが辞書順非増加であるもの．
- （一意性）Lyndon 分解は一意．
- （構成）$w_1$ は，$S$ の接頭辞で Lyndon であるような最長のもの．

## 実装されている関数

### lyndon_factorization

```cpp
vector<pair<int, int>> ret = lyndon_factorization(s);
```

- 文字列など比較可能な要素の列 `s` を Lyndon 分解した際の，（先頭位置，長さ）の組の列を出力
- 計算量 $O(N)$

### longest_lyndon_prefixes

``` cpp
vector<int> ret = longest_lyndon_prefixes(s, LCPLEN_Callable_obj);
```

- 各 suffix `s[i:N)` に関する最長な Lyndon prefix `s[i:i+len(i))` の長さ `len(i)` を格納した配列を出力
- 計算量 $O(NL)$
  - $L$ は `s[i:)` と `s[j:)` の longest common prefix 長の計算一回に要する計算量

### run_enumerate

``` cpp
ret = run_enumerate<LCPLEN_Callable>(s);
```

- 各 run について `(c, l, r)` （`s[l:r)` が最小周期 `c`，2 周期以上）を全列挙
- 計算量 $O(NL)$
