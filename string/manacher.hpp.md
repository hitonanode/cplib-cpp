---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: string/test/manacher.test.cpp
    title: string/test/manacher.test.cpp
  - icon: ':x:'
    path: string/test/manacher_mp.test.cpp
    title: string/test/manacher_mp.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links:
    - https://snuke.hatenablog.com/entry/2014/12/02/235837
  bundledCode: "#line 2 \"string/manacher.hpp\"\n#include <string>\n#include <utility>\n\
    #include <vector>\n\n// CUT begin\n// Manacher's Algorithm: radius of palindromes\n\
    // Input: std::string or std::vector<T> of length N\n// Output: std::vector<int>\
    \ of size N\n// Complexity: O(N)\n// Sample:\n// - `sakanakanandaka` -> [1, 1,\
    \ 2, 1, 4, 1, 4, 1, 2, 2, 1, 1, 1, 2, 1]\n// Reference: https://snuke.hatenablog.com/entry/2014/12/02/235837\n\
    template <typename T> std::vector<int> manacher(const std::vector<T> &S) {\n \
    \   std::vector<int> res(S.size());\n    int i = 0, j = 0;\n    while (i < int(S.size()))\
    \ {\n        while (i - j >= 0 and i + j < int(S.size()) and S[i - j] == S[i +\
    \ j]) j++;\n        res[i] = j;\n        int k = 1;\n        while (i - k >= 0\
    \ and i + k < int(S.size()) and k + res[i - k] < j)\n            res[i + k] =\
    \ res[i - k], k++;\n        i += k, j -= k;\n    }\n    return res;\n}\nstd::vector<int>\
    \ manacher(const std::string &S) {\n    std::vector<char> v(S.size());\n    for\
    \ (int i = 0; i < int(S.size()); i++) v[i] = S[i];\n    return manacher(v);\n\
    }\n\ntemplate <typename T>\nstd::vector<std::pair<int, int>> enumerate_palindromes(const\
    \ std::vector<T> &vec) {\n    std::vector<T> v;\n    const int N = vec.size();\n\
    \    for (int i = 0; i < N - 1; i++) {\n        v.push_back(vec[i]);\n       \
    \ v.push_back(-1);\n    }\n    v.push_back(vec.back());\n    const auto man =\
    \ manacher(v);\n    std::vector<std::pair<int, int>> ret;\n    for (int i = 0;\
    \ i < N * 2 - 1; i++) {\n        if (i & 1) {\n            int w = man[i] / 2;\n\
    \            ret.emplace_back((i + 1) / 2 - w, (i + 1) / 2 + w);\n        } else\
    \ {\n            int w = (man[i] - 1) / 2;\n            ret.emplace_back(i / 2\
    \ - w, i / 2 + w + 1);\n        }\n    }\n    return ret;\n}\n\nstd::vector<std::pair<int,\
    \ int>> enumerate_palindromes(const std::string &S) {\n    std::vector<char> v(S.size());\n\
    \    for (int i = 0; i < int(S.size()); i++) v[i] = S[i];\n    return enumerate_palindromes<char>(v);\n\
    }\n"
  code: "#pragma once\n#include <string>\n#include <utility>\n#include <vector>\n\n\
    // CUT begin\n// Manacher's Algorithm: radius of palindromes\n// Input: std::string\
    \ or std::vector<T> of length N\n// Output: std::vector<int> of size N\n// Complexity:\
    \ O(N)\n// Sample:\n// - `sakanakanandaka` -> [1, 1, 2, 1, 4, 1, 4, 1, 2, 2, 1,\
    \ 1, 1, 2, 1]\n// Reference: https://snuke.hatenablog.com/entry/2014/12/02/235837\n\
    template <typename T> std::vector<int> manacher(const std::vector<T> &S) {\n \
    \   std::vector<int> res(S.size());\n    int i = 0, j = 0;\n    while (i < int(S.size()))\
    \ {\n        while (i - j >= 0 and i + j < int(S.size()) and S[i - j] == S[i +\
    \ j]) j++;\n        res[i] = j;\n        int k = 1;\n        while (i - k >= 0\
    \ and i + k < int(S.size()) and k + res[i - k] < j)\n            res[i + k] =\
    \ res[i - k], k++;\n        i += k, j -= k;\n    }\n    return res;\n}\nstd::vector<int>\
    \ manacher(const std::string &S) {\n    std::vector<char> v(S.size());\n    for\
    \ (int i = 0; i < int(S.size()); i++) v[i] = S[i];\n    return manacher(v);\n\
    }\n\ntemplate <typename T>\nstd::vector<std::pair<int, int>> enumerate_palindromes(const\
    \ std::vector<T> &vec) {\n    std::vector<T> v;\n    const int N = vec.size();\n\
    \    for (int i = 0; i < N - 1; i++) {\n        v.push_back(vec[i]);\n       \
    \ v.push_back(-1);\n    }\n    v.push_back(vec.back());\n    const auto man =\
    \ manacher(v);\n    std::vector<std::pair<int, int>> ret;\n    for (int i = 0;\
    \ i < N * 2 - 1; i++) {\n        if (i & 1) {\n            int w = man[i] / 2;\n\
    \            ret.emplace_back((i + 1) / 2 - w, (i + 1) / 2 + w);\n        } else\
    \ {\n            int w = (man[i] - 1) / 2;\n            ret.emplace_back(i / 2\
    \ - w, i / 2 + w + 1);\n        }\n    }\n    return ret;\n}\n\nstd::vector<std::pair<int,\
    \ int>> enumerate_palindromes(const std::string &S) {\n    std::vector<char> v(S.size());\n\
    \    for (int i = 0; i < int(S.size()); i++) v[i] = S[i];\n    return enumerate_palindromes<char>(v);\n\
    }\n"
  dependsOn: []
  isVerificationFile: false
  path: string/manacher.hpp
  requiredBy: []
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - string/test/manacher.test.cpp
  - string/test/manacher_mp.test.cpp
documentation_of: string/manacher.hpp
layout: document
title: "Longest palindromic substring enumeration (Manacher's algorithm) \uFF08\u56DE\
  \u6587\u9577\u914D\u5217\u69CB\u7BC9\uFF09"
---

文字列・数列などの列に対して Manacher's algorithm を適用．長さ $N$ の入力に対し時間計算量 $O(N)$．

## 使用方法

```cpp
string S = "sakanakanandaka";
vector<int> v = manacher(S); // Manacher's algorithm を適用（奇数長の回文だけならこれでOK）．
vector<pair<int, int>> palindromes = enumerate_palindromes(S);
for (auto [l, r] : palindromes) {
    cout << r - l << ' '; // S[l, r) は最長回文連続部分列（[1, 1) のような空文字列も含む）．
}
```

## 文献

- [1] G. Manacher, "A new linear-time "on-line" algorithm for finding the smallest initial palindrome of a string", Journal of the ACM, 22 (3), 346-351, 1975.
